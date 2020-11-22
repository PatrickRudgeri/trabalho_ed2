#include <iostream>

#ifndef TRABALHO_ED2_NOVP_HPP
#define TRABALHO_ED2_NOVP_HPP

/** Breve descri��o da classe
 *
 *  A classe noVp contem atributos de um noh de uma Arvore Vermelho-Preta
 *  ou seja, a informacao do noh, os ponteiros para esquerda e direita, para o pai_
 *  e a Cor do noh (Vermelho ou Preta)
 *
 *  Atributos
 *  ----------------
 *  @attr info_ <valor armazenado no noh>
 *  @attr esq_ <ponteiro para o filho esquerdo>
 *  @attr dir_ <ponteiro para o filho direito>
 *  @attr pai_ <ponteiro para o pai_>
 *  @attr tipoCor_ <Cor do noh>
 *
 * */

//duas cores: V-> Vermelho, P-> Preto
enum Cor {
    VERMELHO, PRETO
};

class NoVP {

public:

    //Construtor da classe
    NoVP();

    //Destrutor da classe
    ~NoVP();

    //Sets
    void setEsq(NoVP *p);

    void setInfo(int val);

    void setDir(NoVP *p);

    void setPai(NoVP *p);

    void setCor(Cor c);

    //Gets
    NoVP *getEsq() const;

    int getInfo() const;

    NoVP *getDir() const;

    Cor getCor() const;

    NoVP *getPai();

    NoVP *getAvo();

    NoVP *getIrmao();

    NoVP *getTio();

private:
    int info_;
    NoVP *esq_;
    NoVP *dir_;
    NoVP *pai_;
    Cor tipoCor_;
};

#endif //TRABALHO_ED2_NOVP_HPP
