#ifndef TRABALHO_ED2_TXT_HPP
#define TRABALHO_ED2_TXT_HPP

#include <iostream>

class Txt {
public:
    Txt();

    virtual ~Txt();

    void lerEntrada(std::string nomeArquivo);

    int *getNargs() const;

    int getXarg() const;
private:
    int *nArgs;
    int xArg;
};


#endif //TRABALHO_ED2_TXT_HPP
