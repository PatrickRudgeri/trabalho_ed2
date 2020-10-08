#include <iostream>

#ifndef TRABALHO_ED2_CSV_H
#define TRABALHO_ED2_CSV_H


class Csv {
public:
    explicit Csv();

    ~Csv();

    void lerCsv(std::string nome_arquivo, int num_linhas = -1, bool aleatorio = false);

    std::string padronizarCsv(std::string nomeArquivo);

private:
    std::string nome_arquivo;
};


#endif //TRABALHO_ED2_CSV_H
