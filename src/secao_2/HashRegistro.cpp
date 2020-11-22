#include <assert.h>
#include "../../include/secao_2/HashRegistro.hpp"
#include "../../include/secao_2/Primo.hpp"

using namespace std;

//Larissa: (TODO) Luci, justifique por favor porque você fez "n/0.75"
//TODO: documentar definição da função
//TODO: documentar os blocos funcionais e variáveis dentro da funçãoam n Tamanho da tabela Hash a ser criada
HashRegistro::HashRegistro(int n) {
    tamanhoTabela_ = (int) (n / 0.75);
    tamanhoTabela_ = Primo::proxPrimo(tamanhoTabela_);

    //se == -1 então deu erro. Para o programa e lança um erro
    assert(tamanhoTabela_ != -1);

    cout << "Tamanho da tabela hash de registros: " << tamanhoTabela_ << endl;
    tabelaRegistros_ = new Registro[tamanhoTabela_];
}

HashRegistro::~HashRegistro() {
    delete[] tabelaRegistros_;
}

// --------------------- Métodos privados -------------------- //

//TODO: documentar definição da função
//TODO: documentar os blocos funcionais e variáveis dentro da função
int HashRegistro::calculaHash(int ch, int i) {
    //variável do tipo long para calcular a melhor funcao quadratica
    long valorQuadratica = pow(ch, 2) - 5 * ch + 7;

    //vari�vel do tipo ...
    int valorHash = (int) (((long) ch + (long) i * valorQuadratica) % tamanhoTabela_);
    //question (Larissa): Porque essa verificacao?
    //para ver se j� foi dada uma volta completa. Ela chegar no mesmo valor da chave original, implica em ela repetir o mesmo caminho depois.

//    if (valorHash == ch) return -1;
    if (i == tamanhoTabela_) //question: Não é assim que representa a volta completa?
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
    aux = &tabelaRegistros_[indiceTabela];

    if (aux->getId() == -1) { //Se essa posição está vazia_
        cout << indiceTabela << endl;
        return indiceTabela;

    } else {
        //Senao calcula nova posiçãoo na tabela
        return funcaoHash(ch, i + 1);
    }
}

//Larissa: Luci, calculachave eh a fun��o hash de divis�o Para livro? N�o, ela s� retorna um n�mero para ser usado na hash
//TODO: documentar definição da função
//TODO: documentar os blocos funcionais e variáveis dentro da função
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
*/
//TODO: documentar definição da função
//TODO: documentar os blocos funcionais e variáveis dentro da função
void HashRegistro::inserir(Registro *p) {

    //Variavel do tipo inteira que recebe a chave a ser utilizada na hash
    if (p != nullptr) {
        int ch = calculaChave(p->getId());

        int pos = funcaoHash(ch, 0);

        if (pos == -1) {
            cout << "Não foi possivel inserir o valor" << endl;
        } else {
            if (vazia_) {
                vazia_ = false;
            }
            tabelaRegistros_[pos] = *p;
        }
    }
}

//TODO: documentar definição da função
//TODO: documentar os blocos funcionais e variáveis dentro da função
int HashRegistro::buscar(long long id) {
    int pos; //variavel do tipo...
    int ch; //variavel do tipo...
    int i;

    if (vazia_) {
        cout << "Tabela vazia_" << endl;
        return -1;
    }
    ch = calculaChave(id);

    i = 0;
    while (true) {
        if (i == tamanhoTabela_) {
            break;
        }
        pos = calculaHash(ch, i);

        assert(pos >= 0 && pos < tamanhoTabela_);

        Registro aux = tabelaRegistros_[pos];
        if (aux.getId() == id) {
            return pos;
        }
        i++;
    }
    //não encontrou, retorna -1
    return -1;

}

