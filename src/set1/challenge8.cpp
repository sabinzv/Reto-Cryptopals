#include "set1/set1.h"

//////////////////////////////////////////////////////
// Challenge 8: Detect AES in ECB mode
// https://cryptopals.com/sets/1/challenges/8
// In this file are a bunch of hex-encoded ciphertexts.
// One of them has been encrypted with ECB.
// Detect it.
// Remember that the problem with ECB is that it is stateless and deterministic;
// the same 16 byte plaintext block will always produce the same 16 byte ciphertext.
//////////////////////////////////////////////////////

// Para detectar si un texto cifrado ha sido cifrado utilizando AES en modo ECB, se puede buscar bloques de texto cifrado repetidos.
// Si se encuentran bloques de texto cifrado que se repiten, es una fuerte indicación de que el texto ha sido cifrado utilizando AES en modo ECB, ya que este
// modo produce el mismo bloque de texto cifrado para el mismo bloque de texto plano, lo que puede resultar en patrones repetitivos en el texto cifrado.

std::string detect_aes_ecb(const std::vector<std::string>& hex_ciphertexts) {
    for (const auto& hex : hex_ciphertexts) {
        std::vector<uint8_t> ciphertext = hex_to_bytes(hex); // Convertir el texto cifrado de hexadecimal a bytes para poder analizarlo en bloques de 16 bytes (128 bits).
        std::set<std::vector<uint8_t>> seen_blocks; // Utilizar un conjunto para almacenar los bloques de texto cifrado que ya se han visto. Esto permite detectar fácilmente si un bloque se repite.
        bool is_ecb = false; // Variable para indicar si se ha detectado que el texto cifrado es en modo ECB.

        // Dividir el texto cifrado en bloques de 16 bytes (128 bits) y verificar si hay bloques repetidos.
        for (size_t i = 0; i < ciphertext.size(); i += 16) {
            std::vector<uint8_t> block(ciphertext.begin() + i, ciphertext.begin() + i + 16);
            if (seen_blocks.count(block)) { // count devuelve el número de elementos en el conjunto que son iguales al bloque actual.
                                            // Si es mayor que 0, significa que el bloque ya se ha visto antes, lo que indica un bloque repetido.
                is_ecb = true; // Si se encuentra un bloque repetido, marcar como ECB.
                break;
            }
            seen_blocks.insert(block); // Agregar el bloque al conjunto de bloques vistos.
        }

        if (is_ecb) {
            return hex; // Devolver el texto cifrado en hexadecimal que ha sido detectado como cifrado en modo ECB.
        }
    }
    return ""; // Si no se detecta ningún texto cifrado en modo ECB, devolver una cadena vacía.
}

// Main para ejecutar el challenge8.cpp sin testeo para detectar el texto cifrado en modo ECB
// int main() {
//     std::ifstream file("../src/set1/utils/ch8.txt");
//     if (!file.is_open()) {
//         throw std::runtime_error("Could not open ch8.txt");
//     }

//     std::vector<std::string> hex_ciphertexts;
//     std::string line;
//     while (std::getline(file, line)) {
//         hex_ciphertexts.push_back(line); // Leer cada línea del archivo y almacenarla en un vector de cadenas.
//     }

//     std::string ecb_hex = detect_aes_ecb(hex_ciphertexts);
//     if (!ecb_hex.empty()) {
//         std::cout << "Detected AES-ECB ciphertext: " << ecb_hex << std::endl; // Imprimir el texto cifrado en hexadecimal que ha sido detectado como cifrado en modo ECB.
//     } else {
//         std::cout << "No AES-ECB ciphertext detected." << std::endl; // Si no se detecta ningún texto cifrado en modo ECB, imprimir un mensaje indicando que no se ha detectado.
//     }

//     return 0;
// }