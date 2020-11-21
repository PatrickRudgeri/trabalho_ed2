//
// Created by Larissa on 19/11/2020.
//

#ifndef TRABALHO_ED2_AVP_H
#define TRABALHO_ED2_AVP_H
#include "noVP.h"


/** Breve descrição da classe
 *
 *  A classe AVP contem o ponteiro para a raiz, e os metodos da Arvore Vermelho Preta.
 *  Ou seja, metodos de insercao, busca e remocao.
 *  Alem disso, metodos das rotacoes a esquerda e direita
 *  e verificacao das propriedades.
 *
 * */

class AVP{

public:
    //Construtor
    AVP();
    //Destrutor
    ~AVP();
    //Ponteiro para raiz
    NoVP* raiz;

    //contadores das metricas
    int qtdComparacoes;

    int qtdTrocas;

    //métodos

    //void insere(int val);


    //Rotacoes

    /**  <Breve descrição> rotacao_esquerda
    *  @param n <indica noh a ser rotacionado>
    *	Executa uma rotacao simples a esquerda
        */
    void rotacao_esquerda(NoVP* n);
    /**  <Breve descrição> rotacao_direita
    *  @param n <indica noh a ser rotacionado>
    *	Executa uma rotacao simples a direita
        */
    void rotacao_direita(NoVP* n);

    //Insercoes

    /**  <Breve descrição> insere
    *  @param val <indica valor a ser inserido>
    *	Aloca um novo noh na memoria, coloca inicialmente como vermelho,
    *	e chama a funcao auxinsere para inserir valor na arvore
        */
    void insere(int val);
    /**  <Breve descrição> auxinsere
    *  @param raiz <indica ponteiro para raiz da arvore>
    *  @param n <indica novo noh a ser inserido>
    *	Chama a funcoes insereRecursivo para insercao do noh na folha
    *   e a funcao insereCorrecao para verifica as propriedades da VP
        */

    NoVP* auxinsere(NoVP* raiz, NoVP* n);

    /**  <Breve descrição> insereCorrecao
    *  @param n <indica novo noh a ser inserido>
    *	Para correcao, existem varios casos de insercao da arvore vermelho-preto para lidar.
    *   Para cada caso sao chamadas insereCaso 1,2,3 ou 4.
        */
    void insereCorrecao(NoVP* n);

    /**  <Breve descrição> insereRecursivo
    *  @param raiz <indica ponteiro para raiz da arvore>
    *  @param n <indica novo noh a ser inserido>
    * Desce recursivamente na arvore ate que uma folha seja encontrada, em seguida o noh eh inserido.
        */
    void insereRecursivo(NoVP* raiz, NoVP* n);

    /**  <Breve descrição> insereCaso1
    *  @param n <indica novo noh a ser inserido>
    *
    *	Insere Caso 1: O noh n sera inserido na raiz da arvore
        */

    static void insereCaso1(NoVP* n);

    /**  <Breve descrição> insereCaso2
    *  @param n <indica novo noh a ser inserido>
    *
    *	Insere Caso 2: Verificacao se a o pai do noh inserido eh preto
        */
    void insereCaso2();

    /**  <Breve descrição> insereCaso3
    *  @param n <indica novo noh a ser inserido>
    *
    *	Insere Caso 3: se o pai P e o tio T sao vermelhos, ambos podem ser repintados de preto.
    A verificacao das propriedades no noh Avo eh feita.
        */
    static void insereCaso3(NoVP* n);


    /**  <Breve descrição> insereCaso4
    *  @param n <indica novo noh a ser inserido>
    *
    *	Insere Caso 4:  O pai P eh vermelho, mas o tio T eh preto. As rotacoes necessarias sao realizadas.
    *   A propriedade de ambos os filhos de cada noh vermelho são pretos eh restaurada na etapa 2.
        */
    void insereCaso4(NoVP* n);

    /**  <Breve descrição> insereCaso4etapa2
    *  @param n <indica novo noh a ser inserido>
    *
    *	Insere Caso 4 etapa 2:  Faz a rotação sobre o avo A, e troca-se as cores do pai (P) e avo (A)
        */

    void insereCaso4etapa2(NoVP* n);


    //Impressao

    /**  <Breve descrição> imprime_AVP
    * Faz a chamada da funcao auxiliar imprime_aux
    *
        */
    void imprime_AVP();

    /**  <Breve descrição> imprime_aux
    * @param n <indica novo noh passado>
    * @param indent <indica identacao desejada>
    * Imprime a arvore a partir do noh passado e a identacao desejada
	*
        */
    void imprime_aux(NoVP* n, int indent);


    //Busca

    /**  <Breve descrição> auxBusca
    * @param n <indica em qual noh sera o inicio da busca>
    * @param val <indica valor a ser buscado>
    * @return boleano verdadeiro (valor esta na arvore) ou false (valor nao encontrado)
    * AuxBusca percorre a arvore igualmente a uma ABB(arvore binaria de busca) a partir do noh
    e valor passado
        */
    bool auxBusca(NoVP *n, int val);

    /**  <Breve descrição> busca
    *  @param val <indica valor a ser buscado>
    * Faz chamada a funcao auxiliar auxBusca
	*
        */
    bool busca(int val);

    /**  <Breve descrição> busca
   * @param val <indica valor a ser buscado>
   * Retorna o ponteiro do Noh onde foi encontrado o valor passado
   * @return Ponteiro de NoVP
   *
       */
    NoVP* busca_no(int val) const;

