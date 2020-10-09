#include "../include/Registro.hpp"
#include "../include/helpers.hpp"

using namespace std;

void Registro::setTodosAtributosStr(string *stringArray) {
    setAutores(stringArray[0]);
    setRankBestsellers(stringArray[1]);
    setCategorias(stringArray[2]);
    setEdicao(stringArray[3]);
    setId(stringArray[4]);
    setIsbn10(stringArray[5]);
    setIsbn13(stringArray[6]);
    setAvaliacaoMedia(stringArray[7]);
    setQtAvaliacoes(stringArray[8]);
    setTitulo(stringArray[9]);
}

void Registro::setAutores(string autoresStr) {
    string stripStr = autoresStr.substr(1, autoresStr.length() - 1);
    autores_ = splitString(stripStr);
}

void Registro::setAutores(int *autores) {
    autores_ = autores;
}

void Registro::setRankBestsellers(std::string rankBestsellersStr) {
    rankBestsellers_ = rankBestsellersStr;
}

void Registro::setCategorias(std::string categorias) {
    string stripStr = categorias.substr(1, categorias.length() - 1);
    categorias_ = splitString(stripStr);
}

void Registro::setCategorias(int *categorias) {
    categorias_ = categorias;
}

void Registro::setEdicao(string edicao) {
    edicao_ = edicao;
}

void Registro::setId(string idStr) {
    id_ = stoll(idStr);
}

void Registro::setId(long long id) {
    id_ = id;
}

void Registro::setIsbn10(string isbn10) {
    isbn10_ = isbn10;
}

void Registro::setIsbn13(string isbn13) {
    isbn13_ = isbn13;
}

void Registro::setAvaliacaoMedia(string avalMedia) {
    avaliacaoMedia_ = avalMedia;
}

void Registro::setQtAvaliacoes(string qtAvaliacoes) {
    qtAvaliacoes_ = qtAvaliacoes;
}

void Registro::setTitulo(string titulo) {
    titulo_ = titulo;
}