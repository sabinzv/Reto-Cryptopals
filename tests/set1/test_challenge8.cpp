#include <gtest/gtest.h>
#include "set1/set1.h"

// Challenge 8: Detect AES in ECB mode

TEST(Set1Challenge8, DetectAESInECBMode) {
    // Abrir el archivo ch8.txt que contiene los textos cifrados en hexadecimal. Si no se puede abrir, se lanza una excepción.
    std::ifstream file("../src/set1/utils/ch8.txt");
    ASSERT_TRUE(file.good()) << "Failed to open ch8.txt";

    // Leer cada línea del archivo, que representa un texto cifrado en hexadecimal, y almacenarla en un vector de cadenas.
    std::vector<std::string> hex_ciphertexts;
    std::string line;
    while (std::getline(file, line)) {
        hex_ciphertexts.push_back(line);
    }

    // Llamar a la función detect_aes_ecb para analizar los textos cifrados y detectar cuál de ellos ha sido cifrado utilizando AES en modo ECB.
    std::string ecb_hex = detect_aes_ecb(hex_ciphertexts);
    EXPECT_EQ(ecb_hex, "d880619740a8a19b7840a8a31c810a3d08649af70dc06f4fd5d2d69c744cd283e2dd052f6b641dbf9d11b0348542bb5708649af70dc06f4fd5d2d69c744cd2839475c9dfdbc1d46597949d9c7e82bf5a08649af70dc06f4fd5d2d69c744cd28397a93eab8d6aecd566489154789a6b0308649af70dc06f4fd5d2d69c744cd283d403180c98c8f6db1f2a3f9c4040deb0ab51b29933f2c123c58386b06fba186a");
}