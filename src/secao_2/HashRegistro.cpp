#include <cassert>
#include "../../include/secao_2/HashRegistro.hpp"
#include "../../include/secao_2/Primo.hpp"

using namespace std;

/**
    * Cria a tabela Hash com preenchimento m�ximo de 80% com base no n�mero de dados. Escolhesse o menor primo que atende esse requisito.
    * @param n Tamanho da tabela Hash a ser criada
    */
HashRegistro::HashRegistro(int n) {
    tamanhoTabela_ = (int) (n / 0.8);
    tamanhoTabela_ = Primo::proxPrimo(tamanhoTabela_);

    //se == -1 então deu erro. Para o programa e lança um erro
    assert(tamanhoTabela_ != -1);

    //cout << "Tamanho da tabela hash de registros: " << tamanhoTabela_ << endl; //fixme:debug
    tabelaRegistros_ = new Registro[tamanhoTabela_];
}

HashRegistro::~HashRegistro() {
    delete[] tabelaRegistros_;
}

// --------------------- Métodos privados -------------------- //

/**
* Função calculaHash eh responsável por calcular o valor da hash com base na chave e no numero de colisoes ja ocorridas
* @param ch chave referente ao Registro
* @param numColisoes numero de colisoes ocorridas ate o momento
* @return valor encontrado
*/
int HashRegistro::calculaHash(int ch, int numColisoes) {
    //variável do tipo  long para calcular o valor obitido pela equação quadratica usada no segundo termo da equacao hash
    long valorQuadratica = pow(ch, 2) - 5 * ch + 7;

    //vari�vel do tipo inteira que recebe o valor calculado para a hash
    int valorHash = (int) (((long) ch + (long) numColisoes * valorQuadratica) % tamanhoTabela_);

    //se o valor da equacao para o numero de colisoes fornecida for igual ao numero da chave, isso implica na consulta
    //dos mesmos valores já testados logo retorna-se -1, que indica que não foi encontrada posicao
    if (valorHash == ch) return -1;
    //fixme: verificar
    //if (numColisoes == tamanhoTabela_)
    //    return -1;
    else
        return valorHash;
}

/**
* Função recursiva funcaoHash eh responsável por encontrar uma posicao na Tabela Hash com base na chave referente ao Registro
* @param ch chave referente ao Registro
* @param numColisoes numero de colisoes ocorridas ate o momento
* @return posicao encontrada
*/
int HashRegistro::funcaoHash(int ch, int numColisoes) {
    //variável do tipo inteira que recebe a posicao calculada para os valores passados
    int indiceTabela = calculaHash(ch, numColisoes);

    //se não há registro
    if (indiceTabela == -1)
        return -1;

    //variavel do tipo Registro que axilia a saber se a posicao já se encontra ocupada
    Registro *aux;
    aux = &tabelaRegistros_[indiceTabela];

    if (aux->getId() == -1) { //Se essa posição está vazia_
        return indiceTabela;

    } else {
        //Senao calcula nova posiçãoo na tabela
        return funcaoHash(ch, numColisoes + 1);
    }
}

/**
* Função calculaChave eh responsável por calcular a chave utilizada na funcao hash
 * @param id id do livro
 * @return ch chave a ser utilizada na funcao hash
*/
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
 * @param p Registro a ser inserido
*/
void HashRegistro::inserir(Registro *p) {

    if (p != nullptr) {
        //Variavel do tipo inteira que recebe a chave a ser utilizada na hash
        int ch = calculaChave(p->getId());

        //Variavel do tipo inteira que recebe a posição onde o registro p deve ser inserido
        int pos = funcaoHash(ch, 0);

        //se pos recebe -1, inica que não foi encontrada posição na tabela
        if (pos == -1) {
            cout << "Não foi possivel inserir o Registro" << endl;
        } else {
            //se a tabela estiver vazia, altera o valor da variavel de classe vazia_ para false
            if (vazia_) {
                vazia_ = false;
            }
            tabelaRegistros_[pos] = *p;
        }
    }
}

/**
* Função buscar eh responsável por procurar um Registro na Tabela Hash de Livros
 * @param id id do livro
 * @return posicao do registro na tabela Hash
*/
int HashRegistro::buscar(long long id) {
    int pos; //variavel do tipo inteira que recebe a posição calculada pela funcao hash
    int ch; //variavel do tipo inteira que recebe a chave chaculada para o registo
    int numColisoes;

    if (vazia_) {
        cout << "Tabela vazia_" << endl;
        return -1;
    }
    ch = calculaChave(id);

    //Enquanto encontra o registro e o número de colisões é diferente do tamanho da tabela, procura uma posição vazia na tabela, se encontado retorna a posição
    numColisoes = 0;
    while (true) {
        if (numColisoes == tamanhoTabela_) {
            break;
        }
        pos = calculaHash(ch, numColisoes);

        assert(pos >= 0 && pos < tamanhoTabela_);

        Registro aux = tabelaRegistros_[pos];
        if (aux.getId() == id) {
            return pos;
        }
        numColisoes++;
    }
    //não encontrou, retorna -1
    return -1;

}

Registro *HashRegistro::getTabelaRegistros() {
    return tabelaRegistros_;
}

bool HashRegistro::isVazia() {
    return vazia_;
}

