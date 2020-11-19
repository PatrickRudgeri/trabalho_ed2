#include "../../include/secao_2/Primo.hpp"
#include <iostream>
#include <cmath>

using namespace std;

bool *Primo::tabelaPrimos = NULL;
int Primo::tamanho = 0;

//TODO: documentar os blocos funcionais e variáveis dentro do método
void Primo::criarTabela(int n) {

    //variável do tipo ...
    tamanho = n + 2 * ((int) (sqrt((double) n)) + 1) + 1;

    //variável do tipo ...
    tabelaPrimos = new bool[tamanho];
    int m = (int) sqrt((double) n) + 1; // arrumar

    //todos na tabela são primos e depois conforme é rodado.. ele tira os multiliplos dos anteriores
    for (int i = 1; i < tamanho; i++)
        tabelaPrimos[i] = true;

    //muda para falso(diz que não é primo) todo mundo que é multiplo de um número primo. restando quem é primo como true
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
    return -1; // question: Essa função deve ter um retorno padrão, entãp defini -1 caso os laços acima sejam completados. VERIFICAR
}