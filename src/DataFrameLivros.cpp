#include "../include/DataFrameLivros.hpp"

using namespace std;

DataFrameLivros::DataFrameLivros() {
    registros = nullptr;
}

DataFrameLivros::~DataFrameLivros() {
    delete[] registros; //TODO: verificar
}

//TODO
void DataFrameLivros::lerCsv(std::string nomeArquivo, int numLinhas, bool aleatorio, int seed) {
    Csv csv = Csv(); //Prencher um objeto DataFrameLivros com os dados retirados de Csv
    //...
}

//TODO
void DataFrameLivros::ordenar(string chave, string algoritmoOrd, bool imprimeMetricas) {
    //...
}

//TODO
void DataFrameLivros::escreverCsv(string nomeArquivo) {

};