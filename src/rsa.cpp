/*g++ -std=c++17 -Iinclude src/main.cpp src/rsa.cpp -o rsa_program -lgmp -lgmpxx -lstdc++fs*/

/*rsa.cpp*/

#include "rsa.hpp"

#include <iostream>
#include <cmath>
#include <random>
#include <limits>
#include <string>
#include <vector>
#include <gmpxx.h>
#include <chrono>
#include <thread>
#include <fstream>
#include <sstream>

using namespace std;

// en: Generate a large random number using GMP library for better randomness
// pt-br: Gera um número aleatório grande usando a biblioteca GMP para melhor aleatoriedade
long long generate_large_number() {
    static gmp_randclass generator(gmp_randinit_default);
    static bool initialized = false;
    
    if (!initialized) {
        generator.seed(time(nullptr));  
        initialized = true;
    }
    
    // en: Generate 20-bit random number (for faster testing)
    // pt-br: Gera número aleatório de 20 bits (para testes mais rápidos)
    mpz_class large_number = generator.get_z_bits(20);  
    long long number = large_number.get_si();
    
    // en: Ensure it's odd by setting the least significant bit to 1
    // pt-br: Garante que seja ímpar configurando o bit menos significativo para 1
    number = (number | 1);   
    
    return number;
}

// en: Modular exponentiation: (base^exp) % mod
// pt-br: Exponenciação modular: (base^exp) % mod
long long pow_mod(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;

    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        } 
        exp = exp / 2;
        base = (base * base) % mod;
    }
    return result;
}

// en: Miller-Rabin primality test for a specific base 'a'
// pt-br: Teste de primalidade Miller-Rabin para uma base específica 'a'
bool test_with_a(long long n, long long a, long long d, long long k) {
    long long x = pow_mod(a, d, n);

    if (x == 1 || x == n - 1) {
        return true;
    }

    for (int i = 0; i < k - 1; i++) {
        x = pow_mod(x, 2, n);
        if (x == n - 1) {
            return true;
        }
    }
    return false;
}

// en: Quick check using small primes to filter out composites
// pt-br: Verificação rápida usando primos pequenos para filtrar números compostos
bool quick_sieve(long long n) {
    int small_primes[] = {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 
        67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 
        139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 
        223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 
        293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 
        383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 
        463, 467, 479, 487, 491, 499
    };

    for (int p : small_primes) {
        if (n == p) return true;
        if (n % p == 0) return false;
    }
    return true;
}

// en: Main primality test combining quick sieve and Miller-Rabin
// pt-br: Teste de primalidade principal combinando peneira rápida e Miller-Rabin
bool is_prime(long long n) {
    if (n <= 1) return false;    
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    
    if (!quick_sieve(n)) {
        return false;
    }
    
    // en: Factor n-1 as 2^k * d
    // pt-br: Fatora n-1 como 2^k * d
    long long temp = n - 1;
    long long k = 0;

    while (temp % 2 == 0) {
        temp /= 2;
        k++;
    }

    long long d = temp;
    
    // en: Perform 5 rounds of Miller-Rabin test
    // pt-br: Executa 5 rodadas do teste Miller-Rabin
    for (int test = 0; test < 5; test++) {
        long long a = 2 + test;
        if (a >= n - 1) break;
        if (!test_with_a(n, a, d, k)) {
            return false;
        }
    }
    return true;
}

// en: Generate a large prime number by testing random candidates
// pt-br: Gera um número primo grande testando candidatos aleatórios
long long generate_large_prime() { 
    int attempts = 0;
    while (true) {
        attempts++;

        long long candidate = generate_large_number();

        if (candidate % 2 == 0) continue;

        if (is_prime(candidate)) {
            //cout << "LARGE PRIME FOUND: " << candidate << " (attempt " << attempts << ")" << endl;
            return candidate;
        }
    }
}

// en: Extended Euclidean Algorithm to find gcd and coefficients
// pt-br: Algoritmo Estendido de Euclides para encontrar mdc e coeficientes
Bezout extended_euclid(long long a, long long b) {
    if (b == 0) {
        return {a, 1, 0};
    }

    long long x1 = 0, x2 = 1;
    long long y1 = 1, y2 = 0;

    while (b != 0) {
        long long quotient = a / b;
        long long remainder = a % b;

        long long x = x2 - quotient * x1;
        long long y = y2 - quotient * y1;

        x2 = x1;
        y2 = y1;
        x1 = x;
        y1 = y;

        a = b;
        b = remainder;
    }

    return {a, x2, y2};
}

