#ifndef AUTOR_H
#define AUTOR_H
#include <iostream>
#include "stdio.h"

using namespace std;

/** Breve descrição da classe
 *
 *  Descrição detalhada da classe
 *
 *  Atributos
 *  ----------------
 *  @attr nomeDoAutor <o que é esse atributo?>
 *  @attr frequencia <o que é esse atributo?>
 * 
 * */

class Autor
{
    private:
        string nomeDoAutor;
        int frequencia;

    public:
        //Construtor da classe
        Autor();
        //Destrutor da classe
        ~Autor();
        void setNome(string nome);
        void setfrequencia(int freq);
        string getNome();
        int getFrequencia();
};

#endif // AUTOR_H

