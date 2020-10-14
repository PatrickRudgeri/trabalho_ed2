#ifndef TRABALHO_ED2_CSV_H
#define TRABALHO_ED2_CSV_H

#include <iostream>
#include "Registro.hpp"

class CsvLivros {
public:

    CsvLivros();

    CsvLivros(Registro *registros);

    void lerCsv(const std::string &nomeArquivo, int numLinhas, bool aleatorio = false, int seed = -1);

    std::string padronizarCsv(std::string nomeArquivoOriginal);


private:
    std::string nomeArquivo_;
    Registro *registros_{};

    static void processarLinha(const std::string &linha, Registro *registro);
};


#endif //TRABALHO_ED2_CSV_H
