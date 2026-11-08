cmake_minimum_required(VERSION 3.16)
project(MatrixVectorLibrary C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

include_directories(include)

# 1. Gemeinsame / Geteilte Bibliothek (.dylib / .so / .dll)
add_library(matrix_math SHARED
    src/Matrix.c
)

# 2. Ausführbare Client-Testanwendung
add_executable(matrix_test
    src/main.c
)

target_link_libraries(matrix_test PRIVATE matrix_math)
