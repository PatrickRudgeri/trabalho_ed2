#include "../../include/secao_2/Primo.hpp"
#include <iostream>
#include <cmath>

using namespace std;

//Construtor da Classe
Primo::Primo() {}

//Destrutor da Classe
Primo::~Primo() {}

//TODO: documentar os blocos funcionais e variáveis dentro do método
void Primo::criatabela(int n) {

    //variável do tipo ...
    tamanho = n + 2 * (int) (sqrt((double) n)) + 1;
    //variável do tipo ...
    tabelaPrimos = new bool[tamanho];

    //o que faz o for?
    for (int i = 1; i < tamanho; i++)
        tabelaPrimos[i] = true;

    //o que faz o for?
    for (int i = 2; i < (int) sqrt((double) n); i++) {
        if (tabelaPrimos[i]) {
            for (int j = pow(i, 2); j < tamanho; j = j + i)
                tabelaPrimos[j] = false;
        }
    }
}

//TODO: documentar os blocos funcionais e variáveis dentro do método
int Primo::proxPrimo(int num) {

    for (int i = num; i < tamanho; i++) {
        if (tabelaPrimos[i])
            return i;
    }

    for (int i = num; i > 0; i--) {
        if (tabelaPrimos[i])
            return i;
    }

}