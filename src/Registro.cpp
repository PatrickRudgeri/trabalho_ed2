#include <sstream>  //stringstream
#include <vector>
#include "../include/Registro.hpp"

using namespace std;

int *splitString(std::string str, char delim = ','); //não é membro da classe

void Registro::setTodosAtributosStr(string *stringArray) {
    cout << stringArray[9] << endl; //fixme: retirar esse debug
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
    edicao_ = edicao; //fixme: BUG aqui. Depurar
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

int *Registro::getAutores() const {
    return autores_;
}

const string &Registro::getRankBestsellers() const {
    return rankBestsellers_;
}

int *Registro::getCategorias() const {
    return categorias_;
}

const string &Registro::getEdicao() const {
    return edicao_;
}

long long int Registro::getId() const {
    return id_;
}

const string &Registro::getIsbn10() const {
    return isbn10_;
}

const string &Registro::getIsbn13() const {
    return isbn13_;
}

const string &Registro::getAvaliacaoMedia() const {
    return avaliacaoMedia_;
}

const string &Registro::getQtAvaliacoes() const {
    return qtAvaliacoes_;
}

const string &Registro::getTitulo() const {
    return titulo_;
}

int *splitString(std::string str, char delim) {
    std::stringstream ss(str);
    std::string item;
    auto *itens = new std::vector<int>; //question: é possivel implementar sem std::vector?
    while (true) {
        if (ss.eof()) break;
        getline(ss, item, delim);
        itens->push_back(stoi(item));
    }
    return itens->data();
}