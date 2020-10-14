#include <iostream>

using namespace std;
#define TAM_MAX 10

int particionamento(string vet[TAM_MAX], int pos_ini, int pos_fim) {

    int p = (pos_ini + pos_fim) / 2;
    string pivo = vet[p];
    int esq = pos_ini;
    int dir = pos_fim;
    string aux;

    while (esq < dir) {

        while (vet[esq] < pivo) {
            esq++;
        }

        while (vet[dir] > pivo) {
            dir--;
        }
        if (esq <= dir) {
            if (dir == p) {
                p = esq;
            }
            if (esq == p) {
                p = dir;
            }

            aux = vet[dir];
            vet[dir] = vet[esq];
            vet[esq] = aux;
        }
        esq++;
        dir--;
    }

    return p + 1;

}

void quickSort(string vet[TAM_MAX], int pos_ini, int pos_fim) {
    if (pos_fim - pos_ini > 0) {
        int q = particionamento(vet, pos_ini, pos_fim);
        quickSort(vet, pos_ini, q - 1);
        quickSort(vet, q, pos_fim);
    }

}

int main_quicksort() {
    string vet[6] = {"aaa", "cc", "bb", "dd", "ff", "ee"};

    quickSort(vet, 0, 5);

    for (int i = 0; i < 6; i++)
        cout << vet[i];
    return 0;
}
