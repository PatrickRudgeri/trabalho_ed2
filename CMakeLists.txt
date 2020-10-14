cmake_minimum_required(VERSION 3.12)
project(trabalho_ed2)

set(CMAKE_CXX_STANDARD 14)

add_executable(trabalho_ed2
        src/main.cpp
        src/CsvLivros.cpp include/CsvLivros.hpp
        src/DataFrameLivros.cpp include/DataFrameLivros.hpp
        src/Registro.cpp include/Registro.hpp
        src/TxtLivros.cpp include/TxtLivros.hpp)