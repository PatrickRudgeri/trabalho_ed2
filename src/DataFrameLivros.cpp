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
/*
 * A função QuickSort implementada incorpora as seguintes funcionalidades
 *
 * 1. A função de particionamentoQuick, responsável por pegar uma sequência de entrada
 *    registrosQuick_ e dividi-la em duas partes. Para isto, é escolhido uma posição
 *    denominada pivô. Desta forma, a parte da esquerda possui chaves menores ou iguais
 *    ao pivô, e a parte direita com chaves maiores ou iguais ao pivô.
 *
 * 2. A escolha do pivô influencia no desempenho do método. Nesta implementação utilizou-se
 *    o valor mediano entre o primeiro, do último e do meio elemento do vetor. A vantagem
 *    é sua simplicidade de codificação, rápido de calcular e pode ajudar
 *    a evitar a pegar valores extremos. Todavia, o custo ainda pode degradar para O(n2)
 */
int DataFrameLivros::particionamentoQuick(int pos_ini, int pos_fim) {
    //variável pontoMedio recebe a posição localizada no meio do vetor
    int pontoMedio = (pos_ini + pos_fim) / 2;

    //variável do tipo Registro que recebe o primeiro registro
    Registro primeiraPosicao = registrosQuick_[pos_ini];
    //variável do tipo Registro que recebe o registro do meio
    Registro meioPosicao = registrosQuick_[pontoMedio];
    //variável variável do tipo Registro que recebe o último registro
    Registro UltimaPosicao = registrosQuick_[pos_fim];

    //variável para calcular a media das três posições: primeira,meio,última
    int mediaDeTres;

    /*
     *  Abaixo é feito o calculo da média utilizando os valores entre o primeiro, do último e do meio.
     *
     */
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

    //variavel pivo é o elemento central da minha entrada de dados
    string pivo;

    //a variável pivo recebe o titulo localizado no indice mediaDeTres de registrosQuick_

    //pivo = registrosQuick_[p].getTitulo();
    pivo = registrosQuick_[mediaDeTres].getTitulo();
    int esq = pos_ini;
    int dir = pos_fim;

    //Variável auxiliar do tipo Registro para armazenar as trocas de posições
    Registro aux;

    /*
     *  A primeira partição é percorrida da esquerda para direita enquanto o elemento no indice < pivô
     *
     *  A segunda partição  é percorrida da direita para esquerda enquanto o elemento no indice > pivo
     *
     */
    while (esq < dir) {
        contTrocasQuick_++; //question: contabiliza trocas aqui? para mim seria abaixo
        while (registrosQuick_[esq].getTitulo() < pivo) {
            contComparacoesQuick_++;
            esq++;
        }

        while (registrosQuick_[dir].getTitulo() > pivo) {
            contComparacoesQuick_++;
            dir--;
        }
        if (esq <= dir) {
            if (dir == pontoMedio) {
                pontoMedio = esq; //question: vai contabilizar essas comparações? acredito que não porque não está comparando chaves.
            }
            if (esq == pontoMedio) {
                pontoMedio = dir;
            }

            /*
             * Abaixo realizamos as trocas de dados entre duas posições no vetor
             * */

            //question: para mim, contTrocasQuick_ seria aqui e seriam 3 trocas (movimentação de dados)
            aux = registrosQuick_[dir];
            registrosQuick_[dir] = registrosQuick_[esq];
            registrosQuick_[esq] = aux;
        }
        esq++;
        dir--;
    }

    return pontoMedio + 1;

}

//TODO: documentar os blocos funcionais e variáveis dentro do método
void DataFrameLivros::quickSort(int pos_ini, int pos_fim) {
    /*
     *  O Quick Sort é a execução de consectivos particionamentos.
     *  Efetua-se o primeiro levando em consideração o array inteiro (posição inicial = 0 e posição final = tamanho do Vetor - 1).
     *  Depois, leva-se em consideração a esquerda do pivo, ou seja, posição inicial = 0 e posição final = pivo - 1
     *  e à direita do pivo (left = pivo + 1 e right = values.length - 1). Adiante, o mesmo processo
     *  é feito com a esquerda e a direita dos novos pivos em chamada recursivas até que
     *  array inteiro já tenha sido percorrido (esquerda >= direita).
     *
     * */
    if (pos_fim - pos_ini > 0) {
        int q = particionamentoQuick(pos_ini, pos_fim); //realiza a partição
        quickSort(pos_ini, q - 1); //ordena a partição esquerda
        quickSort(q, pos_fim); //ordena a partição direita
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


    /*
     *  O método heapMax implementa um algoritmo Heap de Máximo. Construímos uma árvore binária completa
     *  de n nós tal que a chave de cada nó seja menor ou igual à chave de seu pai.
     *  Cada nó da arvore corresponde um elemento do array.
     *  O heap é acessado da seguinte maneira.
     *  Dado um elemento e na localização i:
     *  o nó filho esquerdo de e está em 2 * i + 1.
     *  o nó filho direito de e está em 2 * i + 2.
     *
     */
//TODO: documentar os blocos funcionais e variáveis dentro do método
void DataFrameLivros::heapMax(Registro *registrosHeap, int raiz, int n) {


    //Variável que representa a posição do filho a esquerda
    int filho_esq = 2 * raiz + 1;

    //Variável que representa a posição do filho a direita
    int filho_dir = 2 * raiz + 2;

    //Variavel que recebe o maior entre os nós
    int maior; //question: seria do tipo inteiro ou do tipo string?

    /*
     * Percorre a árvore para baixo começando na raiz, recupera quais são os nós filhos da esquerda e
     * da direita em chamadas recursivas até que se chegue no fim da árvore.
     * Se o nó pai é maior ou igual que seus filhos então não é preciso fazer nada.
     * Se não, troque o pai com o maior dos filhos e repita o processo para o filho envolvido na troca.
     *
     * */
    if ((filho_esq < n) and (registrosHeap[filho_esq].getTitulo() > registrosHeap[raiz].getTitulo())) {
        contComparacoesHeap_ = contComparacoesHeap_ + 1;
        //o nó a esquerda é maior que o nó pai
        maior = filho_esq;
    } else {
        //caso em que nó pai é maior ou igual que seus filhos
        maior = raiz;
    }
    if ((filho_dir < n) and (registrosHeap[filho_dir].getTitulo() > registrosHeap[maior].getTitulo())) {
        //o nó a direita é maior que o nó pai
        contComparacoesHeap_ = contComparacoesHeap_ + 1;
        maior = filho_dir;
    }
    if (maior != raiz) {
        /*
         * Se maior não é o pai, então troque o pai com o maior dos filhos
         * e repita o processo para o filho envolvido na troca
         *
         */
        contTrocasHeap_ = contTrocasHeap_ + 1;
        Registro aux = registrosHeap[raiz];
        registrosHeap[raiz] = registrosHeap[maior];
        registrosHeap[maior] = aux;
        heapMax(registrosHeap, maior, n);
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