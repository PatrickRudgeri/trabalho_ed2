#ifndef TRABALHO_ED2_REGISTRO_H
#define TRABALHO_ED2_REGISTRO_H

#include <iostream>

/** @brief Documentação de teste da classe Registro
 *
 * Uma descrição detalhada da classe ficará aqui
 * */
class Registro {
public:
    /** Construtor padrão
     * */
    Registro() {};

    /** Converte uma string contendo autores em um vetor de int
     *  testando latex: \f$\sum_{i=0}^{X}{i^2+i}$\f
     * @param autoresStr é uma string contento, entre "[]" identificadores de autores separados por vírgula.
     * */
    void setAutores(std::string autoresStr);

    void setAutores(int *autores);

    void setTodosAtributosStr(std::string *stringArray);

    void setEdicao(std::string edicao);

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

private:
    int *autores_; /** armazena um vetor de identificadores de autores*/
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
