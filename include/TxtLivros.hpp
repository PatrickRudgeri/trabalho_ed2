#ifndef TRABALHO_ED2_TXTLIVROS_HPP
#define TRABALHO_ED2_TXTLIVROS_HPP

#include <iostream>

class TxtLivros {
public:
    TxtLivros();

    virtual ~TxtLivros();

    void lerEntrada(std::string nomeArquivo);

    int *getNargs() const;

    int getXarg() const;
private:
    int *nArgs;
    int xArg;
};


#endif //TRABALHO_ED2_TXTLIVROS_HPP
