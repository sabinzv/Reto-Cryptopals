#include "set1/set1.h" // Incluye el archivo de encabezado "set1.h" que contiene la declaración de la función hex_to_base64,
                            // lo que permite utilizar esa función en este archivo fuente para implementar su funcionalidad.

// Set 1 Challenge 1: Convert hex to base64
// Always operate on raw bytes, never on encoded strings. Only use hex and base64 for pretty-printing.

// Wikipedia:
// Basado en la codificación de base64, que representa datos binarios en formato ASCII utilizando un conjunto de 64 caracteres. 
// Cada grupo de 3 bytes (24 bits) se divide en 4 grupos de 6 bits, y cada grupo de 6 bits se mapea a un carácter en la tabla de base64. 
// Si el número de bytes no es múltiplo de 3, se añaden caracteres de relleno '=' al final para completar el bloque de 4 caracteres.

// Tabla de caracteres para base64, para convertir los valores de 6 bits a su representación en base64
const char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


// Función para convertir un string hexadecimal a su valor numérico (0..15)
int hex_char_to_value(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0'; // Convierte '0'-'9' a 0-9
    } else if (c >= 'A' && c <= 'F') {
        return (c - 'A') + 10; // Convierte 'A'-'F' a 10-15
    } else if (c >= 'a' && c <= 'f') {
        return (c - 'a') + 10; // Convierte 'a'-'f' a 10-15
    } else {
        throw std::invalid_argument("Invalid hexadecimal character");
    }
}

// Función para convertir una cadena hexadecimal a un vector de bytes
std::vector<uint8_t> hex_to_bytes(const std::string& hex) { 
    if (hex.length() % 2 != 0) { 
        throw std::invalid_argument("\n Hex string must have an even length: '" + hex + "' has length " + std::to_string(hex.length()) + "\n");
    }
    std::vector<uint8_t> bytes; // Vector para almacenar los bytes resultantes de la conversión
    bytes.reserve(hex.length() / 2); // Reserva espacio en el vector para la cantidad de bytes que se generarán
    for (size_t i = 0; i < hex.length(); i += 2) { // Itera sobre la cadena hexadecimal de dos en dos caracteres
        int high = hex_char_to_value(hex[i]); // Convierte el primer carácter hexadecimal a su valor numérico (4 bits altos)
        int low = hex_char_to_value(hex[i + 1]); // Convierte el segundo carácter hexadecimal a su valor numérico (4 bits bajos)
        bytes.push_back((high << 4) | low); // agregar al vector la combinacion
    }
    return bytes; 
}

// Función para convertir un vector de bytes a su representación en base64
// Agrupa los bytes en bloques de 3 (24 bits) y los convierte a 4 caracteres base64 (6bits cada uno) utilizando la tabla de caracteres base64.
// Si el número de bytes no es múltiplo de 3, se añaden caracteres de relleno '=' al final.
std::string bytes_to_base64(const std::vector<uint8_t>& bytes) { 
    size_t bytesize = bytes.size();
    if (bytesize == 0) {
        return ""; // Si el vector de bytes está vacío, devuelve una cadena vacía
    }

    std::string base64; // Cadena para almacenar el resultado en base64

    base64.reserve(((bytesize + 2) / 3) * 4); // Reserva espacio en la cadena base64 para la cantidad de caracteres que se generarán.
    // Cada bloque de 3 bytes se convierte en 4 caracteres base64
    // El cálculo (n + 2) / 3 , el +2 se utiliza para redondear hacia arriba en caso de que el número de bytes no sea múltiplo de 3,
    // asegurando que se reserve suficiente espacio para los caracteres base64 resultantes, incluyendo cualquier relleno necesario.

    for (size_t i = 0; i < bytesize; i += 3) { // Itera sobre el vector de bytes en bloques de 3 bytes
        // Tomamos hasta 3 octetos (si faltan, ponemos 0)
        uint32_t octet_a = bytes[i]; // El primer byte del bloque
        uint32_t octet_b = (i + 1 < bytesize) ? bytes[i + 1] : 0; // El segundo byte del bloque, o 0 si no hay suficientes bytes
        // Si el índice i + 1 es menor que bytesize, significa que hay un segundo byte disponible, por lo que se asigna bytes[i + 1] a octet_b.
        // Si el índice i + 1 es igual o mayor que bytesize, significa que no hay suficientes bytes disponibles, por lo que se asigna 0 a octet_b.
        uint32_t octet_c = (i + 2 < bytesize) ? bytes[i + 2] : 0; // El tercer byte del bloque, o 0 si no hay suficientes bytes

        uint32_t triple = (octet_a << 16) | (octet_b << 8) | octet_c; // Combina los 3 bytes en un solo número de 24 bits

        // Extraemos 4 índices de 6 bits y los convertimos a caracteres base64 utilizando la tabla de caracteres base64
        base64 += base64_table[(triple >> 18) & 0x3F]; // El primer carácter base64 se obtiene tomando los 6 bits más altos del triple y aplicando una máscara de 0x3F para obtener solo esos 6 bits. 
        base64 += base64_table[(triple >> 12) & 0x3F]; 
        base64 += base64_table[(triple >> 6)  & 0x3F];
        base64 += base64_table[ triple        & 0x3F];

        // Ajustamos padding '=' si faltaron bytes reales
        if (i + 1 >= bytesize) {           // solo había 1 byte en este bloque
            base64[base64.size() - 1] = '='; // sustituir último carácter por '=' 
            base64[base64.size() - 2] = '='; // y el penúltimo
        } else if (i + 2 >= bytesize) {    // había 2 bytes en este bloque
            base64[base64.size() - 1] = '='; // sustituir último
        }
    }

    return base64;
}

// Función principal que convierte una cadena hexadecimal a su representación en base64
std::string hex_to_base64(const std::string& hex) {
    std::vector<uint8_t> bytes = hex_to_bytes(hex); // Convierte la cadena hexadecimal a un vector de bytes utilizando la función hex_to_bytes
    return bytes_to_base64(bytes); // Convierte el vector de bytes a su representación en base64 utilizando la función bytes_to_base64
} 