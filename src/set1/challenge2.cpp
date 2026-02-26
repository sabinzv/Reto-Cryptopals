#include "set1/set1.h" // Incluye el archivo de encabezado "set1.h" que contiene la declaración de la función hex_to_base64,
                            // lo que permite utilizar esa función en este archivo fuente para implementar su funcionalidad.
#include <stdexcept>
#include <vector>
#include <string>
#include <cstdint>


// Set 1 Challenge 2: Fixed XOR
// Write a function that takes two equal-length buffers and produces their XOR combination.
// If your function works properly, then when you feed it the string:
// 1c0111001f010100061a024b53535009181c
// ... after hex decoding, and when XOR'd against:
// 686974207468652062756c6c277320657965
// ... should produce:
// 746865206b696420646f6e277420706c6179

// bytes to hex
std::string bytes_to_hex(const std::vector<uint8_t>& bytes) {
    std::string hex; // Cadena para almacenar el resultado en formato hexadecimal
    //hex.reserve(bytes.size() * 2); // Reserva espacio en la cadena hexadecimal para el número de bytes que se convertirán

    for (uint8_t byte : bytes) { // Itera sobre cada byte en el vector de bytes
        // Convierte cada byte a su representación hexadecimal de dos caracteres y lo agrega a la cadena hex
        hex += "0123456789abcdef"[byte >> 4]; // El primer carácter hexadecimal se obtiene tomando los 4 bits más altos del byte (byte >> 4)
        hex += "0123456789abcdef"[byte & 0x0F]; // El segundo carácter hexadecimal se obtiene tomando los 4 bits más bajos del byte (byte & 0x0F)
    }
    return hex; // Devuelve la cadena hexadecimal resultante de la conversión
}

std::string fixed_xor_hex(const std::string& hex1, const std::string& hex2) {
    if (hex1.length() != hex2.length()) {
        throw std::invalid_argument("Input strings must have the same length");
    }
    std::vector<uint8_t> bytes1 = hex_to_bytes(hex1); // Convierte la primera cadena hexadecimal a un vector de bytes
    std::vector<uint8_t> bytes2 = hex_to_bytes(hex2); // Convierte la segunda cadena hexadecimal a un vector de bytes

    std::vector<uint8_t> result(bytes1.size()); // Vector para almacenar el resultado del XOR
                                                // result(bytes1.size()) inicializa el vector result con el mismo tamaño que bytes1

    for (size_t i = 0; i < bytes1.size(); ++i) { // Itera sobre los bytes de ambos vectores
        result[i] = bytes1[i] ^ bytes2[i]; // Realiza la operación XOR (^) entre los bytes correspondientes de ambos vectores
    }
    // bytes to hex
    std::string hex_result; // Cadena para almacenar el resultado en formato hexadecimal
    hex_result = bytes_to_hex(result); 
    return hex_result; // Devuelve la cadena hexadecimal resultante del XOR
}