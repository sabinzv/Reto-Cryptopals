#include "set1/set1.h"

//////////////////////////////////////////////////////
// Challenge 7: AES in ECB mode
// https://cryptopals.com/sets/1/challenges/7
// The Base64-encoded content in ch7.txt has been encrypted via AES-128 in ECB mode under the key "YELLOW SUBMARINE".
// (case-sensitive, without the quotes; exactly 16 bytes long)
// Decrypt it. You know the key, after all.
// Easiest way: use OpenSSL::cypher and give it AES-128-ECB as the cipher.
//////////////////////////////////////////////////////

// We use OpenSSL EVP APIs and selects the cipher by name (aes-128-ecb).
// https://docs.openssl.org/3.5/man3/EVP_EncryptInit/#return-values
// https://wiki.openssl.org/index.php/EVP_Symmetric_Encryption_and_Decryption

// Resumen corto de la función aes_128_ecb_decrypt:
// - Verifica que la clave tenga 16 bytes (128 bits).
// - Crea un contexto de cifrado EVP.
// - Selecciona el cifrado AES-128-ECB por su nombre.
// - Inicializa el contexto para descifrar con la clave dada.
// - Habilita el relleno PKCS#7 para manejar el padding del bloque.
// - Realiza la operación de descifrado en dos pasos: primero con EVP_DecryptUpdate y luego con EVP_DecryptFinal_ex para manejar el padding.
// - Libera el contexto y devuelve el texto descifrado como una cadena.

std::string aes_128_ecb_decrypt(const std::vector<uint8_t>& ciphertext, const std::string& key) {
	if (key.size() != 16) {
		throw std::invalid_argument("Key must be 16 bytes for AES-128");
	}

    // Crear un nuevo contexto de cifrado EVP para realizar la operación de descifrado.
	EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new(); // EVP_CIPHER_CTX es una estructura que almacena el estado de una operación de cifrado o descifrado. 
                                                // Se utiliza para mantener la información necesaria durante el proceso de cifrado o descifrado, como la clave, el vector
                                                // de inicialización (IV), el modo de operación, etc. En este caso, se crea un nuevo contexto para realizar la operación de descifrado AES-128-ECB.
	if (!ctx) {
		throw std::runtime_error("EVP_CIPHER_CTX_new failed");
	}

    // Seleccion del cifrado AES-128-ECB utilizando su nombre.
    // La función EVP_get_cipherbyname busca el cifrado especificado por su nombre y devuelve un puntero a la estructura EVP_CIPHER correspondiente.
	const EVP_CIPHER* cipher = EVP_get_cipherbyname("aes-128-ecb");
	if (!cipher) {
		EVP_CIPHER_CTX_free(ctx); // Liberar el contexto creado antes de lanzar la excepción para evitar fugas de memoria.
		throw std::runtime_error("Cipher 'aes-128-ecb' not available"); 
	}

    // Inicializar el contexto para descifrar utilizando la clave dada. No se proporciona un IV porque ECB no lo utiliza.
	if (1 != EVP_DecryptInit_ex(ctx, cipher, nullptr, reinterpret_cast<const unsigned char*>(key.data()), nullptr)) {
		EVP_CIPHER_CTX_free(ctx);
		throw std::runtime_error("EVP_DecryptInit_ex failed");
	}

    // La función EVP_CIPHER_CTX_set_padding se utiliza para habilitar o deshabilitar el relleno en las operaciones de cifrado o descifrado.
    // En este caso, se habilita el relleno (padding) para que OpenSSL maneje automáticamente el relleno PKCS#7 al descifrar, lo cual es necesario para manejar
    // correctamente los datos cifrados que no son múltiplos del tamaño del bloque (16 bytes para AES-128).
	EVP_CIPHER_CTX_set_padding(ctx, 1);

    // Realizar la operación de descifrado en dos pasos: primero con EVP_DecryptUpdate para procesar los datos cifrados, y luego con EVP_DecryptFinal_ex para manejar el padding.
	std::vector<uint8_t> out(ciphertext.size() + EVP_CIPHER_block_size(cipher)); // El tamaño de salida se establece como el tamaño del texto cifrado más el tamaño  del bloque
                                                                                 // para asegurarse de que haya suficiente espacio para el texto descifrado, incluso si se agrega padding.
	
    // EVP_DecryptUpdate procesa los datos cifrados y escribe el resultado descifrado en el buffer de salida. El número de bytes escritos se almacena en outlen1.
    int outlen1 = 0;
	if (1 != EVP_DecryptUpdate(ctx, out.data(), &outlen1, ciphertext.data(), static_cast<int>(ciphertext.size()))) {
		EVP_CIPHER_CTX_free(ctx);
		throw std::runtime_error("EVP_DecryptUpdate failed");
	}

    // EVP_DecryptFinal_ex se llama después de procesar todos los datos cifrados para manejar el padding. Escribe cualquier byte adicional descifrado en el buffer
    // de salida y actualiza outlen2 con el número de bytes escritos.
	int outlen2 = 0;
	if (1 != EVP_DecryptFinal_ex(ctx, out.data() + outlen1, &outlen2)) {
		EVP_CIPHER_CTX_free(ctx);
		unsigned long err = ERR_get_error();
		(void)err;
		throw std::runtime_error("EVP_DecryptFinal_ex failed (bad padding or corrupted ciphertext)");
	}

	EVP_CIPHER_CTX_free(ctx);
    // Redimensionar el vector de salida para contener solo los bytes descifrados válidos (outlen1 + outlen2) y convertirlo a una cadena.
	out.resize(static_cast<size_t>(outlen1 + outlen2));
	return std::string(out.begin(), out.end());
}

// Main para ejecutar el challenge7.cpp sin testeo para sacar el texto descifrado y la clave
// int main() {
//     std::cout << decrypt_challenge7() << std::endl;
//     return 0;
// }

// std::string decrypt_challenge7() {
// 	std::ifstream file("../src/set1/utils/ch7.txt");
// 	if (!file.is_open()) {
// 		throw std::runtime_error("Could not open ch7.txt");
// 	}

//     // Leer todo el archivo en un stringstream, luego convertirlo a string
// 	std::stringstream ss;
// 	ss << file.rdbuf();
// 	std::string b64 = ss.str();

//     // Convertir la cadena base64 a bytes
// 	auto ciphertext = base64_to_bytes(b64);

//     // Descifrar el texto cifrado utilizando AES-128-ECB con la clave dada
// 	std::string key = "YELLOW SUBMARINE";
// 	return aes_128_ecb_decrypt(ciphertext, key);
// }



