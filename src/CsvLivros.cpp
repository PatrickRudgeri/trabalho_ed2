#include <fstream> //ifstream
#include <sstream> //stringstream
#include "../include/CsvLivros.hpp"

using namespace std;

template<class ClasseStream>
int tamanhoArquivo(ClasseStream &arq);

CsvLivros::CsvLivros(Registro *registros) {
    registros_ = registros;
}

//TODO: documentar os blocos funcionais e variáveis dentro do método
void CsvLivros::processarLinha(const std::string &linha, Registro *registro) {
    int index;
    std::stringstream ss(linha); // converte a string para o tipo std::stringstream e salva em ss
    std::string campo;
    std::string camposTemp[10];

    // 9 campos, 2 aspas em cada = 18 iterações
    for (int i = 0; i < 18; i++) {
        getline(ss, campo, '"');  // salva em str2 tudo até "
        if (i % 2 == 0) continue; // as colunas pares possuem virgulas que ficam entre as aspas de 2 campos
        index = i / 2;
        camposTemp[index] = campo;
    }

    //lendo ultimo campo (pode conter vírgulas e aspas internas)
    getline(ss, campo);

    camposTemp[9] = campo.substr(2, campo.length() - 4);//retira as aspas iniciais e finais do titulo_
    registro->setTodosAtributosStr(camposTemp);
}

//TODO: documentar os blocos funcionais e variáveis dentro do método
void CsvLivros::lerCsv(const string &nomeArquivo, int numLinhas, bool aleatorio, int seed) {
    std::string linha;
    int qtLinhas, tamArq, posRandom;

    srand(seed);
    qtLinhas = 0;
    std::ifstream arquivo(nomeArquivo);
    tamArq = tamanhoArquivo<ifstream>(arquivo);

    // TODO: refatorar para tratar excessões (try...catch)
    if (!arquivo.is_open()) {
        std::cerr << "ERRO=> CsvLivros::lerCsv\n";
        return;
    }

    while (true) {
        if (arquivo.eof() || (numLinhas != -1 && qtLinhas == numLinhas))
            break;
        //se aleatorio == true, seleciona uma posição aleatoria do arquivo, lê até o final da
        // linha e processa a próxima.
        if (aleatorio) {
            posRandom = rand() % (tamArq - 1);//
            arquivo.seekg(posRandom);
            getline(arquivo, linha); //lê até o final da linha para ignorá-la
        }
        getline(arquivo, linha); //lê a proxima linha

        if (linha.empty()) continue;

        cout << qtLinhas << " : ";  //fixme: retirar esse debug
        processarLinha(linha, &registros_[qtLinhas]);
        qtLinhas++;
    }
    arquivo.close();
}

//TODO: (implementando esse metodo)
string CsvLivros::padronizarCsv(string nomeArquivoOriginal) {

    string linha, linhaTemp;
    int qtLinhas, tamArq;

    qtLinhas = 0;
    ifstream arquivo(nomeArquivoOriginal);
    tamArq = tamanhoArquivo<ifstream>(arquivo);

    // TODO: refatorar para tratar excessões (try...catch)
    if (!arquivo.is_open()) {
        cerr << "ERRO=> CsvLivros::padronizarCsv\n";
        return "";
    }
    linhaTemp = "";
    linha = "";
    while (!arquivo.eof()) {
        getline(arquivo, linha); //lê a proxima linha

        if (linha.size() < 2) continue;

        linhaTemp += linha;
        cout << (linha.substr(linha.size() - 2, 1)) << " >> ";
        if (linha.substr(linha.size() - 2, 1) == "\"") {
            cout << qtLinhas << "\n";  //fixme: retirar esse debug
//            cout << "\t" << linhaTemp << endl;  //fixme: retirar esse debug

            linhaTemp = "";
            qtLinhas++;
        }
    }
    arquivo.close();
    return "teste_std_" + nomeArquivoOriginal;
}

//TODO: documentar os blocos funcionais e variáveis dentro da função
template<class ClasseStream>
int tamanhoArquivo(ClasseStream &arq) {
    arq.seekg(0, arq.end);
    int tam = arq.tellg();
    arq.seekg(0);
    return tam;
}



