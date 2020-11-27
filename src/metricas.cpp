#include "../include/metricas.hpp"
#include "../include/txtLivros.hpp"
#include <fstream>
#include <cassert>

std::ostream &operator<<(std::ostream &os, const Stats &stats) {
    os << "alg: " << stats.alg << " n: " << stats.n << " seed: " << stats.seed << " comp: " << stats.comp
       << " trocas: " << stats.trocas
       << " seed: " << stats.seed << " tempo: " << stats.tempo;
    return os;
}

std::istream &operator>>(std::istream &is, Stats &stats) {
    is >> stats.alg >> stats.n >> stats.seed >> stats.comp >> stats.trocas >> stats.tempo;
    return is;
}

double Stats::getStats(int m) {
    if (m == metricas::_comp)
        return (double) comp;
    else if (m == metricas::_trocas)
        return (double) trocas;
    else
        return tempo;
}

void calcularMetricas(const int x, int *&N, const std::string &pathSecao, const std::string &arquivo) {
    double somaQuick, somaHeap, somaVP, somaB;
    int secao = pathSecao == "../io/secao_1/" ? 1 : 3;
    int qtAlgs = secao == 1 ? ORD_ALGS : ARV_ALGS;

    auto *stats = new Stats[x * ITER * qtAlgs]; // x * 5 iter * 2 algs. ord.
    // lê o arquivo de saida e armazena em um vetor de Stats de tamanho x * ITER * ORD_ALGS
    txt::lerSaida(stats, pathSecao + arquivo);

    // itera sobre as métricas armazenadas no enum metricas
    for (int m = Stats::metricas::_comp; m <= Stats::metricas::_tempo; m++) {
        std::string statsNome = m == 0 ? "comp" : (m == 2 ? "tempo" : "trocas");
        std::ofstream arqStats(pathSecao + "stats/stats_" + statsNome + ".txt");

        assert(arqStats.is_open() && arqStats.good());// teste do arquivo
        if (secao == 1) {
            somaQuick = 0;
            somaHeap = 0;
            for (int i = 0, j = 0; i < x * ITER * qtAlgs;) {
                if (stats[i].alg == 'Q' && stats[i].n == N[j]) {
                    somaQuick += stats[i].getStats(m);
                }
                if (stats[i].alg == 'H' && stats[i].n == N[j]) {
                    somaHeap += stats[i].getStats(m);
                }
                i++;
                if (i % (ITER * qtAlgs) == 0) {
                    arqStats << N[j] << "\t" << somaQuick / ITER << "\t" << somaHeap / ITER << "\t" << std::endl;
                    somaQuick = 0;
                    somaHeap = 0;
                    j++;
                }
            }
        }else {
            somaVP = 0;
            somaB = 0;
            for (int i = 0, j = 0; i < x * ITER * qtAlgs;) {
                if (stats[i].alg == 'V' && stats[i].n == N[j]) {
                    somaVP += stats[i].getStats(m);
                }
                if (stats[i].alg == 'P' && stats[i].n == N[j]) {
                    somaB += stats[i].getStats(m);
                }
                i++;
                if (i % (ITER * qtAlgs) == 0) {
                    arqStats << N[j] << "\t" << somaVP / ITER << "\t" << somaB / ITER << "\t" << std::endl;
                    somaVP = 0;
                    somaB = 0;
                    j++;
                }
            }
        }
        arqStats.close();
    }

    delete[] stats;
}

