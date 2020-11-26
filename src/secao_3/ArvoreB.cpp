#include "../../include/secao_3/ArvoreB.h"

#include "../../include/secao_3/NoB.h"

using namespace std;

//variaveis globais para o metodo de busca. g retorna a posição e pt retorna o nó em que o valor
// buscado se encontra ou deve ser inserido.
int f, g;
NoB* pt;

ArvoreB::ArvoreB()
{
    //ctor
    //ordem_ = m;
    raiz_ = nullptr;
    qtdComparacoes_ = 0;
    qtdTrocas_ = 0;
}

ArvoreB::~ArvoreB()
{
    //dtor
}

int getOrdem(){
    //  return ordem;
}

bool ArvoreB::busca(int val){
    return auxBusca(pt, val, f, g);
}

void ArvoreB::insere(int val){
    raiz_ =  auxInsere(raiz_, val);
}


bool ArvoreB::auxBusca(NoB* pt,int val,int f,int g){
    NoB* d = raiz_; pt = nullptr; f=0;
    int i = g = 0; pt = d;
    while(d!= nullptr){
        int i = g = 0; pt = d;
        int x = d->getn();
        while (i<x){
            if(val > d->getChaves(i)){
                i=g=i+1;
            } else if(val == d->getChaves(i)){
                f=1;
                d=nullptr;
                return true;
            } else {
                d = d->getVetFilhos(i);
                i=x+2;
            }
        }
        if (i==x+1){
            d = d->getVetFilhos(x+1);
        }
    }
    return false;
}

NoB* ArvoreB::auxInsere(NoB *p, int val){
    bool b = auxBusca(pt, val, f, g);
    if (f == 1){
        // std::cout << "Valor Já inserido";
    } else {
        if (raiz_ == nullptr){
            raiz_ = new NoB(3);
            pt = raiz_;
        }
        InsereOrdenado(pt, val, g);
        pt->setn();
    }
}

/*
void ArvoreB::Cisao(NoB* p){
    int meio = (ordem_/2);

    //se pai de p é igual a null, cria novo nó pai e add o do meio de p na pos 0
    if (p->getPai()== nullptr){
        NoB* NovoPai = new NoB();
        NovoPai->setChaves(p->getChaves(meio),0);
    }

    NoB* q = new NoB();
    int i = 0;
    x=meio+1;
    //insere os valores dps do meio em outro vetor e seta o valor de n
    while(x<ordem_){
        q->setChaves(p->getChaves(x),i);
        x++;
        i++;
    }
    q->setn(i+1);

    //seta os valores de p do meio pra frente como -1
    for(int j=meio;j<ordem_;j++){
        p->setChaves(-1,j);
    }

    q->setPai(p->getPai());
}
*/

void ArvoreB::InsereOrdenado(NoB* p, int val, int pos){
    int aux = p->getn();
    while (aux > pos){
        p->setChaves(p->getChaves(aux),(aux+1));
        aux--;
    }
    p->setChaves(val, pos);
    // std::cout << "Valor inserido!";
}
