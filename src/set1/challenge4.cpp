#include "set1/set1.h"

// Set 1 Challenge 4: Detect single-character XOR
// One of the 60-character strings in this file has been encrypted by single-character XOR.
// Find it.
// (Your code from #3 should help.)


// Solo para ejecutar el challenge4.cpp sin testeo para sacar el texto descifrado y la clave
// int main() {
//     std::string filename = "../src/set1/utils/ch4.txt";
//     std::string plaintext = detect_single_char_xor(filename);
//     //std::cout << "Decrypted text:\n" << plaintext << std::endl;
//     return 0;
// }


// Lee un archivo con varias líneas de texto cifrado con XOR de un solo byte, descifra cada línea y devuelve el texto descifrado con
// la mejor puntuación indicando que es el más probable
std::string detect_single_char_xor(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    std::string line;
    double best_overall_score = -1.0;
    std::string best_plaintext;
    uint8_t best_key = 0;
    int best_line_number = 0;
    int line_number = 0;
    std::string best_line;

    // Leer cada hex string de 60 caracteres 
    while (std::getline(file, line)) {
        line_number++;

        // eliminar espacios y \r que pueden estar presentes al leer líneas de un archivo, especialmente si el archivo fue creado o editado en un sistema operativo
        // diferente (como Windows, que utiliza \r\n para las nuevas líneas).
        line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
        
        // Saltar líneas vacías
        if (line.empty()) {
            continue;
        }

        // Para cada línea del archivo, se llama a la función single_byte_xor_decrypt, que intenta descifrar la línea utilizando
        // todas las posibles claves y devuelve el texto descifrado con la mejor puntuación
        std::pair<std::string, uint8_t> result = single_byte_xor_decrypt(line);

        // Obtener la puntuación del texto descifrado utilizando la función score_text, que evalúa la probabilidad de que el texto sea una frase en inglés legible.
        double score = score_text(result.first);

        // Si la puntuación del texto descifrado es mejor que la mejor puntuación general encontrada hasta ahora, actualiza los resultados almacenados.
        if (score > best_overall_score) {
            best_overall_score = score;
            best_plaintext = result.first;
            best_key = result.second;
            best_line_number = line_number;
            best_line = line;
        }
    }

    file.close();

    // Para printear el resultado con la línea con más puntuación, la clave y el texto descifrado 
    // std::cout << "Found XOR-encrypted string at line " << best_line_number << ":\n";
    // std::cout << "Ciphertext (hex): " << best_line << "\n";
    // std::cout << "Key: '" << best_key << "' (0x" << std::hex << static_cast<int>(best_key) << std::dec << ")\n";
    // std::cout << "Plaintext: " << best_plaintext << "\n";
    // std::cout << "Score: " << best_overall_score << "\n";

    return best_plaintext;
}


