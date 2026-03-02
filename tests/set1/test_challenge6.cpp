#include <gtest/gtest.h>
#include "set1/set1.h"

// Challenge 6: Break repeating-key XOR file

TEST(Set1Challenge6, HammingDistance) {
    std::string a = "this is a test";
    std::string b = "wokka wokka!!!";
    std::vector<uint8_t> va(a.begin(), a.end()); // Convertir la cadena a un vector de bytes (uint8_t)
    std::vector<uint8_t> vb(b.begin(), b.end());
    EXPECT_EQ(hamming_distance(va, vb), 37);
}

TEST(Set1Challenge6, BreakRepeatingKeyXOR) {
    // read entire base64 file
    std::string filename = "../src/set1/utils/ch6.txt";
    std::ifstream in(filename);
    ASSERT_TRUE(in.good()) << "Failed to open " << filename;
    std::string b64; // La cadena base64 completa extraída del archivo
    std::string line;
    while (std::getline(in, line)) {
        b64 += line; // Concatenar cada línea del archivo para formar la cadena base64 completa
    }
    std::vector<uint8_t> ciphertext = base64_to_bytes(b64);

    std::pair<std::string, std::string> result = break_repeating_key_xor(ciphertext);
    std::string key = result.first;
    std::string plaintext = result.second;

    //Imprimir la clave y el texto plano recuperados para verificar visualmente que son correctos.
    std::cout << "Recovered key: " << key << std::endl;
    std::cout << "Recovered plaintext (first 100 chars): " << plaintext.substr(0, 100) << "..." << std::endl;

    // Verificar que la clave recuperada es la esperada y que el texto plano comienza con la frase conocida.
    EXPECT_EQ(key, "Terminator X: Bring the noise");
    EXPECT_TRUE(plaintext.rfind("I'm back and I'm ringin' the bell", 0) == 0); // rfind con posición 0 verifica que el texto plano comience con la cadena dada

    
}
