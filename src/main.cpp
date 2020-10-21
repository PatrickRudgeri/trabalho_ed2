#include <iostream>
#include <chrono>
#include "../include/DataFrameLivros.hpp"
#include "../include/TxtLivros.hpp"
//#include "../include/CsvLivros.hpp"

using namespace std;

int main() {
    TxtLivros txtArgs;
    int x, *n, seed;
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
    txtArgs.lerEntrada("../io/entrada.txt");

    x = txtArgs.getXarg(); //guarda iterações
    n = txtArgs.getNargs(); //guarda quantidade de registros por iteração
///*
    //utilizar o codigo comentado abaixo quando tudo já estiver funcional
    for (int i=0; i < x; i++) {
        seed = i; //utilize esse para dar sempre os mesmos resultados
//        seed = time(nullptr); //utilize esse para sempre dar resultados diferentes

        cout << "seed: "<< seed << endl;
        cout << "n= "<< n[i] << endl;
         // lê o csv e salva n[i] registros_ aleatórios
         dfLivros.lerCsv(nomeDatasetTeste, n[i], true, seed);  //fixme: trocar para ler dataset original

         // Faz as ordenações e imprime métricas

         //chama algoritmo de Ordenação Quicksort
        dfLivros.ordenar(AlgOrdenacao::quicksort, true);

         //chama algoritmo de Ordenação HeapSort
        dfLivros.ordenar(AlgOrdenacao::heapsort, true); //fixme: passar tamanho de registros

         cout << "\n\n-------------------\n\n";
     }
//*/
    return 0;
}
