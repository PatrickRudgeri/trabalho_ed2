#include "../../include/secao_2/Autor.hpp"

using namespace std;

Autor::Autor() {
    frequencia_ = 0;
}

Autor::Autor(string nomeAutor, int id) {
    nomeAutor_ = nomeAutor;
    id_ = id;
    frequencia_ = 0;
}

Autor::~Autor() {
    //dtor
}

void Autor::setNome(string nome) {
    nomeAutor_ = nome;
}

void Autor::setfrequencia(int freq) {
    frequencia_ = freq;
}

string Autor::getNome() {
    return nomeAutor_;
}

int Autor::getFrequencia() {
    return frequencia_;
}

int Autor::getId() {
    return id_;
}

void Autor::setId(int id) {
    id_ = id;
}


