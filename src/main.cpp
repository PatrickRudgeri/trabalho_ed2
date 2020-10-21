#include <iostream>
#include <chrono>
#include "../include/DataFrameLivros.hpp"
#include "../include/TxtLivros.hpp"
//#include "../include/CsvLivros.hpp"

using namespace std;

int main() {
    int x;      // Número de iterações (n)
    int *n = nullptr;     // vetor para armazenar os valores de n (qt. de registros) lidos de "entrada.txt"
    int seed;   // semente de randomização
    DataFrameLivros dfLivros;
    string nomeDataset,
            nomeDatasetTeste,
            nomeDatasetOriginal,
            path;

    path = "../dataset/";
    nomeDataset = "dataset_simp_sem_descricao.csv";

    nomeDatasetOriginal = path + nomeDataset;
    nomeDatasetTeste = path + "std_" + nomeDataset;

    //corrige erros, salva em um novo csv e retorna o nome
//    CsvLivros csv;
//    nomeDataset = csv.padronizarCsv(path+"std_"+nomeDataset); // TODO: mover para CsvLivros::lerCsv

    // obtendo os parâmetros de entrada
    TxtLivros::lerEntrada(&x, n);
///*
    //utilizar o codigo comentado abaixo quando tudo já estiver funcional
    for (int i = 0; i < x; i++) {
        //segundo a descrição do trabalho:
        //  "Para cada valor de N, você deve gerar 5 (cinco) conjuntos de elementos diferentes, utilizando sementes
        //   diferentes para o gerador de números aleatórios."
        for (int j = 0; j < 5; j++) {
            seed = j; //utilize esse para dar sempre os mesmos resultados para o mesmo `i`
//            seed = time(nullptr); //utilize esse para sempre dar resultados diferentes

            cout << "seed: " << seed << endl;
            cout << "n= " << n[i] << endl;

            // lê o csv e salva n[i] registros aleatórios
            dfLivros.lerCsv(nomeDatasetTeste, n[i], true, seed);  //fixme: trocar para ler dataset original

            // Faz as ordenações e imprime métricas

            //chama algoritmo de Ordenação Quicksort
            dfLivros.ordenar(AlgOrdenacao::quicksort, true);

            //chama algoritmo de Ordenação HeapSort
            dfLivros.ordenar(AlgOrdenacao::heapsort, true); //fixme: passar tamanho de registros

            cout << "\n\n-------------------\n\n";
        }
    }
//*/
    delete [] n;
    return 0;
}
