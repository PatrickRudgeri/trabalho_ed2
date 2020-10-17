#ifndef TRABALHO_ED2_MATRIZ_HPP
#define TRABALHO_ED2_MATRIZ_HPP

#include <iostream>
#include "Registro.hpp"

enum AlgOrdenacao {
    quicksort,
    heapsort
};
enum ChavesOrdenacao {
    titulo,
    id
};

/** Breve descrição da classe
 *
 *  Descrição detalhada da classe
 *
 *  Atributos
 *  ----------------
 *  @attr numLinhas_ <indica a quantidade de Registros lidos>
 *  @attr contTrocasQuick_  <contador de trocas no QuickSort>
 *  @attr contTrocasHeap_ <contador de trocas no HeapSort>
 *  @attr contComparacoesHeap_ <contador de Comparações no HeapSort>
 *  @attr *registros_   <o que é esse atributo?>
 *  @attr *registrosQuick_ <o que é esse atributo?>
 *  @attr *registrosHeap_ <o que é esse atributo?>
 * */
class DataFrameLivros {
public:
    // Construtor sem parâmetros para inicialização dos atributos da classe
    DataFrameLivros();

    // Destrutor da classe
    ~DataFrameLivros();

    /**  <Breve descrição>
     *  @return <se tiver algum retorno descreva aqui>
     * */
    Registro *getRegistros();

    /**  <Breve descrição>
     *  @param registros <o que é esse parâmetro?>
     * */
    void setRegistros(Registro *registros);

    /**  <Breve descrição>
     *  @param nomeArquivo <indica qual o nome do Arquivo>
     *  @param numLinhas <indica a quantidade de Registros lidos>
     *  @param aleatorio <indica se os Registros serão lidos de forma aleatória ou não>
     *  @param seed <semente do gerador aleatório>
     * */
    void lerCsv(const std::string &nomeArquivo, int numLinhas = -1, bool aleatorio = false, int seed = 42);

    /**  <Breve descrição>
     *  @param nomeArquivo <indica qual o nome do Arquivo>
     * */
    void escreverCsv(std::string nomeArquivo);

    /**  <Breve descrição>
     *  @param algoritmoOrd <indica qual algoritmo de ordenação>
     *  @param chave <o que é esse parâmetro?> //vai usar?
     *  @param imprimeMetricas <indica se irá imprimir metricas>
     * */
    void ordenar(AlgOrdenacao algoritmoOrd, ChavesOrdenacao chave = ChavesOrdenacao::titulo,
                 bool imprimeMetricas = false);

private:
    int numLinhas_;
    int contTrocasQuick_;
    int contTrocasHeap_;
    int contComparacoesHeap_;
    int contComparacoesQuick_;
//    ChavesOrdenacao chaveOrd_; // para usar se getCampoChave() for implementado
    Registro *registros_;
    Registro *registrosQuick_;
    Registro *registrosHeap_;

    //métodos de ordenação
    //quicksort
    /**  <Breve descrição>
     *  @param pos_ini <Posição inicial do Vetor a ser Ordenado>
     *  @param pos_fim <Posição final do Vetor a ser Ordenado>
     *  @return <se tiver algum retorno descreva aqui>
     * */
    //TODO: Documentar esse método, seguindo padrão acima
    int particionamentoQuick(int pos_ini, int pos_fim);

    /**  <Breve descrição>
     *  @param pos_ini <Posição inicial do Vetor a ser Ordenado>
     *  @param pos_fim <Posição final do Vetor a ser Ordenado>
     *  @return <se tiver algum retorno descreva aqui>
     * */
    //TODO: Documentar esse método, seguindo padrão acima
    void quickSort(int pos_ini, int pos_fim);

    //heapsort
    /**  <Breve descrição>
     *  @param registrosHeap <Vetor para armazenar Registros Ordenados por HeapSort>
     *  @param raiz <Raiz da Heap>
     *  @param n <Número de nós da Heap>
     *  @return <se tiver algum retorno descreva aqui>
     * */
    //TODO: Documentar esse método, seguindo padrão acima
    void heapMax(Registro *registrosHeap, int raiz, int n);

    /**  <Breve descrição>
     *  @param registrosHeap <Vetor para armazenar Registros Ordenados por HeapSort>
     *  @param raiz <Raiz da Heap>
     *  @param n <Número de nós da Heap>
     *  @return <se tiver algum retorno descreva aqui>
     * */
    //TODO: Documentar esse método, seguindo padrão acima
    void criaHeap(Registro *registrosHeap, int n);

    /**  <Breve descrição>
     *  @param registrosHeap <Vetor para armazenar Registros Ordenados por HeapSort>
     *  @param n <Número de nós da Heap>
     *  @return <se tiver algum retorno descreva aqui>
     * */
    //TODO: Documentar esse método, seguindo padrão acima
    void heapSort(Registro *registrosHeap, int n);

    void copiadeRegistros();
};


#endif //TRABALHO_ED2_MATRIZ_HPP
