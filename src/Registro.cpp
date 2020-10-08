#include "../include/Registro.hpp"


using namespace std;

void Registro::setTodosAtributosStr(std::string *registro_array) {
    setAutores(registro_array[0]);
//    setRankBestsellers(registro_array[1]);
//    setCategorias(registro_array[2]);
    setEdicao(registro_array[3]);
//    setId(registro_array[4]);
    setIsbn10(registro_array[5]);
    setIsbn13(registro_array[6]);
    setAvaliacaoMedia(registro_array[7]);
    setQtAvaliacoes(registro_array[8]);
    setTitulo(registro_array[9]);
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
