#include "../../include/secao_3/noVP.hpp"

NoVP::NoVP() {
    info_ = 0;
    esq_ = nullptr;
    dir_ = nullptr;
    pai_ = nullptr;
    tipoCor_ = Cor::PRETO;
}

NoVP::~NoVP() = default;


NoVP *NoVP::getPai() {
    //Pai definido como nulo para o noh raiz.
    return pai_;
}

NoVP *NoVP::getAvo() {
    NoVP *p = getPai();
    //se não tem pai, então não tem avô
    if (p == nullptr) {
        return nullptr;
    }
    //retornar nullptr se for raiz ou filho da raiz
    return p->getPai();
}

NoVP *NoVP::getIrmao() {
    NoVP *p = getPai();

    //Nenhum Pai significa nenhum irmao.
    if (p == nullptr) {
        return nullptr;
    }

    if (this == p->esq_) {
        return p->dir_;
    } else {
        return p->esq_;
    }
}

NoVP *NoVP::getTio() {
    NoVP *p = getPai();

    //Irmao do pai eh o tio
    return p->getIrmao();
}


//Sets
void NoVP::setEsq(NoVP *p) {
    esq_ = p;
}

void NoVP::setInfo(long long val) {
    info_ = val;
}

void NoVP::setDir(NoVP *p) {
    dir_ = p;
}

void NoVP::setPai(NoVP *p) {
    pai_ = p;
}

void NoVP::setCor(Cor c) {
    tipoCor_ = c;
}

void NoVP::setRegistro(Registro p) {
    this->registro_ = p;
}

//Gets
NoVP *NoVP::getEsq() const {
    return esq_;
}

long long int NoVP::getInfo() const {
    return info_;
}

NoVP *NoVP::getDir() const {
    return dir_;
}

Cor NoVP::getCor() const {
    return tipoCor_;
}

//cada noh possui o ponteiro para o registro armazenado
Registro NoVP::getRegistro() {
   return registro_;
}