#ifndef TRABALHO_ED2_CSV_H
#define TRABALHO_ED2_CSV_H

#include <iostream>
#include "Registro.hpp"
#include "DataFrameLivros.hpp"

namespace csv {
//TODO: documentar definição da função

    void lerRegistros(DataFrameLivros *df, const std::string &nomeArquivo, int numLinhas, bool aleatorio = false,
                      unsigned int seed = 42);

    void lerAutores(const std::string &nomeArquivo, HashAutor *hashAutor);
}

#endif //TRABALHO_ED2_CSV_H
