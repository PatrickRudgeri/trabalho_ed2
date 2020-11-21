//
// Created by Larissa on 19/11/2020.
//

#include <iostream>
#include <cstdlib>
#include <cassert>
#define INDENT_STEP  4

#include "../../include/secao_3/AVP.h"


using namespace std;

AVP::AVP()
{
    raiz = nullptr;
    qtdComparacoes = 0;
    qtdTrocas = 0;

}

AVP::~AVP()
{
    auxDestrutor(this->raiz);
}

// Fun��o auxiliar do destrutor da �rvore VP
void AVP::auxDestrutor(NoVP *p)
{
    if(p != nullptr)
    {
        auxDestrutor(p->getDir());
        auxDestrutor(p->getEsq());
        free(p);
    }
}



//Propriedades da arvore vermelho preta

/*
 * Funcao que verifica a propriedade 1 (todoh no de uma arvore VP eh vermelho ou preta )
 * e desce recursivamente a arvore ate as folhas verificando cada noh
 */
void AVP::verifica_propriedade1(NoVP* n)
{
    assert(n->noh_cor(n) == VERMELHO || n->noh_cor(n) == PRETO);
    verifica_propriedade1(n->getEsq());
    verifica_propriedade1(n->getDir());
}



/*
 * Funcao que verifica a propriedade 2 (a raiuz da arvore VP eh sempre preta )
 */
void AVP::verifica_propriedade2(NoVP* r)
{
    assert(r->noh_cor(r) == PRETO);
}

/*
 * A propriedade 3 (todas folha (NIL) eh preto eh verificada no metodo "cor NoVP::noh_cor(NoVP* n)" em noVP.cppp
 */


/*
 * Funcao que verifica a propriedade 4 os filhos a direita e a esquerda de um noh vermelho sao sempre pretos
 */
void AVP::verifica_propriedade4(NoVP* n)
{
    if(NoVP::noh_cor(n) == VERMELHO)
    {
        assert(n->getEsq()->noh_cor(n) == PRETO);
        assert(n->getDir()->noh_cor(n) == PRETO);
        assert(n->getPai(n)->noh_cor(n) == PRETO);
    }
    if (n == nullptr)
        return;
    //percorre a arvore inteira recursivamente
    verifica_propriedade4(n->getEsq());
    verifica_propriedade4(n->getDir());
}
/*
 * Funcao que verifica a propriedade 5 da altura negra
 */
void AVP::verifica_propriedade5(NoVP* r)
{
    int contador_caminho_negro = -1;
    verifica_propriedade5_aux(r, 0, &contador_caminho_negro);
}

void AVP::verifica_propriedade5_aux(NoVP* n, int contador, int* contador_caminho_negro)
{
    if( NoVP::noh_cor(n) == PRETO)
    {
        contador++;
    }
    if (n == nullptr)
    {
        if (*contador_caminho_negro == -1)
        {
            *contador_caminho_negro = contador;
        }
        else
        {
            assert(contador == *contador_caminho_negro);
        }
        return;
    }
    verifica_propriedade5_aux(n->getEsq(),  contador, contador_caminho_negro);
    verifica_propriedade5_aux(n->getDir(), contador, contador_caminho_negro);
}






/*
 * Verifica propriedades da AVP
 */
void AVP::verifica_propriedades()
{
    verifica_propriedade1(raiz);
    verifica_propriedade2(raiz);
    verifica_propriedade4(raiz);
    verifica_propriedade5(raiz);
}


//busca e retorna o no

/*NoVP* AVP::busca_no(NoVP *p, int val)
{

    if(p == NULL)
    {
        return NULL;
    }
    else if(p->getInfo() == val)
    {

        return p;
    }

    else if(val < p->getInfo())
    {

        auxBusca(p->getEsq(), val);
    }
    else
    {
        auxBusca(p->getDir(), val);
    }


}*/

NoVP* AVP::busca_no(int val) const
{
    NoVP *p = this->raiz;
    if( p == nullptr)
        return nullptr;
    while (p != nullptr)
    {
        if (p->getInfo() == val)
        {
            return p;
        }
        else if (p->getInfo() < val)
        {
            p = p->getEsq();
        }
        else
        {
            assert(p->getInfo() > val);
            p = p->getDir();
        }
    }
    return p;
}




/*
 * Retorna o no maximo apartir de noh passado
 */
NoVP* AVP::noMaximo(NoVP* n)
{
    assert(n != nullptr);
    while (n->getDir() != nullptr)
    {
        n = n->getDir();
    }
    return n;
}

