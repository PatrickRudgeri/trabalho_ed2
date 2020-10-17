#include <iostream>
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
    x = txtArgs.getXarg();
    n = txtArgs.getNargs();
///*
    //utilizar o codigo comentado abaixo quando tudo já estiver funcional
    for (int i=0; i < x; i++) {
        seed = i; //utilize esse para dar sempre os mesmos resultados
//        seed = time(nullptr); //utilize esse para sempre dar resultados diferentes

        cout << "seed: "<< seed << endl;
        cout << "n= "<< n[i] << endl;
         // lê o csv e salva n[i] registros_ aleatórios
         dfLivros.lerCsv(nomeDatasetTeste, n[i], true, seed);  //fixme: trocar para ler dataset original

         // Faz as ordenações, retorna o vetor ordenado e imprime métricas
         dfLivros.ordenar(AlgOrdenacao::quicksort, ChavesOrdenacao::titulo, true );

         //exemplo com outro algoritmo de ordenação
         dfLivros.ordenar(AlgOrdenacao::heapsort, ChavesOrdenacao::titulo, true);

         cout << "\n\n-------------------\n\n";
     }
//*/
    return 0;
}
