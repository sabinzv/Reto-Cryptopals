cmake_minimum_required(VERSION 3.14) # Establece la versión mínima de CMake requerida para este proyecto
project(Cryptopals LANGUAGES CXX) # Define el nombre del proyecto y especifica que se usará C++ como lenguaje de programación

set(CMAKE_CXX_STANDARD 17) # Establece el estándar de C++ a utilizar para compilar el proyecto, en este caso C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON) # Indica que el estándar de C++ especificado es obligatorio, lo que significa que el compilador debe soportar al menos C++17 para compilar este proyecto
set(CMAKE_CXX_EXTENSIONS OFF) # Desactiva las extensiones específicas del compilador, lo que garantiza que el código se adhiera al estándar de C++ sin utilizar características específicas
                            # de un compilador en particular

# Biblioteca con la implementación de los retos
add_library(set1_lib STATIC
    src/set1/challenge1.cpp
    src/set1/challenge2.cpp
    src/set1/challenge3.cpp
    src/set1/challenge4.cpp
) 
# Agrega una biblioteca estática llamada "set1_lib" que se compila a partir del archivo "challenge1.cpp" ubicado en "src/set 1/".
# Una biblioteca estática es un archivo que contiene código objeto que se enlaza con el ejecutable en tiempo de compilación, lo que permite reutilizar el código en diferentes
# partes del proyecto sin necesidad de recompilarlo cada vez.

# Especifica que el directorio "src" se debe incluir en la ruta de búsqueda de encabezados para la biblioteca "set1_lib", lo que permite que los archivos fuente
# dentro de "src" puedan incluir encabezados ubicados en ese directorio utilizando rutas relativas.
target_include_directories(set1_lib PUBLIC src)

# Ejecutable (opcional)
# add_executable(challenge1_app) # si quieres un ejecutable separable
# target_link_libraries(challenge1_app PRIVATE set1_lib)

# Tests
enable_testing() # Habilita las pruebas para este proyecto

find_package(GTest REQUIRED) # Busca la biblioteca de Google Test (GTest) y marca como requerida, lo que significa que el proyecto no se podrá compilar si GTest no está disponible en el sistema.

add_executable(test_challenge1 tests/set1/test_challenge1.cpp) # Agrega un ejecutable llamado "test_challenge1" que se compila a partir del archivo "test_challenge1.cpp" ubicado en "tests/set1/". Este ejecutable se utilizará para ejecutar las pruebas relacionadas con el desafío 1.
target_link_libraries(test_challenge1 PRIVATE set1_lib GTest::gtest_main) # Especifica que el ejecutable "test_challenge1" debe enlazarse con la biblioteca "set1_lib" y la
                                                                                # biblioteca principal de Google Test (GTest::gtest_main) de forma privada, lo que significa que estas
                                                                                # dependencias solo son necesarias para compilar "test_challenge1" y no se propagan a otros objetivos que puedan
                                                                                # depender de él.
target_include_directories(test_challenge1 PRIVATE src) # Especifica que el directorio "src" se debe incluir en la ruta de búsqueda de encabezados para el ejecutable "test_challenge1"
add_test(NAME TestChallenge1 COMMAND test_challenge1) # Agrega una prueba llamada "TestChallenge1" que se ejecuta utilizando el ejecutable "test_challenge1"

add_executable(test_challenge2 tests/set1/test_challenge2.cpp) 
target_link_libraries(test_challenge2 PRIVATE set1_lib GTest::gtest_main)
target_include_directories(test_challenge2 PRIVATE src)
add_test(NAME TestChallenge2 COMMAND test_challenge2)

# Utilizado para ejecutar el challenge3.cpp sin testeo para sacar el texto descifrado y la clave
# add_executable(run_challenge3 src/set1/challenge3.cpp)
# target_link_libraries(run_challenge3 set1_lib)
# target_include_directories(run_challenge3 PRIVATE src)

# Utilizado cuando ya sabemos la clave y el texto descifrado para testear que el resultado es correcto
add_executable(test_challenge3 tests/set1/test_challenge3.cpp)
target_link_libraries(test_challenge3 PRIVATE set1_lib GTest::gtest_main)
target_include_directories(test_challenge3 PRIVATE src)
add_test(NAME TestChallenge3 COMMAND test_challenge3)

# Utilizado para ejecutar el challenge4.cpp sin testeo para sacar el texto descifrado y la clave
# add_executable(run_challenge4 src/set1/challenge4.cpp)
# target_link_libraries(run_challenge4 set1_lib)
# target_include_directories(run_challenge4 PRIVATE src)

add_executable(test_challenge4 tests/set1/test_challenge4.cpp)
target_link_libraries(test_challenge4 PRIVATE set1_lib GTest::gtest_main)
target_include_directories(test_challenge4 PRIVATE src)
add_test(NAME TestChallenge4 COMMAND test_challenge4)



