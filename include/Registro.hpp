#include <iostream>

#ifndef TRABALHO_ED2_REGISTRO_H
#define TRABALHO_ED2_REGISTRO_H


class Registro {
public:
    Registro(){};
//    Registro(std::string *registro_array); //retirar?

    ~Registro(){};

//    float get();

    void setTodosAtributosStr(std::string *string_array);

    void setEdicao(std::string basicString);

    void setIsbn10(std::string isbn10);

    void setIsbn13(std::string isbn13);

    void setAvaliacaoMedia(std::string avalMedia);

    void setQtAvaliacoes(std::string qtAvaliacoes);

    void setTitulo(std::string titulo);

    void setAutores(std::string autoresStr);
    void setAutores(int *autores);

private:
    int *autores;
    int rankBestsellers;
    int *categorias;
    std::string edicao;
    int id;
    std::string isbn10;
    std::string isbn13;
    std::string avaliacaoMedia;
    std::string qtAvaliacoes;
    std::string titulo;


};


#endif //TRABALHO_ED2_REGISTRO_H
