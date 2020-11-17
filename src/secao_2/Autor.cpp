#include "Autor.h"
#include <iostream>

using namespace std;

Autor::Autor()
{
    frequencia = 0;
}


Autor::~Autor()
{
    //dtor
}

void Autor::setNome(string nome)
{
    nomeDoAutor = nome;
}

void Autor::setfrequencia(int freq)
{
    frequencia = freq;
}

string Autor::getNome()
{
    return nomeDoAutor;
}

int Autor::getFrequencia()
{
    return frequencia;
}
