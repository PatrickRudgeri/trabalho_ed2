#include <iostream>
#include <chrono>

using namespace std;

#include "../include/DataFrameLivros.hpp"
#include "../include/Registro.hpp"
#include "../include/helpers.hpp"
#include "../include/Csv.hpp"
#include "../include/Txt.h"

int main() {
    Csv csv;
    Txt txtArgs;
    int x, *n;
    DataFrameLivros dfLivros;
    string nomeDataset, nomeCsvNovo, path;

    path = "../dataset/";
    nomeDataset = path + "dataset_simp_sem_descricao.csv";

    //corrige erros, salva em um novo csv e retorna o nome
    nomeDataset = csv.padronizarCsv(nomeDataset);

    // obtendo os parâmetros de entrada
    txtArgs.lerParametrosEntrada("../io/entrada.txt");
    x = txtArgs.getXarg();
    n = txtArgs.getNargs();

    for (int i=0; i < x; i++) {
        // lê o csv e salva n[i] registros aleatórios
        dfLivros.lerCsv(nomeDataset, n[i], true);

        // Faz as ordenações, retorna o vetor ordenado e imprime métricas
        dfLivros.ordenar("titulo", "quick", true);

        //exemplo com outro algoritmo de ordenação
        dfLivros.ordenar("titulo", "insertion", true);
    }

//    carregaArquivoPorBlocos(NOME_DATASET, 1001);

//    read_csv(nomeDataset, 1000);
    return 0;
}
