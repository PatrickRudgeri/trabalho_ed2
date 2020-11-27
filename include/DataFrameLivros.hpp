#ifndef TRABALHO_ED2_MATRIZ_HPP
#define TRABALHO_ED2_MATRIZ_HPP

#include <iostream>
#include "Registro.hpp"
#include "secao_2/HashRegistro.hpp"
#include "secao_2/HashAutor.hpp"
#include "txtLivros.hpp"
#include "secao_3/AVP.hpp"
#include "secao_3/ArvoreB.h"

// Constantes que representam os tipos de árvores disponíveis
enum AlgArvores {
    VP,
    B
};

// Constantes que representam os algorítmos disponíveis para ordenação
enum AlgOrdenacao {
    QUICKSORT,
    HEAPSORT
};
// Constantes que representam as estruturas de dados disponíveis para o armazenamento dos registros
enum ED{
    // armazenamento simples com um vetor. Utilizado para a ordenação na seçao 1
    VETOR,
    // armazenamento em uma tabela hash para facilitar a inclusão de apenas registros únicos. Utilizado na seção 2
    HASH_TABLE,
    // registros são armazenados em arvores. Utilizado na seção 3
    ARVORE
};

/** DataFrameLivros: Classe que representa o dataset de Livros
 *
 *  O preenchimento do DataFrame é feito através da função `lerCsv`.
 *  Internamente cada registro é armazenado em uma estrutura chamada Registro, e todos os registros em uma ED de Registros
 *
 *  Atributos
 *  ----------------
 *  @attr numRegistros_ : indica a quantidade de Registros lidos
 *  @attr *registros_ : Vetor de Registros
 *  @attr *registrosQuick_ : Vetor de Registros para ordenação por Quicksort
 *  @attr *registrosHeap_ : Vetor de Registros para ordenação por Heapsort
 * */
class DataFrameLivros {
public:
    DataFrameLivros();

    DataFrameLivros(std::string pathSaida, ED armazInterno);

    DataFrameLivros(std::string pathSaidaInsercao, std::string pathSaidaBusca, ED armazInterno);

// Destrutor da classe
    ~DataFrameLivros();

    /** Método get do vetor registros_
     *
     *  @return : vetor registros_
     * */
    Registro *getRegistros();

    /**  setar o vetor registros_ com outro vetor de Registros
     *
     *  @param registros : vetor de Registros externos
     * */
    void setRegistros(Registro *registros);

    /**  Utilizado para criar e preencher o vetor de Registros
     *
     *  @param pathDataset : indica qual o nome do Arquivo
     *  @param numLinhas : indica a quantidade de Registros lidos
     *  @param aleatorio : indica se os Registros serão lidos de forma aleatória ou não
     *  @param seed : semente do gerador aleatório
     * */
    void lerCsv(const std::string &pathDataset, int numLinhas, bool aleatorio, unsigned int seed);

    /**  Insere um registro no dataframe
     *
     *  @param camposStrVet : vetor de string contendo os campos do registro
     *  @param index : se for != 1  corresponde a posição a ser inserida no vetor registro
     *  @return true se inseriu com sucesso, false caso contrário
     * */
    bool inserirRegistro(std::string *camposStrVet, int index = -1);

    /**  Ordenar o vetor interno de registros
     *
     *  @param algoritmoOrd : indica qual algoritmo de ordenação>
     * */
    void ordenar(AlgOrdenacao algoritmoOrd);

    void testeBuscasArv(AlgArvores arv);

    void setPathSaida(std::string saidaInsercao, std::string saidaBusca);

    void setPathSaida(std::string pathSaida);

    void setArmazInterno(ED armazInterno);

private:
    unsigned seed_;
    int numRegistros_;
    int countTotalAutores_;
    Registro *registros_;
    Registro *registrosQuick_;
    Registro *registrosHeap_;
    HashRegistro *hashRegistros_;
    HashAutor *hashAutores_;
    ED armazInterno_;
    AVP *arvoreVP_; //Ponteiro para Arvore Vermelho-Preta
    ArvoreB *arvoreB_;
    std::string saidaInsercao_; // path de saida das estatisticas de inserção
    std::string saidaBusca_; // path de saida das estatisticas de busca
    std::string saidaOrdenacao_; // path de saida das estatisticas de ordenacao
    Stats metricasOrdenacao_[2]; // um para cada algortmo de ordenacao implementado
    Stats metricasArvInsercao_[2]; // para inserção de cada arvore implementada
    Stats metricasArvBusca[2]; // para busca de cada arvore implementada

    void inicializarAtributos();

    //métodos de ordenação
    //quicksort
    /**  Responsável por pegar uma sequência da entrada e dividi-la em duas partes
     *
     *  @param posIni : Posição inicial do Vetor a ser Ordenado
     *  @param posFim : Posição final do Vetor a ser Ordenado
     *  @return : Retorna o indice do pivô+1
     * */
    int particionamentoQuick(int posIni, int posFim);

    /**  Método para ordenação quicksort
     *
     *  @param posIni : Posição inicial do Vetor a ser Ordenado
     *  @param posFim : Posição final do Vetor a ser Ordenado
     * */
    void quickSort(int posIni, int posFim);

    //heapsort
    /**  TODO:<Breve descrição>
     *
     *  @param registrosHeap : Vetor para armazenar Registros Ordenados por HeapSort
     *  @param raiz : Raiz da Heap
     *  @param n : Número de nós da Heap
     * */
    void heapMax(Registro *registrosHeap, int raiz, int n);

    /**  TODO:<Breve descrição>
     *
     *  @param registrosHeap : Vetor para armazenar Registros Ordenados por HeapSort
     *  @param raiz : Raiz da Heap
     *  @param n : Número de nós da Heap
     * */
    void criaHeap(Registro *registrosHeap, int n);

    /**  TODO:<Breve descrição>
     *
     *  @param registrosHeap : Vetor para armazenar Registros Ordenados por HeapSort
     *  @param n : Número de nós da Heap
     * */
    void heapSort(Registro *registrosHeap, int n);
};


#endif //TRABALHO_ED2_MATRIZ_HPP
