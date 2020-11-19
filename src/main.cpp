#include <iostream>
#include <fstream>
#include <random>
#include <cassert>
#include "../include/DataFrameLivros.hpp"
#include "../include/csvLivros.hpp"
#include "../include/secao_2/HashRegistro.hpp"
#include "../include/secao_2/Primo.hpp"

#define ITER 5  // número de iterações por algoritmo de ordenação
#define ORD_ALGS 2 // número de algoritmos de ordenação que serão testados

using namespace std;

void calcularMetricas(const int x, int *n, string pathSecao, string arquivo);

unsigned gerarRandomSeed();

void secao1(string dataset);

void secao2(string dataset);

void secao3(string dataset);

int main(int argc, char **argv, char **argp) {
    string dataset;

    dataset = "../dataset/dataset_simp_sem_descricao.csv"; //caminho padrão dataset

    // se for passado o nome do dataset por parametro
    if (argc > 1)
        dataset = "../dataset/" + (string) argv[1];

    //TODO: Criar menu interativo aqui

//    secao1(dataset);
    secao2(dataset);
//    secao3(dataset);

    return 0;
}

// ------------------------- Etapa 1 ------------------------- //

void secao1(string dataset) {
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
            dfLivros.lerCsv(dataset, n[i], true, seed, true);
            if (j == 0) cout << n[i] << " registros aleatorios carregados." << endl;
            // Faz as ordenações e imprime métricas

            //chama algoritmo de Ordenação Quicksort
            dfLivros.ordenar(AlgOrdenacao::quicksort, PATH_SECAO + ARQ_SAIDA);

            //chama algoritmo de Ordenação HeapSort
            dfLivros.ordenar(AlgOrdenacao::heapsort, PATH_SECAO + ARQ_SAIDA);

        }
    }

    cout << "As estatisticas foram salvas no arquivo de saida." << endl;

    //calculando métricas
    calcularMetricas(x, n, PATH_SECAO, ARQ_SAIDA);

    delete[] n;
}

// ------------------------- Etapa 2 ------------------------- //

void secao2(string dataset) {
    int N, M;
    DataFrameLivros dfLivros;  //instancia de dfLivros
    unsigned seed;  // semente de randomização
    const string PATH_SECAO = "../io/secao_2/";
    const string ARQ_SAIDA = "saida.txt";

    //remove o arquivo de saida, se existir
    remove((PATH_SECAO + ARQ_SAIDA).c_str());

    N = 50000;
    M = 10;
    Primo::criarTabela(N);

    seed = gerarRandomSeed();
    /*
    Registro *r;
    r = new Registro[10];
    HashRegistro h(10);
    for (int i = 0; i < 14; i++) {
        r[i].setId(12345678912 + i * i);
        h.inserir(&r[i]);
    }
    cout << h.buscar(12345678913) << endl;
    */

    // lê o csv e salva n[i] registros aleatórios e distintos
    dfLivros.lerCsv(dataset, N, true, seed, true);

//    csv::lerAutores("../dataset/authors.csv");

//    cout << "Digite o valor de N: "; cin >> N;
//    cout << "Digite o valor de M: "; cin >> M;

//    Hash h(20);
//    h.inserir(new Autor("Nome Teste", 234));
//    h.buscar(234);
}

// ------------------------- Etapa 3 ------------------------- //


// ------------------- Funções auxiliares -------------------- //
void calcularMetricas(const int x, int *n, string pathSecao, string arquivo) {
    double somaQuick, somaHeap;
    auto *stats = new Stats[x * ITER * ORD_ALGS]; // x * 5 iter * 2 algs. ord.
    // lê o arquivo de saida e armazena em um vetor de Stats de tamanho x * ITER * ORD_ALGS
    txt::lerSaida(stats, pathSecao+arquivo);

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