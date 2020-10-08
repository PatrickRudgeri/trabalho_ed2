#include <iostream>
#include <chrono>
#include <map>
using namespace std;

#include "../include/DataFrameLivros.hpp"
#include "../include/Registro.hpp"
#include "../include/helpers.hpp"
#include "../include/Csv.hpp"

int main() {
    Csv csv;
    DataFrameLivros dfLivros;
    string nomeDataset, nomeCsvNovo, path;

    //FIXME: transformar para caminho relativo
    path = "/home/patrick/CLionProjects/trabalho_ed2/dataset/";
    nomeDataset = path + "dataset_simp_sem_descricao.csv";

    //corrige erros, salva em um novo csv e retorna o nome
    nomeDataset = csv.padronizarCsv(nomeDataset);

    // x e n serão lidos de "entrada.txt"
    int x = 5;
    int n[] = {1000, 5000, 10000, 50000, 100000};

    for (int i=0; i < x; i++) {
        // lê o csv e salva n[i] registros aleatórios
        dfLivros.lerCsv(nomeDataset, n[i], true);

        // Faz as ordenações, retorna o vetor ordenado e imprime métricas
        dfLivros.ordenar("titulo", "quick", true);

        //exemplo com outro algoritmo de ordenação
        dfLivros.ordenar("titulo", "insertion", true);
    }
    /*
    fstream arq(NOME_DATASET);
    carregaArquivoPorBlocos(NOME_DATASET, 1001);

    read_csv(NOME_DATASET, 1000);
     */
    return 0;
}
