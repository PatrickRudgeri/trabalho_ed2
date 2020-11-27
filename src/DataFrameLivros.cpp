#include "../include/DataFrameLivros.hpp"
#include "../include/csvLivros.hpp"
#include <chrono>
#include <fstream>
#include <cassert>

using namespace std;
using namespace std::chrono;

// --------------- Construtores e Destrutores ---------------- //

DataFrameLivros::DataFrameLivros() {
    inicializarAtributos();
}

DataFrameLivros::DataFrameLivros(std::string pathSaida, ED armazInterno) {
    //Inicializando atributos
    inicializarAtributos();
    armazInterno_ = armazInterno;
    saidaOrdenacao_ = pathSaida;
}

DataFrameLivros::DataFrameLivros(std::string pathSaidaInsercao, std::string pathSaidaBusca, ED armazInterno) {
    //Inicializando atributos
    inicializarAtributos();
    armazInterno_ = armazInterno;
    saidaInsercao_ = pathSaidaInsercao;
    saidaBusca_ = pathSaidaBusca;
}

DataFrameLivros::~DataFrameLivros() {
    //liberando o espaço alocado pelos vetores
    delete[] registros_;
    delete[] registrosQuick_;
    delete[] registrosHeap_;
    delete hashRegistros_;
    delete hashAutores_;
    delete arvoreVP_;
    delete arvoreB_;
}

// ----------------------- Sets e Gets ----------------------- //

Registro *DataFrameLivros::getRegistros() {
    return registros_;
}

void DataFrameLivros::setRegistros(Registro *registros) {
    registros_ = registros;
}

void DataFrameLivros::setPathSaida(std::string saidaInsercao, std::string saidaBusca) {
    saidaInsercao_ = saidaInsercao;
    saidaBusca_ = saidaBusca;
}

void DataFrameLivros::setPathSaida(std::string pathSaida) {
    saidaOrdenacao_ = pathSaida;
}

void DataFrameLivros::setArmazInterno(ED armazInterno) {
    armazInterno_ = armazInterno;
}

// ------------------- Funções auxiliares -------------------- //

void DataFrameLivros::inicializarAtributos() {
    registros_ = nullptr;
    registrosHeap_ = nullptr;
    registrosQuick_ = nullptr;
    hashRegistros_ = nullptr;
    hashAutores_ = nullptr;
    numRegistros_ = 0;
    countTotalAutores_ = 0;
    arvoreVP_ = nullptr;
    arvoreB_ = nullptr;
    armazInterno_ = ED::VETOR;
}

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

