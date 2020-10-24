#include <fstream>  // ifstream
#include <cassert>  // assert
#include <algorithm> // replace
#include "../include/TxtLivros.hpp"

using namespace std;

void TxtLivros::lerEntrada(int *x, int *&n, const std::string &nomeArqEntrada) {
    std::string linha, temp;
    std::ifstream arq("../io/" + nomeArqEntrada);
    int i = 0;
    assert(arq.is_open());
    assert(arq.good());
    getline(arq, linha);

    if (!linha.empty()) {
        *x = std::stoi(linha);

        n = new int[*x];

        while (getline(arq, linha)) {
            if (!linha.empty() && linha.length() > 1) {
                n[i] = std::stoi(linha);
                i++;
            }
        }
    }
    arq.close();
}

//fixme: Testando issue automation
// labels: bug, enhancement
void TxtLivros::lerSaida(Stats *&stats, const std::string &nomeArqSaida) {
    string linha, strExec, strStats;
    ifstream arq("../io/" + nomeArqSaida);

    assert(arq.is_open());
    assert(arq.good());

    int numLinha = 0;
    while (arq.good() && !arq.eof()) {
        getline(arq, linha);
        if (linha.size() > 1) {
            stringstream streamLinha(linha);
            while (streamLinha >> stats[numLinha]) {
                numLinha++;
            }
        }
    }
    arq.close();
}