//deleta
/*
* Caso 1: N eh unico noh na arvore. Neste caso, terminamos.
 */
void AVP::deleta_caso1(NoVP* n)
{
    if (NoVP::getPai(n) == nullptr)
        return;
    else
        deleta_caso2(n);
}

/*
 * Caso 2: O irm�o(I) � vermelho. Nesse caso, invertemos as cores do pai (P) e  do irmao (I) e, em seguida,
 giramos para a esquerda em P, transformando irm�o(I) no av� de N. Observe que P tem que ser
 preto porque teve um filho vermelho. A sub�rvore resultante tem um caminho curto um noh
 preto, ent�o n�o terminamos. Agora N tem um irm�o preto e um pai vermelho, ent�o podemos
 prosseguir para a etapa 3, 4, 5 ou 6. (Seu novo irm�o � preto porque j� foi filho do (I) vermelho).
 Em casos posteriores, vamos renomear N novo irm�o como I.
 */
void AVP::deleta_caso2(NoVP* n)
{
    NoVP* noh_irmao = NoVP::getIrmao(n);
    NoVP* noh_pai = NoVP::getPai(n);

    if (NoVP::noh_cor(noh_irmao) == VERMELHO)
    {
        noh_pai->setCor(VERMELHO);

        noh_irmao->setCor(PRETO);

        if (n == noh_pai->getEsq())
            rotacao_esquerda(noh_pai);
        else
            rotacao_direita(noh_pai);

    }
    deleta_caso3(n);
}

/*
 Caso 3:  Pai (P), Irmao (I) e filhos de I s�o pretos. Neste caso, simplesmente repintamos I vermelho.
 O resultado eh que todos os caminhos que passam por I, que s�o precisamente aqueles caminhos que nao
 passam por N, tem um noh preto a menos. Como a exclusao do pai original de N fez com que
 todos os caminhos que passam por N tivessem um noh preto a menos, isso equilibra as coisas.
 No entanto, todos os caminhos atrav�s de P agora t�m um noh preto a menos do que os caminhos
 que n�o passam por P, entao a propriedade 5 (todos os caminhos de qualquer noh dado para
 seus nos folha cont�m o mesmo numero de nos pretos) ainda eh violada.
 Para corrigir isso, realizamos o procedimento de rebalanceamento em P, iniciando no caso 1.
 */
void AVP:: deleta_caso3(NoVP* n)
{
    NoVP* noh_irmao = NoVP::getIrmao(n);
    NoVP* noh_pai = NoVP::getPai(n);

    if ( NoVP::noh_cor(noh_pai) == PRETO &&  NoVP::noh_cor(noh_irmao) == PRETO &&
    noh_irmao->getEsq()->noh_cor(noh_irmao) == PRETO && noh_irmao->getDir()->noh_cor(noh_irmao) == PRETO)
    {
        noh_irmao->setCor(VERMELHO);
        deleta_caso1(noh_pai);

    }
    else
        deleta_caso4(n);
}


/*
 * Caso4: Os filhos de I(Irmao) e o I s�o pretos, mas Pai (P) � vermelho. Neste caso, simplesmente trocamos as cores de I e P.
 Isso nao afeta o numero de n�s pretos nos caminhos que passam por I, mas adiciona um ao numero de nohs pretos
 nos caminhos que passam por N, compensando o noh preto excluido nesses caminhos.
 */
void AVP::deleta_caso4(NoVP* n)
{

    NoVP* noh_irmao = NoVP::getIrmao(n);
    NoVP* noh_pai = NoVP::getPai(n);


    if ( NoVP::noh_cor(noh_pai) == VERMELHO &&  NoVP::noh_cor(noh_irmao) == PRETO &&
            noh_irmao->getEsq()->noh_cor(noh_irmao) == PRETO &&  noh_irmao->getDir()->noh_cor(noh_irmao) == PRETO)
    {
        noh_irmao->setCor(VERMELHO);
        noh_pai->setCor(PRETO);

    }
    else
        deleta_caso5(n);
}

