#ifndef HASHREGISTRO_H
#define HASHREGISTRO_H

#include <iostream>
#include "../Registro.hpp"
#include "Autor.hpp"

/** TODO: Breve descrição da classe
 *
 *  TODO: Descrição detalhada da classe
 *
 *  Atributos
 *  ----------------
 *  @attr tamanhoTabela TODO: O que é esse atributo?
 *  @attr *tabelaRegistros TODO: O que é esse atributo?
 *  @attr vazia TODO: O que é esse atributo?
 *
 * */
class HashRegistro {
private:

    int tamanhoTabela;
    Registro *tabelaRegistros;
    bool vazia;

    /**  TODO: breve descrição da classe
    *  @param ch : TODO: O que é esse parâmetro?
    *  @param i : TODO: O que é esse parâmetro?
    *  @return : TODO: se tiver algum retorno descreva aqui
    */
    int calculaHash(int ch, int i);

    /**  TODO: breve descrição da classe
    *  @param ch : TODO: O que é esse parâmetro?
    *  @param i : TODO: O que é esse parâmetro?
    *  @return : TODO: se tiver algum retorno descreva aqui
    */
    int funcaoHash(int ch, int i);

    /**  Calcular Chave
    *  @param id : indica codigo unico do Livro
    *  @return : TODO: se tiver algum retorno descreva aqui
    */
    int calculaChave(long long id);

public:

    /**  Construtor da classe com parâmetro
    *  @param n : TODO: O que é esse parâmetro?
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
