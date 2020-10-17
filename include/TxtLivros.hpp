#ifndef TRABALHO_ED2_TXTLIVROS_HPP
#define TRABALHO_ED2_TXTLIVROS_HPP

#include <iostream>

/** Breve descrição da classe
 *
 *  Descrição detalhada da classe
 *
 *  Atributos
 *  ----------------
 *  @attr nArgs <o que é esse atributo?>
 *  @attr xArgs  <o que é esse atributo?>
 * */
class TxtLivros {
public:
    TxtLivros();

    virtual ~TxtLivros();

    /**  <Breve descrição>
     *  @param nomeArquivo <o que é esse parâmetro?>
     * */
    void lerEntrada(std::string nomeArquivo);

    /**  <Breve descrição>
     *  @return <se tiver algum retorno descreva aqui>
     * */
    int *getNargs() const;

    /**  <Breve descrição>
     *  @return <se tiver algum retorno descreva aqui>
     * */
    int getXarg() const;

private:
    int *nArgs;
    int xArg;
};


#endif //TRABALHO_ED2_TXTLIVROS_HPP
