#include "../include/DataFrameLivros.hpp"
#include "../include/CsvLivros.hpp"

using namespace std;

DataFrameLivros::DataFrameLivros() {
    registros_ = nullptr;
    registrosHeap_ = nullptr;
    registrosQuick_ = nullptr;
    numLinhas_ = 0;
    contTrocasQuick_ = 0;
    contTrocasHeap_ = 0;
    contComparacoesHeap_ = 0;
    contComparacoesQuick_ = 0;
}

DataFrameLivros::~DataFrameLivros() {
    delete[] registros_;
    delete[] registrosQuick_;
    delete[] registrosHeap_;
}

void DataFrameLivros::lerCsv(const std::string &nomeArquivo, int numLinhas, bool aleatorio, int seed) {
    registros_ = new Registro[numLinhas];
    this->numLinhas_ = numLinhas;
    CsvLivros csv(registros_);
    csv.lerCsv(nomeArquivo, numLinhas, aleatorio, seed);
}

Registro *DataFrameLivros::getRegistros() {
    return registros_;
}

//TODO: documentar os blocos funcionais e variáveis dentro do método
int DataFrameLivros::particionamentoQuick(int pos_ini, int pos_fim) {
    /**
     *  Descrever o que está acontecendo abaixo
     * */
    int pontoMedio = (pos_ini + pos_fim) / 2;
    Registro primeiraPosicao = registrosQuick_[pos_ini];
    Registro meioPosicao = registrosQuick_[pontoMedio];
    Registro UltimaPosicao = registrosQuick_[pos_fim];
    int mediaDeTres;
    if (primeiraPosicao.getTitulo() < meioPosicao.getTitulo()){
        if(primeiraPosicao.getTitulo() > UltimaPosicao.getTitulo()){
            mediaDeTres = pos_ini;
        } else if(meioPosicao.getTitulo() > UltimaPosicao.getTitulo()){
            mediaDeTres = pos_fim;
        } else {
            mediaDeTres = pontoMedio;
        }
    } else {
        if(primeiraPosicao.getTitulo() < UltimaPosicao.getTitulo()){
            mediaDeTres = pos_ini;
        } else if(meioPosicao.getTitulo() < UltimaPosicao.getTitulo()){
            mediaDeTres = pos_fim;
        } else {
            mediaDeTres = pontoMedio;
        }
    }

    //descrever o que é essa variável
    string pivo;

    //descrever o que é essa variável
//    pivo = registrosQuick_[p].getTitulo();
    pivo = registrosQuick[mediaDeTres].getTitulo();
    int esq = pos_ini;
    int dir = pos_fim;

    //descrever o que é essa variável
    Registro aux;

    /*
     * breve descrição do que
     * está acontecendo abaixo
     * */
    while (esq < dir) {
        contTrocasQuick_++;
        while (registrosQuick_[esq].getTitulo() < pivo) {
            contComparacoesQuick_++;
            esq++;
        }

        while (registrosQuick_[dir].getTitulo() > pivo) {
            contComparacoesQuick_++;
            dir--;
        }
        if (esq <= dir) {
            if (dir == p) {
                p = esq;
            }
            if (esq == p) {
                p = dir;
            }

            /*
             * breve descrição do que
             * está acontecendo abaixo
             * */
            aux = registrosQuick_[dir];
            registrosQuick_[dir] = registrosQuick_[esq];
            registrosQuick_[esq] = aux;
        }
        esq++;
        dir--;
    }

    return p + 1;

}

//TODO: documentar os blocos funcionais e variáveis dentro do método
void DataFrameLivros::quickSort(int pos_ini, int pos_fim) {
    /*
     * breve descrição do que
     * está acontecendo abaixo
     * */
    if (pos_fim - pos_ini > 0) {
        int q = particionamentoQuick(pos_ini, pos_fim);
        quickSort(pos_ini, q - 1);
        quickSort(q, pos_fim);
    }
}

