#include <iostream>

#ifndef TRABALHO_ED2_CSV_H
#define TRABALHO_ED2_CSV_H


class Csv {
public:
    explicit Csv();

    ~Csv();

    void lerCsv(std::string nomeArquivo, int numLinhas = -1, bool aleatorio = false);

    std::string padronizarCsv(std::string nomeArquivo);

private:
    std::string nomeArquivo;
};


#endif //TRABALHO_ED2_CSV_H
