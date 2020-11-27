#include "../../include/secao_2/Primo.hpp"
#include <iostream>
#include <cmath>

using namespace std;

bool *Primo::tabelaPrimos = nullptr;
int Primo::tamanho = 0;

/**
    * Cria uma tabela de booleanos que indicam quais valores sao primos
    * @param n Valor maximo que pode ser necessario buscar o proximo primo
    */
void Primo::criarTabela(int n) {

    //variável do tipo inteira que armazena o tamanho da tabela a ser criada
    tamanho = n + 2 * ((int) (sqrt((double) n)) + 1) + 1;

    tabelaPrimos = new bool[tamanho];
    int m = (int) sqrt((double) n) + 1; // arrumar

    //todos na tabela são primos e depois conforme é rodado.. ele tira os multiliplos dos anteriores
    for (int i = 1; i < tamanho; i++)
        tabelaPrimos[i] = true;

    //muda para falso (diz que não é primo) todos que são multiplos de um número primo. Os numeros que são primos permanecem
    // como true
    for (int i = 2; i <= m; i++) {
        if (tabelaPrimos[i]) {
            for (int j = pow(i, 2); j < tamanho; j = j + i) {
                if (i == 5 && j == 24)
                    j = 25;
                tabelaPrimos[j] = false;
            }
        }
    }
}

/**
    * Retorna o menor proximo primo da tabela
    * @param num Numero referido
    * @return numero primo mais proximo acima do numero passado como parametro, quando este ultrapassa o tamanho da tabela é retornado o primo
    * mais proximo abaixo do valor
    */
int Primo::proxPrimo(int num) {
    if (num > tamanho){
        // se num é maior que o tamanho da tabela de primos, então cria-se uma nova tabela passando num como parametro
        Primo::criarTabela(num);
    }

    for (int i = num; i < tamanho; i++) {
        if (tabelaPrimos[i])
            return i;
    }

    for (int i = num; i > 0; i--) {
        if (tabelaPrimos[i])
            return i;
    }
    return -1; // esse retorno não é chamado, pois o numero 1 e primo e eh sempre encontravel na tabela
}