#ifndef AUTOR_H
#define AUTOR_H

#include <iostream>

/** Classe que armazena as informações de um autor e sua frequencia na tabela hash de registros únicos
 *  Atributos
 *  ----------------
 *  @attr nomeAutor_ : nome do autor
 *  @attr id_ : numero de identificação do autor, presente no registro do livro
 *  @attr frequencia_ : frequencia do autor na tabela hash de registros únicos
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

    // ---------------------- Sets e Gets -------------------- //
    void setNome(std::string nome);

    void setfrequencia(int freq);

    void setId(int id);

    std::string getNome();

    int getFrequencia();

    int getId();
};

#endif // AUTOR_H