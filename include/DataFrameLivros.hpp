#ifndef TRABALHO_ED2_MATRIZ_HPP
#define TRABALHO_ED2_MATRIZ_HPP

#include <iostream>
#include "Csv.hpp"
#include "Registro.hpp"

class DataFrameLivros {
public:
    DataFrameLivros();

    ~DataFrameLivros();

    void lerCsv(std::string nomeArquivo, int numLinhas = -1, bool aleatorio = false, int seed = 42);

    void escreverCsv(std::string nomeArquivo);

    void ordenar(std::string chave, std::string algoritmoOrd, bool imprimeMetricas = false);

private:
    Registro *registros;
};


#endif //TRABALHO_ED2_MATRIZ_HPP
