#include <iostream>
#include <fstream>
#include <random>
#include <cassert>
#include "../include/DataFrameLivros.hpp"
#include "../include/csvLivros.hpp"
#include "../include/secao_2/HashRegistro.hpp"
#include "../include/secao_2/Primo.hpp"
#include "../include/secao_3/AVP.hpp"

using namespace std;

unsigned gerarRandomSeed();

void secao1(const string &dataset);

void secao2(const string &dataset);

void secao3(const string &dataset);

void interfaceTerminal(const string &dataset);

int main(int argc, char **argv, char **argp) {
    string dataset;

    dataset = "../dataset/dataset_simp_sem_descricao.csv"; //caminho padrão dataset

    // se for passado o nome do dataset por parametro
    if (argc > 1)
        dataset = "../dataset/" + (string) argv[1];

    interfaceTerminal(dataset);

    return 0;
}

// ------------------------- Etapa 1 ------------------------- //

void secao1(const string &dataset) {
    int x;  // Número de iterações (n)
    int *n = nullptr;  // vetor para armazenar os valores de n (qt. de registros) lidos de "entrada.txt"
    unsigned seed;  // semente de randomização
    DataFrameLivros dfLivros;  //instancia de dfLivros

    const string PATH_SECAO = "../io/secao_1/";
    const string ARQ_ENTRADA = "entrada.txt";
    const string ARQ_SAIDA = "saida.txt";

    // obtendo os parâmetros de entrada
    txt::lerEntrada(&x, n, PATH_SECAO + ARQ_ENTRADA);
    assert(n != nullptr);
    //remove o arquivo de saida, se existir
    remove((PATH_SECAO + ARQ_SAIDA).c_str());
//
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < ITER; j++) {
            seed = gerarRandomSeed();

            // lê o csv e salva n[i] registros aleatórios
            dfLivros.lerCsv(dataset, n[i], true, seed, ED::VETOR);
            if (j == 0) cout << n[i] << " registros aleatorios carregados." << endl;
            // Faz as ordenações e imprime métricas

            //chama algoritmo de Ordenação Quicksort
            dfLivros.ordenar(AlgOrdenacao::QUICKSORT, PATH_SECAO + ARQ_SAIDA);

            //chama algoritmo de Ordenação HeapSort
            dfLivros.ordenar(AlgOrdenacao::HEAPSORT, PATH_SECAO + ARQ_SAIDA);

        }
    }

    cout << "As estatisticas foram salvas no arquivo de saida." << endl;

    //calculando métricas
    calcularMetricas(x, n, PATH_SECAO, ARQ_SAIDA);

    delete[] n;
}

// ------------------------- Etapa 2 ------------------------- //

void secao2(const string &dataset) {
    int N, M;
    DataFrameLivros dfLivros;  //instancia de dfLivros
    unsigned seed;  // semente de randomização
    const string PATH_SECAO = "../io/secao_2/";
    const string ARQ_SAIDA = "saida.txt";
    const int tamArqAutores = 243700;

    //remove o arquivo de saida, se existir
    remove((PATH_SECAO + ARQ_SAIDA).c_str());

    N = 10;
    M = 5;
//    cout << " Digite os valores de N e M: ";
//    cin >> N >> M;

    Primo::criarTabela(N);
    HashAutor auxAutores(tamArqAutores);

    seed = 3202200755;
//    seed = gerarRandomSeed();
    cout << "seed = " << seed << endl;

//    Registro *r;
//    r = new Registro[10];
//
//    HashRegistro h(10);
//    for (int i = 0; i < 10; i++) {
//        r[i].setId(12345678912 + i * i);
//        h.inserir(&r[i]);
//    }
//    cout << h.buscar(12345678913) << endl;


    // lê o csv e salva n[i] registros aleatórios e distintos
    dfLivros.lerCsv(dataset, N, true, seed, ED::HASH_TABLE);

//    auxAutores.inserir(new Autor("Nome Teste", 234));
//    cout << h.busca("Nome Teste");
}

// ------------------------- Etapa 3 ------------------------- //
void secao3(const string &dataset) {
    int x;  // Número de iterações (n)
    int *n = nullptr;  // vetor para armazenar os valores de n (qt. de registros) lidos de "entrada.txt"
    DataFrameLivros dfLivros;  //instancia de dfLivros
    unsigned seed;  // semente de randomização

    const string PATH_SECAO = "../io/secao_3/";
    const string ARQ_SAIDA_BUSCA = "saidaBusca.txt";
    const string ARQ_SAIDA_INSERCAO = "saidaInsercao.txt";
    const string ARQ_ENTRADA = "entrada.txt";

    //remove os arquivos de saida, se existirem
    remove((PATH_SECAO + ARQ_SAIDA_BUSCA).c_str());
    remove((PATH_SECAO + ARQ_SAIDA_INSERCAO).c_str());

    // obtendo os parâmetros de entrada
    txt::lerEntrada(&x, n, PATH_SECAO + ARQ_ENTRADA);

    seed = gerarRandomSeed();
//    dfLivros.lerCsv(dataset, n[0], true, seed, ED::ARVORE);

    for (int i = 0; i < x; i++) {
        for (int j = 0; j < ITER; j++) {
            seed = gerarRandomSeed();

            // lê o csv e salva n[i] registros aleatórios
            dfLivros.lerCsv(dataset, n[i], true, seed, ED::ARVORE);
            if (j == 0) cout << n[i] << " registros aleatorios carregados." << endl;

        }
    }

    //calculando métricas
//    calcularMetricas(x, n, PATH_SECAO, ARQ_SAIDA);

    delete[] n;
}


// ------------------- Funções auxiliares -------------------- //

unsigned gerarRandomSeed() {
    random_device myRandomDevice; //para gerar a semente de randomização
    return myRandomDevice(); //retorna um seed aleatorio
}

void interfaceTerminal(const string &dataset) {
    int opt;
    while (true) {
        cout << "Trabalho Estrutura De Dados II" << endl;
        cout << "Seção *1*: Ordenação dos registros" << endl;
        cout << "Seção *2*: Autores mais frequentes" << endl;
        cout << "Seção *3*: Estruturas balanceadas" << endl;
        cout << "---------------------------------" << endl;
        cout << "Digite o número referente a seção desejada [1-3] ou 0 para sair : ";
        cin >> opt;
        cout << string(100, '\n');
        if (opt == 1) {
            secao1(dataset);
        } else if (opt == 2) {
            secao2(dataset);
        } else if (opt == 3) {
            secao3(dataset);
        } else if (opt == 0) {
            break;
        } else {
            cerr << "\n** " << opt << " não é um número de seção válido** ";
        }
        cout << endl << "Pressione ENTER para voltar ao menu principal" << endl;
        cin.get();
        cin.get();
        cout << string(100, '\n');
    }

}
