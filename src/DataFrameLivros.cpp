#include "../include/DataFrameLivros.hpp"
#include "../include/CsvLivros.hpp"
#include <chrono>

using namespace std;
using namespace std::chrono;

// --------------- Construtores e Destrutores ---------------- //

DataFrameLivros::DataFrameLivros() {
    //Inicializando atributos
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
    //liberando o espaço alocado pelos vetores
    delete[] registros_;
    delete[] registrosQuick_;
    delete[] registrosHeap_;
}

// ----------------------- Sets e Gets ----------------------- //

Registro *DataFrameLivros::getRegistros() {
    return registros_;
}

void DataFrameLivros::setRegistros(Registro *registros) {
    registros_ = registros;
}

// ------------------- Funções auxiliares -------------------- //

/**
 *  A função copiarRegistros copia o vetor original de Registros para um outro vetor
 *  @param vetorOriginal : vetor base para cópia
 *  @param vetorCopia : vetor para armazenar a cópia (de tamanho <= n)
 *  @param n : tamanho do vetor cópia
 */
void copiarRegistros(Registro *vetorOriginal, Registro *vetorCopia, int n) {
    for (int i = 0; i < n; i++) {
        vetorCopia[i] = vetorOriginal[i];
    }
}

// --------------------- Métodos públicos -------------------- //

void DataFrameLivros::lerCsv(const std::string &nomeArquivo, int numLinhas, bool aleatorio, int seed) {
    numLinhas_ = numLinhas;
    // aloca um vetor de Registros de tamanho `numLinhas`
    registros_ = new Registro[numLinhas];
    // o construtor de CsvLivros recebe um vetor de registros (vazio)
    CsvLivros csv(registros_);
    //preenche o vetor registros_ com os valores lidos do csv
    csv.lerCsv(nomeArquivo, numLinhas, aleatorio, seed);
}

void DataFrameLivros::ordenar(AlgOrdenacao algoritmoOrd, bool imprimeMetricas) {
    high_resolution_clock::time_point inicio, fim;
    // Faz a alocação dos vetores que serão ordenados (cópias de registros_)
    // Executa o método de ordenação escolhido em algoritmoOrd
    if (algoritmoOrd == AlgOrdenacao::quicksort) {
        registrosQuick_ = new Registro[numLinhas_];
        /**
         * para deixar o original intacto e armazenar cada ordenação em seu respectivo array, o vetor registros_ é copiado
         *   para registrosQuick_
         */
        copiarRegistros(registros_, registrosQuick_, numLinhas_);
        inicio = high_resolution_clock::now();
        quickSort(0, numLinhas_ - 1);

    }
    if (algoritmoOrd == AlgOrdenacao::heapsort) {
        registrosHeap_ = new Registro[numLinhas_];
        /**
         * para deixar o original intacto e armazenar cada ordenação em seu respectivo array, o vetor registros_ é copiado
         *   para registrosHeap_
         */
        copiarRegistros(registros_, registrosHeap_, numLinhas_);
        inicio = high_resolution_clock::now();
        heapSort(registrosHeap_, numLinhas_);
    }
    fim = high_resolution_clock::now();
    //salva no arquivo de saida o tempo de execução do algoritmo
    //arq << "Tempo de execucao:: "; //fixme: alterar arq para o arquivo de saida ou usar um método de "salvar saida"
    //arq << duration_cast<duration<double>>(fim - inicio).count() << " segundos" << endl;
}

// ----------------- Algorítmos de ordenação ----------------- //

