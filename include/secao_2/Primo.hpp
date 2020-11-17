#ifndef PRIMO_H
#define PRIMO_H

#include <iostream>
#include <cmath>

/** Breve descrição da classe
 *
 *  Descrição detalhada da classe
 *
 *  Atributos
 *  ----------------
 *  @attr tamanho <o que é esse atributo?>
 *  @attr *tabelaPrimos <o que é esse atributo?>
 *
 * */

class Primo {
private:
    int tamanho;
    bool *tabelaPrimos;

public:
    //Construtor da classe
    Primo();

    //Destrutor da classe
    ~Primo();

    /**  <Breve descrição> criatabela
    *  @param n <o que é esse parametro?>
    *  @return <se tiver algum retorno descreva aqui>
    */
    void criatabela(int n);

    /**  <Breve descrição> proxPrimo
    *  @param num <o que é esse parametro?>
    *  @return <se tiver algum retorno descreva aqui>
    */
    int proxPrimo(int num);

};


#endif // PRIMO_H
