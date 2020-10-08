//
// Created by patrick on 03/10/2020.
//

#include "../include/DataFrameLivros.hpp"

using namespace std;

DataFrameLivros::DataFrameLivros() {
    registros = nullptr;
}

DataFrameLivros::~DataFrameLivros() {
    delete[] registros; //TODO: verificar
}

float DataFrameLivros::get(int i, int j) {
    if (verifica(i, j))
        return mat[i][j];
    else {
        cout << "Erro: indice invalido" << endl;
        exit(1);
    }
}

void DataFrameLivros::set(int i, int j, float valor) {
    if (verifica(i, j))
        mat[i][j] = valor;
    else {
        cout << "Erro: indice invalido" << endl;
        exit(1);
    }
}

bool DataFrameLivros::verifica(int i, int j) {
    if (i >= 0 && i < nl && j >= 0 && j < nc)
        return true;
    else
        return false; // indice invalido
}

//TODO
void DataFrameLivros::lerCsv(std::string nome_arquivo, int num_linhas, bool aleatorio, int seed) {
    Csv csv = Csv(); //Prencher um objeto DataFrameLivros os dados retirados de Csv
    //...
}

//TODO
void DataFrameLivros::ordenar(string chave, string algoritmo_ord, bool imprime_metricas) {
    //...
}

//TODO
void DataFrameLivros::escreverCsv(string nome_arquivo) {

};