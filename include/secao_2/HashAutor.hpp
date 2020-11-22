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
 *  @attr tamanhoTabela_ <o que é esse atributo?>
 *  @attr registro <o que é esse atributo?>
 *  @attr vazia_ <o que é esse atributo?>
 *  @attr *tabelaRegistros_ <o que é esse atributo?>
 *  @attr *tabelaAutores_  <o que é esse atributo?>
 *
 * */

class HashAutor {

private:
    int tamanhoTabela_;
    bool vazia_;
    Autor *tabelaAutores_;

    int funcaoHash(int ch, int i);

    int calcularHash(int ch, int i);

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
    int calcularChave(std::string nome);

    /**  <Breve descri??o> Insere
    *  @param isbn <indica codigo unico do Livro>
    *  @param nome <indica nome do Autor>
    *  @return <se tiver algum retorno descreva aqui>
    */

    void inserir(Autor *a);

    /**  <Breve descri??o> Busca
    *  @param isbn <indica codigo unico do Livro>
    *  @param nome <indica nome do Autor>
    *  @return <se tiver algum retorno descreva aqui>
    */
    int busca(const std::string& nome);
};

#endif // HASHAUTOR_H
