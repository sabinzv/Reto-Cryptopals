#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <cctype>
#include <map>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <array>

//////////////////////////////////
// Challenge 1
// hex to base64
std::string hex_to_base64(const std::string& hex);
// hex to bytes
std::vector<uint8_t> hex_to_bytes(const std::string& hex);
// bytes to base64
std::string bytes_to_base64(const std::vector<uint8_t>& bytes);
//////////////////////////////////

//////////////////////////////////
//challenge 2
// fixed XOR
std::string fixed_xor_hex(const std::string& hex1, const std::string& hex2);
// bytes to hex
std::string bytes_to_hex(const std::vector<uint8_t>& bytes);
//////////////////////////////////

//////////////////////////////////
// Challenge 3
// Single-byte XOR decrypt
// Devuelve el texto plano descifrado y la clave de un cifrado XOR de un solo byte dado en hexadecimal.
std::pair<std::string, uint8_t> single_byte_xor_decrypt(const std::string& hex); 
// Devuelve una puntuación que indica qué tan "parecido a texto" es el texto dado, basada en la frecuencia de caracteres comunes en inglés.
double score_text(const std::string& text); 
// Devuelve el resultado de descifrar un texto cifrado con XOR de un solo byte utilizando la clave dada.
std::string xor_decrypt_single_byte(const std::vector<uint8_t>& ciphertext, uint8_t key); 
//////////////////////////////////

//////////////////////////////////
// Challenge 4
// Detect single-character XOR in a file
std::string detect_single_char_xor(const std::string& filename);
//////////////////////////////////

//////////////////////////////////
// Challenge 5
// Repeating-key XOR encryption
std::string repeating_key_xor(const std::string& plaintext, const std::string& key);
//////////////////////////////////

//////////////////////////////////
// Challenge 6
// Hamming distance (number of differing bits) between two byte sequences
int hamming_distance(const std::vector<uint8_t>& a, const std::vector<uint8_t>& b);
// Base64 decoding utility
std::vector<uint8_t> base64_to_bytes(const std::string& base64);
// Break repeating-key XOR cipher (returns <key, plaintext>)
std::pair<std::string, std::string> break_repeating_key_xor(const std::vector<uint8_t>& ciphertext);
//////////////////////////////////
