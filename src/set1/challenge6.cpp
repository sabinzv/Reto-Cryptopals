#include "set1/set1.h"

// Set 1 Challenge 6: Break repeating-key XOR
// https://cryptopals.com/sets/1/challenges/6
// "Break repeating-key XOR" requires several helper utilities:
//  * hamming_distance: number of differing bits between two equal-length buffers
//  * base64_to_bytes: decode the provided ciphertext file (it's base64 encoded)
//  * a routine that guesses key size by normalized hamming distance
//  * transposition + single-byte-XOR breaking (reusing existing score_text)

///////////////////
// Te da un file ch6.txt con un texto cifrado con XOR de clave repetida y codificado en base64. 
// El objetivo es recuperar la clave y el texto plano. 
///////////////////

// -----------------------------------------------------------------------------
//////////////////
// 2. Write a function to compute the edit distance/Hamming distance between two strings. The Hamming distance is just
// the number of differing bits. The distance between "this is a test" and "wokka wokka!!!" should be 37.
////////////////

int hamming_distance(const std::vector<uint8_t>& a, const std::vector<uint8_t>& b) {
    if (a.size() != b.size()) {
        throw std::invalid_argument("Buffers must have equal length for Hamming distance");
    }

    int dist = 0;
    // Para cada byte de las dos cadenas
    for (size_t i = 0; i < a.size(); ++i) {
        uint8_t x = a[i] ^ b[i]; // XOR de los bytes correspondientes de las dos cadenas
        dist += __builtin_popcount(static_cast<unsigned>(x)); // _builtin_popcount cuenta el número de bits 1 en el resultado del XOR, que indica cuántos bits difieren entre los dos bytes.
                                                              // Después, sumamos esa cantidad a la distancia total. 
    }
    return dist;
}
// -----------------------------------------------------------------------------


// decodificador base64 
// Función para decodificar una cadena base64 a un vector de bytes. Utiliza una tabla de caracteres inversa para mapear
// los caracteres base64 a sus valores numéricos. Procesa la cadena base64, acumulando bits y extrayendo bytes cada vez
// que se alcanzan 8 bits completos. Maneja caracteres de relleno '=' y espacios en blanco adecuadamente.
std::vector<uint8_t> base64_to_bytes(const std::string& base64) {
    static const std::array<int, 256> rev = [] {
        std::array<int, 256> m;
        m.fill(-1);
        const std::string table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
        for (size_t i = 0; i < table.size(); ++i) {
            m[static_cast<unsigned char>(table[i])] = static_cast<int>(i);
        }
        return m;
    }();

    std::vector<uint8_t> out;

    int val = 0;
    int bits = 0;
    for (char c : base64) {
        if (c == '=' || std::isspace(static_cast<unsigned char>(c))) {
            // padding or whitespace: stop or skip
            if (c == '=') break;
            else continue;
        }
        int v = rev[static_cast<unsigned char>(c)];
        if (v < 0) {
            throw std::invalid_argument(std::string("Invalid base64 character: ") + c);
        }
        val = (val << 6) | v;
        bits += 6;
        if (bits >= 8) {
            bits -= 8;
            out.push_back(static_cast<uint8_t>((val >> bits) & 0xFF));
        }
    }
    return out;
}

// -----------------------------------------------------------------------------
// Esta función toma un texto y devuelve una puntuación que indica qué tan "parecido a texto" es el texto dado, basada en la
// frecuencia de caracteres comunes en inglés. Se utiliza para evaluar la calidad de los textos descifrados durante el proceso
// de ruptura del cifrado XOR de clave repetida. 
static std::pair<std::string, uint8_t>
single_byte_xor_decrypt_bytes(const std::vector<uint8_t>& ciphertext) {
    double best_score = -1;
    uint8_t best_key = 0;
    std::string best_plain;

    // Para cada posible clave de un solo byte (0 a 255), se intenta descifrar el texto cifrado utilizando esa clave
    // y se calcula la puntuación del resultado.
    for (int k = 0; k < 256; ++k) {
        std::string plain;
        for (uint8_t b : ciphertext) {
            plain += static_cast<char>(b ^ static_cast<uint8_t>(k));
        }
        double sc = score_text(plain);
        if (sc > best_score) {
            best_score = sc;
            best_key = static_cast<uint8_t>(k);
            best_plain = std::move(plain);
        }
    }
    return {best_plain, best_key};
}

// -----------------------------------------------------------------------------

