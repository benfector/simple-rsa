
<div align="center">

![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)
![Debian](https://img.shields.io/badge/Debian-A81D33?style=for-the-badge&logo=debian&logoColor=white)
![RSA](https://img.shields.io/badge/Cryptography-RSA-blue?style=for-the-badge&logo=lock&logoColor=white)

</div>

# 🔐 Simple RSA Implementation
<div align="center">

**Simple RSA implementation for educational purposes (not suitable for real-world use)**

</div>

## 🤔 Why build from scratch? 
- Learning: Understand RSA internals
- Not production: Use OpenSSL for real apps

## 🎯 What Was Implemented:

## Mathematical Theory Behind RSA:

#### Euler's Theorem: φ(n) = (p-1)(q-1) where p and q are primes
#### Modular Arithmetic: C = Mᵉ mod n, M = Cᵈ mod n 
#### Prime Number Theorem: Generation of large prime numbers
#### Extended Euclidean Algorithm: To find d such that e·d ≡ 1 mod φ(n)

## Main Components Implemented:
#### 🔢 Prime Number Generation

```c
// Miller-Rabin Primality Test + Quick Sieve
bool is_prime(long long n)           // Primality test
bool quick_sieve(long long n)        // Small primes filter
long long generate_large_prime()     // Generates 20-bit primes
```
#### 🔐 RSA Key Generation
```cpp
RSAKeys generate_RSA_keys()          // Generates p, q, n, φ(n), e, d
long long find_valid_e(long long phi_n) // Finds e coprime with φ(n)
Bezout extended_euclid(long long a, long long b) // Extended algorithm
```
#### 📨 Encryption/Decryption

```cpp
long long encrypt(long long message, long long e, long long n)
long long decrypt(long long encrypted, long long d, long long n)
vector<long long> encrypt_text_in_blocks() // Text → numeric blocks
string decrypt_text_in_blocks()           // Blocks → text
```
#### 💾 File System
```cpp
bool save_encrypted_to_file()        // Saves encrypted message
vector<long long> load_encrypted_from_file() // Loads for decryption
bool save_decrypted_to_file()        // Saves decrypted text
```
#### 🔄 Text-Number Conversion
```cpp
long long text_to_number()           // Converts string to number (base 256)
string number_to_text()              // Converts number to string
```
## 🧮 Detailed Mathematical Explanation:
### Step by Step RSA:
#### Prime Selection:
#### p = 1234567891, q = 1987654321 (example)
#### Verification with Miller-Rabin
#### Modulus Calculation:
#### n = p × q = 2453847334678011
#### Euler's Totient Function:
#### φ(n) = (p-1) × (q-1)
#### Public Exponent (e):
#### e = 65537 (common) or smaller coprime with φ(n)
#### Private Exponent (d):
#### d ≡ e⁻¹ mod φ(n) (via Extended Euclidean Algorithm)

## 🔐 Encryption:
```text
C = Mᵉ mod n
Where: M = numeric message, C = ciphertext
```
## Decryption:
```text
M = Cᵈ mod n  
```

## 🔒 Key Protection:
#### Public (can share): e, n
#### Private (NEVER share): d, p, q

## 📂 Size:
#### Size used: 20 bits. For testing (1024+ in production)

## 🔧 Library:
#### GMP (GNU Multiple Precision): Large precision arithmetic

## 📊 Real Usage Example:
### Alice (Generates Keys):
```bash
./rsa_program
# Input: "Hello Friend"
# Generates: encrypted/message.enc + keys.txt
```
### Bob (Receives and Decrypts):
```bash
./decrypt_program  
# Input: d = 987654321, n = 2453847334678011
# Result: "Hello Friend" in decrypted/decrypted_message.txt
```
## 📄 License
### This project is under MIT License. See LICENSE file for details.

<div align="center">

Benfector - befectordd@proton.me


![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)
![GIT](https://img.shields.io/badge/GitHub-100000?style=for-the-badge&logo=github&logoColor=white)
![EMAIL](https://img.shields.io/badge/Proton_mail-D14836?style=for-the-badge&logo=protonmail&logoColor=white)

</div>

## ❓ How to Use
```bash
# Clone repository
$git clone https://github.com/benfector/simple-rsa.git

# Enter directory
$cd simple-rsa/
```
## ⚠️ Install Required Dependencies
```bash
# Debian / Ubuntu..
$sudo apt install libgmp-dev g++

# Fedora / RHEL / CentOS..
$sudo dnf install gmp-devel

# Arch / Manjaro..
$sudo pacman -S gmp
```
## 💻 Compilation
```bash
# Option 1

# decrypt.cpp
$g++ -std=c++17 -Iinclude src/decrypt.cpp -o decrypt_program -lgmp -lgmpxx

&& 

# rsa.cpp
$g++ -std=c++17 -Iinclude src/main.cpp src/rsa.cpp -o rsa_program -lgmp -lgmpxx
```
```bash
# Option 2

# Install make

# Debian / Ubuntu..
$sudo apt install make -y

# Fedora / RHEL / CentOS..
$sudo dnf install make

# Arch / Manjaro..
$sudo pacman -S make

# Verify installation
$make --version

# Compile using make
$make
```
## 🚀 Execute
``` bash
# ❤️
$./rsa_program
$./decrypt_program
```
## 🌟 Did You Like It?
### If you liked it, leave a star to help 🫡

