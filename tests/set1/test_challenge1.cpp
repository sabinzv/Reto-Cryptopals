#include <gtest/gtest.h> // Google Test framework
#include "set1/set1.h" // Incluye el archivo de encabezado "set1.h" que contiene la declaración de la función hex_to_base64,
                            // lo que permite utilizar esa función en este archivo fuente para implementar su funcionalidad.


TEST(Set1Challenge1, HexToBase64) { // Test para la función hex_to_base64, que convierte una cadena hexadecimal a su representación en base64
    // Challenge 1: Convert hex to base64
    std::string hex = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    std::string expected_base64 = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";
    EXPECT_EQ(hex_to_base64(hex), expected_base64);
}