#ifndef TRABALHO_ED2_MATRIZ_HPP
#define TRABALHO_ED2_MATRIZ_HPP

#include <iostream>
#include "Registro.hpp"
#include "secao_2/HashRegistro.hpp"
#include "secao_2/HashAutor.hpp"
#include "txtLivros.hpp"
#include "secao_3/AVP.hpp"
#include "secao_3/ArvoreB.h"

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
 *  Essa estrutura foi inspirada na estrutura de dados `data.frame` disponivel na linguagem R e
 *   também em Python, através da biblioteca Pandas.
 *  O preenchimento do DataFrame é feito através da função `lerCsv`.
 *  Internamente cada registro é armazenado em uma estrutura chamada Registro, e todos os registros são
 *   armazenados na ED escolhida (ED::VETOR, ED::HASH_TABLE ou ED::ARVORE foram implementadas nesse trabalho)
 *  É importante ressaltar que essa é uma estrutura especializada para o problema proposto no trabalho, porém
 *   pode servir de base para uma generalização futura.
 *
 *  Atributos
 *  ----------------
 *  @attr numLinhas_ : indica a quantidade de Registros lidos
 *  @attr contTrocas1_ : contador de trocas para o algoritmo 1
 *  @attr contTrocas2_ : contador de trocas para o algoritmo 2
 *  @attr contComparacoes1_ : contador de Comparações para o algoritmo 1
 *  @attr contComparacoes2_ : contador de Comparações para o algoritmo 2
 *  @attr *registros_ : Vetor de Registros
 *  @attr *registrosQuick_ : Vetor de Registros para ordenação por Quicksort
 *  @attr *registrosHeap_ : Vetor de Registros para ordenação por Heapsort
 * */
class DataFrameLivros {
public:
    // Construtor sem parâmetros para inicialização dos atributos da classe
    DataFrameLivros();

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
     *  @param nomeArquivo : indica qual o nome do Arquivo
     *  @param numLinhas : indica a quantidade de Registros lidos
     *  @param aleatorio : indica se os Registros serão lidos de forma aleatória ou não
     *  @param seed : semente do gerador aleatório
     *  @param armazInterno : indica se registros serão armazenados em uma tabela hash ou em um vetor de registros
     * */
    void lerCsv(const std::string &nomeArquivo, int numLinhas, bool aleatorio = true, unsigned int seed = 42,
                ED armazInterno = VETOR);

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
     *  @param logMetricas : indica se irá imprimir metricas no terminal
     * */
    void ordenar(AlgOrdenacao algoritmoOrd, const std::string &nomeArqSaida);

    /**  retorna o valor do atributo armazInterno_
     *
     *  @param algoritmoOrd : indica qual algoritmo de ordenação>
     *  @return armazInterno_
     * */
    bool isHashTable() const;

private:
    unsigned seed_;
    int numLinhas_;
    int contTrocas2_;
    int contTrocas1_;
    int contComparacoes1_;
    int contComparacoes2_;
    Registro *registros_;
    Registro *registrosQuick_;
    Registro *registrosHeap_;
    HashRegistro *hashRegistros_;
    HashAutor *hashAutores_;
    ED armazInterno_;
    int countTotalAutores_;
    AVP *arvoreVP_; //Ponteiro para Arvore Vermelho-Preta
    ArvoreB *arvoreB_;


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
