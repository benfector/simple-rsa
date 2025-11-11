
<div align="center">

![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)
![Debian](https://img.shields.io/badge/Debian-A81D33?style=for-the-badge&logo=debian&logoColor=white)
![RSA](https://img.shields.io/badge/Cryptography-RSA-blue?style=for-the-badge&logo=lock&logoColor=white)

</div>

# 🔐 Simple RSA implementation
<div align="center">


**implementação simples do RSA para fins educativos (não usavel em ambiente real)**

</div>



## 🎯 O Que Foi Implementado:

## Teoria Matemática por Trás do RSA:

#### Teorema de Euler: φ(n) = (p-1)(q-1) onde p e q são primos
#### Aritmética Modular: C = Mᵉ mod n, M = Cᵈ mod n 
#### Teorema dos Números Primos: Geração de números primos grandes
#### Algoritmo Estendido de Euclides: Para encontrar d tal que e·d ≡ 1 mod φ(n)



## Componentes Principais Implementados:
#### 🔢 Geração de Números Primos

```c
// Miller-Rabin Primality Test + Quick Sieve
bool is_prime(long long n)           // Teste de primalidade
bool quick_sieve(long long n)        // Filtro com primos pequenos
long long generate_large_prime()     // Gera primos de 20 bits
```
#### 🔐 Geração de Chaves RSA

```cpp
RSAKeys generate_RSA_keys()          // Gera p, q, n, φ(n), e, d
long long find_valid_e(long long phi_n) // Encontra e coprimo com φ(n)
Bezout extended_euclid(long long a, long long b) // Algoritmo estendido
```

#### 📨 Criptografia/Descriptografia

```cpp
long long encrypt(long long message, long long e, long long n)
long long decrypt(long long encrypted, long long d, long long n)
vector<long long> encrypt_text_in_blocks() // Texto → blocos numéricos
string decrypt_text_in_blocks()           // Blocos → texto
```

#### 💾 Sistema de Arquivos
```cpp
bool save_encrypted_to_file()        // Salva mensagem criptografada
vector<long long> load_encrypted_from_file() // Carrega para descriptografia
bool save_decrypted_to_file()        // Salva texto descriptografado
```

#### 🔄 Conversão Texto-Número
```cpp
long long text_to_number()           // Converte string para número (base 256)
string number_to_text()              // Converte número para string
```

## 🧮 Explicação Matemática Detalhada:
###  Passo a Passo do RSA:

#### Escolha de Primos:

#### p = 1234567891, q = 1987654321 (exemplo)

#### Verificação com Miller-Rabin

#### Cálculo do Módulo:

#### n = p × q = 2453847334678011

#### Função Totiente de Euler:

#### φ(n) = (p-1) × (q-1)

#### Expoente Público (e):

#### e = 65537 (comum) ou menor coprimo com φ(n)

#### Expoente Privado (d):

#### d ≡ e⁻¹ mod φ(n) (via Algoritmo Estendido de Euclides)

## 🔐 Criptografia:

```text
C = Mᵉ mod n
Onde: M = mensagem numérica, C = texto cifrado
```
## Descriptografia:

```text
M = Cᵈ mod n  
```

## 🔒 Proteção de Chaves:
#### Público (pode compartilhar): e, n

#### Privado (NUNCA compartilhar): d, p, q


## 📂 Tamanho:

#### Tamanho usado: 20 bits. Para testes (1024+ em produção)


## 🔧 Biblioteca:

#### GMP (GNU Multiple Precision): Aritmética de grande precisão


## 📊 Exemplo de Uso Real:
### Alice (Gera Chaves):
```bash
./rsa_program
# Digita: "Hello Friend"
# Gera: encrypted/message.enc + keys.txt
```

### Bob (Recebe e Descriptografa):
```bash
./decrypt_program  
# Digita: d = 987654321, n = 2453847334678011
# Resultado: "Hello Friend" em decrypted/decrypted_message.txt
```

## 📄 Licença

### Este projeto está sob a licença MIT. Veja o arquivo LICENSE para detalhes.

<div align="center">

Benfector - befectordd@proton.me


![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)
![GIT](https://img.shields.io/badge/GitHub-100000?style=for-the-badge&logo=github&logoColor=white)
![EMAIL](https://img.shields.io/badge/Proton_mail-D14836?style=for-the-badge&logo=protonmail&logoColor=white)

</div>


## ❓ Como Usar


```bash
# Clone o repositório
$git clone https://github.com/benfector/simple-rsa.git

# Entre na pasta
$cd simple-rsa/
```

### ⚠️ Baixe as dependências necessárias
```bash
#Debian / Ubuntu..
$sudo apt install libgmp-dev g++

#Fedora / RHEL / CentOS..
$sudo dnf install gmp-devel

#Arch / Manjaro..
$sudo pacman -S gmp
```
### 💻 Compilação
```bash
#1 Opção

#decrypt.cpp
$g++ -std=c++17 -Iinclude src/decrypt.cpp -o decrypt_program -lgmp -lgmpxx

&& 

#rsa.cpp
$g++ -std=c++17 -Iinclude src/main.cpp src/rsa.cpp -o rsa_program -lgmp -lgmpxx
```

```bash
#2 opção

#baixe o make

#debian / ubuntu..
$sudo apt install make -y

#Fedora / RHEL / CentOS..
$sudo dnf install make

#Arch / Manjaro..
$sudo pacman -S make

#verifica se baixou
$make --version

#compilar usando make
$make
```

### 🚀 Execute
```bash
# ❤️
./rsa_program
./decrypt_program
```

# 🌟 Gostou?
## Se gostou, deixe uma estrelinha para ajudar 🫡
