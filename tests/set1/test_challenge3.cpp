#include <gtest/gtest.h>
#include "set1/set1.h"

TEST(Set1Challenge3, SingleByteXORDecrypt) {
    // Challenge 3: Single-byte XOR cipher
    // Hex string that was XOR'd with a single byte
    std::string ciphertext = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
    
    // Decrypt the message
    // std::string plaintext = single_byte_xor_decrypt(ciphertext);
    std::pair<std::string, uint8_t> result = single_byte_xor_decrypt(ciphertext); //


    // The expected plaintext is "Cooking MC's like a pound of bacon"
    // Expected tanto el plaintext como la clave, ya que el desafío pide encontrar ambos.
    std::string expected_text = "Cooking MC's like a pound of bacon";
    char expected_key = 'X'; // La clave esperada es 'X' (0x58 en hexadecimal o 88 en decimal)
 
    EXPECT_EQ(result.first, expected_text);
    EXPECT_EQ(result.second, static_cast<uint8_t>(expected_key));
}
