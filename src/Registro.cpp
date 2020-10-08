#include "../include/Registro.hpp"


using namespace std;

void Registro::setTodosAtributosStr(std::string *stringArray) {
    setAutores(stringArray[0]);
//    setRankBestsellers(stringArray[1]);
//    setCategorias(stringArray[2]);
    setEdicao(stringArray[3]);
//    setId(stringArray[4]);
    setIsbn10(stringArray[5]);
    setIsbn13(stringArray[6]);
    setAvaliacaoMedia(stringArray[7]);
    setQtAvaliacoes(stringArray[8]);
    setTitulo(stringArray[9]);
}

void Registro::setEdicao(std::string edicao) {
    this->edicao = edicao;
}

void Registro::setIsbn10(std::string isbn10) {
    this->isbn10 = isbn10;
}

void Registro::setIsbn13(std::string isbn13) {
    this->isbn13 = isbn13;
}

void Registro::setAvaliacaoMedia(std::string avalMedia) {
    this->avaliacaoMedia = avalMedia;
}

void Registro::setQtAvaliacoes(std::string qtAvaliacoes) {
    this->qtAvaliacoes = qtAvaliacoes;
}

void Registro::setTitulo(std::string titulo) {
    this->titulo = titulo;
}

void Registro::setAutores(std::string autoresStr) {
    string *autoresStrArray = nullptr;
    string stripStr = autoresStr.substr(1, autoresStr.length() - 1);
//    splitString(stripStr, autoresStrArray);
}

void Registro::setAutores(int *autores) {
    this->autores = autores;
}
