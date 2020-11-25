#include "../../include/secao_3/NoB.h"


NoB::NoB(int m)
{
    for(int i; i<m;i++){
        vetFilhos[i] = nullptr;
    }
    pai_ = nullptr;
    n_ = 0;
    ehfolha_ = true;
}

NoB::~NoB()
{
    //dtor
}

//Gets
int NoB::getn(){
    return n_;
}

bool NoB::getEhfolha(){
    return ehfolha_;
}

NoB* NoB::getVetFilhos(int i){
    return vetFilhos[i];
}

int NoB::getChaves(int i){
    return chaves[i];
}

NoB* NoB::getPai(){
    return pai_;
}


//Sets
void NoB::setn(int x){
    n_ = x;
}

void NoB::setEhfolha(bool x){
    ehfolha_ = x;
}

void NoB::setVetFilhos(NoB* vetor){
    // vetFilhos = vetor;
}

void NoB::setChaves(int valor, int pos){
    chaves[pos] = valor;
}

void NoB::setPai(NoB* p){
    pai_ = p;
}

