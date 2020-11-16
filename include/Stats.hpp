
#ifndef TRABALHO_ED2_STATS_HPP
#define TRABALHO_ED2_STATS_HPP

#include <iostream>

/* Struct para auxiliar o armazenamento das estatisticas das ordenações
 *
 *  Atributos
 *  ----------------
 * @attr alg : algoritmo de ordeção (Q ou H)
 * @attr n : quantidade de registros
 * @attr comp : mede a quantidade de comparações que foram feitas
 * @attr trocas : medida de trocas/cópias de posições
 * @attr seed : semente de randomização
 * @attr tempo : tempo de processamento
 *
 * */
struct Stats {

    /**
     * método para imprimir a struct em `os`
     * */
    friend std::ostream &operator<<(std::ostream &os, const Stats &stats);

    /**
     * método para ler de istream os atributos de stats
     * */
    friend std::istream &operator>>(std::istream &is, Stats &stats);

    /*
     * retorna um atributo de acordo com o enum metricas
     * */
    double getStats(int m);

    char alg;
    int n, comp, trocas;
    unsigned seed;
    double tempo;

    /*Contem as métricas utilizadas*/
    typedef enum {
        _comp,
        _trocas,
        _tempo
    } metricas;
};


#endif //TRABALHO_ED2_STATS_HPP
