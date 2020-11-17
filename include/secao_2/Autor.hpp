#ifndef AUTOR_H
#define AUTOR_H

#include <iostream>

/** Breve descrição da classe
 *
 *  Descrição detalhada da classe
 *
 *  Atributos
 *  ----------------
 *  @attr nomeAutor_ <o que é esse atributo?>
 *  @attr frequencia_ <o que é esse atributo?>
 * 
 * */

class Autor {
private:
    std::string nomeAutor_;
    int id_;
    int frequencia_;

public:
    //Construtor da classe
    Autor();

    //construtor com parâmetros
    Autor(std::string nomeAutor, int id);

    //Destrutor da classe
    ~Autor();

    void setNome(std::string nome);

    void setfrequencia(int freq);

    void setId(int id);

    std::string getNome();

    int getFrequencia();

    int getId();
};

#endif // AUTOR_H