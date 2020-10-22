#ifndef TRABALHO_ED2_TXTLIVROS_HPP
#define TRABALHO_ED2_TXTLIVROS_HPP

#include <iostream>

/** TODO:Breve descrição da classe
 *
 *  TODO:Descrição detalhada da classe
 * */
class TxtLivros {
public:

    /**  Método para ler os parametros X e N do arquivo de entrada
     *  @param nomeArquivo : nome do arquivo de entrada
     *  @param x : Número de iterações
     *  @param n : vetor de inteiros de tamanho x que será preenchido
     * */
    static void lerEntrada(int *x, int * &n, const std::string &nomeArquivo = "entrada.txt");
};


#endif //TRABALHO_ED2_TXTLIVROS_HPP
