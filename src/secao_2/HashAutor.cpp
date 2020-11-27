#include <cassert>
#include "../../include/secao_2/HashAutor.hpp"
#include "../../include/secao_2/Primo.hpp"
#include "math.h"

using namespace std;

/**
    * Cria a tabela Hash com preenchimento m�ximo de 80% com base no n�mero de dados. Escolhesse o menor primo que atende esse requisito.
    * @param n Tamanho da tabela Hash a ser criada
    */
HashAutor::HashAutor(int n) {

    tamanhoTabela_ = (int) (n / 0.8);
    tamanhoTabela_ = Primo::proxPrimo(tamanhoTabela_); // não está lindo o tabelaPrimos[i] na funcao;

    //se == -1 então deu erro. Para o programa e lança um erro
    assert(tamanhoTabela_ != -1);

    //variável do tipo ... variavel de class
    tabelaAutores_ = new Autor[tamanhoTabela_];
    vazia_ = true;
}

//Destrutor
HashAutor::~HashAutor() {
    delete[] tabelaAutores_;
}

/**
* Função calcularHash eh responsável por calcular o valor da hash com base na chave e no numero de colisoes ja ocorridas
* @param ch chave referente ao Registro
* @param numColisoes numero de colisoes ocorridas ate o momento
* @return valor encontrado
*/
int HashAutor::calcularHash(int ch, int i) {

    //variável do tipo int para calcular o valor obitido pela equação quadratica usada no segundo termo da equacao hash
    int valorQuadratica = pow(ch, 2) - 5 * ch + 7;

    int valorHash = (ch + i * valorQuadratica) % tamanhoTabela_;

    //se o valor da equacao para o numero de colisoes fornecida for igual ao numero da chave, isso implica na consulta dos mesmos valores já testados
    //logo retorna-se -1, que indica que não foi encontrada posicao
    if (valorHash == ch) return -1;
    if (valorHash == ch)
        return -1;
    else
        return valorHash;
}

/**
* Função recursiva funcaoHash eh responsável por encontrar uma posicao na Tabela Hash com base na chave referente ao Autor
* @param ch chave referente ao Autor
* @param numColisoes numero de colisoes ocorridas ate o momento
* @return posicao encontrada
*/
int HashAutor::funcaoHash(int ch, int i) {
    //variável do tipo inteira que recebe a posicao calculada para os valores passados
    int indiceTabela = calcularHash(ch, i);

    //se não há autor
    if (indiceTabela == -1)
        return -1;

    Autor aux = tabelaAutores_[indiceTabela];

    if (aux.getNome() == "")
        return indiceTabela;
        //Senao calcula nova posição na tabela
    else
        return funcaoHash(ch, i + 1);
}


/**
    * Função inserir eh responsável por colocar um Autor na Tabela Hash de Autores
    * @param a Autor a ser inserido
    */
void HashAutor::inserir(Autor *a) {
    //ch recebe a chave
    int ch = a->getId();
    //pos recebe a posiçao para ser inserido o autor
    int pos = funcaoHash(ch, 0);

    if (pos == -1)
        cout << "Não foi possivel inserir o Autor" << endl;
    else {
        if (vazia_)
            vazia_ = false;
        tabelaAutores_[pos] = *a;
    }
}

/**
* Função buscar eh responsável por procurar um Autor na Tabela Hash de Autores
 * @param id id do Autor
 * @return posicao do registro na tabela Hash
*/
int HashAutor::busca(int id) {
    int numColisoes;
    int pos;//variavel do tipo inteira que recebe a posição calculada pela funcao hash
    if (vazia_) {
        cout << "Tabela vazia_" << endl;
        return -1;
    }

    //Enquanto não o autor e o número de colisões é diferente do tamanho da tabela, procura uma posição vazia na tabela, se encontado retorna a posição
    numColisoes = 0;
    while (true) {
        if (numColisoes == tamanhoTabela_) {
            break;
        }
        pos = calcularHash(id, numColisoes);

        assert(pos >= 0 && pos < tamanhoTabela_);

        Autor aux = tabelaAutores_[pos];
        // se autor buscado estiver na tabela, então incrementa frequencia e retorna posição
        if (aux.getId() == id) {
            int freq = aux.getFrequencia();
            aux.setfrequencia(freq + 1);
            return pos;
        }
        numColisoes++;
    }
    //não encontrou, retorna -1
    return -1;
}
