#include "../include/DataFrameLivros.hpp"

using namespace std;

DataFrameLivros::DataFrameLivros() {
    registros = nullptr;
}

DataFrameLivros::~DataFrameLivros() {
    delete[] registros; //TODO: verificar
}

//TODO
void DataFrameLivros::lerCsv(std::string nome_arquivo, int num_linhas, bool aleatorio, int seed) {
    Csv csv = Csv(); //Prencher um objeto DataFrameLivros com os dados retirados de Csv
    //...
}

//TODO
void DataFrameLivros::ordenar(string chave, string algoritmo_ord, bool imprime_metricas) {
    //...
}

//TODO
void DataFrameLivros::escreverCsv(string nome_arquivo) {

};