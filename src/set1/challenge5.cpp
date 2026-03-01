#include "set1/set1.h"

//////////////////////
// Set 1 Challenge 5: Implement repeating-key XOR
// Here is the opening stanza of an important work of the English language:
// "Burning 'em, if you ain't quick and nimble
// I go crazy when I hear a cymbal"
// Encrypt it, under the key "ICE", using repeating-key XOR.
// In repeating-key XOR, you'll sequentially apply each byte of the key; the first byte of plaintext will be XOR'd against I,
// the next C, the next E, then I again for the 4th vyte, and so on.
// It should come out to:
// 0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272
// a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f
// Encrypt a bunch of stuff using your repeating-key XOR function. Encrypt your mail.
// Encrypt your password file. Your .sig file. Get a feel for it. I promise, we aren't wasting your time with this.
//////////////////////


// Toma un texto plano y una clave, y devuelve el resultado de cifrar el texto plano utilizando XOR con la clave repetida.
std::string repeating_key_xor(const std::string& plaintext, const std::string& key) {
    if (key.empty()) {
        throw std::invalid_argument("Key cannot be empty");
    }

    std::vector<uint8_t> result;

    // Para cada byte del texto plano, se hace XOR con el byte correspondiente de la clave, que se repite cíclicamente.
    for (size_t i = 0; i < plaintext.size(); ++i) {
        uint8_t plaintext_byte = static_cast<uint8_t>(plaintext[i]);
        uint8_t key_byte = static_cast<uint8_t>(key[i % key.size()]); // Repetir la clave cíclicamente, 0, 1, 2, 0, 1, 2, ...
        result.push_back(plaintext_byte ^ key_byte); // XOR del byte del texto plano con el byte de la clave
    }

    // Convertir un vector de bytes a una representación hexadecimal.
    std::string hex_result;
    hex_result = bytes_to_hex(result);
    return hex_result;
}