/**
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
int DataFrameLivros::particionamentoQuick(int posIni, int posFim) {
    //variável pontoMedio recebe a posição localizada no meio do vetor
    int pontoMedio = (posIni + posFim) / 2;

    //variável do tipo Registro que recebe o primeiro registro
    Registro primeiraPosicao = registrosQuick_[posIni];
    //variável do tipo Registro que recebe o registro do meio
    Registro meioPosicao = registrosQuick_[pontoMedio];
    //variável variável do tipo Registro que recebe o último registro
    Registro UltimaPosicao = registrosQuick_[posFim];

    //variável para calcular a media das três posições: primeira,meio,última
    int mediaDeTres;

    // Abaixo é feito o calculo da média utilizando os valores entre o primeiro, do último e do meio.
    if (primeiraPosicao.getTitulo() < meioPosicao.getTitulo()) {
        if (primeiraPosicao.getTitulo() > UltimaPosicao.getTitulo()) {
            mediaDeTres = posIni;
        } else if (meioPosicao.getTitulo() > UltimaPosicao.getTitulo()) {
            mediaDeTres = posFim;
        } else {
            mediaDeTres = pontoMedio;
        }
    } else {
        if (primeiraPosicao.getTitulo() < UltimaPosicao.getTitulo()) {
            mediaDeTres = posIni;
        } else if (meioPosicao.getTitulo() < UltimaPosicao.getTitulo()) {
            mediaDeTres = posFim;
        } else {
            mediaDeTres = pontoMedio;
        }
    }

    //variavel pivo é o elemento central da entrada de dados
    string pivo;

    //a variável pivo recebe o titulo localizado no indice mediaDeTres de registrosQuick_
    pivo = registrosQuick_[mediaDeTres].getTitulo();
    int esq = posIni;
    int dir = posFim;

    //Variável auxiliar para armazenar as trocas de posições
    Registro aux; //question: qual o tipo correto dessa variavel?

    /**
     *  A primeira partição é percorrida da esquerda para direita enquanto o elemento no indice < pivô
     *
     *  A segunda partição  é percorrida da direita para esquerda enquanto o elemento no indice > pivo
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

            //Abaixo realizamos as trocas de dados entre duas posições no vetor

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

void DataFrameLivros::quickSort(int posIni, int posFim) {
    /**
     *  O Quick Sort é a execução de consectivos particionamentos.
     *  Efetua-se o primeiro levando em consideração o array inteiro (posição inicial = 0 e posição final = tamanho do Vetor - 1).
     *  Depois, leva-se em consideração a esquerda do pivo, ou seja, posição inicial = 0 e posição final = pivo - 1
     *  e à direita do pivo (left = pivo + 1 e right = values.length - 1). Adiante, o mesmo processo
     *  é feito com a esquerda e a direita dos novos pivos em chamada recursivas até que
     *  array inteiro já tenha sido percorrido (esquerda >= direita).
     *
     * */
    if (posFim - posIni > 0) {
        int q = particionamentoQuick(posIni, posFim); //realiza a partição
        quickSort(posIni, q - 1); //ordena a partição esquerda
        quickSort(q, posFim); //ordena a partição direita
    }
}

/**
 *  O método heapMax implementa um algoritmo Heap de Máximo. Construímos uma árvore binária completa
 *  de n nós tal que a chave de cada nó seja menor ou igual à chave de seu pai.
 *  Cada nó da arvore corresponde um elemento do array.
 *  O heap é acessado da seguinte maneira.
 *  Dado um elemento e na localização i:
 *  o nó filho esquerdo de e está em 2 * i + 1.
 *  o nó filho direito de e está em 2 * i + 2.
 */
void DataFrameLivros::heapMax(Registro *registrosHeap, int raiz, int n) {
    //Variável que representa a posição do filho a esquerda
    int filho_esq = 2 * raiz + 1;

    //Variável que representa a posição do filho a direita
    int filho_dir = 2 * raiz + 2;

    //Variavel que recebe o maior entre os nós
    int maior;

    /*
     * Percorre a árvore para baixo começando na raiz, recupera quais são os nós filhos da esquerda e
     * da direita em chamadas recursivas até que se chegue no fim da árvore.
     * Se o nó pai é maior ou igual que seus filhos então não é preciso fazer nada.
     * Se não, troque o pai com o maior dos filhos e repita o processo para o filho envolvido na troca.
     *
     * */
    if ((filho_esq < n) and (registrosHeap[filho_esq].getTitulo() > registrosHeap[raiz].getTitulo())) {
        contComparacoesHeap_ = contComparacoesHeap_ + 1;
        //Se o filho esquerdo for maior que a raiz
        maior = filho_esq;
    } else {
        //Se não a raiz é maior que o filho esquerdo
        maior = raiz;
    }
    if ((filho_dir < n) and (registrosHeap[filho_dir].getTitulo() > registrosHeap[maior].getTitulo())) {
        //Se o filho direito for maior do que a maior até agora
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
        //Montar recursivamente a subárvore afetada
        heapMax(registrosHeap, maior, n);
    }
}

void DataFrameLivros::criaHeap(Registro *registrosHeap, int n) {
    /**
     * Constrói um heap com o elemento máximo no índice 0, com uma árvore binária e satisfazendo
     * repetidamente a invariante Heap-Máximo
     * */
    for (int i = (n / 2) - 1; i >= 0; i--) {
        heapMax(registrosHeap, i, n);
    }
}

void DataFrameLivros::heapSort(Registro *registrosHeap, int n) {

    //Constrói a Heap
    criaHeap(registrosHeap, n);

    //Extraia um elemento do Heap um por um
    for (int i = n - 1; i >= 0; i--) {
        contTrocasHeap_ = contTrocasHeap_ + 1;
        /*
         * A variável auxilar recebe o novo nó a ser inserido para realizar a troca
         * Troca-se então o item na posição 1 do vetor (raiz do heap) com o item da posição i
         * Use o procedimento Max-Heapify para reconstituir o heap
         * Os passos anteriores são repetidos até que reste apenas um elemento.
         *
         * */
        Registro aux = registrosHeap[i];
        registrosHeap[i] = registrosHeap[0];
        registrosHeap[0] = aux;
        //Chama Max Heapify com a raiz e o elemento inserido
        heapMax(registrosHeap, 0, i);
    }
}