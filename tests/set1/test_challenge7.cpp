#include <gtest/gtest.h>
#include "set1/set1.h"

// Challenge 7: AES in ECB mode

TEST(Set1Challenge7, DecryptAES128ECB) {
    // Abrir el archivo ch7.txt que contiene el texto cifrado en Base64. Si no se puede abrir, se lanza una excepción.
    std::string filename = "../src/set1/utils/ch7.txt";
    std::ifstream in(filename);
    ASSERT_TRUE(in.good()) << "Failed to open " << filename;
    std::string b64; // La cadena base64 completa extraída del archivo
    std::string line;
    while (std::getline(in, line)) {
        b64 += line; // Concatenar cada línea del archivo para formar la cadena base64 completa
    }
    std::vector<uint8_t> ciphertext = base64_to_bytes(b64);

    std::string key = "YELLOW SUBMARINE";
    std::string plaintext = aes_128_ecb_decrypt(ciphertext, key);

    // Verificar que el texto plano descifrado comienza con la frase conocida.
    EXPECT_TRUE(plaintext.rfind("I'm back and I'm ringin' the bell", 0) == 0); // rfind con posición 0 verifica que el texto plano comience con la cadena dada
}