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

// Challenge 1
// hex to base64
std::string hex_to_base64(const std::string& hex);
// hex to bytes
std::vector<uint8_t> hex_to_bytes(const std::string& hex);
// bytes to base64
std::string bytes_to_base64(const std::vector<uint8_t>& bytes);

//challenge 2
// fixed XOR
std::string fixed_xor_hex(const std::string& hex1, const std::string& hex2);
// bytes to hex
std::string bytes_to_hex(const std::vector<uint8_t>& bytes);

// Challenge 3
// Single-byte XOR decrypt
std::pair<std::string, uint8_t> single_byte_xor_decrypt(const std::string& hex);
double score_text(const std::string& text);
std::string xor_decrypt_single_byte(const std::vector<uint8_t>& ciphertext, uint8_t key);

// Find the single-byte XOR key
// uint8_t single_byte_xor_find_key(const std::string& hex);

// Challenge 4
// Detect single-character XOR in a file
std::string detect_single_char_xor(const std::string& filename);