void DataFrameLivros::lerCsv(const std::string &pathDataset, int numLinhas, bool aleatorio, unsigned int seed) {
    numRegistros_ = numLinhas;
    seed_ = seed;


    // se a ED interna é hash table então aloca a tabela hash
    if (armazInterno_ == ED::HASH_TABLE) {

        hashRegistros_ = new HashRegistro(numRegistros_);

    } else if (armazInterno_ == ED::VETOR) {
        metricasOrdenacao_[0].n = numRegistros_;
        metricasOrdenacao_[0].seed = seed_;
        metricasOrdenacao_[1].n = numRegistros_;
        metricasOrdenacao_[1].seed = seed_;
        // se ED interna é vetor aloca um vetor de Registros de tamanho `numLinhas`
        registros_ = new Registro[numRegistros_];

    } else if (armazInterno_ == ED::ARVORE) {
        metricasArvInsercao_[0].n = numRegistros_;
        metricasArvInsercao_[0].seed = seed_;
        metricasArvInsercao_[0].tempo = 0.0;
        metricasArvInsercao_[1].tempo = 0.0;
        arvoreVP_ = new AVP();
//        arvoreB_ = new ArvoreB();
    }
    //preenche o data frame com os valores lidos do csv
    csv::lerRegistros(this, pathDataset, numLinhas, aleatorio, seed);

    if (armazInterno_ == ED::HASH_TABLE) {
        //Com o dataframe, hashRegistros_ e a quantidade de autores preenchidos, podemos criar a hash de autores

        hashAutores_ = new HashAutor(countTotalAutores_);
//        int tamHashRegistros;
//        Registro *registrosTable;
//        int *autoresIds;
//        int qtAutores;
//
//        tamHashRegistros = Primo::proxPrimo(numRegistros_);
//        registrosTable = hashRegistros_->getTabelaRegistros();
//
//        for (int i = 0; i < tamHashRegistros; i++) {
        // se é uma posição vazia, então passa para a proxima posição
//            cout << registrosTable[i].getId() << endl;//fixme: debug
//            if (registrosTable[i].getId() == -1) continue;
//
//            Registro reg = registrosTable[i];
//            autoresIds = reg.getAutores();
//            qtAutores = reg.getQtAutores();
//            cout << reg.getQtAutores() << endl; //fixme: debug
//            for (int j = 0; j < qtAutores; j++) {
//                int autorId = autoresIds[j];
//                if(autorId != -1) {
//                    auto *autor = new Autor();
//                    autor->setId(autorId);
//                    cout << autor->getId() << endl; //fixme: debug
////                    hashAutores_->inserir(autor);
//                    delete autor;
//                }
//            }
//        }
        //TODO: Dentro dessa função, percorrer csv e adicionar nome dos autores da tabela hash
//        csv::lerAutores("../dataset/authors.csv", hashAutores_);
    } else if (armazInterno_ == ED::ARVORE) {
        //Obtendo as quantidades de comparações e trocas realizadas pelas arvores
        metricasArvInsercao_[0].alg = 'V';
        metricasArvInsercao_[0].comp = arvoreVP_->getCompInsercao();
        metricasArvInsercao_[0].trocas = arvoreVP_->getTrocasInsercao();

//        metricasArvInsercao_[1].alg = 'B';
//        metricasArvInsercao_[1].comp  = arvoreB_->getCompInsercao();
//        metricasArvInsercao_[1].trocas = arvoreB_->getTrocasInsercao();

        // ofstreams para concatenar as métricas nos arquivos de saida
        ofstream outInsercao(saidaInsercao_, ios::app);
        assert(outInsercao.is_open());//se arquivo não estiver aberto interrompe a execução

        outInsercao << metricasArvInsercao_[0];
//        outInsercao << metricasArvInsercao_[1];
        outInsercao.close();
    }
}

bool DataFrameLivros::inserirRegistro(std::string *camposStrVet, int index) {
    high_resolution_clock::time_point inicioInsercao, fimInsercao;
    bool statusInsercao;
    if (armazInterno_ == ED::HASH_TABLE) {
        auto *reg = new Registro();
        reg->setTodosAtributosStr(camposStrVet);

        // será true se registro é unico, ou false se 'repetido
        statusInsercao = hashRegistros_->buscar(reg->getId()) == -1;

        //se for livro único então inserir na tabela hash de registros, busca e os autores na tabela hash de autores
        if (statusInsercao) {
            countTotalAutores_ += reg->getQtAutores();
            hashRegistros_->inserir(reg);
        }


    } else if (armazInterno_ == ED::VETOR && index >= 0 && index < numRegistros_) {

        registros_[index].setTodosAtributosStr(camposStrVet);
        statusInsercao = true;

    } else if (armazInterno_ == ED::ARVORE) {
        // cria um novo registro
        Registro reg;
        reg.setTodosAtributosStr(camposStrVet); // preenche o obj Registro

        //Inserindo na arvore VP e medindo tempo
        inicioInsercao = high_resolution_clock::now();
        arvoreVP_->insere(&reg);
        fimInsercao = high_resolution_clock::now();
        metricasArvInsercao_[0].tempo += duration_cast<duration<double>>(fimInsercao - inicioInsercao).count();

//        Inserindo na arvore B e medindo tempo
//        inicioInsercao = high_resolution_clock::now();
//        arvoreB_->insere(&reg);
//        fimInsercao = high_resolution_clock::now();
//        metricasArvInsercao_[1].tempo += duration_cast<duration<double>>(fimInsercao - inicioInsercao).count();

        statusInsercao = true; //se inserção na arvore deu tudo ok
    } else {
        cout << "Erro de index ou armazenamento não implementado na função DataFrameLivros::inserirRegistro()";
        exit(-1);
    }
    return statusInsercao; //se é hashTable, tenta inserir , se já existir retorna falso, caso contrario true;
}


