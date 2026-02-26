#include <gtest/gtest.h>
#include "set1/set1.h" 

TEST(Set1Challenge2, FixedXOR) { // Test para la función fixed_xor_hex, que realiza una operación XOR fija entre dos cadenas hexadecimales de igual longitud
    // Challenge 2: Fixed XOR
    std::string hex1 = "1c0111001f010100061a024b53535009181c";
    std::string hex2 = "686974207468652062756c6c277320657965";
    std::string expected_xor = "746865206b696420646f6e277420706c6179";
    EXPECT_EQ(fixed_xor_hex(hex1, hex2), expected_xor);
}