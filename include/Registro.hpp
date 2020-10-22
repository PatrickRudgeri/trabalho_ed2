#ifndef TRABALHO_ED2_REGISTRO_H
#define TRABALHO_ED2_REGISTRO_H

#include <iostream>

/** TODO: Breve descrição da classe
 *
 *  Descrição detalhada da classe
 *
 *  Atributos
 *  ----------------
 *  @attr autores_ armazena um vetor de identificadores de autores
 *  @attr rankBestsellers_ : o que é esse atributo?
 *  @attr categorias_ : o que é esse atributo?
 *  @attr edicao_ : o que é esse atributo?
 *  @attr id_ : o que é esse atributo?
 *  @attr isbn10_ : o que é esse atributo?
 *  @attr isbn13_ : o que é esse atributo?
 *  @attr avaliacaoMedia_ : o que é esse atributo?
 *  @attr qtAvaliacoes_ : o que é esse atributo?
 *  @attr titulo_ : o que é esse atributo?
 * */
class Registro {
public:
    /** Construtor padrão
     * */
    Registro();

    virtual ~Registro();

    void setAutores(const std::string& autoresStr);

    void setAutores(const int *autores, int n);

    void setTodosAtributosStr(std::string *stringArray);

    void setEdicao(std::string edicao);

    void setRankBestsellers(std::string rankBestsellersStr);

    void setCategorias(const std::string& categorias);

    void setCategorias(int *categorias);

    void setId(const std::string& idStr);

    void setId(long long id);

    void setIsbn10(std::string isbn10);

    void setIsbn13(std::string isbn13);

    void setAvaliacaoMedia(std::string avalMedia);

    void setQtAvaliacoes(std::string qtAvaliacoes);

    void setTitulo(std::string titulo);

    int *getAutores() const;

    const std::string &getRankBestsellers() const;

    int *getCategorias() const;

    const std::string &getEdicao() const;

    long long int getId() const;

    const std::string &getIsbn10() const;

    const std::string &getIsbn13() const;

    const std::string &getAvaliacaoMedia() const;

    const std::string &getQtAvaliacoes() const;

    const std::string &getTitulo() const;

    // O método abaixo será utizado para comparar dois Registros, eles serão iguais se todos os campos forem iguais
    // (poderá ser utilizada na parte 2 do trabalho para obter apenas registros diferentes)
    bool operator==(const Registro &rhs) const;

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
