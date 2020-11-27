#ifndef TRABALHO_ED2_METRICAS_HPP
#define TRABALHO_ED2_METRICAS_HPP

#include <iostream>
#include <chrono>

#define ITER 5  // número de iterações por algoritmo de ordenação
#define ORD_ALGS 2 // número de algoritmos de ordenação que serão testados
#define ARV_ALGS 1 // número de arvores que serão testadas FIXME: quando adicionar Arv B, ARV_ALGS = 2


/* Struct para auxiliar o armazenamento das estatisticas
 *
 *  Atributos
 *  ----------------
 * @attr alg : algoritmo  (Q (quicksort), H (heapsort), V (arvore vermelho-preto) ou B (arvore B))
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

/**
 * Método que fará a contabilização das estatisticas salvas em saida.txt para as seções 1 e 3
 *
 * @param x : Número de amostras (1º linha de entrada.txt)
 * @param N : vetor de inteiros contendo o tamanho de cada uma das x amostras (demais linhas de entrada.txt)
 * @param pathSecao : caminho para a seçao (ex: "../io/secao_1/")
 * @param arquivo : nome do arquivo de saida
 */
void calcularMetricas(const int x, int *&N, const std::string &pathSecao, const std::string &arquivo);

#endif //TRABALHO_ED2_METRICAS_HPP