#ifndef HASH_H
#define HASH_H

#include <iostream>
#include "../Registro.hpp"
#include "Autor.hpp"

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

class Hash {

private:
    int tamanhoTabela;
    bool registro;
    bool vazia;
    Registro *tabelaRegistros;
    Autor *tabelaAutores;

    int funcaoHash(int ch, int i);

    int calculaHash(int ch, int i);

public:
    // Construtor
    Hash(int n);

    // Destrutor da classe
    ~Hash();

    /**  <Breve descrição> Calcula Chave
    *  @param id <indica codigo unico do Livro>
    *  @param nome <indica nome do Autor>
    *  @return <se tiver algum retorno descreva aqui>
    */
    int calculaChave(long long int id);

    int calculaChave(std::string nome);

    /**  <Breve descrição> Insere
    *  @param id <indica codigo unico do Livro>
    *  @param nome <indica nome do Autor>
    *  @return <se tiver algum retorno descreva aqui>
    */

    void insere(Registro *p);

    void insere(Autor *a);

    /**  <Breve descrição> Busca
    *  @param id <indica codigo unico do Livro>
    *  @param nome <indica nome do Autor>
    *  @return <se tiver algum retorno descreva aqui>
    */
    int busca(long long int id);

    int busca(std::string nome);

};

#endif // HASH_H
