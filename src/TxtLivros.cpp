#include <fstream>  //ifstream
#include "../include/TxtLivros.hpp"

//TODO: documentar os blocos funcionais e variáveis dentro do método
void TxtLivros::lerEntrada(int *x, int * &n, const std::string &nomeArquivo) {
    std::string linha, temp;
    std::ifstream arq("../io/" + nomeArquivo);

    getline(arq, linha);
    *x = std::stoi(linha);

    n = new int[*x];

    for (int i = 0; i < *x; i++) {
        getline(arq, linha);
        n[i] = std::stoi(linha);
    }
}
