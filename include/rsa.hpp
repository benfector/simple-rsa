/*rsa.hpp*/

#pragma once

#include <string>
#include <vector>
#include <fstream>

// en: Structure to store Extended Euclidean Algorithm results
// pt-br: Estrutura para armazenar resultados do Algoritmo Estendido de Euclides
struct Bezout {
    long long gcd;
    long long x;
    long long y;
};

// en: Structure to store RSA keys
// pt-br: Estrutura para armazenar chaves RSA
struct RSAKeys {
    long long n;
    long long e;
    long long d;
};

// en: Function declarations (what they do)
// pt-br: Declarações de funções (o que elas fazem)

long long generate_large_number();

bool is_prime(long long n);

long long generate_large_prime();

Bezout extended_euclid(long long a, long long b);

RSAKeys generate_RSA_keys();

long long encrypt(long long message, long long e, long long n);

//long long decrypt(long long encrypted, long long d, long long n);

long long text_to_number(const std::string& text);

std::string number_to_text(long long number);

std::vector<long long> encrypt_text_in_blocks(const std::string& text, long long e, long long n, int block_size = 3);

bool save_encrypted_to_file(const std::vector<long long>& encrypted, const std::string& filename);

//std::vector<long long> load_encrypted_from_file(const std::string& filename);

bool save_decrypted_to_file(const std::string& decrypted_text, const std::string& filename);

//std::string decrypt_text_in_blocks(const std::vector<long long>& encrypted, long long d, long long n);

int calculate_max_block(long long n);
