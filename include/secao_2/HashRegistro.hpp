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
 *  @attr tamanhoTabela_ TODO: O que � esse atributo?
 *  @attr *tabelaRegistros_ TODO: O que � esse atributo?
 *  @attr vazia_ TODO: O que � esse atributo?
 *
 * */
class HashRegistro {
private:

    int tamanhoTabela_;
    bool vazia_;
    Registro *tabelaRegistros_;

    int calculaHash(int ch, int i);

    int funcaoHash(int ch, int i);

    /**  Calcular Chave
    *  @param id : indica codigo unico do Livro
    */
    int calculaChave(long long id);

public:

    /**  Construtor da classe com par�metro
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
    */
    int buscar(long long id);

    bool isVazia();

    Registro *getTabelaRegistros();

};

#endif // HASHREGISTRO_H
