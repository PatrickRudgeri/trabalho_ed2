#ifndef HASHREGISTRO_H
#define HASHREGISTRO_H

#include <iostream>
#include "../Registro.hpp"
#include "Autor.hpp"

/** TODO: Breve descri��o da classe
 *
 *  TODO: Descri��o detalhada da classe
 *
 *  Atributos
 *  ----------------
 *  @attr tamanhoTabela TODO: O que � esse atributo?
 *  @attr *tabelaRegistros TODO: O que � esse atributo?
 *  @attr vazia TODO: O que � esse atributo?
 *
 * */
class HashRegistro {
private:

    int tamanhoTabela;
    Registro *tabelaRegistros;
    bool vazia;

    /**  TODO: breve descri��o da classe
    *  @param ch : TODO: O que � esse par�metro?
    *  @param i : TODO: O que � esse par�metro?
    *  @return : TODO: se tiver algum retorno descreva aqui
    */
    int calculaHash(int ch, int i);

    /**  TODO: breve descri��o da classe
    *  @param ch : TODO: O que � esse par�metro?
    *  @param i : TODO: O que � esse par�metro?
    *  @return : TODO: se tiver algum retorno descreva aqui
    */
    int funcaoHash(int ch, int i);

    /**  Calcular Chave
    *  @param id : indica codigo unico do Livro
    *  @return : TODO: se tiver algum retorno descreva aqui
    */
    int calculaChave(long long id);

public:

    /**  Construtor da classe com par�metro
    *  @param n : TODO: O que � esse par�metro?
    */
    HashRegistro(int n);

    // Destrutor da classe
    ~HashRegistro();

    /** Inserir um registro na tabela hash
    *  @param p : registro a ser inserido
    */
    void inserir(Registro *p);

    /**  Buscar na tabela hash de registros
    *  @param id indica codigo unico do Livro
    *  @return TODO: se tiver algum retorno descreva aqui
    */
    int buscar(long long id);

};

#endif // HASHREGISTRO_H