void DataFrameLivros::ordenar(AlgOrdenacao algoritmoOrd) {
    high_resolution_clock::time_point inicio, fim;
    //zerando contadores
    metricasOrdenacao_[0].trocas = 0;
    metricasOrdenacao_[0].comp = 0;
    metricasOrdenacao_[1].trocas = 0;
    metricasOrdenacao_[1].comp = 0;

    // ofstream para concatenar as métricas no arquivo de saida
    ofstream outStream(saidaOrdenacao_, ios::app);
    assert(outStream.is_open());//se arquivo não estiver aberto interrompe a execução

    // Faz a alocação dos vetores que serão ordenados (cópias de registros_)
    // Executa o método de ordenação escolhido em algoritmoOrd
    if (algoritmoOrd == AlgOrdenacao::QUICKSORT) {
        registrosQuick_ = new Registro[numRegistros_];
        /**
         * para deixar o original intacto e armazenar cada ordenação em seu respectivo array, o vetor registros_ é copiado
         *   para registrosQuick_
         */
        copiarRegistros(registros_, registrosQuick_, numRegistros_);

        inicio = high_resolution_clock::now();
        quickSort(0, numRegistros_ - 1);
        fim = high_resolution_clock::now();

        //métricas:
        metricasOrdenacao_[0].alg = 'Q';
        //salva no arquivo de saida o tempo de execução do algoritmo
        metricasOrdenacao_[0].tempo = duration_cast<duration<double>>(fim - inicio).count();
        outStream << metricasOrdenacao_[0];
    }
    if (algoritmoOrd == AlgOrdenacao::HEAPSORT) {
        registrosHeap_ = new Registro[numRegistros_];
        /**
         * para deixar o original intacto e armazenar cada ordenação em seu respectivo array, o vetor registros_ é copiado
         *   para registrosHeap_
         */
        copiarRegistros(registros_, registrosHeap_, numRegistros_);

        inicio = high_resolution_clock::now();
        heapSort(registrosHeap_, numRegistros_);
        fim = high_resolution_clock::now();

        //métricas:
        metricasOrdenacao_[1].alg = 'H';
        //salva no arquivo de saida o tempo de execução do algoritmo
        metricasOrdenacao_[1].tempo = duration_cast<duration<double>>(fim - inicio).count();
        outStream << metricasOrdenacao_[1];
    }


    outStream.close();
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
    int pivo;

    //a variável pivo recebe o titulo localizado no indice mediaDeTres de registrosQuick_
    pivo = mediaDeTres;
    int esq = posIni;
    int dir = posFim;

    //Variável auxiliar para armazenar as trocas de posições

    /**
     *  A primeira partição é percorrida da esquerda para direita enquanto o elemento no indice < pivô
     *
     *  A segunda partição  é percorrida da direita para esquerda enquanto o elemento no indice > pivo
     */
    while (esq < dir) {
        while (registrosQuick_[esq].getTitulo() < registrosQuick_[pivo].getTitulo()) {
            metricasOrdenacao_[0].comp++;
            esq++;
        }

        while (registrosQuick_[dir].getTitulo() > registrosQuick_[pivo].getTitulo()) {
            metricasOrdenacao_[0].comp++;
            dir--;
        }
        if (esq <= dir) {
            //Abaixo é realizado as trocas de dados entre duas posições no vetor
            metricasOrdenacao_[0].trocas += 3;
            Registro aux = registrosQuick_[dir];
            registrosQuick_[dir] = registrosQuick_[esq];
            registrosQuick_[esq] = aux;
        }
        esq++;
        dir--;
    }

    return dir + 1;

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
    if (posIni < posFim) {
        int q = particionamentoQuick(posIni, posFim); //realiza a partição
        quickSort(posIni, q - 1); //ordena a partição esquerda
        quickSort(q + 1, posFim); //ordena a partição direita
    }
}

