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
        qtdComparacoes_++;
        int i = g = 0; pt = d;
        int x = d->getn();
        while (i<x){
            qtdComparacoes_++;
            if(val > d->getChaves(i)){
                qtdComparacoes_++;
                i=g=i+1;
            } else if(val == d->getChaves(i)){
                qtdComparacoes_++;
                f=1;
                d=nullptr;
                return true;
            } else {
                d = d->getVetFilhos(i);
                i=x+2;
            }
        }
        if (i==x+1){
            qtdComparacoes_++;
            d = d->getVetFilhos(x+1);
        }
    }
    return false;
}

NoB* ArvoreB::auxInsere(NoB *p, int val){
    bool b = auxBusca(pt, val, f, g);
    if (f == 1){
        qtdComparacoes_++;
        // std::cout << "Valor Já inserido";
    } else {
        if (raiz_ == nullptr){
            qtdComparacoes_++;
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
    int aux = p->getChaves(meio);

    //se pai de p é igual a null, cria novo nó pai e add o do meio de p na pos 0
    if (p->getPai()== nullptr){
        NoB* NovoPai = new NoB();
        NovoPai->setChaves(p->getChaves(aux),0);
    } else {
        //se não insere
        NoB* q = p->getPai();
        for (int i=0;i<q->getn();i++){
            if (q->getChaves(i) > aux){
                int pos = i;
            } else if(q->getn() == i+1){
                pos = i+1;
                else { i++; }
            }
            InsereOrdenado(pt,aux,pos);
        }

        NoB* q = new NoB();
        int x = meio+1;
        j=0;
        //insere os valores dps do meio em outro vetor e seta o valor de n
        while(x<p->getn()){
            q->setChaves(p->getChaves(x),j);
            x++;
            j++;
        }
        q->setn(j+1);
        int cont = 0;
        //seta os valores de p do meio pra frente como -1
        for(int j=meio;j<p->getn;j++){
            p->setChaves(-1,j);
            cont++;
        }
        p->setn(cont);

        q->setPai(p->getPai());
    }
*/

void ArvoreB::InsereOrdenado(NoB* p, int val, int pos){
    int aux = p->getn();
    while (aux > pos){
        qtdComparacoes_++;
        p->setChaves(p->getChaves(aux),(aux+1));
        qtdTrocas_++;
        aux--;
    }
    qtdTrocas_++;
    p->setChaves(val, pos);
    // std::cout << "Valor inserido!";
}
