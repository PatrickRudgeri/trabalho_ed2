#ifndef TRABALHO_ED2_TXT_H
#define TRABALHO_ED2_TXT_H

#include <iostream>

class Txt {
public:
    Txt();

    void lerEntrada(std::string nomeArquivo);

    int *getNargs() const;

    int getXarg() const;
private:
    int *nArgs;
    int xArg;
};


#endif //TRABALHO_ED2_TXT_H