/**
 *  O método heapMax implementa um algoritmo Heap de Máximo. Construímos uma árvore binária completa
 *  de n nós tal que a chave de cada nó seja menor ou igual à chave de seu pai_.
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
     * Percorre a árvore para baixo começando na raiz_, recupera quais são os nós filhos da esquerda e
     * da direita em chamadas recursivas até que se chegue no fim da árvore.
     * Se o nó pai_ é maior ou igual que seus filhos então não é preciso fazer nada.
     * Se não, troque o pai_ com o maior dos filhos e repita o processo para o filho envolvido na troca.
     *
     * */
    if ((filho_esq < n) and (registrosHeap[filho_esq].getTitulo() > registrosHeap[raiz].getTitulo())) {
        metricasOrdenacao_[1].comp++;
        //Se o filho esquerdo for maior que a raiz_
        maior = filho_esq;
    } else {
        //Se não a raiz_ é maior que o filho esquerdo
        maior = raiz;
    }
    if ((filho_dir < n) and (registrosHeap[filho_dir].getTitulo() > registrosHeap[maior].getTitulo())) {
        //Se o filho direito for maior do que a maior até agora
        metricasOrdenacao_[1].comp++;
        maior = filho_dir;
    }
    if (maior != raiz) {
        /*
         * Se maior não é o pai_, então troque o pai_ com o maior dos filhos
         * e repita o processo para o filho envolvido na troca
         *
         */
        metricasOrdenacao_[1].trocas += 3;
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
        /*
         * A variável auxilar recebe o novo nó a ser inserido para realizar a troca
         * Troca-se então o item na posição 1 do vetor (raiz_ do heap) com o item da posição i
         * Use o procedimento Max-Heapify para reconstituir o heap
         * Os passos anteriores são repetidos até que reste apenas um elemento.
         *
         * */
        metricasOrdenacao_[1].trocas += 3;
        Registro aux = registrosHeap[i];
        registrosHeap[i] = registrosHeap[0];
        registrosHeap[0] = aux;
        //Chama Max Heapify com a raiz_ e o elemento inserido
        heapMax(registrosHeap, 0, i);
    }
}

// ------------------------- Árvores ------------------------- //

void DataFrameLivros::testeBuscasArv(AlgArvores arv) {
    srand(seed_);
    high_resolution_clock::time_point inicioBusca, fimBusca;

    ofstream outBusca(saidaBusca_, ios::app);
    assert(outBusca.is_open());

    if (arv == AlgArvores::VP) {

        inicioBusca = high_resolution_clock::now();
        for (int i = 0; i < numRegistros_; i++) {
            long val = rand() % 9790000000000 + 9780000000001;
            arvoreVP_->busca(val);
        }
        fimBusca = high_resolution_clock::now();

        metricasArvBusca[0].alg = 'V';
        metricasArvBusca[0].n = numRegistros_;
        metricasArvBusca[0].seed = seed_;
        metricasArvBusca[0].comp = arvoreVP_->getCompBusca();
        metricasArvBusca[0].trocas = arvoreVP_->getTrocasBusca();
        metricasArvBusca[0].tempo = duration_cast<duration<double>>(fimBusca - inicioBusca).count();
        //salvando log de métricas de buscas na Arv VP:
        outBusca << metricasArvBusca[1];
    }

    if (arv == AlgArvores::B) {
        //Ativar esse código quando Arvore B estiver ok
//        inicioBusca = high_resolution_clock::now();
//        for (int i = 0; i < numRegistros_; i++) {
//            long val = rand() % 9790000000000 + 9780000000001;
//            arvoreB_->busca(val);
//        }
//        fimBusca = high_resolution_clock::now();
//
//        metricasArvBusca[1].alg = 'B';
//        metricasArvBusca[1].n = numRegistros_;
//        metricasArvBusca[1].seed = seed_;
//        metricasArvBusca[1].comp = arvoreB_->getCompBusca(); //implementar
//        metricasArvBusca[1].trocas = arvoreB_->getTrocasBusca(); // implementar
//        metricasArvBusca[1].tempo = duration_cast<duration<double>>(fimBusca - inicioBusca).count();
//        //salvando log de métricas de buscas na Arv B:
//        outBusca << metricasArvBusca[1];
    }

    outBusca.close();
}
