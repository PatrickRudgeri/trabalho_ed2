#ifndef TRABALHO_ED2_MATRIZ_HPP
#define TRABALHO_ED2_MATRIZ_HPP

#include <iostream>
#include "Registro.hpp"
#include "secao_2/HashRegistro.hpp"
#include "secao_2/HashAutor.hpp"
#include "txtLivros.hpp"

/** Constantes que representam os algorítmos disponíveis para ordenação
 * */
enum AlgOrdenacao {
    QUICKSORT,
    HEAPSORT
};

enum ED{
    VETOR,
    HASH_TABLE,
    ARVORE
};

/** Classe que representa o dataset de Livros
 *
 *  TODO: Descrição detalhada da classe
 *
 *  Atributos
 *  ----------------
 *  @attr numLinhas_ : indica a quantidade de Registros lidos
 *  @attr contTrocasQuick_ : contador de trocas no QuickSort
 *  @attr contTrocasHeap_ : contador de trocas no HeapSort
 *  @attr contComparacoesHeap_ : contador de Comparações no HeapSort
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
    int contTrocasQuick_;
    int contTrocasHeap_;
    int contComparacoesHeap_;
    int contComparacoesQuick_;
    Registro *registros_;
    Registro *registrosQuick_;
    Registro *registrosHeap_;
    HashRegistro *hashRegistros_; //TODO: documentar
    HashAutor *hashAutores_; //TODO: documentar
    ED armazInterno_; //TODO: documentar

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
