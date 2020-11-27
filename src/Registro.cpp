#include <sstream>  //stringstream
#include <vector>
#include <cassert>
#include "../include/Registro.hpp"

using namespace std;


// --------------- Construtores e Destrutores ---------------- //

Registro::Registro() {
    autores_ = nullptr;
    categorias_ = nullptr;
    id_ = -1;
    regQtAutores_ = -1;
    regQtCategorias_ = -1;
}

Registro::~Registro() {
    //fixme: verificar
//    delete[] autores_;
//    delete[] categorias_;
}

// -------------------------- Sets --------------------------- //

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

void Registro::setAutores(const string &autoresStr) {
    string stripStr = autoresStr.substr(1, autoresStr.length() - 2);
    if (!stripStr.empty() && stripStr.length() > 1) {
        splitString(stripStr, autores_, &regQtAutores_);
    }
}

void Registro::setAutores(const int *autores, int n) {
    regQtAutores_ = n;
    for (int i = 0; i < n; i++) {
        autores_[i] = autores[i];
    }
}

void Registro::setRankBestsellers(std::string rankBestsellersStr) {
    rankBestsellers_ = rankBestsellersStr;
}

void Registro::setCategorias(const std::string &categorias) {
    string stripStr = categorias.substr(1, categorias.length() - 2);
    if (!stripStr.empty() && stripStr.length() > 1) {
        splitString(stripStr, categorias_, &regQtCategorias_);
    }
}

void Registro::setCategorias(const int *categorias, int n) {
    regQtCategorias_ = n;
    for (int i = 0; i < n; i++) {
        categorias_[i] = categorias[i];
    }
}

void Registro::setEdicao(string edicao) {
    edicao_ = edicao;
}

//TODO: documentar os blocos funcionais e variáveis dentro do método
void Registro::setId(const string &idStr) {
    assert(isdigit(idStr[0]));
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

// --------------------------- Gets -------------------------- //

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

int Registro::getQtAutores() const {
    return regQtAutores_;
}

// --------------------- Métodos privados -------------------- //

void Registro::splitString(const std::string &str, int *&array, int *n, char delim) {
    int cont = 0;
    int itemInt;
    stringstream ss(str);
    string item;

    //se n > 0, então aloca um vetor de tamanho n
    if (*n > 0) {
        array = new int[*n];
    }
    // se *n==-1 então esse loop fará a contagem de elementos dentro da string `str`
    while (!ss.eof()) {
        getline(ss, item, delim);
        if (!item.empty() && item.length() > 1) {
            if (*n > 0) {
                //somente quando o array foi criado que os itens serão atribuidos
                itemInt = std::stoi(item);
                array[cont] = itemInt;
//                cout << cont << endl; //fixme: debug
            }
            cont++;
        }

    }
    // se não foi passado paramêtro nenhum para `n` então a função é chamada novamente contendo o valor de n que
    // foi contabilizado
    if (*n == -1) {
        *n = cont;
        splitString(str, array, n, delim);
    }
}

// ----------------- Sobrecarga de operadores ---------------- //

//função auxiliar. Apenas para debug por enquanto
std::ostream &operator<<(ostream &os, const Registro &reg) {
    // imprimindo 1 autor e 1 categoria, apenas para teste
    os << "qtAutores: " << reg.regQtAutores_ << " | ";
    os << "qtCategorias: " << reg.regQtCategorias_ << " || ";
    os << "1º Autor: " << reg.autores_[0] << " | ";
    os << "RankBestsellers: " << reg.rankBestsellers_ << " | ";
    os << "1ª Categoria: " << reg.categorias_[0] << " | ";
    os << "Edicao: " << reg.edicao_ << " | ";
    os << "Id: " << reg.id_ << " | ";
    os << "isbn10: " << reg.isbn10_ << " | ";
    os << "isbn13: " << reg.isbn13_ << " | ";
    os << "avaliacaoMedia: " << reg.avaliacaoMedia_ << " | ";
    os << "qtAvaliacoes: " << reg.qtAvaliacoes_ << " | ";
    os << "Titulo: " << reg.titulo_ << endl;
    return os;
}
