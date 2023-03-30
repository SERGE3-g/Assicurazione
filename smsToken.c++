#include <iostream>
#include <iomanip>
#include <cstring>
#include <random>
#include <scrypt.h>

std::string generateToken() {
    // Genera una stringa casuale di 4 byte

    std::random_device rd; // Genera un numero casuale
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint32_t> dis(0, 0xFFFFFFFF);// Genera un numero casuale da 0 a 0xFFFFFFFF
    uint32_t tokenInt = dis(gen);

    // Converti la stringa casuale in esadecimale
    std::ostringstream oss;
    oss << std::setw(8) << std::setfill('0') << std::hex << tokenInt;
    std::string tokenHex = oss.str();

    // Converte la stringa esadecimale in binario
    std::vector<uint8_t> tokenBytes(tokenHex.length() / 2);// 4 byte = 8 caratteri esadecimali
    for (std::size_t i = 0; i < tokenHex.length(); i += 2)
     {
        std::string byteString = tokenHex.substr(i, 2);
        uint8_t byte = (uint8_t) strtol(byteString.c_str(), NULL, 16);
        tokenBytes[i / 2] = byte;
    }

    // Calcola l'hash della stringa binaria
    std::vector<uint8_t> hash(32);// 32 byte
    scrypt(&tokenBytes[0], tokenBytes.size(), NULL, 0, 16384, 8, 1, &hash[0], hash.size());// 16384 = 2^14

    // Converte l'hash in una stringa esadecimale
    std::ostringstream oss2;
    for (std::size_t i = 0; i < hash.size(); i++) {
        oss2 << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];// Converte l'hash in una stringa esadecimale
    }
    std::string tokenSMS = oss2.str();

    return tokenSMS;
}

int main() {
    std::string token = generateToken();// Genera un token casuale
    std::cout << token << std::endl;// Stampa il token

    return 0;
}
