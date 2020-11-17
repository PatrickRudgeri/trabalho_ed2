
#include <cmath>
#include "../../include/secao_2/Hash.hpp"
#include "../../include/Registro.hpp"
#include "../../include/secao_2/Autor.hpp"
#include "../../include/secao_2/Primo.hpp"


using namespace std;

//Larissa: Luci, justifique por favor porque voc� fez "n/0.75"
/**
    * Cria a tabela Hash fazendo (...)
    * @param n Tamanho da tabela Hash a ser criada
    */
Hash::Hash(int n) {
    Primo *p;
    //vari�vel do tipo ...
    tamanhoTabela = (int) (n / 0.75);

    //teste?
    cout << tamanhoTabela << endl;
    //vari�vel do tipo ...
    vazia = true;

    //Descrever brevemente o que est� sendo feito
    p = new Primo();
    p->criatabela(tamanhoTabela);
    tamanhoTabela = p->proxPrimo(tamanhoTabela);
    cout << tamanhoTabela << endl;
}

//Destrutor
Hash::~Hash() {
    //dtor
}

//Larissa: Luci, para que serve essa funcao calculaHash?
/**
    * Descreva o que esse m�todo faz (...)
    * @param ch 
    * @param i
    */
int Hash::calculaHash(int ch, int i) {

    int valorQuadratica; //vari�vel do tipo inteira para calcular a melhor funcao quadratica
    int valorHash;  //vari�vel do tipo ...

    valorQuadratica = pow(ch, 2) - 5 * ch + 7;

    valorHash = (ch + i * valorQuadratica) % tamanhoTabela;

    //Larissa: Porque essa verificacao?
    if (valorHash == ch)
        return -1;
    else
        return valorHash;
}


/**
    * Larissa: Luci, funcaoHash retorna um indice baseada se eh um Registro ou n�o?
    * @param ch (...)
    * @param i (...)
    */
int Hash::funcaoHash(int ch, int i) {
    //vari�vel do tipo ...
    int indiceTabela = calculaHash(ch, i);

    //se n�o h� registro ou autor no indice?
    if (indiceTabela < 0)
        return -1;

    //se eh registro
    if (registro) {
        //Larissa:Ponteiro auxiliar do tipo Registro
        Registro *aux;
        *aux = tabelaRegistros[indiceTabela];
        //Larissa: Se aux eh null retorna o indice???? Achei estranho
        if (aux == NULL)
            return indiceTabela;
            //Senao calcula nova posi��o na tabela
        else
            return funcaoHash(ch, i + 1);
    } else {
        //Larissa: Ali em cima voc� colocou ponteiro, aqui nao deveria ser tamb�m?
        Autor aux = tabelaAutores[indiceTabela];

        //Larissa: Se nao tem nome retorna o indice, porque?
        if (aux.getNome() == "")
            return indiceTabela;
            //Senao calcula nova posi��o na tabela
        else
            return funcaoHash(ch, i + 1);
    }
}

//Larissa: Luci, calculachave eh a fun��o hash de divis�o Para livro? 
int Hash::calculaChave(long long id) {
    int ch = 0;
    for (int i = 1; i <= 4; i++) {
        ch += id % 10000;
        id = id / 10000;
    }
    return ch;
}


//Larissa: Luci, calculachave com essa assinatura eh a fun��o hash Para autor? Como voc� fez esse c�lculo?
int Hash::calculaChave(string nome) {
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
    * Fun��o insere eh respons�vel por colocar um Registro na Tabela Hash de Livros
    * @param p Registro a ser inserido
    */
void Hash::insere(Registro *p) {
    int ch; //Variavel do tipo inteira que recebe a posicao a ser inserida
    int pos;

    //se a tabela esta vazia
    if (vazia) {
        //Uma nova tabela eh criada
        tabelaRegistros = new Registro[tamanhoTabela];
        vazia = false;
        registro = true;
    }

    ch = calculaChave(p->getIsbn10());
    pos = funcaoHash(ch, 0);

    //Larissa: Luci, tem duas variaveis para receber a posicao? Porque?
    if (pos == -1)
        cout << "N�o foi possivel inserir o valor" << endl;
    else
        tabelaRegistros[pos] = *p;
}

/**
    * Fun��o insere eh respons�vel por colocar um Autor na Tabela Hash de Autores
    * @param a Autor a ser inserido
    */
void Hash::insere(Autor *a) {
    int ch;//Larissa: Luci, tem duas variaveis para receber a posicao? Porque?
    int pos;

    //se a tabela esta vazia
    if (vazia) {
        //Uma nova tabela eh criada
        tabelaAutores = new Autor[tamanhoTabela];
        vazia = false;
        registro = false;
    }

    ch = calculaChave(a->getNome());
    pos = funcaoHash(ch, 0);

    if (pos == -1)
        cout << "N�o foi possivel inserir o valor" << endl;
    else
        tabelaAutores[pos] = *a;
}

/**
    * Fun��o busca eh respons�vel por procurar um Livro na Tabela Hash de Livros
    * @param id codigo unico do Livro a ser procurado
    */
int Hash::busca(long long int id) {
    Registro *aux;
    int ch; //variavel do tipo...
    int pos; //variavel do tipo...

    if (vazia) {
        cout << "Tabela vazia" << endl;
        return -1;
    }

    ch = calculaChave(id);

    for (int i = 0; aux != NULL && aux->getId() != id; i++) {
        pos = calculaHash(ch, i);
        *aux = tabelaRegistros[pos];
    }
    if (aux == NULL)
        return -1;
    else
        return pos;

}

/**
    * Fun��o busca eh respons�vel por procurar um Autor na Tabela Hash de Autores
    * @param nome nome do autor a ser procurado
    */
int Hash::busca(string nome) {
    int pos;
    int i;
    int ch;
    Autor *aux;

    if (vazia) {
        cout << "Tabela vazia" << endl;
        return -1;
    }
    //variavel do tipo...
    ch = calculaChave(nome);

    for (int i = 0; aux != NULL && aux->getNome() != nome; i++) {
        pos = calculaHash(ch, i);
        *aux = tabelaAutores[pos];
    }
    if (aux == nullptr)
        return -1;
    else
        return pos;

}
