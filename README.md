# Reto Criptopals en C++

**Requisitos**

- Compiler C++ compatible con C++17
- CMake (>= 3.10)
- Google Test

**Estructura del proyecto**

- src/ — implementaciones por reto (p. ej. set1/)
- tests/ — pruebas unitarias (Google Test)
- build/ — carpeta de construcción (generada por CMake)
- CMakeLists.txt — configuración del proyecto

**Compilar y ejecutar**

Desde la raíz del proyecto:

```bash
git clone https://github.com/user-111241/crptpls.git
cd crptpls
mkdir -p build
cd build
cmake ..
cmake --build .
```

Para ejecutar las pruebas (desde build):

```bash
ctest --verbose
```

O ejecutar el binario de pruebas directamente, por ejemplo:

```bash
./test_challenge1
```
