//
// Created by patrick on 03/10/2020.
//
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream> // std::stringstream
#include <vector>
#include <regex>
#include "Registro.hpp"

#ifndef TRABALHO_ED2_HELPERS_H
#define TRABALHO_ED2_HELPERS_H

//using namespace std; //fixme retirar daqui depois

void processarLinha(const std::string &linha, Registro *registro) {
    std::stringstream ss(linha); // converte a string para o tipo std::stringstream e salva em ss
    std::string *campos_temp = new std::string[10],
            campo;

    int index;

    for (int i = 0; i < 18; i++) {
        getline(ss, campo, '"');  // salva em str2 tudo até "
        if (i % 2 == 0) continue; // as colunas pares possuem virgulas que ficam entre as aspas
        index = i / 2;
        campos_temp[index] = campo;
    }

    //lendo ultimo campo (pode conter vírgulas e aspas internas)
    getline(ss, campo);

    //FIXME: linha 55408 e outras possuem erro (quebrou a linha dentro do titulo, ignorar?)

    //O csv original está com erro de quebra de linha ou vazia em algumas linhas, então, temporariamente
    // adicionei essa condicional para *não* cortar o lado direito (p/ tirar aspas) da std::string quando
    // a linha tiver esse erro


    if (campo.rfind('"') > 2) { // se posuir o fechamento das aspas (titulo completo)
        campo = campo.substr(2, campo.length() - 4);//retira as aspas iniciais e finais do titulo
    } else {
        campo = campo.substr(2, campo.length());
    }

    campos_temp[9] = campo;
    registro->setTodosAtributosStr(campos_temp);
}

//TODO: Utilizar essa função para "limpar" e corrigir erros do dataset, salvar em um tsv (tab)?
void read_csv(std::string filename, int n) {
    std::string linha;
    std::vector <Registro> registros;
    std::ifstream arquivo(filename);

    srand(time(0));

    // TODO: refatorar para tratar excessões
    if (!arquivo.is_open()) {
        std::cerr << "ERRO\n";
        return;
    }
    int linhas = 1;
    while (true) {
        getline(arquivo, linha);
        if (arquivo.eof()) break;
//        Registro registro;
        if (std::regex_match(linha, std::regex("\".+\"?[[:space:]]*"))) { //se a linha não estiver com erro

//            processarLinha(linha, &registro);
//            registros.push_back(registro);
        }
        linhas++;
    }


}
/*
void carregaArquivoPorBlocos(std::string name, int tamBloco) {
    char *dados = new char[tamBloco];
    std::ifstream arq(name);
    if (arq.is_open()) {

//        while (!arq.eof()) {
        arq.read(dados, tamBloco);
        cout << dados << endl;
        arq.read(dados, tamBloco);
        cout << dados << endl;
//        }
    }

    arq.close();
    delete[] dados;
}
*/
void splitString(std::string str, std::string *strArray){
    std::stringstream ss(str);
    std::string item;
    std::vector<std::string> itens;
    while(true){
        if (ss.eof()) break;
        getline(ss, item, ',');
        itens.push_back(item);
    }
    strArray = itens.data();
}

/*
std::chrono::high_resolution_clock::time_point inicio = std::chrono::high_resolution_clock::now();
//CODE HERE
std::chrono::high_resolution_clock::time_point fim = std::chrono::high_resolution_clock::now();
std::cout << chrono::duration_cast<chrono::duration<double>>(fim - inicio).count() << " segundos" << endl;
*/

#endif //TRABALHO_ED2_HELPERS_H
