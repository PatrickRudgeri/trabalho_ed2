#ifndef TRABALHO_ED2_MATRIZ_HPP
#define TRABALHO_ED2_MATRIZ_HPP

#include <iostream>
#include "Registro.hpp"

enum AlgOrdenacao {
    quicksort,
    heapsort
};

class DataFrameLivros {
public:
    DataFrameLivros();

    ~DataFrameLivros();

    Registro *getRegistros();

    void setRegistros(Registro *registros_);

    void lerCsv(const std::string &nomeArquivo, int numLinhas = -1, bool aleatorio = false, int seed = 42);

    void escreverCsv(std::string nomeArquivo);

    void ordenar(std::string chave, AlgOrdenacao algoritmoOrd, bool imprimeMetricas = false);

private:
    Registro *registros_;

    //métodos de ordenação
    int particionamentoQuick(int pos_ini, int pos_fim);
    void quickSort(int pos_ini, int pos_fim);

    int contTrocasQuick;
};


#endif //TRABALHO_ED2_MATRIZ_HPP
