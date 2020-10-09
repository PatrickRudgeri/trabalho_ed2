#include <fstream> //ifstream
#include <sstream> //stringstream
#include "../include/Csv.hpp"

using namespace std;

template<class ClasseStream>
int tamanhoArquivo(ClasseStream &arq);

Csv::Csv() {}

Csv::Csv(Registro *registros) {
    registros_ = registros;
}

void Csv::processarLinha(const std::string &linha, Registro *registro) {
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

void Csv::lerCsv(const string &nomeArquivo, int numLinhas, bool aleatorio, int seed) {
    std::string linha;
    int qtLinhas, tamArq, posRandom;

    srand(seed);
    qtLinhas = 0;
    std::ifstream arquivo(nomeArquivo);
    tamArq = tamanhoArquivo<ifstream>(arquivo);

    // TODO: refatorar para tratar excessões (try...catch)
    if (!arquivo.is_open()) {
        std::cerr << "ERRO=> Csv::lerCsv\n";
        return;
    }

    while (true) {
        if (arquivo.eof() || (numLinhas != -1 && qtLinhas == numLinhas))
            break;
        //se aleatorio == true, seleciona uma posição aleatoria do arquivo, lê até o final da
        // linha e processa a próxima.
        //fixme: do jeito que está implementado, a ultima e a primeira linha nunca serão lidas
        if (aleatorio) {
            posRandom = rand() % (tamArq - 1);//
            arquivo.seekg(posRandom);
            getline(arquivo, linha); //lê até o final da linha para ignorá-la
        }
        getline(arquivo, linha); //lê a proxima linha

        if (linha.empty()) continue;

        cout << qtLinhas << ", posRand=" << posRandom << ": ";  //fixme: retirar esse debug
        processarLinha(linha, &registros_[qtLinhas]);
        qtLinhas++;
    }
    arquivo.close();
}

//TODO, implementar essa função para "padronizar" o DF
string Csv::padronizarCsv(string nomeArquivoOriginal) {

    // processar o arquivo inteiro e salvar em outro csv

    // Para continuar o desenvolvimento, criei um dataset manualmente padronizado.
    // Assim que tudo estiver funcionando implementarei essa função
    return "std_" + nomeArquivoOriginal;
}

template<class ClasseStream>
int tamanhoArquivo(ClasseStream &arq) {
    arq.seekg(0, arq.end);
    int tam = arq.tellg();
    arq.seekg(0);
    return tam;
}



