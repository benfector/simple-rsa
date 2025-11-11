/*decrypt.cpp*/
/*g++ -std=c++17 -Iinclude src/decrypt.cpp -o decrypt_program -lgmp -lgmpxx*/

#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <thread>
#include <gmpxx.h>

using namespace std;

// en: Load encrypted message from file
// pt-br: Carrega mensagem criptografada do arquivo
vector<long long> load_encrypted_from_file(const string& filename) {
    vector<long long> encrypted;
    ifstream file(filename);
    
    if (!file.is_open()) {
        cout << "Error: Could not open file " << filename << " for reading." << endl;
        return encrypted;
    }
    
    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            try {
                long long block = stoll(line);
                encrypted.push_back(block);
            } catch (const exception& e) {
                cout << "Error reading encrypted block: " << e.what() << endl;
            }
        }
    }
    
    file.close();
    cout << "\n\033[1;34mLoaded " << encrypted.size() << " encrypted blocks from: " << filename << "\033[0m" << endl;
    return encrypted;
}

// en: Save decrypted text to file
// pt-br: Salva texto descriptografado em arquivo
bool save_decrypted_to_file(const string& decrypted_text, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file " << filename << " for writing." << endl;
        return false;
    }
    
    file << decrypted_text;
    file.close();
    cout << "\033[1;33mDecrypted message saved to: " << filename << "\033[0m" << endl;
    return true;
}


// en: Decrypt a message using private key (d, n)
// pt-br: Descriptografa uma mensagem usando chave privada (d, n)
long long decrypt(long long encrypted, long long d, long long n) {
    mpz_class base = (long)encrypted;
    mpz_class exp = (long)d;
    mpz_class mod = (long)n;
    mpz_class result;
    
    mpz_powm(result.get_mpz_t(), base.get_mpz_t(), exp.get_mpz_t(), mod.get_mpz_t());
    return result.get_si();
}

string number_to_text(long long number) {
    string text;
    long long temp = number;

    while (temp > 0) {
        long long remainder = temp % 256;
        text = static_cast<char>(remainder) + text;
        temp /= 256;
    }
    return text;
}

// en: Decrypt encrypted blocks back to text
// pt-br: Descriptografa blocos criptografados de volta para texto
string decrypt_text_in_blocks(const vector<long long>& encrypted, long long d, long long n) {
    string text;

    for (long long encrypted_block : encrypted) {
        long long decrypted_block = decrypt(encrypted_block, d, n);
        string block_text = number_to_text(decrypted_block);
        text += block_text;
    }
    return text;
}

int main() {
    cout << "\n\033[1;32m--RSA decryption--\033[0m" << endl;

    long long d, n;

    cout << "\n\033[1;31mEnsure that they are the correct keys from the latest encryption available in encrypted/keys.txt.\033[0m" << endl;
    cout << "\033[1;32mEnter private key (d): \033[0m";
    cin >> d;
    cout << "\033[1;32mEnter modulus (n): \033[0m";
    cin >> n;

    vector<long long> encrypted = load_encrypted_from_file("encrypted/message.enc");

    if(encrypted.empty()) {
        cout << "No encrypted message found!" << endl;
        return 1;
    }

    // en: Decryption animation
    // pt-br: Animação de descriptografia
    char spinner[4] = {'/', '-', '\\', '|'};
    cout << "\n\033[1;34mDecrypting from file: \033[0m";
    for (int i = 0; i < 4; i++) {
        cout << spinner[i] << flush;
        this_thread::sleep_for(chrono::seconds(1));
        cout << "\b";
    }
    cout << "\r";

    string decrypted = decrypt_text_in_blocks(encrypted, d, n);

    //cout << "\033[0m\033[1;33mDecrypted message: " << decrypted << "\033[0m" << endl;

    save_decrypted_to_file(decrypted, "decrypted/decrypted_message.txt");

    cout << "\n\033[1;32mDecryption complete!\33[0m" << endl;
    return 0;
}