/*
Irmao (I) eh preto, o filho esquerdo de I eh vermelho, o filho direito de I eh preto e N eh
o filho esquerdo de seu pai. Nesse caso, giramos para a direita em I, de modo que
o filho esquerdo de I se torne o pai de I e o novo irm�o de N. Em seguida, trocamos as
 cores de I e de seu novo pai. Todos os caminhos ainda tem o mesmo n�mero de nohs pretos,
 mas agora N tem um irmao preto cujo filho direito eh vermelho, ent�o caimos no caso 6.
 Nem N nem seu pai s�o afetados por esta transforma��o. (Novamente, para o caso 6, renomeamos o novo irmao de N como I.)

*/
void AVP::deleta_caso5(NoVP* n)
{
    NoVP* irmao = NoVP::getIrmao(n);

    // Esta instru��o if eh trivial, devido ao caso 2 (mesmo que o caso 2 tenha mudado
    // irmao do filho do irmao, o filho do irmao nao pode ser vermelho, pois
    // nenhum pai vermelho pode ter um filho vermelho).
    if ( NoVP::noh_cor(irmao)== PRETO)
    {
        // As instrucoes a seguir apenas for�am o vermelho a ficar a esquerda do
        // esquerda do pai, ou direita da direita, ent�o o caso seis ir� girar
        // corretamente.
        if ((n == NoVP::getPai(n)->getEsq()) && (irmao->getDir()->noh_cor(irmao) == PRETO) &&
            (irmao->getEsq()->noh_cor(irmao) == VERMELHO))
        {
            // Este ultimo teste tambem eh trivial devido aos casos 2-4.
            irmao->setCor(VERMELHO);
            irmao->getEsq()->setCor(PRETO);
            rotacao_direita(irmao);

        }
        else if ((n == NoVP::getPai(n)->getDir()) && (irmao->getEsq()->noh_cor(irmao) == PRETO) &&
                 (irmao->getDir()->noh_cor(irmao) == VERMELHO))
        {
            // Este ultimo teste tambem eh trivial devido aos casos 2-4.
            irmao->setCor(VERMELHO);
            irmao->getDir()->setCor(PRETO);
            rotacao_esquerda(irmao);

        }
    }
    deleta_caso6(n);
}
/*
Irmao (I) eh preto, filho direito de I eh vermelho, e N eh o filho esquerdo do pai P .
Neste caso, giramos a esquerda em P , de modo que I torna-se o pai de P.
Em seguida, trocamos as cores de P e I e tornamos o filho certo de I preto.
A subarvore ainda tem a mesma cor em sua raiz, ent�o as propriedades 4
(ambos os filhos de cada noh vermelho s�o pretos) e 5 (todos os caminhos
de qualquer noh dado para seus
nohss folha cont�m o mesmo n�mero de n�s pretos)
nao foram violadas
*/
void AVP::deleta_caso6(NoVP* n)
{
    NoVP* irmao = NoVP::getIrmao(n);
    NoVP* pai = NoVP::getPai(n);

    irmao->setCor(NoVP::noh_cor(pai));
    pai->setCor(PRETO);


    if (n == pai->getEsq())
    {
        irmao->getDir()->setCor(PRETO);
        rotacao_esquerda(pai);

    }
    else
    {
        irmao->getEsq()->setCor(PRETO);
        rotacao_direita(pai);

    }
}


/*
 * substitui um no
 */
void AVP::substitui_no(NoVP* velho, NoVP* novo) {

    if (NoVP::getPai(velho) == nullptr)
    {
        this->raiz = novo;
    }
    else
    {
        if (velho == NoVP::getPai(velho)->getEsq())
            NoVP::getPai(velho)->setEsq(novo);
        else
            NoVP::getPai(velho)->setDir(novo);
    }
    if (novo != nullptr)
    {
        novo->setPai(NoVP::getPai(velho));
    }
}


/*
 * Deleta noh da AVP
 */


void AVP::deleta(int val)
{
    NoVP* filho;

    NoVP* n = busca_no(val);

    if (n == nullptr)
        return;
    if (n->getEsq() != nullptr && n->getDir() != nullptr)
    {
        NoVP* pred = noMaximo(n->getEsq());
        n->setInfo(pred->getInfo());
        n = pred;
    }
    assert(n->getEsq()== nullptr || n->getDir() == nullptr);

    filho = n->getDir() == nullptr ? n->getEsq()  : n->getDir();

    if (NoVP::noh_cor(n) == PRETO)
    {
        n->setCor(NoVP::noh_cor(filho));
        deleta_caso1(n);
    }
    substitui_no(n, filho);
    //free(n);
    delete(n);
    verifica_propriedades();
}


//Busca
bool AVP::busca(int val)
{
    return auxBusca(raiz, val);
}

