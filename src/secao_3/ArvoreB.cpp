#include "../../include/secao_3/ArvoreB.h"
#include "../../include/secao_3/NoB.h"


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
    return auxBusca(raiz_, val);
}

void ArvoreB::insere(int val){
    raiz_ =  auxInsere(raiz_, val);
}

bool ArvoreB::auxBusca(NoB *p, int val){
    int i;
    if (p = nullptr){
        return false;
    } else {
        for(i=0;i<=(p->getn()-1);i++){
            if (p->getChaves(i) == val){
                return true;
            } else if(val < p->getChaves(i)){
                auxBusca(p->getVetFilhos(i), val);
            }
        }
        auxBusca(p->getVetFilhos(i+1), val);
    }
}

NoB* ArvoreB::auxInsere(NoB *p, int val){
    int i;
    if (p == nullptr && p == raiz_){
        p = new NoB(3);
        p->setChaves(val, 0);
        p->setn(p->getn()+1);
    } else {
        for(i =0;i<=(p->getn()-1);i++){
            if(val < p->getChaves(i)){
                if (p->getEhfolha() == true){
                    int aux = p->getn()-1;
                    while(aux != i){
                        p->setChaves(p->getChaves(aux),aux+1);
                        aux--;
                    }
                    p->setChaves(val, i);
                    p->setn(p->getn()+1);
                    if (p->getn() == 3){

                        // Cisão(p);
                    }
                }
                auxInsere(p->getVetFilhos(i), val);
            }
        }
        auxBusca(p->getVetFilhos(i+1), val);
    }
}


void ArvoreB::Cisao(NoB* p){

}

