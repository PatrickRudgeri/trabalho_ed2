#ifndef TRABALHO_ED2_REGISTRO_H
#define TRABALHO_ED2_REGISTRO_H

#include <iostream>

/** Armazena um registro/livro do dataset e possui métodos para manipulação dos mesmos
 *
 *  Atributos
 *  ----------------
 *  @attr autores_ : armazena um vetor de identificadores de autores
 *  @attr rankBestsellers_ : o que é esse atributo?
 *  @attr categorias_ : armazena um vetor de identificadores de categorias
 *  @attr edicao_ : edição do livro
 *  @attr id_ : id do livro
 *  @attr isbn10_ : isbn10 atribuido ao registro
 *  @attr isbn13_ : isbn13 atribuido ao registro
 *  @attr avaliacaoMedia_ : avaliação média do livro
 *  @attr qtAvaliacoes_ : quantidae de avaliacoes
 *  @attr titulo_ : titulo do livro
 *  @attr regQtAutores_ : armazena a quantidade de autores do atual registro
 * */
class Registro {
public:
    //Construtor padrão
    Registro();

    virtual ~Registro();

    void setAutores(const std::string &autoresStr);

    void setAutores(const int *autores, int n);

    void setTodosAtributosStr(std::string *stringArray);

    void setEdicao(std::string edicao);

    void setRankBestsellers(std::string rankBestsellersStr);

    void setCategorias(const std::string &categorias);

    void setCategorias(const int *categorias, int n);

    void setId(const std::string &idStr);

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

    friend std::ostream &operator<<(std::ostream &os, const Registro &reg);

    int getQtAutores() const;

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
    int regQtAutores_;
    int regQtCategorias_;
    /**
     *  Faz a tokenização de uma string que contem IDs de autores ou categorias separados por `delim` e converte para um
     *      vetor de inteiros
     * @param str : string de autores ou categorias
     * @param n : tamanho do vetor de autores ou categorias, inicialmente definida como -1
     * @param delim : delimitador
     */
    void splitString(const std::string &str, int *&array, int *n, char delim = ',');
};


#endif //TRABALHO_ED2_REGISTRO_H
