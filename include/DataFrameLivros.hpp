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
 *  @attr numLinhas_ <o que é esse atributo?>
 *  @attr contTrocasQuick_  <o que é esse atributo?>
 *  @attr contTrocasHeap_ <o que é esse atributo?>
 *  @attr contComparacoesHeap_ <o que é esse atributo?>
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
     *  @param nomeArquivo <o que é esse parâmetro?>
     *  @param numLinhas <o que é esse parâmetro?>
     *  @param aleatorio <o que é esse parâmetro?>
     *  @param seed <o que é esse parâmetro?>
     * */
    void lerCsv(const std::string &nomeArquivo, int numLinhas = -1, bool aleatorio = false, int seed = 42);

    /**  <Breve descrição>
     *  @param nomeArquivo <o que é esse parâmetro?>
     * */
    void escreverCsv(std::string nomeArquivo);

    /**  <Breve descrição>
     *  @param algoritmoOrd <o que é esse parâmetro?>
     *  @param chave <o que é esse parâmetro?>
     *  @param imprimeMetricas <o que é esse parâmetro?>
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
     *  @param pos_ini <o que é esse parâmetro?>
     *  @param pos_fim <o que é esse parâmetro?>
     *  @return <se tiver algum retorno descreva aqui>
     * */
    //TODO: Documentar esse método, seguindo padrão acima
    int particionamentoQuick(int pos_ini, int pos_fim);

    /**  <Breve descrição>
     *  @param pos_ini <o que é esse parâmetro?>
     *  @param pos_fim <o que é esse parâmetro?>
     *  @return <se tiver algum retorno descreva aqui>
     * */
    //TODO: Documentar esse método, seguindo padrão acima
    void quickSort(int pos_ini, int pos_fim);

    //heapsort
    /**  <Breve descrição>
     *  @param registrosHeap <o que é esse parâmetro?>
     *  @param raiz <o que é esse parâmetro?>
     *  @param n <o que é esse parâmetro?>
     *  @return <se tiver algum retorno descreva aqui>
     * */
    //TODO: Documentar esse método, seguindo padrão acima
    void heapMax(Registro *registrosHeap, int raiz, int n);

    /**  <Breve descrição>
     *  @param registrosHeap <o que é esse parâmetro?>
     *  @param raiz <o que é esse parâmetro?>
     *  @param n <o que é esse parâmetro?>
     *  @return <se tiver algum retorno descreva aqui>
     * */
    //TODO: Documentar esse método, seguindo padrão acima
    void criaHeap(Registro *registrosHeap, int n);

    /**  <Breve descrição>
     *  @param registrosHeap <o que é esse parâmetro?>
     *  @param n <o que é esse parâmetro?>
     *  @return <se tiver algum retorno descreva aqui>
     * */
    //TODO: Documentar esse método, seguindo padrão acima
    void heapSort(Registro *registrosHeap, int n);

    void copiadeRegistros();
};


#endif //TRABALHO_ED2_MATRIZ_HPP
