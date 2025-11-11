# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Iinclude
LIBS = -lgmp -lgmpxx

# Targets
TARGETS = rsa_program decrypt_program

# Default target
all: $(TARGETS)

# RSA Program (encryption + key generation)
rsa_program: src/main.cpp src/rsa.cpp
	$(CXX) $(CXXFLAGS) src/main.cpp src/rsa.cpp -o rsa_program $(LIBS)

# Decryption Program
decrypt_program: src/decrypt.cpp src/rsa.cpp
	$(CXX) $(CXXFLAGS) src/decrypt.cpp src/rsa.cpp -o decrypt_program $(LIBS)

# Individual compilation (if you want to compile separately)
rsa_only: src/main.cpp src/rsa.cpp
	$(CXX) $(CXXFLAGS) src/main.cpp src/rsa.cpp -o rsa_program $(LIBS)

decrypt_only: src/decrypt.cpp src/rsa.cpp
	$(CXX) $(CXXFLAGS) src/decrypt.cpp src/rsa.cpp -o decrypt_program $(LIBS)

# Create necessary directories
directories:
	mkdir -p encrypted decrypted keys

# Run RSA program
run_rsa: rsa_program directories
	./rsa_program

# Run decrypt program  
run_decrypt: decrypt_program directories
	./decrypt_program

# Clean build files
clean:
	rm -f $(TARGETS) *.o

# Install dependencies (Debian/Ubuntu)
install_deps:
	sudo apt update && sudo apt install -y libgmp-dev g++ make

# Show help
help:
	@echo "Available targets:"
	@echo "  all          - Build both programs"
	@echo "  rsa_program  - Build only RSA program"
	@echo "  decrypt_program - Build only decrypt program"
	@echo "  run_rsa      - Build and run RSA program"
	@echo "  run_decrypt  - Build and run decrypt program"
	@echo "  directories  - Create necessary folders"
	@echo "  clean        - Remove compiled programs"
	@echo "  install_deps - Install dependencies (Debian/Ubuntu)"
	@echo "  help         - Show this help message"

.PHONY: all clean help directories install_deps run_rsa run_decrypt