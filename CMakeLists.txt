cmake_minimum_required(VERSION 3.17)
project(trabalho_ed2)

set(CMAKE_CXX_STANDARD 14)

add_executable(trabalho_ed2
        src/main.cpp
        include/helpers.hpp
        src/Csv.cpp include/Csv.hpp
#        src/DataFrameLivros.cpp include/DataFrameLivros.hpp
        src/Registro.cpp include/Registro.hpp
        src/Txt.cpp include/Txt.h)