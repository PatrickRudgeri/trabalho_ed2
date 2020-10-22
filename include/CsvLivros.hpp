#ifndef TRABALHO_ED2_CSV_H
#define TRABALHO_ED2_CSV_H

#include <iostream>
#include "Registro.hpp"


/** TODO:Breve descrição da classe
 *
 *  TODO:Descrição detalhada da classe
 *
 *  Atributos
 *  ----------------
 *  @attr nomeArquivo_ : o que é esse atributo?
 *  @attr registros_  : o que é esse atributo?
 * */
class CsvLivros {
public:

    CsvLivros(){};

    /**  TODO:<Breve descrição>
     *  @param registros <o que é esse parâmetro?>
     * */
    CsvLivros(Registro *registros);

    /**  TODO:<Breve descrição>
     *  @param nomeArquivo <o que é esse parâmetro?>
     *  @param numLinhas <o que é esse parâmetro?>
     *  @param aleatorio <o que é esse parâmetro?>
     *  @param seed <o que é esse parâmetro?>
     * */
    void lerCsv(const std::string &nomeArquivo, int numLinhas, bool aleatorio = false, int seed = -1);

private:
    std::string nomeArquivo_;
    Registro *registros_;

    /**  TODO:<Breve descrição>
     *  @param linha <o que é esse parâmetro?>
     *  @param numRegistro <o que é esse parâmetro?>
     * */
    void processarLinha(const std::string &linha, int numRegistro);
};


#endif //TRABALHO_ED2_CSV_H
