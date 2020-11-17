#include "Hash.h"
#include "math.h"
#include "Registro.h"
#include "Autor.h"
#include "Primo.h"
#include <iostream>


using namespace std;

//Larissa: Luci, justifique por favor porque voc� fez "n/0.75"
/**
    * Cria a tabela Hash fazendo (...)
    * @param n Tamanho da tabela Hash a ser criada
    */
Hash::Hash(int n)
{
    //vari�vel do tipo ...
    tamanhoTabela = (int)(n/0.75);

    //teste?
    cout << tamanhoTabela << endl;
    //vari�vel do tipo ...
    vazia = true;

    //Descrever brevemente o que est� sendo feito
    Primo *p = new Primo();
    p->criatabela(tamanhoTabela);
    tamanhoTabela = p->proxPrimo(tamanhoTabela);
    cout << tamanhoTabela << endl;
}

//Destrutor
Hash::~Hash()
{
    //dtor
}

//Larissa: Luci, para que serve essa funcao calculaHash?
/**
    * Descreva o que esse m�todo faz (...)
    * @param ch 
    * @param i
    */
int Hash::calculaHash(int ch , int i){

    //vari�vel do tipo inteira para calcular a melhor funcao quadratica
    int valorQuadratica = pow(ch,2) - 5*ch + 7; 

    //vari�vel do tipo ...
    int valorHash = (ch + i*valorQuadratica)%tamanhoTabela;

    //Larissa: Porque essa verificacao?
    if(valorHash == ch)
        return -1;
    else
        return valorHash;
}


/**
    * Larissa: Luci, funcaoHash retorna um indice baseada se eh um Registro ou n�o?
    * @param ch (...)
    * @param i (...)
    */
int Hash::funcaoHash(int ch , int i)
{
    //vari�vel do tipo ...
    int indiceTabela = calculaHash(ch , i);

    //se n�o h� registro ou autor no indice?
    if(indiceTabela == -1)
        return -1;

    //se eh registro
    if(registro)
    {
        //Larissa:Ponteiro auxiliar do tipo Registro
        Registro *aux;
        //Larissa:Aux aponta para a tabela no indice calculado?
        *aux = tabelaRegistros[indiceTabela];
        //Larissa: Se aux eh null retorna o indice???? Achei estranho
        if(aux == NULL)
            return indiceTabela;
        //Senao calcula nova posi��o na tabela
        else
            return funcaoHash(ch , i+1);
    }
    else
    {
        //Larissa: Ali em cima voc� colocou ponteiro, aqui nao deveria ser tamb�m?
        Autor aux = tabelaAutores[indiceTabela];

        //Larissa: Se nao tem nome retorna o indice, porque?
        if(aux.getNome() == "")
            return indiceTabela;
        //Senao calcula nova posi��o na tabela
        else
            return funcaoHash(ch , i+1);
    }


}

//Larissa: Luci, calculachave eh a fun��o hash de divis�o Para livro? 
int Hash::calculaChave(int isbn)
{
    int ch = 0;
    for(int i = 1 ; i <= 4 ; i++)
    {
        ch += isbn%10000;
        isbn = isbn/10000;
    }
    return ch;
}


//Larissa: Luci, calculachave com essa assinatura eh a fun��o hash Para autor? Como voc� fez esse c�lculo?
int Hash::calculaChave(string nome)
{
    int ch = 0;
    int tamanhoString = nome.size();
    for(int i = 1 ; i < tamanhoString ; i++)
    {
        if(nome[i] > 'A' && nome[i] < 'Z')
            ch += (nome[i] - 'A');
        else if(nome[i] > 'a' && nome[i] < 'z')
            ch += (nome[i] - 'a');
    }

    return ch;

}


/**
    * Fun��o insere eh respons�vel por colocar um Registro na Tabela Hash de Livros
    * @param p Registro a ser inserido
    */
void Hash::insere(Registro *p)
{
    //se a tabela esta vazia
    if(vazia)
    {
        //Uma nova tabela eh criada
        tabelaRegistros = new Registro[tamanhoTabela];
        vazia = false;
        registro = true;
    }

    //Variavel do tipo inteira que recebe a posicao a ser inserida
    int ch = calculaChave(p->getISNB());
    //variavel ?
    int pos = funcaoHash(ch , 0);

    //Larissa: Luci, tem duas variaveis para receber a posicao? Porque?


    if(pos == -1)
        cout << "N�o foi possivel inserir o valor" << endl;
    else
        tabelaRegistros[pos] = *p;
}

/**
    * Fun��o insere eh respons�vel por colocar um Autor na Tabela Hash de Autores
    * @param a Autor a ser inserido
    */
void Hash::insere(Autor *a)
{
    //se a tabela esta vazia
    if(vazia)
    {
        //Uma nova tabela eh criada
        tabelaAutores = new Autor[tamanhoTabela];
        vazia = false;
        registro = false;
    }

    //Larissa: Luci, tem duas variaveis para receber a posicao? Porque?
    int ch = calculaChave(a->getNome());
    int pos = funcaoHash(ch , 0);

    if(pos == -1)
        cout << "N�o foi possivel inserir o valor" << endl;
    else
        tabelaAutores[pos] = *a;
}

/**
    * Fun��o busca eh respons�vel por procurar um Livro na Tabela Hash de Livros
    * @param isbn codigo unico do Livro a ser procurado
    */
int Hash::busca(int isbn)
{
    if(vazia)
    {
        cout << "Tabela vazia" << endl;
        return -1;
    }
    //variavel do tipo...
    int ch = calculaChave(isbn);
    //variavel do tipo...
    int pos;

    Registro *aux;
    for(int i = 0 ; aux != NULL && aux->getISNB() != isbn ; i++ )
    {
        pos = calculaHash(ch , i);
        *aux = tabelaRegistros[pos];
    }
    if(aux == NULL)
        return -1;
    else
        return pos;

}

/**
    * Fun��o busca eh respons�vel por procurar um Autor na Tabela Hash de Autores
    * @param nome nome do autor a ser procurado
    */
int Hash::busca(string nome)
{
    if(vazia)
    {
        cout << "Tabela vazia" << endl;
        return -1;
    }
    //variavel do tipo...
    int ch = calculaChave(nome);
    //variavel do tipo...
    int pos;
    
    Autor *aux;
    for(int i = 0 ; aux != NULL && aux->getNome() != nome ; i++ )
    {
        pos = calculaHash(ch , i);
        *aux = tabelaAutores[pos];
    }
    if(aux == NULL)
        return -1;
    else
        return pos;

}
