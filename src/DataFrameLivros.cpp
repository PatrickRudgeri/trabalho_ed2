#include "../include/DataFrameLivros.hpp"
#include "../include/CsvLivros.hpp"

using namespace std;

DataFrameLivros::DataFrameLivros() {
    registros_ = nullptr;
    contTrocasQuick = 0;
    contTrocasHeap = 0;
    contComparacoesHeap = 0;
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

<<<<<<< HEAD
int DataFrameLivros::particionamentoQuick(int pos_ini, int pos_fim) {
=======


int DataFrameLivros::particionamento(int pos_ini, int pos_fim) {
>>>>>>> origin/master

    int p = (pos_ini + pos_fim) / 2;
    string pivo;
    // Não está sendo possivel usar a variavel registros_ da classe
    pivo = registrosQuick[p].getTitulo();
    int esq = pos_ini;
    int dir = pos_fim;
    string aux;

    while (esq < dir) {
        contTrocasQuick++;
        while (registrosQuick[esq].getTitulo() < pivo) {
            esq++;
        }

        while (registrosQuick[dir].getTitulo() > pivo) {
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
            // Poderia ser feito desse jeito abaixo, porém quando a gente for chamar o próximo algorítimo de ordenação
            // o vetor registro já vai estar ordenado. O que vai obrigar a gente a fazer uma "copia" do vetor registro original
            // e passar esse cópia pro próximo algoritmo

            aux = registrosQuick[dir];  //teria que alterar aux pro tipo (Registro*)
            registrosQuick[dir] = registrosQuick[esq];
            registrosQuick[esq] = aux;
 
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
            registrosQuick = new Registro[numLinhas];
            for(int i = 0 ; i < tamanhoVetor ; i++)
                registrosQuick[i] = resgistros_[i];
            quickSort(0 , tamanhoVetor - 1)
            cout << ">>chamar a função de quicksort aqui<<" << endl;
            break;
        case AlgOrdenacao::heapsort:
            registrosHeap = new Registro[numLinhas];
            for(int i = 0 ; i < tamanhoVetor ; i++)
                registrosHeap[i] = resgistros_[i];
            HeapSort(registrosHeap,tamanhoVetor);
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

    void DataFrameLivros::HeapMax(Registro registrosHeap[],int raiz,int n){
        int filho_esq = 2*raiz+1;
        int filho_dir = 2*raiz+2;
        int m;
        if ((filho_esq<n) and (registrosHeap[filho_esq].getTitulo()>registrosHeap[raiz].getTitulo())){
            contComparacoesHeap = contComparacoesHeap + 1;
            m = filho_esq;
        } else m = raiz;
        if ((filho_dir<n) and (registrosHeap[filho_dir].getTitulo()>registrosHeap[m].getTitulo())){
            contComparacoesHeap = contComparacoesHeap + 1;
            m = filho_dir;
        }
        if (m != raiz) {
            contTrocasHeap = contTrocasHeap + 1;
            Registro aux = registrosHeap[raiz];
            registrosHeap[raiz] = registrosHeap[m];
            registrosHeap[m] = aux;
            HeapMax(registrosHeap,m,n);
        }
    }

    void DataFrameLivros::CriaHeap(Registro registrosHeap[],int n){
        for(int i=(n/2)-1;i>=0;i--){
            HeapMax(registrosHeap,i,n);
        }
    }

    void DataFrameLivros::HeapSort(Registro registrosHeap[],int n){
        CriaHeap(registrosHeap,n);
        for(int i=n-1;i>=0;i--){
            contTrocasHeap = contTrocasHeap + 1;
            Registro aux = registrosHeap[i];
            registrosHeap[i]= registrosHeap[0];
            registrosHeap[0]= aux;
            HeapMax(registrosHeap,0,i);
        }
    }
