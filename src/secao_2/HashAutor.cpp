#include <cassert>
#include "../../include/secao_2/HashAutor.hpp"
#include "../../include/secao_2/Primo.hpp"

using namespace std;

//Larissa: Luci, justifique por favor porque você fez "n/0.75"
/**
    * Cria a tabela Hash com preenchimento m�ximo de 75% com base no n�mero de dados. Escolhesse o menor primo que atende esse requisito.
    * @param n Tamanho da tabela Hash a ser criada
    */
HashAutor::HashAutor(int n) {
    //variável do tipo ...
    tamanhoTabela_ = (int) (n / 0.75);
    tamanhoTabela_ = Primo::proxPrimo(tamanhoTabela_);

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

//Larissa: Luci, para que serve essa funcao calcularHash?
// retorna uma posi��o na tabela para que veja se � possivel inserir ou para realizar buscas.
//TODO: documentar definição da função
//TODO: documentar os blocos funcionais e variáveis dentro da função
int HashAutor::calcularHash(int ch, int i) {

    //vari�vel do tipo inteira para calcular a melhor funcao quadratica
    int valorQuadratica = pow(ch, 2) - 5 * ch + 7;

    //vari�vel do tipo ...
    int valorHash = (ch + i * valorQuadratica) % tamanhoTabela_;

    //Larissa: Porque essa verificacao?
    //para ver se j� foi dada uma volta completa. Ela chegar no mesmo valor da chave original, implica em ela repetir o mesmo caminho depois.
    if (valorHash == ch)
        return -1;
    else
        return valorHash;
}

//TODO: documentar definição da função
//TODO: documentar os blocos funcionais e variáveis dentro da função
int HashAutor::funcaoHash(int ch, int i) {
    //variável do tipo ...
    int indiceTabela = calcularHash(ch, i);

    //se não há registro ou autor no indice?
    if (indiceTabela == -1)
        return -1;

    Autor aux = tabelaAutores_[indiceTabela];

    if (aux.getNome() == "")
        return indiceTabela;
        //Senao calcula nova posição na tabela
    else
        return funcaoHash(ch, i + 1);


}

//Larissa: Luci, calculachave com essa assinatura eh a fun��o hash Para autor? Como voc� fez esse c�lculo? Sim, pegando valor da tabela ASCII
//TODO: documentar definição da função
//TODO: documentar os blocos funcionais e variáveis dentro da função
int HashAutor::calcularChave(string nome) {
    int ch = 0;
    int tamanhoString = nome.size();
    for (int i = 1; i < tamanhoString; i++) {
        if (nome[i] >= 'A' && nome[i] <= 'Z')
            ch += (nome[i] - 'A');
        else if (nome[i] >= 'a' && nome[i] <= 'z')
            ch += (nome[i] - 'a');
    }

    return ch;

}


/**
    * Função inserir eh responsável por colocar um Autor na Tabela Hash de Autores
    * @param a Autor a ser inserido
    */
//TODO: documentar os blocos funcionais e variáveis dentro da função
void HashAutor::inserir(Autor *a) {
    //ch recebe a chave
    int ch = calcularChave(a->getNome());
    //pos recebe a posiçao para ser inserido o autor
    int pos = funcaoHash(ch, 0);

    if (pos == -1)
        cout << "Não foi possivel inserir o valor" << endl;
    else {
        if (vazia_)
            vazia_ = false;
        tabelaAutores_[pos] = *a;
    }
}

//TODO: documentar definição da função
//TODO: documentar os blocos funcionais e variáveis dentro da função
int HashAutor::busca(const string& nome) {
    int i;
    int ch;
    int pos;
    if (vazia_) {
        cout << "Tabela vazia_" << endl;
        return -1;
    }
    //variavel do tipo...
    ch = calcularChave(nome);

    i = 0;
    while (true) {
        if (i == tamanhoTabela_) {
            break;
        }
        pos = calcularHash(ch, i);

        assert(pos >= 0 && pos < tamanhoTabela_);

        Autor aux = tabelaAutores_[pos];
        if (aux.getNome() == nome) {
            return pos;
        }
        i++;
    }

    return -1;
}
