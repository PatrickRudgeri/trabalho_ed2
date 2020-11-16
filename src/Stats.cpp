#include "../include/Stats.hpp"

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
