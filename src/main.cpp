#include <iostream>
#include <fstream>
#include <random>
#include <cassert>
#include "../include/DataFrameLivros.hpp"

#define ITER 5  // número de iterações por algoritmo de ordenação
#define ORD_ALGS 2 // número de algoritmos de ordenação que serão testados

using namespace std;

void calcularMetricas(int x, int *n);

int main() {
    int x;  // Número de iterações (n)
    int *n = nullptr;  // vetor para armazenar os valores de n (qt. de registros) lidos de "entrada.txt"
    unsigned seed;  // semente de randomização
    random_device myRandomDevice; //para gerar a semente de randomização
    DataFrameLivros dfLivros;  //instancia de dfLivros

    const string dataset = "../dataset/dataset_simp_sem_descricao.csv";
    const char *const arqSaida = "../io/saida.txt";

    // obtendo os parâmetros de entrada
    TxtLivros::lerEntrada(&x, n);

    //remove o arquivo de saida, se existir
    remove(arqSaida);

    for (int i = 0; i < x; i++) {
        for (int j = 0; j < ITER; j++) {
            seed = myRandomDevice(); //gera um seed

            // lê o csv e salva n[i] registros aleatórios
            dfLivros.lerCsv(dataset, n[i], true, seed);
            if (j == 0) cout << n[i] << " registros aleatorios carregados." << endl;
            // Faz as ordenações e imprime métricas

            //chama algoritmo de Ordenação Quicksort
            dfLivros.ordenar(AlgOrdenacao::quicksort, arqSaida);

            //chama algoritmo de Ordenação HeapSort
            dfLivros.ordenar(AlgOrdenacao::heapsort, arqSaida);

        }
    }

    cout << "As estatisticas foram salvas no arquivo de saida." << endl;

    //calculando métricas
    calcularMetricas(x, n);

    delete[] n;

    return 0;
}
// ------------------- Funções auxiliares -------------------- //
void calcularMetricas(const int x, int *n) {
    double somaQuick, somaHeap;
    auto *stats = new Stats[x * ITER * ORD_ALGS]; // x * 5 iter * 2 algs. ord.
    // lê o arquivo de saida e armazena em um vetor de Stats de tamanho x * ITER * ORD_ALGS
    TxtLivros::lerSaida(stats);

    // itera sobre as métricas armazenadas no enum metricas
    for (int m = Stats::metricas::_comp; m <= Stats::metricas::_tempo; m++) {
        string statsNome = m == 0 ? "comp" : (m == 2 ? "tempo" : "trocas");
        ofstream arqTempo("../io/stats/stats_"+statsNome+".txt");

        assert(arqTempo.is_open() && arqTempo.good());// teste do arquivo

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
                arqTempo << n[j] << "\t" << somaQuick / ITER << "\t" << somaHeap / ITER << "\t" << endl;
                somaQuick = 0;
                somaHeap = 0;
                j++;
            }
        }
        arqTempo.close();
    }

    delete[] stats;
}