#ifndef HASH_H
#define HASH_H
#include <iostream>
#include "../../tabela-hash/include/Registro.h"
#include "Autor.h"

using namespace std;

/** Breve descrição da classe
 *
 *  Descrição detalhada da classe
 *
 *  Atributos
 *  ----------------
 *  @attr tamanhoTabela <o que é esse atributo?>
 *  @attr registro <o que é esse atributo?>
 *  @attr vazia <o que é esse atributo?>
 *  @attr *tabelaRegistros <o que é esse atributo?>
 *  @attr *tabelaAutores  <o que é esse atributo?>
 * 
 * */

class Hash{

    private:
        int tamanhoTabela;
        bool registro;
        bool vazia;
        Registro *tabelaRegistros;
        Autor *tabelaAutores;
        int funcaoHash(int ch , int i );
        int calculaHash(int ch , int i);

    public:
        // Construtor 
        Hash(int n);
        // Destrutor da classe
        ~Hash();
        /**  <Breve descrição> Calcula Chave 
        *  @param isbn <indica codigo unico do Livro>
        *  @param nome <indica nome do Autor>
        *  @return <se tiver algum retorno descreva aqui>
        */
        int calculaChave(int isbn);
        int calculaChave(string nome);

        /**  <Breve descrição> Insere
        *  @param isbn <indica codigo unico do Livro>
        *  @param nome <indica nome do Autor>
        *  @return <se tiver algum retorno descreva aqui>
        */

        void insere(Registro *p);
        void insere(Autor *a);

        /**  <Breve descrição> Busca
        *  @param isbn <indica codigo unico do Livro>
        *  @param nome <indica nome do Autor>
        *  @return <se tiver algum retorno descreva aqui>
        */
        int busca(int isbn);
        int busca(string nome);

};

#endif // HASH_H
