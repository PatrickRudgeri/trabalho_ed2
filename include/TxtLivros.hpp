#ifndef TRABALHO_ED2_TXTLIVROS_HPP
#define TRABALHO_ED2_TXTLIVROS_HPP

#include <iostream>
#include <sstream>

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
    friend std::ostream &operator<<(std::ostream &os, const Stats &stats) {
        os << "alg: " << stats.alg << " n: " << stats.n << " seed: " << stats.seed << " comp: " << stats.comp
           << " trocas: " << stats.trocas
           << " seed: " << stats.seed << " tempo: " << stats.tempo;
        return os;
    }

    /**
     * método para ler de istream os atributos de stats
     * */
    friend std::istream &operator>>(std::istream &is, Stats &stats) {
        is >> stats.alg >> stats.n >> stats.seed >> stats.comp >> stats.trocas >> stats.tempo;
        return is;
    }
    /*Contem as métricas utilizadas*/
    typedef enum{
        _comp,
        _trocas,
        _tempo
    } metricas;

    /*
     * retorna um atributo de acordo com o enum metricas
     * */
    double getStats(int m){
        if(m == metricas::_comp)
            return (double)comp;
        else if(m == metricas::_trocas)
            return (double)trocas;
        else
            return tempo;
    }

    char alg;
    int n, comp, trocas;
    unsigned seed;
    double tempo;
};

/**
 * Classe para leitura e escrita em arquivos flat
 * */
class TxtLivros {
public:

    /**  Método para ler os parametros X e N do arquivo de entrada
     *  @param x : Número de iterações
     *  @param n : vetor de inteiros de tamanho x que será preenchido
     *  @param nomeArqEntrada : nome do arquivo que contém os parametros de entrada
     * */
    static void lerEntrada(int *x, int *&n, const std::string &nomeArquivo = "entrada.txt");

    /**  Método para ler o arquivo de saida e preencher a struct Stats
     *  @param stats : struct que armazena as métricas
     *  @param nomeArqSaida : nome do arquivo de saída
     * */
    static void lerSaida(Stats *&stats, const std::string &nomeArqSaida = "saida.txt");
};


#endif //TRABALHO_ED2_TXTLIVROS_HPP
