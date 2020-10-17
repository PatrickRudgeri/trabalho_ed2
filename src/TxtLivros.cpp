#include <fstream>  //ifstream
#include "../include/TxtLivros.hpp"

TxtLivros::TxtLivros() {
    nArgs = nullptr;
    xArg = -1;
}

TxtLivros::~TxtLivros() {
    delete [] nArgs;
}

//TODO: documentar os blocos funcionais e variáveis dentro do método
void TxtLivros::lerEntrada(std::string nomeArquivo) {
    std::string linha, temp;
    std::ifstream arq(nomeArquivo);

    getline(arq, linha);
    xArg = std::stoi(linha);

    nArgs = new int[xArg];

    for(int i=0; i < xArg; i++){
        getline(arq, linha);
        nArgs[i] = std::stoi(linha);
    }
}
//TODO: criar método para salvar saidas

int *TxtLivros::getNargs() const {
    return nArgs;
}

int TxtLivros::getXarg() const {
    return xArg;
}