bool AVP::auxBusca(NoVP *p, int val)
{
    if(p == nullptr)
    {
        //Contabiliza comparacao
        this->qtdComparacoes++;


        return false;
    }
    else if(p->getInfo() == val)
    {

        //Contabiliza comparacao
        this->qtdComparacoes++;
        return true;
    }

    else if(val < p->getInfo())
    {

        //Contabiliza comparacao
        this->qtdComparacoes++;
        return auxBusca(p->getEsq(), val);
    }
    else
    {
        return auxBusca(p->getDir(), val);
    }

}

void AVP::rotacao_esquerda(NoVP* n)
{

    //nnovo eh noh auxiliar
    NoVP* nnovo = n->getDir();

    //Contabiliza troca
    this->qtdTrocas++;

    //p eh noh pai do no passado
    NoVP* p = NoVP::getPai(n);

    //Contabiliza troca
    this->qtdTrocas++;

    //A fun��o assert() testa se uma express�o � true (verdadeira). Sa express�o for falsa (false),
    //o assert interrompe a execucao do programa.

    assert(nnovo != nullptr);  //Como as folhas de uma arvore vermelho-preto estao vazias,
    //elas nao podem se tornar nos internos.

    //realiza a rotacao
    n->setDir(nnovo->getEsq());
    nnovo->setEsq(n);
    n->setPai(nnovo);

    //Contabiliza troca
    this->qtdTrocas = this->qtdTrocas+3;

    // Lidar com outros ponteiros filho/pai.

    if (n->getDir() != nullptr)
    {
        //Contabiliza comparacao
        this->qtdComparacoes++;

        n->getDir()->setPai(n);

        //Contabiliza troca
        this->qtdTrocas++;

    }

    //Inicialmente n poderia ser a raiz.
    if (p != nullptr)
    {
        if (n == p->getEsq())
        {
            //Contabiliza comparacao
            this->qtdComparacoes++;

            p->setEsq(nnovo);

        }
        else if (n == p->getDir())
        {
            //Contabiliza comparacao
            this->qtdComparacoes++;

            p->setDir(nnovo);

            //Contabiliza troca
            this->qtdTrocas++;
        }
    }
    //Contabiliza troca
    this->qtdTrocas++;

    nnovo->setPai(p);
}

void AVP::rotacao_direita(NoVP* n)
{

    //nnovo eh um noh auxiliar
    NoVP* nnovo = n->getEsq();

    //Contabiliza troca
    this->qtdTrocas++;

    //p eh noh pai do no passado
    NoVP* p = NoVP::getPai(n);

    //Contabiliza troca
    this->qtdTrocas++;

    assert(nnovo != nullptr); //Como as folhas de uma arvore vermelho-preto estao vazias,
    //elas nao podem se tornar nos internos.

    //realiza a rotacao
    n->setEsq(nnovo->getDir());
    nnovo->setDir(n);
    n->setPai(nnovo);

    //Contabiliza troca
    this->qtdTrocas = this->qtdTrocas+3;

    //Lidar com outros ponteiros filho/pai.
    if (n->getEsq() != nullptr)
    {
        //Contabiliza comparacao
        this->qtdComparacoes++;

        n->getEsq()->setPai(n);

        //Contabiliza troca
        this->qtdTrocas++;

    }

    //Inicialmente n poderia ser a raiz.
    if (p != nullptr)
    {
        if (n == p->getEsq())
        {
            //Contabiliza comparacao
            this->qtdComparacoes++;

            p->setEsq(nnovo);

            //Contabiliza troca
            this->qtdTrocas++;
        }
        else if (n == p->getDir())
        {
            //Contabiliza comparacao
            this->qtdComparacoes++;

            p->setDir(nnovo);

            //Contabiliza troca
            this->qtdTrocas++;
        }
    }


    nnovo->setPai(p);

    //Contabiliza troca
    this->qtdTrocas++;
}

//Insercao
/*
* A insercao come�a adicionando o noh de uma maneira muito semelhante a uma insercao de arvore de pesquisa binaria
de busca. A grande diferen�a eh que na arvore binaria de busca um novo noh
eh adicionado como uma folha,que nao contem nenhuma informacao sobre cor e sem verificacao. Na arvore vermelho-preto,
entao, em vez disso, o novo noh eh inserido como folha e vermelho, em seguida, eh verificado se as propriedades da arvore vermelho preto
foram violadas
*
*/

