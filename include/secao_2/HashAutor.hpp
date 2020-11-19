#ifndef HASHAUTOR_H
#define HASHAUTOR_H

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

class HashAutor {

private:
    int tamanhoTabela;
    bool vazia;
    Autor *tabelaAutores;

    int funcaoHash(int ch, int i);

    int calculaHash(int ch, int i);

public:
    // Construtor
    HashAutor(int n);

    // Destrutor da classe
    ~HashAutor();

    /**  <Breve descrição> Calcula Chave
    *  @param id <indica codigo unico do Livro>
        *  @param nome <indica nome do Autor>
        *  @return <se tiver algum retorno descreva aqui>
        */
    int calculaChave(std::string nome);

    /**  <Breve descri??o> Insere
    *  @param isbn <indica codigo unico do Livro>
    *  @param nome <indica nome do Autor>
    *  @return <se tiver algum retorno descreva aqui>
    */

    void insere(Autor *a);

    /**  <Breve descri??o> Busca
    *  @param isbn <indica codigo unico do Livro>
    *  @param nome <indica nome do Autor>
    *  @return <se tiver algum retorno descreva aqui>
    */
    int busca(std::string nome);
};

#endif // HASHAUTOR_H