//TODO: documentar os blocos funcionais e variáveis dentro do método
void DataFrameLivros::ordenar(AlgOrdenacao algoritmoOrd, ChavesOrdenacao chave, bool imprimeMetricas) {
//    chaveOrd_ = chave; não está sendo usada no momento
    switch (algoritmoOrd) {
        case AlgOrdenacao::quicksort:
            registrosQuick_ = new Registro[numLinhas_];  //question: mover para o construtor?
            //TODO: criar uma função para fazer essa cópia de registros_
            for (int i = 0; i < numLinhas_; i++)
                registrosQuick_[i] = registros_[i];
            quickSort(0, numLinhas_ - 1);
            break;
        case AlgOrdenacao::heapsort:
            registrosHeap_ = new Registro[numLinhas_];  //question: mover para o construtor?
            //TODO: criar uma função para fazer essa cópia de registros_
            for (int i = 0; i < numLinhas_; i++)
                registrosHeap_[i] = registros_[i];
            heapSort(registrosHeap_, numLinhas_);
            break;
    }
}

//TODO: (//FW) - função para escrever o dataset processado em um csv
//question: vamos precisar para esse trabalho?
void DataFrameLivros::escreverCsv(string nomeArquivo) {}

void DataFrameLivros::setRegistros(Registro *registros) {
    registros_ = registros;
}

//TODO: documentar os blocos funcionais e variáveis dentro do método
void DataFrameLivros::heapMax(Registro *registrosHeap, int raiz, int n) {
    //descrever o que é essa variável
    int filho_esq = 2 * raiz + 1;

    //descrever o que é essa variável
    int filho_dir = 2 * raiz + 2;

    //descrever o que é essa variável
    int m;

    /*
     * breve descrição do que
     * está acontecendo abaixo
     * */
    if ((filho_esq < n) and (registrosHeap[filho_esq].getTitulo() > registrosHeap[raiz].getTitulo())) {
        contComparacoesHeap_ = contComparacoesHeap_ + 1;
        m = filho_esq;
    } else {
        //descrição aqui
        m = raiz;
    }
    if ((filho_dir < n) and (registrosHeap[filho_dir].getTitulo() > registrosHeap[m].getTitulo())) {
        //descrição aqui
        contComparacoesHeap_ = contComparacoesHeap_ + 1;
        m = filho_dir;
    }
    if (m != raiz) {
        /*
         * breve descrição do que
         * está acontecendo abaixo
         * */
        contTrocasHeap_ = contTrocasHeap_ + 1;
        Registro aux = registrosHeap[raiz];
        registrosHeap[raiz] = registrosHeap[m];
        registrosHeap[m] = aux;
        heapMax(registrosHeap, m, n);
    }
}

//TODO: documentar os blocos funcionais e variáveis dentro do método
void DataFrameLivros::criaHeap(Registro *registrosHeap, int n) {
    /*
     * breve descrição do que
     * está acontecendo abaixo
     * */
    for (int i = (n / 2) - 1; i >= 0; i--) {
        heapMax(registrosHeap, i, n);
    }
}

//TODO: documentar os blocos funcionais e variáveis dentro do método
void DataFrameLivros::heapSort(Registro *registrosHeap, int n) {
    /*
     * breve descrição do que
     * está acontecendo abaixo
     * */
    criaHeap(registrosHeap, n);
    for (int i = n - 1; i >= 0; i--) {
        contTrocasHeap_ = contTrocasHeap_ + 1;
        /*
         * breve descrição do que
         * está acontecendo abaixo
         * */
        Registro aux = registrosHeap[i];
        registrosHeap[i] = registrosHeap[0];
        registrosHeap[0] = aux;
        heapMax(registrosHeap, 0, i);
    }
}
//TODO: para deixar o código mais organizado e mais flexível podemos criar a função abaixo que retorna um campo
// do vetor correspondende, precisando passar apenas o indice do registro como argumento
/*
template<typename TipoCampo>
TipoCampo DataFrameLivros::getCampoChave(int indiceRegistro) {
    TipoCampo campo;
    if (chaveOrd_ == ChavesOrdenacao::titulo){
        //retornar o campo titulo do vetor especifico
    }
    if(chaveOrd_ == ChavesOrdenacao::id){
        //retornar o campo id do vetor especifico
    }
    .
    .
    .
}
*/