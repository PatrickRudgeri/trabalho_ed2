#ifndef TRABALHO_ED2_ARVOREB_H
#define TRABALHO_ED2_ARVOREB_H

#include "../../include/secao_3/NoB.h"

/** Breve descrição da classe
 *
 *  A classe ArvoreB contem o ponteiro para a raiz, e os metodos de inserção e busca da Arvore B.
 *  Alem disso, possui o metodo para executar a cisão quando o nó estiver cheio.
 *
 * */

class ArvoreB {
public:
    //Construtor
    ArvoreB();

    //Destrutor
    virtual ~ArvoreB();

    int getOrdem();
    bool vazia(); // verifica se a árvore está vazia

    /**  <Breve descrição> busca
    *  @param val <indica valor a ser buscado>
    * Faz chamada a funcao auxiliar auxBusca
    *
    */
    bool busca(int val);

    /**  <Breve descrição> busca
   *  @param val <indica valor a ser inserido>
   * Faz chamada a funcao auxiliar auxInsere
   *
   */
    void insere(int val);

private:
    //Ponteiro para raiz_
    NoB* raiz_;

    int ordem_;

    //contadores das metricas
    int qtdComparacoes_;
    int qtdTrocas_;

    bool auxBusca(NoB *p, int val);
    NoB* auxInsere(NoB *p, int val);
    void Cisao(NoB* p);

};

#endif //TRABALHO_ED2_ARVOREB_H
