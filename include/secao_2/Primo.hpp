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
public:
    static bool *tabelaPrimos;
    static int tamanho;

    /**  <Breve descrição> criarTabela
    *  @param n <o que é esse parametro?>
    *  @return <se tiver algum retorno descreva aqui>
    */
    static void criarTabela(int n);

    /**  <Breve descrição> proxPrimo
    *  @param num <o que é esse parametro?>
    *  @return <se tiver algum retorno descreva aqui>
    */
    static int proxPrimo(int num);

private:
    //Definindo construtor como privado, para impedir de instanciar a classe
    Primo() {}
};


#endif // PRIMO_H
