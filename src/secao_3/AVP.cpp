#include <iostream>
#include <cstdlib>
#include <cassert>

#define INDENT_STEP  4

#include "../../include/secao_3/AVP.hpp"

using namespace std;

AVP::AVP() {
    raiz_ = nullptr;
    qtdComparacoes_ = 0;
    qtdTrocas_ = 0;
}

AVP::~AVP() {
    auxDestrutor(this->raiz_);
}

/*
 * Retorna PRETO se é noh folha (NIL), caso contrário retorna s cor do noh
 */
Cor AVP::getCorNo(NoVP *n) {
    return n == nullptr ? Cor::PRETO : n->getCor();
}

// Fun��o auxiliar do destrutor da �rvore VP
void AVP::auxDestrutor(NoVP *p) {
    if (p != nullptr) {
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
void AVP::verificaPropriedade1(NoVP *n) {
    assert(getCorNo(n) == VERMELHO || getCorNo(n) == PRETO);
    verificaPropriedade1(n->getEsq());
    verificaPropriedade1(n->getDir());
}

/*
 * Funcao que verifica a propriedade 2 (a raiuz da arvore VP eh sempre preta )
 */
void AVP::verificaPropriedade2(NoVP *raiz) {
    assert(getCorNo(raiz) == PRETO);
}

/*
 * A propriedade 3 (todas folha (NIL) eh preto eh verificada no metodo "Cor getCorNo(NoVP* n)"
 */


/*
 * Funcao que verifica a propriedade 4 os filhos a direita e a esquerda de um noh vermelho sao sempre pretos
 */
void AVP::verificaPropriedade4(NoVP *n) {
    if (getCorNo(n) == VERMELHO) {
        assert(getCorNo(n->getEsq()) == PRETO);
        assert(getCorNo(n->getDir()) == PRETO);
        assert(getCorNo(n->getPai()) == PRETO);
    }
    if (n == nullptr)
        return;
    //percorre a arvore inteira recursivamente
    verificaPropriedade4(n->getEsq());
    verificaPropriedade4(n->getDir());
}

/*
 * Funcao que verifica a propriedade 5 da altura negra
 */
void AVP::verificaPropriedade5(NoVP *raiz) {
    int contadorCaminhoNegro = -1;
    verificaPropriedade5Aux(raiz, 0, &contadorCaminhoNegro);
}

void AVP::verificaPropriedade5Aux(NoVP *n, int contador, int *contadorCaminhoNegro) {
    if (getCorNo(n) == PRETO) {
        contador++;
    }
    if (n == nullptr) {
        if (*contadorCaminhoNegro == -1) {
            *contadorCaminhoNegro = contador;
        } else {
            assert(contador == *contadorCaminhoNegro);
        }
        return;
    }
    verificaPropriedade5Aux(n->getEsq(), contador, contadorCaminhoNegro);
    verificaPropriedade5Aux(n->getDir(), contador, contadorCaminhoNegro);
}

/*
 * Verifica propriedades da AVP
 */
void AVP::verificaPropriedades() {
    verificaPropriedade1(raiz_);
    verificaPropriedade2(raiz_);
    verificaPropriedade4(raiz_);
    verificaPropriedade5(raiz_);
}

//busca e retorna o no

/*NoVP* AVP::buscaNo(NoVP *p, int val)
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

NoVP *AVP::buscaNo(int val) const {
    NoVP *p = this->raiz_;
    if (p == nullptr)
        return nullptr;
    while (p != nullptr) {
        if (p->getInfo() == val) {
            return p;
        } else if (p->getInfo() < val) {
            p = p->getEsq();
        } else {
            assert(p->getInfo() > val);
            p = p->getDir();
        }
    }
    return p;
}

/*
 * Retorna o no maximo apartir de noh passado
 */
NoVP *AVP::noMaximo(NoVP *n) {
    assert(n != nullptr);
    while (n->getDir() != nullptr) {
        n = n->getDir();
    }
    return n;
}

//deleta
/*
* Caso 1: N eh unico noh na arvore. Neste caso, terminamos.
 */
void AVP::deletaCaso1(NoVP *n) {
    if (n->getPai() != nullptr)
        deletaCaso2(n);
}

/*
 * Caso 2: O irm�o(I) � vermelho. Nesse caso, invertemos as cores do pai_ (P) e  do irmao (I) e, em seguida,
 giramos para a esquerda em P, transformando irm�o(I) no av� de N. Observe que P tem que ser
 preto porque teve um filho vermelho. A sub�rvore resultante tem um caminho curto um noh
 preto, ent�o n�o terminamos. Agora N tem um irm�o preto e um pai_ vermelho, ent�o podemos
 prosseguir para a etapa 3, 4, 5 ou 6. (Seu novo irm�o � preto porque j� foi filho do (I) vermelho).
 Em casos posteriores, vamos renomear N novo irm�o como I.
 */
void AVP::deletaCaso2(NoVP *n) {
    NoVP *noh_irmao = n->getIrmao();
    NoVP *noh_pai = n->getPai();

    if (getCorNo(noh_irmao) == VERMELHO) {
        noh_pai->setCor(VERMELHO);

        noh_irmao->setCor(PRETO);

        if (n == noh_pai->getEsq())
            rotacaoEsquerda(noh_pai);
        else
            rotacaoDireita(noh_pai);

    }
    deletaCaso3(n);
}

/*
 Caso 3:  Pai (P), Irmao (I) e filhos de I s�o pretos. Neste caso, simplesmente repintamos I vermelho.
 O resultado eh que todos os caminhos que passam por I, que s�o precisamente aqueles caminhos que nao
 passam por N, tem um noh preto a menos. Como a exclusao do pai_ original de N fez com que
 todos os caminhos que passam por N tivessem um noh preto a menos, isso equilibra as coisas.
 No entanto, todos os caminhos atrav�s de P agora t�m um noh preto a menos do que os caminhos
 que n�o passam por P, entao a propriedade 5 (todos os caminhos de qualquer noh dado para
 seus nos folha cont�m o mesmo numero de nos pretos) ainda eh violada.
 Para corrigir isso, realizamos o procedimento de rebalanceamento em P, iniciando no caso 1.
 */
void AVP::deletaCaso3(NoVP *n) {
    NoVP *noh_irmao = n->getIrmao();
    NoVP *noh_pai = n->getPai();

    if (getCorNo(noh_pai) == PRETO && getCorNo(noh_irmao) == PRETO &&
        getCorNo(noh_irmao->getEsq()) == PRETO &&
        getCorNo(noh_irmao->getDir()) == PRETO) {
        noh_irmao->setCor(VERMELHO);
        deletaCaso1(noh_pai);

    } else
        deletaCaso4(n);
}

/*
 * Caso4: Os filhos de I(Irmao) e o I s�o pretos, mas Pai (P) � vermelho. Neste caso, simplesmente trocamos as cores de I e P.
 Isso nao afeta o numero de n�s pretos nos caminhos que passam por I, mas adiciona um ao numero de nohs pretos
 nos caminhos que passam por N, compensando o noh preto excluido nesses caminhos.
 */
void AVP::deletaCaso4(NoVP *n) {

    NoVP *noh_irmao = n->getIrmao();
    NoVP *noh_pai = n->getPai();

    if (getCorNo(noh_pai) == VERMELHO && getCorNo(noh_irmao) == PRETO &&
        getCorNo(noh_irmao->getEsq()) == PRETO &&
        getCorNo(noh_irmao->getDir()) == PRETO) {
        noh_irmao->setCor(VERMELHO);
        noh_pai->setCor(PRETO);

    } else
        deletaCaso5(n);
}

/*
Irmao (I) eh preto, o filho esquerdo de I eh vermelho, o filho direito de I eh preto e N eh
o filho esquerdo de seu pai_. Nesse caso, giramos para a direita em I, de modo que
o filho esquerdo de I se torne o pai_ de I e o novo irm�o de N. Em seguida, trocamos as
 cores de I e de seu novo pai_. Todos os caminhos ainda tem o mesmo n�mero de nohs pretos,
 mas agora N tem um irmao preto cujo filho direito eh vermelho, ent�o caimos no caso 6.
 Nem N nem seu pai_ s�o afetados por esta transforma��o. (Novamente, para o caso 6, renomeamos o novo irmao de N como I.)

*/
void AVP::deletaCaso5(NoVP *n) {
    NoVP *irmao = n->getIrmao();

    // Esta instru��o if eh trivial, devido ao caso 2 (mesmo que o caso 2 tenha mudado
    // irmao do filho do irmao, o filho do irmao nao pode ser vermelho, pois
    // nenhum pai_ vermelho pode ter um filho vermelho).
    if (getCorNo(irmao) == PRETO) {
        // As instrucoes a seguir apenas for�am o vermelho a ficar a esquerda do
        // esquerda do pai_, ou direita da direita, ent�o o caso seis ir� girar
        // corretamente.
        if ((n == n->getPai()->getEsq()) && (getCorNo(irmao->getDir()) == PRETO) &&
            (getCorNo(irmao->getEsq()) == VERMELHO)) {
            // Este ultimo teste tambem eh trivial devido aos casos 2-4.
            irmao->setCor(VERMELHO);
            irmao->getEsq()->setCor(PRETO);
            rotacaoDireita(irmao);

        } else if ((n == n->getPai()->getDir()) && (getCorNo(irmao->getEsq()) == PRETO) &&
                   (getCorNo(irmao->getDir()) == VERMELHO)) {
            // Este ultimo teste tambem eh trivial devido aos casos 2-4.
            irmao->setCor(VERMELHO);
            irmao->getDir()->setCor(PRETO);
            rotacaoEsquerda(irmao);
        }
    }
    deletaCaso6(n);
}

/*
Irmao (I) eh preto, filho direito de I eh vermelho, e N eh o filho esquerdo do pai_ P .
Neste caso, giramos a esquerda em P , de modo que I torna-se o pai_ de P.
Em seguida, trocamos as cores de P e I e tornamos o filho certo de I preto.
A subarvore ainda tem a mesma Cor em sua raiz_, ent�o as propriedades 4
(ambos os filhos de cada noh vermelho s�o pretos) e 5 (todos os caminhos
de qualquer noh dado para seus
nohss folha cont�m o mesmo n�mero de n�s pretos)
nao foram violadas
*/
void AVP::deletaCaso6(NoVP *n) {
    NoVP *irmao = n->getIrmao();
    NoVP *pai = n->getPai();

    irmao->setCor(getCorNo(pai));
    pai->setCor(PRETO);

    if (n == pai->getEsq()) {
        irmao->getDir()->setCor(PRETO);
        rotacaoEsquerda(pai);
    } else {
        irmao->getEsq()->setCor(PRETO);
        rotacaoDireita(pai);
    }
}

/*
 * substitui um no
 */
void AVP::substituiNo(NoVP *velho, NoVP *novo) {

    if (velho->getPai() == nullptr) {
        this->raiz_ = novo;
    } else {
        if (velho == velho->getPai()->getEsq())
            velho->getPai()->setEsq(novo);
        else
            velho->getPai()->setDir(novo);
    }
    if (novo != nullptr) {
        novo->setPai(velho->getPai());
    }
}

/*
 * Deleta noh da AVP
 */
void AVP::deleta(int val) {
    NoVP *filho;

    NoVP *n = buscaNo(val);

    if (n == nullptr)
        return;
    if (n->getEsq() != nullptr && n->getDir() != nullptr) {
        NoVP *pred = noMaximo(n->getEsq());
        n->setInfo(pred->getInfo());
        n = pred;
    }
    assert(n->getEsq() == nullptr || n->getDir() == nullptr);

    filho = n->getDir() == nullptr ? n->getEsq() : n->getDir();

    if (getCorNo(n) == PRETO) {
        n->setCor(getCorNo(filho));
        deletaCaso1(n);
    }
    substituiNo(n, filho);
    //free(n);
    delete (n);
    verificaPropriedades();
}

//Busca
bool AVP::busca(int val) {
    return auxBusca(raiz_, val);
}

bool AVP::auxBusca(NoVP *p, int val) {
    if (p == nullptr) {
        //Contabiliza comparacao
        this->qtdComparacoes_++;
        return false;
    } else if (p->getInfo() == val) {

        //Contabiliza comparacao
        this->qtdComparacoes_++;
        return true;
    } else if (val < p->getInfo()) {

        //Contabiliza comparacao
        this->qtdComparacoes_++;
        return auxBusca(p->getEsq(), val);
    } else {
        return auxBusca(p->getDir(), val);
    }

}

void AVP::rotacaoEsquerda(NoVP *n) {

    //nnovo eh noh auxiliar
    NoVP *nnovo = n->getDir();

    //Contabiliza troca
    this->qtdTrocas_++;

    //p eh noh pai_ do no passado
    NoVP *p = n->getPai();

    //Contabiliza troca
    this->qtdTrocas_++;

    //A fun��o assert() testa se uma express�o � true (verdadeira). Sa express�o for falsa (false),
    //o assert interrompe a execucao do programa.

    assert(nnovo != nullptr);  //Como as folhas de uma arvore vermelho-preto estao vazias,
    //elas nao podem se tornar nos internos.

    //realiza a rotacao
    n->setDir(nnovo->getEsq());
    nnovo->setEsq(n);
    n->setPai(nnovo);

    //Contabiliza troca
    this->qtdTrocas_ = this->qtdTrocas_ + 3;

    // Lidar com outros ponteiros filho/pai_.

    if (n->getDir() != nullptr) {
        //Contabiliza comparacao
        this->qtdComparacoes_++;

        n->getDir()->setPai(n);

        //Contabiliza troca
        this->qtdTrocas_++;
    }

    //Inicialmente n poderia ser a raiz_.
    if (p != nullptr) {
        if (n == p->getEsq()) {
            //Contabiliza comparacao
            this->qtdComparacoes_++;

            p->setEsq(nnovo);

        } else if (n == p->getDir()) {
            //Contabiliza comparacao
            this->qtdComparacoes_++;

            p->setDir(nnovo);

            //Contabiliza troca
            this->qtdTrocas_++;
        }
    }
    //Contabiliza troca
    this->qtdTrocas_++;

    nnovo->setPai(p);
}

void AVP::rotacaoDireita(NoVP *n) {

    //nnovo eh um noh auxiliar
    NoVP *nnovo = n->getEsq();

    //Contabiliza troca
    this->qtdTrocas_++;

    //p eh noh pai_ do no passado
    NoVP *p = n->getPai();

    //Contabiliza troca
    this->qtdTrocas_++;

    assert(nnovo != nullptr); //Como as folhas de uma arvore vermelho-preto estao vazias,
    //elas nao podem se tornar nos internos.

    //realiza a rotacao
    n->setEsq(nnovo->getDir());
    nnovo->setDir(n);
    n->setPai(nnovo);

    //Contabiliza troca
    this->qtdTrocas_ = this->qtdTrocas_ + 3;

    //Lidar com outros ponteiros filho/pai_.
    if (n->getEsq() != nullptr) {
        //Contabiliza comparacao
        this->qtdComparacoes_++;

        n->getEsq()->setPai(n);

        //Contabiliza troca
        this->qtdTrocas_++;
    }

    //Inicialmente n poderia ser a raiz_.
    if (p != nullptr) {
        if (n == p->getEsq()) {
            //Contabiliza comparacao
            this->qtdComparacoes_++;

            p->setEsq(nnovo);

            //Contabiliza troca
            this->qtdTrocas_++;
        } else if (n == p->getDir()) {
            //Contabiliza comparacao
            this->qtdComparacoes_++;

            p->setDir(nnovo);

            //Contabiliza troca
            this->qtdTrocas_++;
        }
    }
    nnovo->setPai(p);

    //Contabiliza troca
    this->qtdTrocas_++;
}

//Insercao
/*
* A insercao come�a adicionando o noh de uma maneira muito semelhante a uma insercao de arvore de pesquisa binaria
de busca. A grande diferen�a eh que na arvore binaria de busca um novo noh
eh adicionado como uma folha,que nao contem nenhuma informacao sobre Cor e sem verificacao. Na arvore vermelho-preto,
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
void AVP::insereCaso1(NoVP *n) {
    if (n != nullptr)
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
void AVP::insereCaso2() {
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
void AVP::insereCaso3(NoVP *n) {
    n->getPai()->setCor(PRETO);
    n->getTio()->setCor(PRETO);
    n->getAvo()->setCor(VERMELHO);
}

/*
Caso 4, etapa 1: O pai P � vermelho, mas o tio T � preto. Neste caso, realizamos uma rota��o em P
que muda os pap�is do novo n� N e de seu pai P. E tanto P quanto N s�o vermelhos, ent�o propriedade 5
(todos os caminhos de um n� para suas folhas cont�m o mesmo n�mero de preto n�s) � preservado.
 A propriedade 4 (ambos os filhos de cada n� vermelho s�o pretos) � restaurada na etapa 2
*/
void AVP::insereCaso4(NoVP *n) {

    NoVP *p = n->getPai();
    NoVP *g = n->getAvo();

    if (g != nullptr) {
        insereCorrecao(g);

        if (n == p->getDir() && p == g->getEsq()) {
            //Contabiliza comparacao
            this->qtdComparacoes_++;

            rotacaoEsquerda(p);
            n = n->getEsq();
        } else if (n == p->getEsq() && p == g->getDir()) {
            //Contabiliza comparacao
            this->qtdComparacoes_++;

            rotacaoDireita(p);
            n = n->getDir();
        }
    }
    insereCaso4etapa2(n);
}

/*
Caso 4, etapa 2: Faz a rota��o sobre o av� A,  colocando P no lugar de A e tornando P o pai
de N e A. A � preto e seu antigo filho P � vermelho, pois a propriedade 4 foi violada.
Trocamos ent�o as cores de P e A.
*/
void AVP::insereCaso4etapa2(NoVP *n) {

    NoVP *p = n->getPai();
    NoVP *g = n->getAvo();
    if (g != nullptr) {
        insereCorrecao(g);

        if (n == p->getEsq()) {
            //Contabiliza comparacao
            this->qtdComparacoes_++;
            rotacaoDireita(g);
        } else {
            //Contabiliza comparacao
            this->qtdComparacoes_++;
            rotacaoEsquerda(g);
        }
        g->setCor(VERMELHO);
    }
    p->setCor(PRETO);
}

void AVP::insereRecursivo(NoVP *r, NoVP *n) {
    //Desce recursivamente na �rvore ate que uma folha seja encontrada.

    //se raiz nao eh nula
    if (r != nullptr) {
        //Contabiliza comparacao
        this->qtdComparacoes_++;
        //se a info_ eh menor vai para esquerda
        if (n->getInfo() < r->getInfo()) {
            //Contabiliza comparacao
            this->qtdComparacoes_++;
            if (r->getEsq() != nullptr) {
                //Contabiliza comparacao
                this->qtdComparacoes_++;
                insereRecursivo(r->getEsq(), n);
                return;
            } else {
                //Contabiliza comparacao
                this->qtdComparacoes_++;
                r->setEsq(n);
            }
        } else     // se a info_ eh maior ou igual vai para direita
        {
            if (r->getDir() != nullptr) {
                //Contabiliza comparacao
                this->qtdComparacoes_++;
                insereRecursivo(r->getDir(), n);
                return;
            } else {
                //Contabiliza comparacao
                this->qtdComparacoes_++;
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
void AVP::insereCorrecao(NoVP *n) {

    if (n->getPai() == nullptr) {
        //Contabiliza comparacao
        this->qtdComparacoes_++;
        insereCaso1(n);
    } else if (n->getPai()->getCor() == PRETO) {
        //Contabiliza comparacao
        this->qtdComparacoes_++;
        insereCaso2();
    } else if (n->getTio() != nullptr && n->getTio()->getCor() == VERMELHO) {
        //Contabiliza comparacao
        this->qtdComparacoes_++;
        insereCaso3(n);
    } else {
        //Contabiliza comparacao
        this->qtdComparacoes_++;
        insereCaso4(n);
    }
}

NoVP *AVP::auxinsere(NoVP *r, NoVP *n) {
//Insere um novo noh na �rvore atual.
    insereRecursivo(r, n);

    //Repara a arvore no caso de qualquer uma das propriedades vermelho-preto ter sido violada.
    insereCorrecao(n);

    //Encontre a nova raiz_ para retornar.
    r = n;

    //Contabiliza troca
    this->qtdTrocas_++;

    while (r->getPai() != nullptr) {
        //Contabiliza comparacao
        this->qtdComparacoes_++;
        r = r->getPai();
    }

    return r;
}

void AVP::insere(int val) {
    NoVP *n = new NoVP();
    n->setCor(VERMELHO);
    n->setInfo(val);
    n->setEsq(nullptr);
    n->setDir(nullptr);
    raiz_ = auxinsere(raiz_, n);

}

/*
 * Imprime Arvore Vermelho-Preta
 */
void AVP::imprimeAux(NoVP *n, int indent) {
    int i;
    if (n == nullptr) {
        fputs("<Arvore vazia_!>", stdout);
        return;
    }
    if (n->getDir() != nullptr) {
        imprimeAux(n->getDir(), indent + INDENT_STEP);
    }
    for (i = 0; i < indent; i++)
        fputs(" ", stdout);
    if (n->getCor() == PRETO)
        cout << (int) n->getInfo() << endl;
    else
        //noh vermelho aparece entre o simbolo "<>"
        cout << "<" << (int) n->getInfo() << ">" << endl;
    if (n->getEsq() != nullptr) {
        imprimeAux(n->getEsq(), indent + INDENT_STEP);
    }
}

void AVP::imprimeAVP() {
    imprimeAux(raiz_, 0);
    puts("");
}

int AVP::getQtdComparacoes() const {
    return qtdComparacoes_;
}

int AVP::getQtdTrocas() const {
    return qtdTrocas_;
}
