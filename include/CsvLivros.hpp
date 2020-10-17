#ifndef TRABALHO_ED2_CSV_H
#define TRABALHO_ED2_CSV_H

#include <iostream>
#include "Registro.hpp"


/** Breve descrição da classe
 *
 *  Descrição detalhada da classe
 *
 *  Atributos
 *  ----------------
 *  @attr nomeArquivo_ <o que é esse atributo?>
 *  @attr registros_  <o que é esse atributo?>
 * */
class CsvLivros {
public:

    CsvLivros(){};

    /**  <Breve descrição>
     *  @param registros <o que é esse parâmetro?>
     * */
    CsvLivros(Registro *registros);

    /**  <Breve descrição>
     *  @param nomeArquivo <o que é esse parâmetro?>
     *  @param numLinhas <o que é esse parâmetro?>
     *  @param aleatorio <o que é esse parâmetro?>
     *  @param seed <o que é esse parâmetro?>
     * */
    void lerCsv(const std::string &nomeArquivo, int numLinhas, bool aleatorio = false, int seed = -1);

    /**  <Breve descrição>
     *  @param nomeArquivoOriginal <o que é esse parâmetro?>
     *  @return <se tiver algum retorno descreva aqui>
     * */
    std::string padronizarCsv(std::string nomeArquivoOriginal);


private:
    std::string nomeArquivo_;
    Registro *registros_{};

    /**  <Breve descrição>
     *  @param linha <o que é esse parâmetro?>
     *  @param registro <o que é esse parâmetro?>
     * */
    static void processarLinha(const std::string &linha, Registro *registro);
};


#endif //TRABALHO_ED2_CSV_H
