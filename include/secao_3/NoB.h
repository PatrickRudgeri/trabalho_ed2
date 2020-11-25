#ifndef TRABALHO_ED2_NOB_H
#define TRABALHO_ED2_NOB_H

/** Breve desncri��o da classe
 *
 *  A classe oB contem atributos de um noh de uma Arvore B,
 *  ou seja,o vetor Chave com as informações contidas no noh, os ponteiros para os filhos_ e para o pai_
 *  Alem disso possui o ponteiro para o Registro(Livro) inserido
 *
 *  Atributos
 *  ----------------
 *  @attr Chaves_ <vetor com as informações contidas no noh>
 *  @attr n_ <numero de informações no vetor Chave>
 *  @attr vetorFilhos_ <vetor de ponteiro para os filhos>
 *  @attr pai_ <ponteiro para o pai_>
 *  @attr ehFolha_ <booleano que indica se o noh e folha ou nao>
 *
 * */

class NoB {
public:
    //Construtor
    NoB(int m);

    //Destrutor
    virtual ~NoB();

    bool getEhfolha();
    void setEhfolha(bool x);
    int getn();
    void setn(int x);
    NoB* getVetFilhos(int i);
    void setVetFilhos(NoB* vetor);
    int getChaves(int i);
    void setChaves(int valor, int pos);
    NoB* getPai();
    void setPai(NoB* p);

private:
    int chaves[3];
    NoB* vetFilhos[3];
    NoB* pai_;
    int n_;
    bool ehfolha_;
};


#endif //TRABALHO_ED2_NOB_H

