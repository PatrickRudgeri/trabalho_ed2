#include "../../include/secao_2/HashRegistro.hpp"
#include "../../include/secao_2/Primo.hpp"

using namespace std;

//Larissa: (TODO) Luci, justifique por favor porque você fez "n/0.75"
/**
* Cria a tabela Hash fazendo (...)
* @param n Tamanho da tabela Hash a ser criada
*/
HashRegistro::HashRegistro(int n) {
    tamanhoTabela = (int) (n / 0.75);
    tamanhoTabela = Primo::proxPrimo(tamanhoTabela);
    cout << "Tamanho da tabela hash de registros: " << tamanhoTabela << endl;
    tabelaRegistros = new Registro[tamanhoTabela];
}

HashRegistro::~HashRegistro() {
    delete[] tabelaRegistros;
}

// --------------------- Métodos privados -------------------- //

/**
* TODO: Descreva o que esse método faz
*
*/
int HashRegistro::calculaHash(int ch, int i) {

    //vari�vel do tipo inteira para calcular a melhor funcao quadratica
    int valorQuadratica = pow(ch, 2) - 5 * ch + 7;

    //vari�vel do tipo ...
    int valorHash = (ch + i * valorQuadratica) % tamanhoTabela;
    //question (Larissa): Porque essa verificacao?
    //para ver se j� foi dada uma volta completa. Ela chegar no mesmo valor da chave original, implica em ela repetir o mesmo caminho depois.
//    if (valorHash == ch)
    if (i == tamanhoTabela) //question (Patrick): não seria essa a forma correta de dar uma volta completa?
        return -1;
    else
        return valorHash;
}

/**
* question (Larissa): Luci, funcaoHash retorna um indice baseada se eh um Registro ou não?
* TODO: Descrever o que esse método faz
*/
int HashRegistro::funcaoHash(int ch, int i) {
    //variável do tipo ...
    int indiceTabela = calculaHash(ch, i);

    //se não há registro ou autor no indice?
    if (indiceTabela == -1)
        return -1;

    //question (Larissa): Ponteiro auxiliar do tipo Registro
    Registro *aux;
    //question (Larissa): Aux aponta para a tabela no indice calculado?
    aux = &tabelaRegistros[indiceTabela];
    //question (Larissa): Se aux eh null retorna o indice???? Achei estranho
//    cout << ">>> " << aux->getId() << endl;
    if (aux->getId() == -1) { //Se essa posição está vazia
        cout << indiceTabela << endl;
        return indiceTabela;

    } else {
        //Senao calcula nova posiçãoo na tabela
        return funcaoHash(ch, i + 1);
    }
}

//Larissa: Luci, calculachave eh a fun��o hash de divis�o Para livro? N�o, ela s� retorna um n�mero para ser usado na hash
int HashRegistro::calculaChave(long long id) {
    long long ch = 0;
    for (int i = 1; i <= 4; i++) {
        ch += id % 10000;
        id /= 10000;
    }
    return (int) ch;
}

// --------------------- Métodos públicos -------------------- //

/**
* Função inserir eh responsável por colocar um Registro na Tabela Hash de Livros
*
*/
void HashRegistro::inserir(Registro *p) {

    //Variavel do tipo inteira que recebe a chave a ser utilizada na hash
    if (p != nullptr) {
        int ch = calculaChave(p->getId());

        int pos = funcaoHash(ch, 0);

        //question (Larissa): Luci, tem duas variaveis para receber a posicao? Por que?

        // Essa função é a que retorna a posição candidata

        if (pos == -1) {
            cout << "Não foi possivel inserir o valor" << endl;
        }else {
            if (vazia) {
                vazia = false;
            }
            tabelaRegistros[pos] = *p;
        }
    }
}


int HashRegistro::buscar(long long id) {
    int pos; //variavel do tipo...
    int ch; //variavel do tipo...
    int i;
    Registro *aux;

    if (vazia) {
        cout << "Tabela vazia" << endl; //fixme: debug
        return -1;
    }
    ch = calculaChave(id);

    i = 0;
    while (true) {
        pos = calculaHash(ch, i);
        aux = &tabelaRegistros[pos];
        if (i == tamanhoTabela || aux->getId() == id) {
            break;
        }
        i++;
    }
    if (aux->getId() == -1) { //não encontrou, retorna -1
        return -1;
    } else {
        return pos; // caso contrário retorna a posição encontrada
    }
}

