#include <iostream>
#include <fstream>
#include <random>
#include <cassert>
#include "../include/DataFrameLivros.hpp"
#include "../include/csvLivros.hpp"
#include "../include/secao_2/HashRegistro.hpp"
#include "../include/secao_2/Primo.hpp"
#include "../include/secao_3/AVP.hpp"

#define ITER 5  // número de iterações por algoritmo de ordenação
#define ORD_ALGS 2 // número de algoritmos de ordenação que serão testados

using namespace std;

void calcularMetricas(int x, int *n, const string& pathSecao, const string& arquivo);

unsigned gerarRandomSeed();

void secao1(const string& dataset);

void secao2(const string& dataset);

void secao3(const string& dataset);

int main(int argc, char **argv, char **argp) {
    string dataset;

    dataset = "../dataset/dataset_simp_sem_descricao.csv"; //caminho padrão dataset

    // se for passado o nome do dataset por parametro
    if (argc > 1)
        dataset = "../dataset/" + (string) argv[1];

    //TODO: Criar menu interativo aqui

    Primo::criarTabela(1000000); // escolher o melhor tamanho
//  secao1(dataset);
    secao2(dataset);
//  secao3(dataset);

    return 0;
}

// ------------------------- Etapa 1 ------------------------- //

void secao1(const string& dataset) {
    int x;  // Número de iterações (n)
    int *n = nullptr;  // vetor para armazenar os valores de n (qt. de registros) lidos de "entrada.txt"
    unsigned seed;  // semente de randomização
    DataFrameLivros dfLivros;  //instancia de dfLivros

    const string PATH_SECAO = "../io/secao_1/";
    const string ARQ_ENTRADA = "entrada.txt";
    const string ARQ_SAIDA = "saida.txt";

    // obtendo os parâmetros de entrada
    txt::lerEntrada(&x, n, PATH_SECAO + ARQ_ENTRADA);

    //remove o arquivo de saida, se existir
    remove((PATH_SECAO + ARQ_SAIDA).c_str());

    for (int i = 0; i < x; i++) {
        for (int j = 0; j < ITER; j++) {
            seed = gerarRandomSeed();

            // lê o csv e salva n[i] registros aleatórios
            dfLivros.lerCsv(dataset, n[i], true, seed, ED::VETOR);
            if (j == 0) cout << n[i] << " registros aleatorios carregados." << endl;
            // Faz as ordenações e imprime métricas

            //chama algoritmo de Ordenação Quicksort
            dfLivros.ordenar(AlgOrdenacao::QUICKSORT, PATH_SECAO + ARQ_SAIDA);

            //chama algoritmo de Ordenação HeapSort
            dfLivros.ordenar(AlgOrdenacao::HEAPSORT, PATH_SECAO + ARQ_SAIDA);

        }
    }

    cout << "As estatisticas foram salvas no arquivo de saida." << endl;

    //calculando métricas
    calcularMetricas(x, n, PATH_SECAO, ARQ_SAIDA);

    delete[] n;
}

// ------------------------- Etapa 2 ------------------------- //

void secao2(const string& dataset) {
    cout << "secao2" << endl;
    int N, M;
    DataFrameLivros dfLivros;  //instancia de dfLivros
    unsigned seed;  // semente de randomização
    const string PATH_SECAO = "../io/secao_2/";
    const string ARQ_SAIDA = "saida.txt";
    const int tamArqAutores = 243700;



    //remove o arquivo de saida, se existir
    remove((PATH_SECAO + ARQ_SAIDA).c_str());

    N = 10;  //deverá ser lido da entrada
    M = 5;  //deverá ser lido da entrada

    HashAutor auxAutores(tamArqAutores);


    seed = 3202200755;
    seed = gerarRandomSeed();
    cout << "seed = " << seed << endl;

    Registro *r;
    r = new Registro[10];

    HashRegistro h(10);
    for (int i = 0; i < 14; i++) {
        r[i].setId(12345678912 + i * i);
        h.inserir(&r[i]);
    }
    cout << h.buscar(12345678913) << endl;



    // lê o csv e salva n[i] registros aleatórios e distintos
    // dfLivros.lerCsv(dataset, N, true, seed, true);

    csv::lerAutores("../dataset/authors.csv");

//    auxAutores.inserir(new Autor("Nome Teste", 234));
//    cout << h.busca("Nome Teste");
}

// ------------------------- Etapa 3 ------------------------- //
void secao3(const string& dataset) {
    int N;
    DataFrameLivros dfLivros;  //instancia de dfLivros
    unsigned seed;  // semente de randomização

    const string PATH_SECAO = "../io/secao_3/";
    const string ARQ_SAIDA_BUSCA = "saidaBusca.txt";
    const string ARQ_SAIDA_INSERCAO = "saidaInsercao.txt";
    const string ARQ_ENTRADA = "entrada.txt";

    //Copie e cole o código da seção 1 para calcular as métricas e gerar as 5 amostras aleatorias para cada N
    seed = gerarRandomSeed();
    dfLivros.lerCsv(dataset, N, true, seed, ED::ARVORE);

    /* //Testes da VP
    int i;
    AVP *arvoreVP = new AVP();

    for (i = 12; i >= 0; i--) {
//    for (i = 0; i < 12; i++) {
        int x = rand() % 10;
//        int x = i;
        cout << "Inserindo " << x << " -> " << endl << endl;
        arvoreVP->insere(x);
        arvoreVP->imprimeAVP();
    }

    bool achou = arvoreVP->busca(2);
    cout << endl << endl;
    cout << "Achou? -> ";
    cout << achou << endl;

    cout << "Qtd Comparacoes : " << arvoreVP->getQtdComparacoes() << endl;

    cout << "Qtd Trocas" << arvoreVP->getQtdTrocas() << endl;

    delete arvoreVP;
    */
}


// ------------------- Funções auxiliares -------------------- //
void calcularMetricas(const int x, int *n, const string& pathSecao, const string& arquivo) {
    double somaQuick, somaHeap;
    auto *stats = new Stats[x * ITER * ORD_ALGS]; // x * 5 iter * 2 algs. ord.
    // lê o arquivo de saida e armazena em um vetor de Stats de tamanho x * ITER * ORD_ALGS
    txt::lerSaida(stats, pathSecao + arquivo);

    // itera sobre as métricas armazenadas no enum metricas
    for (int m = Stats::metricas::_comp; m <= Stats::metricas::_tempo; m++) {
        string statsNome = m == 0 ? "comp" : (m == 2 ? "tempo" : "trocas");
        ofstream arqStats(pathSecao + "stats/stats_" + statsNome + ".txt");

        assert(arqStats.is_open() && arqStats.good());// teste do arquivo

        somaQuick = 0;
        somaHeap = 0;
        for (int i = 0, j = 0; i < x * ITER * ORD_ALGS;) {
            if (stats[i].alg == 'Q' && stats[i].n == n[j]) {
                somaQuick += stats[i].getStats(m);
            }
            if (stats[i].alg == 'H' && stats[i].n == n[j]) {
                somaHeap += stats[i].getStats(m);
            }
            i++;
            if (i % (ITER * 2) == 0) {
                arqStats << n[j] << "\t" << somaQuick / ITER << "\t" << somaHeap / ITER << "\t" << endl;
                somaQuick = 0;
                somaHeap = 0;
                j++;
            }
        }
        arqStats.close();
    }

    delete[] stats;
}

unsigned gerarRandomSeed() {
    random_device myRandomDevice; //para gerar a semente de randomização
    return myRandomDevice(); //retorna um seed aleatorio
}