#include <fstream> //ifstream
#include <sstream> //stringstream
#include <algorithm> //replace
#include <random>
#include "../include/csvLivros.hpp"

using namespace std;

//TODO: documentar os blocos funcionais e variáveis dentro da função
template<class ClasseStream>
int tamanhoArquivo(ClasseStream &arq) {
    arq.seekg(0, arq.end);
    int tam = arq.tellg();
    arq.seekg(0);
    return tam;
}

//TODO: documentar definição da função
void processarLinhaRegistro(Registro *registros, const string &linha, int numRegistro) {
    int index;
    stringstream ss(linha); // converte a string para o tipo stringstream e salva em ss
    string campo;
    string camposTemp[10];

    // 9 campos iniciais, 2 aspas em cada = 18 iterações
    for (int i = 0; i < 18; i++) {
        // salva em str2 tudo até "
        getline(ss, campo, '"');

        // as colunas pares possuem virgulas que ficam entre as aspas de 2 campos
        if (i % 2 == 0) continue;
        index = i / 2;
        camposTemp[index] = campo;
    }

    //lendo ultimo campo (pode conter vírgulas e aspas internas)
    getline(ss, campo);
    //retira as aspas iniciais e finais do titulo
    camposTemp[9] = campo.substr(2, campo.length() - 4);
    //set todos os atributos do Registro da posição numRegistro
    registros[numRegistro].setTodosAtributosStr(camposTemp);
}

//TODO: documentar definição da função
//TODO: documentar os blocos funcionais e variáveis dentro da função
void processarLinhaAutores(const string &linha) {
    string id, autor;
    stringstream linhaStream(linha);
    getline(linhaStream, id, ',');
    getline(linhaStream, autor);
    id = id.substr(1, id.length() - 2);
    autor = autor.substr(1, autor.length() - 3); // autor.length() - 3, pois tbm retira a quebra de linha

    cout << stoi(id) << " <-> " << autor << endl;
}

int gerarRandomNum(unsigned int seed, int rangeMin, int rangeMax) {
    // inicializando a engine de randomização com o seed
    default_random_engine myRandomEngine(seed);

    // utilizando uma distribuição uniforme para gerar valores entre 0 e tamArq-1
    uniform_int_distribution<int> myUnifIntDist(rangeMin, rangeMax);
    return myUnifIntDist(myRandomEngine);
}

namespace csv {
    void lerRegistros(Registro *registros, const string &nomeArquivo, int numLinhas, bool aleatorio,
                      unsigned int seed) {
        string linha;  // armazenará a linha atual
        string linhaTemp;  // utilizado como auxiliar para tratar as quebras de linha do CSV
        int numRegistro;  // contador de registros/linhas
        int posRandom;  // armazenará uma posição randômica contida no arquivo
        int tamArq;  // tamanho do arquivo

        ifstream arquivo(nomeArquivo);

        tamArq = tamanhoArquivo<ifstream>(arquivo);
        numRegistro = 0;

        if (!arquivo.is_open()) {
            cerr << "ERRO=> CsvLivros::lerRegistros\n";
            exit(0);
        }
        while (true) {
            /**
             *  se aleatorio == true, seleciona uma posição aleatoria do arquivo, lê até o final da
             *   linha e processa a próxima.
            */
            if (aleatorio) {
                //se já obteve a quantidade de linhas suficiente
                if (numRegistro == numLinhas) {
                    break;
                }
                posRandom = gerarRandomNum(seed, 0, tamArq - 1);

                // acessa a posição, definida por `posRandom`, do arquivo
                arquivo.seekg(posRandom);
                //lê até o final da linha
                getline(arquivo, linha);
                /**
                 * se contem apenas um char ou não terminar com " então inicia o loop novamente e escolhe outra posição
                 * aleatória.
                 *se o if for falso a linha atual será ignorada
                */
                if (linha.length() < 2 || linha[linha.length() - 2] != '"') {
                    continue;
                }
            } else {
                /*
                 * quando aleatorio é falso o término do loop será quando chegar ao final do arquivo ou
                 *  se numLinhas foi definido e numRegistro já alcançou essa quantidade
                */
                if (arquivo.eof() || (numLinhas != -1 && numRegistro == numLinhas)) {
                    break;
                }
            }
            // se a linha anterior foi a ultima do arquivo, então volta o arquivo pra pos 0
            if (arquivo.tellg() == tamArq) {
                arquivo.seekg(0);
            }
            linhaTemp = "";
            while (true) {
                //lê a proxima linha
                getline(arquivo, linha);
                linhaTemp += linha;
                if (linha[linha.length() - 2] == '"') {
                    break;
                }
            }
            //substitui todas as quebras de linha da string
            replace(linhaTemp.begin(), linhaTemp.end(), (char) 13, ' ');

            //processa a linha atual e salva na posição `numRegistro` do vetor de Registros
            processarLinhaRegistro(registros, linhaTemp, numRegistro);

            numRegistro++;
        }
        //fechando o arquivo
        arquivo.close();
    }

    //TODO question: processar authors.csv
    void lerAutores(const string &nomeArquivo) {
        string linha;  // armazenará a linha atual
//        string linhaTemp;  // utilizado como auxiliar para tratar as quebras de linha do CSV
        int numLinhas;  // contador de linhas
//        int tamArq;  // tamanho do arquivo

        ifstream arquivo(nomeArquivo);

//        tamArq = tamanhoArquivo<ifstream>(arquivo);
        numLinhas = 0;

        if (!arquivo.is_open()) {
            cerr << "ERRO=> CsvLivros::lerAutores\n";
            exit(0);
        }
        //ignorando a primeira linha (header)
        getline(arquivo, linha);
        //lê a proxima linha
        while (getline(arquivo, linha)) {
            //processa a linha atual e salva na posição `numRegistro` do vetor de Registros
            processarLinhaAutores(linha);
        }
        numLinhas++;

        //fechando o arquivo
        arquivo.close();
    }

}