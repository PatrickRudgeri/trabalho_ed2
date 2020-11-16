#include <fstream>  // ifstream
#include <cassert>  // assert
#include <algorithm> // replace
#include "../include/txtLivros.hpp"

using namespace std;

namespace txt {
    void lerEntrada(int *x, int *&n, const string &pathArquivo) {
        string linha, temp;
        ifstream arq(pathArquivo);
        int i = 0;
        assert(arq.is_open());
        assert(arq.good());
        getline(arq, linha);

        if (!linha.empty()) {
            *x = stoi(linha);

            n = new int[*x];

            while (getline(arq, linha)) {
                if (!linha.empty() && linha.length() > 1) {
                    n[i] = stoi(linha);
                    i++;
                }
            }
        }
        arq.close();
    }

    void lerSaida(Stats *&stats, const string &pathArqSaida) {
        string linha, strExec, strStats;
        ifstream arq(pathArqSaida);

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
}