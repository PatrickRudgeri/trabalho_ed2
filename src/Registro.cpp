#include <sstream>  //stringstream
#include <vector>
#include <cassert>
#include "../include/Registro.hpp"

using namespace std;


// ------------------- Funções auxiliares -------------------- //

void splitString(std::string str, int *&array, int n = -1, char delim = ',') {
    int cont = 0;
    stringstream ss(str);
    string item;

    //se n > 0, então aloca um vetor de tamanho n e atribui pro array passado como parametro
    if (n > 0)
        array = new int[n];

    // se n==-1 então esse loop fará a contagem de elementos dentro da string `str`
    while (!ss.eof()) {
        getline(ss, item, delim);

        //somente quando o array foi criado que os itens serão atribuidos
        if (n > 0) {
            if (!item.empty() && item.length() > 1) {
                array[cont] = std::stoi(item);
            }
        }
        cont++;
    }
    // se não foi passado paramêtro nenhum para `n` então a função é chamada novamente contendo o valor de n que
    // foi contabilizado
    if (n == -1)
        splitString(str, array, cont);
}

// --------------- Construtores e Destrutores ---------------- //

Registro::Registro() {
    autores_ = nullptr;
    categorias_ = nullptr;
    id_ = -1;
}

Registro::~Registro() {
    delete[] autores_;
    delete[] categorias_;
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

//TODO: documentar os blocos funcionais e variáveis dentro do método
void Registro::setAutores(const string &autoresStr) {

    string stripStr = autoresStr.substr(1, autoresStr.length() - 2);
    if (!stripStr.empty() && stripStr.length() > 1) {
        splitString(stripStr, autores_);
    }
}

void Registro::setAutores(const int *autores, int n) {
    for (int i = 0; i < n; i++) {
        autores_[i] = autores[i];
    }
}

void Registro::setRankBestsellers(std::string rankBestsellersStr) {
    rankBestsellers_ = rankBestsellersStr;
}

//TODO: documentar os blocos funcionais e variáveis dentro do método
void Registro::setCategorias(const std::string &categorias) {
    string stripStr = categorias.substr(1, categorias.length() - 2);
    if (!stripStr.empty() && stripStr.length() > 1) {
        splitString(stripStr, categorias_);
    }
}

void Registro::setCategorias(int *categorias) {
    categorias_ = categorias;
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

// ----------------- Sobrecarga de operadores ---------------- //

/*
//Se for verificar se uma instancia de Registro é igual a outra, usar esse método
//obs:corrigir comparações de arrays
bool Registro::operator==(const Registro &rhs) const {
    return autores_ == rhs.autores_ &&
           rankBestsellers_ == rhs.rankBestsellers_ &&
           categorias_ == rhs.categorias_ &&
           edicao_ == rhs.edicao_ &&
           id_ == rhs.id_ &&
           isbn10_ == rhs.isbn10_ &&
           isbn13_ == rhs.isbn13_ &&
           avaliacaoMedia_ == rhs.avaliacaoMedia_ &&
           qtAvaliacoes_ == rhs.qtAvaliacoes_ &&
           titulo_ == rhs.titulo_;
}
*/

///*
//Se atribuir uma instancia de Registro em outra a classe usa esse método
Registro &Registro::operator=(const Registro &rhs) {
    if (&rhs != this) {
//        setAutores(rhs.autores_); //TODO
        rankBestsellers_ = rhs.rankBestsellers_;
//        categorias_ = rhs.categorias_;//TODO
        edicao_ = rhs.edicao_;
        id_ = rhs.id_;
        isbn10_ = rhs.isbn10_;
        isbn13_ = rhs.isbn13_;
        avaliacaoMedia_ = rhs.avaliacaoMedia_;
        qtAvaliacoes_ = rhs.qtAvaliacoes_;
        titulo_ = rhs.titulo_;
    }
    return *this;
}
//*/
