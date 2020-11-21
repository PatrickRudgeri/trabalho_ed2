//
// Created by Larissa on 19/11/2020.
//


#include "../../include/secao_3/noVP.h"

NoVP::NoVP()
{
    info = 0;
    esq = nullptr;
    dir = nullptr;
    pai = nullptr;
    tipocor = PRETO;
}

NoVP::~NoVP()
= default;


NoVP* NoVP::getPai(NoVP* n)
{
    //Pai definido como nulo para o noh raiz.
    return n == nullptr ? nullptr : n->pai;
}

NoVP* NoVP::getAvo(NoVP* n)
{
    //retornar nullptr se for raiz ou filho da raiz
    return getPai(getPai(n));
}

NoVP* NoVP::getIrmao(NoVP* n)
{
    NoVP* p = getPai(n);

    //Nenhum Pai significa nenhum irmao.
    if (p == nullptr)
    {
        return nullptr;
    }

    if (n == p->esq)
    {
        return p->dir;
    }
    else
    {
        return p->esq;
    }
}

NoVP* NoVP::getTio(NoVP* n)
{
    NoVP* p = getPai(n);

    //Irmao do pai eh o tio
    return getIrmao(p);
}



//Sets
void NoVP::setEsq(NoVP *p)
{
    esq = p;
}
void NoVP::setInfo(int val)
{
    info = val;
}
void NoVP::setDir(NoVP *p)
{
    dir = p;
}
void NoVP::setPai(NoVP *p)
{
    pai = p;
}
void NoVP::setCor(cor c)
{
    tipocor = c;
}

//Gets
NoVP* NoVP::getEsq() const
{
    return esq;
}
int NoVP::getInfo() const
{
    return info;
}
NoVP* NoVP::getDir() const
{
    return dir;
}

/*
 * Retorna a cor do no
 essa funcao especificamente verifica o caso no noh folha (NIL)
 */
cor NoVP::noh_cor(NoVP* n)
{
    return n == nullptr ? PRETO : n->tipocor;
}



cor NoVP::getCor() const
{
    return tipocor;
}




