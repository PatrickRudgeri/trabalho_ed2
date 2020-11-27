#ifndef TRABALHO_ED2_TXTLIVROS_HPP
#define TRABALHO_ED2_TXTLIVROS_HPP

#include <iostream>
#include <sstream>
#include "metricas.hpp"

namespace txt {
/**  Função para ler os parametros X e N do arquivo de entrada
 *  @param x : Número de iterações
 *  @param nomeArqEntrada : nome do arquivo que contém os parametros de entrada
 *  @return vetor de inteiros contendo o tamanho das amostras
 * */
    void lerEntrada(int *x, int *&n, const std::string &pathArquivo);

/**  Função para ler o arquivo de saida e preencher a struct Stats
 *  @param stats : struct que armazena as métricas
 *  @param pathArqSaida : nome do arquivo de saída
 * */
    void lerSaida(Stats *&stats, const std::string &pathArqSaida);
}


#endif //TRABALHO_ED2_TXTLIVROS_HPP
