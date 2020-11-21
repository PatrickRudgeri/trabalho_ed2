//
// Created by Larissa on 19/11/2020.
//

#ifndef TRABALHO_ED2_NOVP_H
#define TRABALHO_ED2_NOVP_H

/** Breve descrição da classe
 *
 *  A classe noVp contem atributos de um noh de uma Arvore Vermelho-Preta
 *  ou seja, a informacao do noh, os ponteiros para esquerda e direita, para o pai
 *  e a cor do noh (Vermelho ou Preta)
 *
 *  Atributos
 *  ----------------
 *  @attr info <valor armazenado no noh>
 *  @attr esq <ponteiro para o filho esquerdo>
 *  @attr dir <ponteiro para o filho direito>
 *  @attr pai <ponteiro para o pai>
 *  @attr tipocor <cor do noh>
 *
 * */


//duas cores: V-> Vermelho, P-> Preto
enum cor { VERMELHO, PRETO };

class NoVP
{
public:

    //Construtor da classe
    NoVP();
    //Destrutor da classe
    ~NoVP();

    int info;
    NoVP* esq;
    NoVP* dir;
    NoVP* pai;
    enum cor tipocor;

    //Sets
    void setEsq(NoVP *p);
    void setInfo(int val);
    void setDir(NoVP *p);
    void setPai(NoVP *p);
    void setCor(cor c);

    //Gets
    NoVP* getEsq() const;
    int getInfo() const;
    NoVP* getDir() const;

    cor getCor() const;
    /*
		Diferentemente de getCor(), o noh_cor verifica a cor dos nohs NIL
    */
    static cor noh_cor(NoVP* n);


    static NoVP* getPai(NoVP* n);
    static NoVP* getAvo(NoVP* n);
    static NoVP* getIrmao(NoVP* n);
    static NoVP* getTio(NoVP* n);


};

#endif //TRABALHO_ED2_NOVP_H