/*
Observa-se que:

A propriedade 1 (cada n� � vermelho ou preto) e a propriedade 3 (todas as folhas s�o pretas) sempre s�o v�lidas.
A propriedade 2 (a raiz � preta) � verificada e corrigida com o caso 1.
A propriedade 4 (n�s vermelhos t�m apenas filhos pretos) � amea�ada apenas pela adi��o de um n� vermelho, repintura de um n� de preto para vermelho ou uma rota��o.
A propriedade 5 (todos os caminhos de qualquer n� dado para suas folhas t�m o mesmo n�mero de n�s pretos) � amea�ada apenas pela adi��o de um n� preto, repintura de um n� ou uma rota��o.
*/

/*
Caso 1: O n� atual N est� na raiz da �rvore. Nesse caso, � repintado de preto para satisfazer a propriedade 2
 (a raiz � preta). Uma vez que isso adiciona um n� preto a cada caminho de uma vez, a propriedade 5
 (todos os caminhos de qualquer n� dado para seus n�s folha cont�m o mesmo n�mero de n�s pretos) n�o � violada.
*/
void AVP::insereCaso1(NoVP* n)
{
    n->setCor(PRETO);


}

/*
Caso 2: A propriedade 2 (a raiz � preta) � verificada e corrigida com o caso 1

Sendo o pai P do noh atual preto, ent�o a propriedade 4 (ambos os filhos de cada n�
vermelho s�o pretos) � v�lida. A propriedade 5 (todos os caminhos de qualquer n� dado
para seus n�s folhas cont�m o mesmo n�mero de n�s pretos) n�o est� amea�ada, porque o
novo n� N tem dois filhos folhas pretas, e ainda N sendo vermelho, os caminhos atrav�s
de cada um de seus filhos t�m o mesmo n�mero de n�s pretos que o caminho atrav�s da
folha que ele substituiu, que era preto, e assim essa propriedade permanece satisfeita.
Portanto, a �rvore permanece v�lida.
*/
void AVP::insereCaso2()
{
//Nao faz nada, pois a arvore continua valida.
}

/*
Caso 3: se o pai P e o tio T s�o vermelhos, ambos podem ser repintados de preto e
o av� A torna-se vermelho para manter a propriedade 5 (todos os caminhos de um
n� para as folhas cont�m o mesmo n�mero de n�s pretos) . Uma vez que qualquer
caminho atrav�s dos pais ou tio deve passar pelo av�, o n�mero de n�s pretos
nesses caminhos n�o mudou. No entanto, o av� A pode violar a Propriedade
2 (a raiz � preta) se for a raiz ou a Propriedade 4 (ambos os filhos de cada n� vermelho s�o pretos)
se ele tiver um pai vermelho. Para corrigir isso, realizamos o procedimento de reparo da �rvore vermelho-preto
novamente em A.
*/

void AVP::insereCaso3(NoVP* n)
{
    NoVP::getPai(n)->setCor(PRETO);
    NoVP::getTio(n)->setCor(PRETO);
    NoVP::getAvo(n)->setCor(VERMELHO);


}

/*
Caso 4, etapa 1: O pai P � vermelho, mas o tio T � preto. Neste caso, realizamos uma rota��o em P
que muda os pap�is do novo n� N e de seu pai P. E tanto P quanto N s�o vermelhos, ent�o propriedade 5
(todos os caminhos de um n� para suas folhas cont�m o mesmo n�mero de preto n�s) � preservado.
 A propriedade 4 (ambos os filhos de cada n� vermelho s�o pretos) � restaurada na etapa 2
*/

void AVP::insereCaso4(NoVP* n)
{

    NoVP* p = NoVP::getPai(n);
    NoVP* g = NoVP::getAvo(n);


    insereCorrecao(NoVP::getAvo(n));

    if (n == p->getDir() && p == g->getEsq())
    {
        //Contabiliza comparacao
        this->qtdComparacoes++;

        rotacao_esquerda(p);
        n = n->getEsq();
    }
    else if (n == p->getEsq() && p == g->getDir())
    {

        //Contabiliza comparacao
        this->qtdComparacoes++;

        rotacao_direita(p);
        n = n->getDir();
    }

    insereCaso4etapa2(n);
}

/*
Caso 4, etapa 2: Faz a rota��o sobre o av� A,  colocando P no lugar de A e tornando P o pai
de N e A. A � preto e seu antigo filho P � vermelho, pois a propriedade 4 foi violada.
Trocamos ent�o as cores de P e A.
*/

