cmake_minimum_required(VERSION 3.12)
project(trabalho_ed2)

set(CMAKE_CXX_STANDARD 14)

add_executable(trabalho_ed2
        src/main.cpp
        src/Registro.cpp include/Registro.hpp
        include/secao_2/Autor.hpp src/secao_2/Autor.cpp
        include/secao_2/HashRegistro.hpp src/secao_2/HashRegistro.cpp
        include/secao_2/HashAutor.hpp src/secao_2/HashAutor.cpp
        include/secao_2/Primo.hpp src/secao_2/Primo.cpp
        include/secao_3/noVP.hpp src/secao_3/noVP.cpp
        include/secao_3/AVP.hpp src/secao_3/AVP.cpp
        src/csvLivros.cpp include/csvLivros.hpp
        src/DataFrameLivros.cpp include/DataFrameLivros.hpp
        src/txtLivros.cpp include/txtLivros.hpp
        include/metricas.hpp src/metricas.cpp
        )