// en: Find a valid public exponent e that is coprime with phi_n
// pt-br: Encontra um expoente público e válido que seja coprimo com phi_n
long long find_valid_e(long long phi_n) {
    // en: Common RSA public exponents
    // pt-br: Expoentes públicos comuns do RSA
    long long candidates[] = {3, 5, 17, 257, 65537};
    
    for (long long e : candidates) {
        if (e < phi_n && extended_euclid(e, phi_n).gcd == 1) {
            return e;
        }
    }
    
    // en: If no standard values work, find one manually
    // pt-br: Se nenhum valor padrão funcionar, encontra um manualmente
    for (long long e = 3; e < phi_n; e += 2) {
        if (extended_euclid(e, phi_n).gcd == 1) {
            return e;
        }
    }
    
    return -1;  // None found / Nenhum encontrado
}


// en: Generate RSA public and private keys
// pt-br: Gera chaves públicas e privadas RSA
RSAKeys generate_RSA_keys() {
    RSAKeys keys;

    // en: Generate two distinct large primes
    // pt-br: Gera dois primos grandes distintos
    long long p = generate_large_prime();
    long long q;
    do {
        q = generate_large_prime();
    } while (q == p);

    // en: Calculate modulus n = p × q
    // pt-br: Calcula o módulo n = p × q
    keys.n = p * q;
    //cout << "DEBUG: n = " << keys.n << endl;

    // en: Calculate Euler's totient function φ(n) = (p-1) × (q-1)
    // pt-br: Calcula a função totiente de Euler φ(n) = (p-1) × (q-1)
    long long phi_n = (p - 1) * (q - 1);
    //cout << "DEBUG: φ(n) = " << phi_n << endl;

    // en: Find valid public exponent e
    // pt-br: Encontra expoente público e válido
    keys.e = find_valid_e(phi_n);
    if (keys.e == -1) {
        cout << "ERROR: No valid e found!" << endl;
        keys.e = 3; // fallback / fallback
    }

    // en: Calculate private exponent d using Extended Euclidean Algorithm
    // pt-br: Calcula expoente privado d usando Algoritmo Estendido de Euclides
    Bezout solution = extended_euclid(keys.e, phi_n);
    keys.d = solution.x;
    if (keys.d < 0) {
        keys.d += phi_n;
    }

    return keys;
}

// en: Encrypt a message using public key (e, n)
// pt-br: Criptografa uma mensagem usando chave pública (e, n)
long long encrypt(long long message, long long e, long long n) {
    mpz_class base = (long)message;
    mpz_class exp = (long)e;
    mpz_class mod = (long)n;
    mpz_class result;
    
    mpz_powm(result.get_mpz_t(), base.get_mpz_t(), exp.get_mpz_t(), mod.get_mpz_t());
    return result.get_si();
}

// en: Convert text string to numerical representation
// pt-br: Converte string de texto para representação numérica
long long text_to_number(const string& text) {
    long long number = 0;
    for (char c : text) {
        number = number * 256 + static_cast<unsigned char>(c);
    }
    return number;
}

// en: Encrypt text by breaking it into blocks
// pt-br: Criptografa texto dividindo-o em blocos
vector<long long> encrypt_text_in_blocks(const string& text, long long e, long long n, int block_size) {
    vector<long long> result;

    for (size_t i = 0; i < text.length(); i += block_size) {
        string block = text.substr(i, block_size);
        long long block_number = text_to_number(block);

        if (block_number >= n) {
            cout << "Block too large! Reduce block_size." << endl;
            break;
        }

        long long encrypted_block = encrypt(block_number, e, n);
        result.push_back(encrypted_block);
    }

    return result;
}

// en: Save encrypted message to file
// pt-br: Salva mensagem criptografada em um arquivo
bool save_encrypted_to_file(const vector<long long>& encrypted, const string& filename) {

    ofstream file(filename);

    if(!file.is_open()) {
        cout << "Error: Could not open file " << filename << " for writing." << endl;
        return false;
    } 

    // en: Save each encrypted block on a separate line
    // pt-br: Salva cada bloco criptografado em uma linha separada
    for (size_t i = 0; i < encrypted.size(); i++) {
        file << encrypted[i];
        if(i < encrypted.size() - 1) {
            file << endl;
        }
    }

    file.close();

    cout << "\033[1;33mencrypted message saved to: \"" << filename << "\"\033[0m" << endl;
    return true;
}


// en: Calculate maximum safe block size based on modulus n
// pt-br: Calcula tamanho máximo seguro do bloco baseado no módulo n
int calculate_max_block(long long n) {
    int max_chars = 0;
    long long temp = 1;

    while (temp * 256 <= n) {
        temp *= 256;
        max_chars++;
    }

    cout << "\n\033[1;34mMaximum characters per block: \033[0m" << max_chars << endl;
    return max_chars;
}

