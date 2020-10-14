#include "../include/DataFrameLivros.hpp"
#include "../include/CsvLivros.hpp"

using namespace std;

DataFrameLivros::DataFrameLivros() {
    registros_ = nullptr;
    contTrocasQuick = 0;
}

DataFrameLivros::~DataFrameLivros() {
    delete[] registros_;
}


void DataFrameLivros::lerCsv(const std::string &nomeArquivo, int numLinhas, bool aleatorio, int seed) {
    registros_ = new Registro[numLinhas];
    CsvLivros csv(registros_);
    csv.lerCsv(nomeArquivo, numLinhas, aleatorio, seed);
}

Registro *DataFrameLivros::getRegistros() {
    return registros_;
}

int DataFrameLivros::particionamentoQuick(int pos_ini, int pos_fim) {

    int p = (pos_ini + pos_fim) / 2;
    string pivo;
    // Não está sendo possivel usar a variavel registros_ da classe
    pivo = registros_[p].getTitulo();
    int esq = pos_ini;
    int dir = pos_fim;
    string aux;

    while (esq < dir) {
        contTrocasQuick++;
        while (registros_[esq].getTitulo() < pivo) {
            esq++;
        }

        while (registros_[dir].getTitulo() > pivo) {
            dir--;
        }
        if (esq <= dir) {
            if (dir == p) {
                p = esq;
            }
            if (esq == p) {
                p = dir;
            }
            //FIXME: Se fizer dessa forma apenas os titulos dos livros serão alterados de posição, sendo que o
            // certo seria todo o registro mudar de posição (baseado na ordem dos titulos)
            aux = registros_[dir].getTitulo();
            registros_[dir].setTitulo(registros_[esq].getTitulo());
            registros_[esq].setTitulo(aux);
            // Poderia ser feito desse jeito abaixo, porém quando a gente for chamar o próximo algorítimo de ordenação
            // o vetor registro já vai estar ordenado. O que vai obrigar a gente a fazer uma "copia" do vetor registro original
            // e passar esse cópia pro próximo algoritmo
            /*//------------------------
            aux = registros_[dir];  //teria que alterar aux pro tipo (Registro*)
            registros_[dir] = registros_[esq];
            registros_[esq] = aux;
            *///------------------------
            //TODO: Creio que a melhor solução seja cria um vetor vazio de tamanho n[i] (numLinhas) para armazenar esses
            // registros ordenados. Pq assim não teriamos que fazer uma cópia do original
        }
        esq++;
        dir--;
    }

    return p + 1;

}

void DataFrameLivros::quickSort(int pos_ini, int pos_fim) {
    if (pos_fim - pos_ini > 0) {
        int q = particionamentoQuick(pos_ini, pos_fim);
        quickSort( pos_ini, q - 1);
        quickSort(q, pos_fim);
    }
// TODO: chamar os algoritmos de ordenação nessa função
void DataFrameLivros::ordenar(string chave, int tamanhoVetor ,  AlgOrdenacao algoritmoOrd, bool imprimeMetricas) {
    
    switch (algoritmoOrd) {
        case AlgOrdenacao::quicksort:
            quickSort(0 , tamanhoVetor)
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



void DataFrameLivros::setRegistros(Registro *registros) {
    registros_ = registros;
}