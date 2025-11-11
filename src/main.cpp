/* main.cpp */

/*
 *
 *   MIT License
 *
 *   Copyright (c) 2025 benfector
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

/*g++ -std=c++17 -Iinclude src/main.cpp src/rsa.cpp -o rsa_program -lgmp -lgmpxx*/

#include "rsa.hpp"
#include <iostream>
#include <chrono>
#include <thread>
#include <filesystem>
#include <fstream>

using namespace std;

bool save_keys_file(const string& filename, const long long& key_n, const long long& key_d, const long long& key_e) {
    ofstream file(filename);

    if(!file.is_open()) {
        cout << "Error: Could not open file " << filename << " for writing." << endl;
        return false;
    }

    file << "Public Key (e, n): (" << key_e << ", " << key_n << ") \n" << "Private key: (d, n): (" << key_d << ", " << key_n << ") /*In a production environment, the 'd' key must NOT be exposed.*/\n";
    file.close();
    cout << "\033[1;33mKeys saved successfully in \"" << filename << "\"\033[0m" << endl;
    return true;
}


int main() {
    cout << "\n\033[1;32m--Simple RSA with File Storage--\033[0m\n" << endl;

    // en: Create directories if they don't exist
    // pt-br: Cria diretórios se não existirem
    filesystem::create_directories("encrypted");
    filesystem::create_directories("decrypted");

    // en: Generate RSA keys
    // pt-br: Gera chaves RSA
    RSAKeys keys = generate_RSA_keys();

    /*
    cout << "\033[1;34mPublic key (e, n): (" << keys.e << ", " << keys.n << ")\033[0m" << endl;
    cout << "\033[1;34mPrivate key (d, n): (" << keys.d << ", " << keys.n << ")\033[0m" << endl;
    cout << "\n";
    */

    long long key_n = keys.n;
    long long key_d = keys.d;
    long long key_e = keys.e;

    string filename = "encrypted/keys.txt";
    save_keys_file(filename, key_n, key_d, key_e);
        

    string message;
    cout << "\n\033[1;32mEnter the text to encrypt: \033[0m";
    getline(cin, message);

    cout << "\033[1;32mOriginal message: \033[0m" << message << endl;

    // en: Calculate safe block size
    // pt-br: Calcula tamanho seguro do bloco
    int max_block = calculate_max_block(keys.n);
    int block_size = min(3, max_block);

    // en: Encrypt the message
    // pt-br: Criptografa a mensagem
    vector<long long> encrypted_text = encrypt_text_in_blocks(message, keys.e, keys.n, block_size);

    cout << "Encrypted text (" << encrypted_text.size() << " blocks): ";
    for (size_t i = 0; i < encrypted_text.size(); i++) {
        cout << encrypted_text[i];
        if (i < encrypted_text.size() - 1) cout << " | ";
    }
    cout << "\n";
    cout << endl;

    // en: Save encrypted message to file
    // pt-br: Salva mensagem criptografada em arquivo
    string encrypted_filename = "encrypted/message.enc";
    save_encrypted_to_file(encrypted_text, encrypted_filename);

    return 0;
}
