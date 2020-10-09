#include <iostream>

#ifndef TRABALHO_ED2_REGISTRO_H
#define TRABALHO_ED2_REGISTRO_H


class Registro {
public:
    Registro(){};

    void setAutores(std::string autoresStr);
    void setAutores(int *autores);

    void setTodosAtributosStr(std::string *stringArray);

    void setEdicao(std::string basicString);
    void setRankBestsellers(std::string rankBestsellersStr);

    void setCategorias(std::string categorias);
    void setCategorias(int *categorias);

    void setId(std::string idStr);
    void setId(long long id);

    void setIsbn10(std::string isbn10);

    void setIsbn13(std::string isbn13);

    void setAvaliacaoMedia(std::string avalMedia);

    void setQtAvaliacoes(std::string qtAvaliacoes);

    void setTitulo(std::string titulo);

private:
    int *autores_;
    std::string rankBestsellers_;
    int *categorias_;
    std::string edicao_;
    long long id_;
    std::string isbn10_;
    std::string isbn13_;
    std::string avaliacaoMedia_;
    std::string qtAvaliacoes_;
    std::string titulo_;
};


#endif //TRABALHO_ED2_REGISTRO_H