void AVP::insereCaso4etapa2(NoVP* n)
{

    NoVP* p = NoVP::getPai(n);
    NoVP* g = NoVP::getAvo(n);


    insereCorrecao(NoVP::getAvo(n));

    if (n == p->getEsq())
    {
        //Contabiliza comparacao
        this->qtdComparacoes++;
        rotacao_direita(g);
    }
    else
    {
        //Contabiliza comparacao
        this->qtdComparacoes++;
        rotacao_esquerda(g);
    }
    p->setCor(PRETO);
    g->setCor(VERMELHO);
}

void AVP::insereRecursivo(NoVP* r, NoVP* n)
{
    //Desce recursivamente na �rvore ate que uma folha seja encontrada.

    //se raiz nao eh nula
    if (r != nullptr)
    {
        //Contabiliza comparacao
        this->qtdComparacoes++;
        //se a info eh menor vai para esquerda
        if (n->getInfo() < r->getInfo())
        {
            //Contabiliza comparacao
            this->qtdComparacoes++;
            if (r->getEsq() != nullptr)
            {
                //Contabiliza comparacao
                this->qtdComparacoes++;
                insereRecursivo(r->getEsq(), n);
                return;
            }
            else
            {
                //Contabiliza comparacao
                this->qtdComparacoes++;
                r->setEsq(n);
            }
        }
        else     // se a info eh maior ou igual vai para direita
        {
            if (r->getDir() != nullptr)
            {
                //Contabiliza comparacao
                this->qtdComparacoes++;
                insereRecursivo(r->getDir(), n);
                return;
            }
            else
            {
                //Contabiliza comparacao
                this->qtdComparacoes++;
                r->setDir(n);
            }
        }
    }


    //inser um novo noh n.
    n->setPai(r);
    n->setEsq(nullptr);
    n->setDir(nullptr);
    n->setCor(VERMELHO);


}

/*
Para correcao, existem varios casos de insercao da arvore vermelho-preto para lidar:

1) N eh o noh raiz, ou seja, o primeiro noh da arvoreVP
2) O pai de N (P) eh preto
3) P eh vermelho (entao nao pode ser a raiz da arvore) e o tio de N (T) eh vermelho
4) P eh vermelho e T eh preto
*/
void AVP::insereCorrecao(NoVP* n)
{
    if (NoVP::getPai(n) == nullptr)
    {
        //Contabiliza comparacao
        this->qtdComparacoes++;
        insereCaso1(n);
    }
    else if (NoVP::getPai(n)->getCor()== PRETO)
    {
        //Contabiliza comparacao
        this->qtdComparacoes++;
        insereCaso2();
    }
    else if (NoVP::getTio(n) != nullptr && NoVP::getTio(n)->getCor() == VERMELHO)
    {
        //Contabiliza comparacao
        this->qtdComparacoes++;
        insereCaso3(n);
    }
    else
    {
        //Contabiliza comparacao
        this->qtdComparacoes++;
        insereCaso4(n);
    }
}

NoVP* AVP::auxinsere(NoVP* r, NoVP* n)
{
//Insere um novo noh na �rvore atual.
    insereRecursivo(r, n);

    //Repara a arvore no caso de qualquer uma das propriedades vermelho-preto ter sido violada.
    insereCorrecao(n);

    //Encontre a nova raiz para retornar.
    r = n;

    //Contabiliza troca
    this->qtdTrocas++;

    while (NoVP::getPai(r) != nullptr)
    {
        //Contabiliza comparacao
        this->qtdComparacoes++;
        r = NoVP::getPai(r);
    }

    return r;
}

void AVP::insere(int val)
{
    NoVP* n = new NoVP();
    n->setCor(VERMELHO);
    n->setInfo(val);
    n->setEsq(nullptr);
    n->setDir(nullptr);
    raiz = auxinsere(raiz, n);

}

/*
 * Imprime Arvore Vermelho-Preta
 */
void AVP::imprime_aux(NoVP* n, int indent)
{
    int i;
    if (n == nullptr)
    {
        fputs("<Arvore vazia!>", stdout);
        return;
    }
    if (n->dir != nullptr)
    {
        imprime_aux(n->dir, indent + INDENT_STEP);
    }
    for(i = 0; i < indent; i++)
        fputs(" ", stdout);
    if (n->getCor() == PRETO)
        cout<<(int)n->info<<endl;
    else
        //noh vermelho aparece entre o simbolo "<>"
        cout<<"<"<<(int)n->info<<">"<<endl;
    if (n->esq != nullptr)
    {
        imprime_aux(n->esq, indent + INDENT_STEP);
    }
}

void AVP::imprime_AVP()
{
    imprime_aux(raiz, 0);
    puts("");
}



