#include "../../include/secao_2/HashAutor.hpp"
#include "../../include/secao_2/Primo.hpp"

using namespace std;

//Larissa: Luci, justifique por favor porque você fez "n/0.75"
/**
    * Cria a tabela Hash com preenchimento m�ximo de 75% com base no n�mero de dados. Escolhesse o menor primo que atende esse requisito.
    * @param n Tamanho da tabela Hash a ser criada
    */
HashAutor::HashAutor(int n) {
    //vari�vel do tipo ...
    tamanhoTabela = (int) (n / 0.75);
    tamanhoTabela = Primo::proxPrimo(tamanhoTabela);
    //vari�vel do tipo ... variavel de class
    tabelaAutores = new Autor[tamanhoTabela];
    vazia = true;


}

//Destrutor
HashAutor::~HashAutor() {
    delete[] tabelaAutores;
}

//Larissa: Luci, para que serve essa funcao calculaHash?
// retorna uma posi��o na tabela para que veja se � possivel inserir ou para realizar buscas.
/**
    * Descreva o que esse método faz (...)
    * @param ch
    * @param i
    */
int HashAutor::calculaHash(int ch, int i) {

    //vari�vel do tipo inteira para calcular a melhor funcao quadratica
    int valorQuadratica = pow(ch, 2) - 5 * ch + 7;

    //vari�vel do tipo ...
    int valorHash = (ch + i * valorQuadratica) % tamanhoTabela;

    //Larissa: Porque essa verificacao?
    //para ver se j� foi dada uma volta completa. Ela chegar no mesmo valor da chave original, implica em ela repetir o mesmo caminho depois.
    if (valorHash == ch)
        return -1;
    else
        return valorHash;
}


/**
    * Larissa: Luci, funcaoHash retorna um indice baseada se eh um Registro ou n�o? N�o, independe do dado, pq a funcao calcula chave j� passa para um int.
    * @param ch (...)
    * @param i (...)
    */
int HashAutor::funcaoHash(int ch, int i) {
    //variável do tipo ...
    int indiceTabela = calculaHash(ch, i);

    //se não há registro ou autor no indice?
    if (indiceTabela == -1)
        return -1;


    //Larissa: Ali em cima voc� colocou ponteiro, aqui nao deveria ser tamb�m? n�o sei pq s� rodou assim.. tb n�o entendi.
    Autor aux = tabelaAutores[indiceTabela];

    //Larissa: Se nao tem nome retorna o indice, porque? Porque assim eu insiro em uma posi��o vazia.
    if (aux.getNome() == "")
        return indiceTabela;
        //Senao calcula nova posição na tabela
    else
        return funcaoHash(ch, i + 1);


}


//Larissa: Luci, calculachave com essa assinatura eh a fun��o hash Para autor? Como voc� fez esse c�lculo? Sim, pegando valor da tabela ASCII
int HashAutor::calculaChave(string nome) {
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
void HashAutor::insere(Autor *a) {
    //Larissa: Luci, tem duas variaveis para receber a posicao? Porque? Uma calcula a chave e a outra a posi��o
    int ch = calculaChave(a->getNome());
    int pos = funcaoHash(ch, 0);

    if (pos == -1)
        cout << "N�o foi possivel inserir o valor" << endl;
    else {
        if (vazia)
            vazia = false;
        tabelaAutores[pos] = *a;
    }
}


/**
    * Função buscar eh responsável por procurar um Livro na Tabela Hash de Livros
    * @param id codigo unico do Livro a ser procurado
    */
int HashAutor::busca(string nome) {
    if (vazia) {
        cout << "Tabela vazia" << endl;
        return -1;
    }
    //variavel do tipo...
    int ch = calculaChave(nome);
    //variavel do tipo...
    int pos;

    Autor *aux;
    //fixme: ERRO. corrigir
    for (int i = 0; aux != NULL && aux->getNome() != nome; i++) {
        pos = calculaHash(ch, i);
        *aux = tabelaAutores[pos];
    }
    if (aux == NULL)
        return -1;
    else
        return pos;

}