    /**  <Breve descrição> noMaximo
    * @param n <indica noh passado>
    * Retorna o ponteiro do Noh de maior valor a partir do noh passado por parametro.
    * @return Ponteiro de NoVP
	*
        */
    static NoVP* noMaximo(NoVP* n);


    //Propriedades da Arvore Vermelho-Preta

    /**  <Breve descrição> verifica_propriedades
    * Chama todas as funcoes de propriedades (1,2,4,5)
    * OBS: * A propriedade 3 (todas folha (NIL) eh preto eh verificada no metodo "cor NoVP::noh_cor(NoVP* n)" em noVP.cpp
    */

    void verifica_propriedades();


    /** <Breve descrição> verifica_propriedade1
    * @param n <indica noh passado>
 	* Funcao que verifica a propriedade 1 (todas no de uma arvore VP eh vermelho ou preta )
 	* e desce recursivamente a arvore ate as folhas verificando cada noh
 	*/

    void verifica_propriedade1(NoVP* n);

    /** <Breve descrição> verifica_propriedade2
    * @param raiz <indica noh raiz passado>
 	* Funcao que verifica a propriedade 2 (a raiz da arvore VP eh sempre preta )
 	* e desce recursivamente a arvore ate as folhas verificando cada noh
 	*/

    static void verifica_propriedade2(NoVP* raiz) ;

    /*
    * OBS: * A propriedade 3 (todas folha (NIL) eh preto eh verificada no metodo "cor NoVP::noh_cor(NoVP* n)" em noVP.cpp
    */

    /** <Breve descrição> verifica_propriedade4
    * @param n <indica noh  passado>
 	*  Funcao que verifica a propriedade 4 os filhos a direita e a esquerda de um noh vermelho sao sempre pretos
 	*/

    void verifica_propriedade4(NoVP* n);

    /** <Breve descrição> verifica_propriedade5
    * @param raiz <indica noh raiz passado>
 	*  Chama a funcao auxiliar para verificar a altura preta
 	*/

    void verifica_propriedade5(NoVP* raiz);

    /** <Breve descrição> verifica_propriedade5_aux
    * @param n <indica noh raiz passado>
    * @param contador <conta cada noh preto>
    * @param contador_caminho_negro <contador da altura preta>
 	*  Funcao que verifica a propriedade 5 da altura negra
 	*/

    void verifica_propriedade5_aux(NoVP* n, int contador, int* contador_caminho_negro);

    //Remocao

    //OBS: ainda nao funcional


    /** <Breve descrição> deleta
    * @param n <indica noh raiz passado>
 	* Chama as funcoes auxiliares de remocao (casos 1,2,3,4,5,6)
 	*/
    void deleta(int val);


    /** <Breve descrição> deleta_caso1
    * @param n <indica noh passado>
 	* Caso 1: N eh unico noh na arvore
 	*/
    void deleta_caso1(NoVP* n);

    /** <Breve descrição> deleta_caso2
    * @param n <indica noh passado>
 	* Caso 2: O irmao(I) eh vermelho, invertemos as cores do pai (P) e  do irmao (I) e, em seguida,
 	giramos para a esquerda em P. Chamamos as proximas etapas para outras verificacoes.
 	*/
    void deleta_caso2(NoVP* n);

    /** <Breve descrição> deleta_caso3
    * @param n <indica noh passado>
 	* Caso 3: Pai (P), Irmao (I) e filhos de I são pretos. Neste caso, simplesmente repintamos I vermelho.
 	*/
    void deleta_caso3(NoVP* n);

    /** <Breve descrição> deleta_caso4
    * @param n <indica noh passado>
 	* Caso 4:Os filhos de I(Irmao) e o proprio I são pretos, mas Pai (P) é vermelho.
 	* Neste caso, simplesmente trocamos as cores de I e P.
 	*/
    void deleta_caso4(NoVP* n);

    /** <Breve descrição> deleta_caso5
    * @param n <indica noh passado>
 	* Caso 5: Irmao (I) eh preto, o filho esquerdo de I eh vermelho, o filho direito de I eh preto e N eh
	*  o filho esquerdo de seu pai. Nesse caso, giramos para a direita em I
 	*/
    void deleta_caso5(NoVP* n);

    /** <Breve descrição> deleta_caso6
    * @param n <indica noh passado>
 	* Caso 6: Irmao (I) eh preto, filho direito de I eh vermelho, e N eh o filho esquerdo do pai P .
	* Neste caso, giramos a esquerda em P
 	*/
    void deleta_caso6(NoVP* n);


    /** <Breve descrição> substitui_no
    * @param velho <indica noh a ser substituido>
    * @param novo <indica noh a ser colocado>
 	* Funcao que substitui um noh antigo por um novo
 	*/
    void substitui_no(NoVP* velho, NoVP* novo);

    /** <Breve descrição> auxDestrutor
   * @param p <indica noh passado>
    * Funcao que auxilia o destrutor, ou seja, desaloca a arvore da memoria
    */

    void auxDestrutor(NoVP *p);


    /** <Breve descrição> getRaiz
 	* Retorna a raiz da arvore
 	*/
    NoVP* getRaiz()       { return raiz; };

    /** <Breve descrição> setRaiz
 	* Seta uma nova raiz para a arvore
 	*/
    void setRaiz(NoVP* r)       { raiz= r; };


};

#endif //TRABALHO_ED2_AVP_H
