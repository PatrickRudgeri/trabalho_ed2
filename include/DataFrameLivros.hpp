#include <iostream>
#include "Csv.hpp"
#include "Registro.hpp"

#ifndef TRABALHO_ED2_MATRIZ_HPP
#define TRABALHO_ED2_MATRIZ_HPP


class DataFrameLivros {
public:
    DataFrameLivros();

    ~DataFrameLivros();

    void lerCsv(std::string nome_arquivo, int num_linhas = -1, bool aleatorio = false, int seed = 42);

    void escreverCsv(std::string nome_arquivo);

    void ordenar(std::string chave, std::string algoritmo_ord, bool imprime_metricas = false);

private:
    Registro *registros;

    bool verifica(int i, int j);
};


#endif //TRABALHO_ED2_MATRIZ_HPP