// Función principal que toma un texto cifrado con XOR de clave repetida y codificada en base64 y devuelve la clave y el texto plano.
std::pair<std::string, std::string> break_repeating_key_xor(const std::vector<uint8_t>& ciphertext) {
    if (ciphertext.empty()) {
        return {"", ""};
    }

    /////////////////////
    // 1. Let KEYSIZE be the guessed length of the key; try values from 2 to (say) 40.
    // 3. For each KEYSIZE, take the first KEYSIZE worth of bytes, and the second KEYSIZE worth of bytes, and find the edit distance
    // between them. Normalize this result by dividing by KEYSIZE.
    // 4. The KEYSIZE with the smallest normalized edit distance is probably the key. You could proceed perhaps with the 
    // smallest 2-3 KEYSIZE values. Or take 4 KEYSIZE blocks instead of 2 and average the distances.
    /////////////////////

    // Calcular la distancia normalizada para cada tamaño de clave candidato
    std::vector<std::pair<size_t, double>> candidates; // (ks, norm) son los tamaños de clave candidatos y sus distancias normalizadas promedio
    // Para cada tamaño de clave candidato entre 2 y 40 (o hasta que no haya suficientes bloques completos)
    for (size_t ks = 2; ks <= 40 && ks * 4 <= ciphertext.size(); ++ks) { // Asegurarse de que haya al menos 4 bloques completos para este tamaño de clave
        double total = 0.0;
        int count = 0;
        // Usar hasta 4 bloques consecutivos y promediar distancias entre adyacentes: 0-1,1-2,2-3
        for (int b = 0; b + 1 < 4; ++b) {
            size_t off1 = b * ks; // Offset del bloque b
            size_t off2 = (b + 1) * ks; // Offset del bloque b+1
            if (off2 + ks <= ciphertext.size()) { // Asegurarse de que ambos bloques estén completos
                std::vector<uint8_t> block1(ciphertext.begin() + off1, ciphertext.begin() + off1 + ks); // Extraer el bloque b
                std::vector<uint8_t> block2(ciphertext.begin() + off2, ciphertext.begin() + off2 + ks); // Extraer el bloque b+1
                // Calcular la distancia normalizada entre los dos bloques y acumularla
                total += static_cast<double>(hamming_distance(block1, block2)) / static_cast<double>(ks); 
                ++count;
            }
        }
        // Si se calcularon distancias para este tamaño de clave, agregar el candidato a la lista con su distancia normalizada promedio
        if (count > 0) {
            candidates.emplace_back(ks, total / count);// emplace_back agrega un nuevo par (ks, distancia normalizada promedio) a la lista de candidatos.
            // total / count se asegura de que la distancia normalizada se promedie correctamente si se calcularon varias distancias para este tamaño de clave.
        }
    }

    // Ordenar por distancia normalizada ascendente
    // La función de comparación lambda [](const auto &a, const auto &b) { return a.second < b.second; } se utiliza para ordenar
    // los candidatos en orden ascendente según su distancia normalizada (el segundo elemento del par).
    // sort() reordenará la lista de candidatos de modo que aquellos con la distancia normalizada más baja (es decir, los más prometedores) aparezcan primero en la lista.
    std::sort(candidates.begin(), candidates.end(), [](const auto &a, const auto &b) {
        return a.second < b.second;
    });

    // Probar top-N candidatos y elegir el mejor plaintext por puntuación
    size_t topN = std::min<size_t>(3, candidates.size()); // Probar los 3 mejores candidatos (o menos si hay menos de 3) para encontrar el mejor resultado final.
    double best_score_overall = -1e9; // Inicializar la mejor puntuación general a un valor muy bajo
    std::string best_key_overall; // La clave que produce el mejor texto plano encontrado
    std::string best_plain_overall; // El texto plano que tiene la mejor puntuación encontrada

    for (size_t ci = 0; ci < topN; ++ci) {// Para cada uno de los top-N candidatos
        size_t ks = candidates[ci].first; // Obtener el tamaño de clave candidato del par (ks, distancia normalizada)

        ////////////////////////////
        // 5. Now that you probably know the KEYSIZE: break the ciphertext into blocks of KEYSIZE length.
        // 6. Now transpose the blocks: make a block that is the first byte of every block, and a block that is the second byte of every block, and so on.
        ////////////////////////////

        // Transponer
        std::vector<std::vector<uint8_t>> tblocks(ks);
        for (size_t i = 0; i < ciphertext.size(); ++i) {
            tblocks[i % ks].push_back(ciphertext[i]);
        }

        ////////////////////////////
        // 7. Solve each block as if it was single-character XOR. You already have code to do this.
        // 8. For each KEYSIZE, the single-byte XOR key that produces the best looking histogram is the repeating-key XOR key byte
        // for that block. Put them together and you have the full KEYSIZE-length key.
        ////////////////////////////

        // Resolver cada bloque con el solver que opera sobre bytes
        std::string key_candidate;
        for (size_t i = 0; i < ks; ++i) {
            auto res = single_byte_xor_decrypt_bytes(tblocks[i]); // {plaintext, key}
            key_candidate.push_back(static_cast<char>(res.second));
        }

        // Descifrar y puntuar
        // Para cada candidato de clave, descifrar el texto completo utilizando la clave candidata y calcular su puntuación
        // para determinar qué tan "parecido a texto" es el resultado.
        std::string plain_candidate;
        // Para cada byte del texto cifrado, aplicar XOR con el byte correspondiente de la clave candidata (usando módulo para repetir la clave)
        // y construir el texto plano candidato.
        for (size_t i = 0; i < ciphertext.size(); ++i) {
            plain_candidate.push_back(static_cast<char>(ciphertext[i] ^ static_cast<uint8_t>(key_candidate[i % key_candidate.size()])));
        }
        // Calcular la puntuación del texto plano candidato utilizando la función score_text, que evalúa qué tan "parecido a texto" es el
        // resultado basado en la frecuencia de caracteres comunes en inglés.
        double sc = score_text(plain_candidate);
        // Si la puntuación del texto plano candidato es mejor que la mejor puntuación general encontrada hasta ahora, actualizar la mejor
        // puntuación general y almacenar la clave y el texto plano correspondientes a esta nueva mejor puntuación.
        if (sc > best_score_overall) {
            best_score_overall = sc;
            best_key_overall = key_candidate;
            best_plain_overall = plain_candidate;
        }
    }

    // Después de probar los top-N candidatos, si se encontró una clave con una puntuación mejor que la inicial, devolver esa clave y su
    // texto plano correspondiente. De lo contrario, devolver un par de cadenas vacías.
    if (!best_key_overall.empty()) {
        return {best_key_overall, best_plain_overall};
    }

    return {"", ""};
}
