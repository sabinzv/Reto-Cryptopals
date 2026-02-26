#include "set1/set1.h"


// Set 1 Challenge 3: Single-byte XOR cipher
// The hex encoded string:
// 1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736
// ... has been XOR'd against a single character. Find the key and decrypt the message.
// How? Devise some method for "scoring" a piece of English plaintext. Character frequency is a good metric. Evaluate each output and choose the one with the best score.


// Solo para probar la función single_byte_xor_decrypt sin testeo, para sacar el texto descifrado y la clave
// int main() {
//     std::string hex =
//         "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";

//     std::pair<std::string, uint8_t> result = single_byte_xor_decrypt(hex);

//     std::string plaintext = result.first;
//     char key = result.second;
//     std::vector<uint8_t> key_bytes = { static_cast<uint8_t>(key) };

//     std::cout << "Key: '" << key << "' (0x"
//               << bytes_to_hex(key_bytes) << ")\n"; 

//     std::cout << "Decrypted text:\n";
//     std::cout << plaintext << std::endl;

//     return 0;
// }


// Calcula una puntuación para un texto dado basada en la frecuencia de caracteres en inglés
// Las frecuencias extraidas de https://en.wikipedia.org/wiki/Letter_frequency#Relative_frequencies_of_letters_in_the_English_language 
double score_text(const std::string& text) {
    // Expected frequency of English letters (approximate)
    static const std::map<char, double> english_freq = {
        {'e', 0.127}, {'t', 0.091}, {'a', 0.082}, {'o', 0.075},
        {'i', 0.070}, {'n', 0.067}, {'s', 0.063}, {'h', 0.061},
        {'r', 0.060}, {'d', 0.043}, {'l', 0.040}, {'c', 0.028},
        {'u', 0.028}, {'m', 0.024}, {'w', 0.024}, {'f', 0.022},
        {'g', 0.020}, {'y', 0.020}, {'p', 0.019}, {'b', 0.015},
        {'v', 0.010}, {'k', 0.008}, {'j', 0.002}, {'x', 0.002},
        {'q', 0.001}, {'z', 0.001}, {' ', 0.200}
    };

    double score = 0.0; // Variable para almacenar la puntuación total del texto
    
    // Para cada carácter del texto:
    for (unsigned char c : text) { 
        char lower = std::tolower(c); // Convierte el carácter a minúscula para comparar con las claves del mapa de frecuencias
        if (english_freq.count(lower)) { // Verifica si el carácter convertido a minúscula está presente en el mapa de frecuencias 
            score += english_freq.at(lower); // suma su frecuencia a la puntuación total
        }
    }
    return score;
}

// Toma un texto cifrado en forma de vector de bytes y una clave de un solo byte, y devuelve el texto descifrado
std::string xor_decrypt_single_byte(const std::vector<uint8_t>& ciphertext, uint8_t key) {
    std::string plaintext;
    // Itera sobre cada byte en el texto cifrado, aplica la operación XOR con la clave
    for (uint8_t byte : ciphertext) {
        plaintext += static_cast<char>(byte ^ key); // Agrega el resultado de la operación XOR al texto descifrado
    }
    return plaintext;
}

// Resumen muy corto en una frase: 
// Descifra un texto cifrado con XOR de un solo byte probando todas las posibles claves y eligiendo la que produce el texto con la mejor puntuación 
std::pair<std::string, uint8_t> single_byte_xor_decrypt(const std::string& hex) {
    std::vector<uint8_t> ciphertext = hex_to_bytes(hex); // Convierte la cadena hexadecimal de entrada a un vector de bytes para su procesamiento
    
    double best_score = -1.0; // Variable para almacenar la mejor puntuación encontrada durante el proceso de descifrado. Se inicializa con un 
                             // valor negativo para asegurar que cualquier puntuación calculada será mayor que esta inicialización.

    // Variable para almacenar la mejor clave encontrada durante el proceso de descifrado.
    uint8_t best_key = 0;
    std::string best_plaintext;  

    // Itera sobre todas las posibles claves de un solo byte (0 a 255)
    for (int key = 0; key < 256; ++key) {
        std::string plaintext = xor_decrypt_single_byte(ciphertext, static_cast<uint8_t>(key)); // Descifra el texto cifrado utilizando la clave actual
        double score = score_text(plaintext); // Calcula la puntuación del texto descifrado
        
        if (score > best_score) { // Si la puntuación obtenida es mejor que la mejor puntuación encontrada hasta ahora
            best_score = score; // Actualiza la mejor puntuación
            best_key = static_cast<uint8_t>(key); // Actualiza la mejor clave encontrada
            best_plaintext = plaintext; // Actualiza el mejor texto descifrado encontrado hasta ahora
        }
    }

    return std::make_pair(best_plaintext, best_key); 
    // return best_plaintext, best_key;
}


