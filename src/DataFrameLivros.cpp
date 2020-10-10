#include "../include/DataFrameLivros.hpp"
#include "../include/Csv.hpp"

using namespace std;

DataFrameLivros::DataFrameLivros() {
    registros_ = nullptr;
}

DataFrameLivros::~DataFrameLivros() {
    delete[] registros_;
}


void DataFrameLivros::lerCsv(const std::string &nomeArquivo, int numLinhas, bool aleatorio, int seed) {
    registros_ = new Registro[numLinhas];
    Csv csv(registros_);
    csv.lerCsv(nomeArquivo, numLinhas, aleatorio, seed);
}

// TODO: chamar os algoritmos de ordenação nessa função
void DataFrameLivros::ordenar(string chave, AlgOrdenacao algoritmoOrd, bool imprimeMetricas) {
    
    switch (algoritmoOrd) {
        case AlgOrdenacao::quicksort:
            cout << ">>chamar a função de quicksort aqui<<" << endl;
            break;
        case AlgOrdenacao::heapsort:
            cout << ">>chamar a função de heapsort aqui<<" << endl;
            break;
    }
}

//TODO: (//FW) - função para escrever o dataset processado em um csv
//question: vamos precisar para esse trabalho?
void DataFrameLivros::escreverCsv(string nomeArquivo) {

}

Registro *DataFrameLivros::getRegistros() {
    return registros_;
}

void DataFrameLivros::setRegistros(Registro *registros) {
    registros_ = registros;
}