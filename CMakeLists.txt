cmake_minimum_required(VERSION 3.12)
project(trabalho_ed2)

set(CMAKE_CXX_STANDARD 14)

add_executable(trabalho_ed2
        src/main.cpp
        src/csvLivros.cpp include/csvLivros.hpp
        src/DataFrameLivros.cpp include/DataFrameLivros.hpp
        src/Registro.cpp include/Registro.hpp
        src/txtLivros.cpp include/txtLivros.hpp include/Stats.hpp src/Stats.cpp
        include/secao_2/Autor.hpp include/secao_2/Hash.hpp include/secao_2/Primo.hpp
        src/secao_2/Autor.cpp src/secao_2/Hash.cpp src/secao_2/Primo.cpp
        )