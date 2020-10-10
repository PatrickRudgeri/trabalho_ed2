#include <fstream>  //ifstream
#include "../include/Txt.hpp"

Txt::Txt() {
    nArgs = nullptr;
    xArg = -1;
}

Txt::~Txt() {
    delete [] nArgs;
}

void Txt::lerEntrada(std::string nomeArquivo) {
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

int *Txt::getNargs() const {
    return nArgs;
}

int Txt::getXarg() const {
    return xArg;
}
