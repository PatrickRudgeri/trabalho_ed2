[![Build Status](https://travis-ci.com/PatrickRudgeri/trabalho_ed2.svg?branch=master)](https://travis-ci.com/PatrickRudgeri/trabalho_ed2)

# Trabalho de Estrutura de Dados II - UFJF
## Parte 1 

## Instruções para executar o programa
1. Colocar o dataset no diretório dataset/ 
2. executar o comando: `cd bin && ./trabalho_ed2 [<nomeDataset>.csv]`. 

Obs: 
trocar `<nomeDataset>.csv` pelo nome do dataset. Se o nome do dataset possui espaços colocar entre aspas duplas.

## Métricas foram utilizadas:

- N° de comparações de chaves;
- N° de cópias de registros realizadas;
- Tempo total gasto (processamento);

## Estrutura do projeto:

<pre><span style="background-color:#00AA00"><font color="#0000AA">.</font></span>
├── <font color="#5555FF"><b>bin</b></font>
│   └── <font color="#55FF55"><b>trabalho_ed2</b></font>
├── <font color="#55FF55"><b>CMakeLists.txt</b></font>
├── <span style="background-color:#00AA00"><font color="#0000AA">dataset</font></span>
│   ├── <font color="#55FF55"><b>authors.csv</b></font>
│   └── <font color="#55FF55"><b>dataset_simp_sem_descricao.csv</b></font>
├── <span style="background-color:#00AA00"><font color="#0000AA">include</font></span>
│   ├── <font color="#55FF55"><b>csvLivros.hpp</b></font>
│   ├── <font color="#55FF55"><b>DataFrameLivros.hpp</b></font>
│   ├── metricas.hpp
│   ├── <font color="#55FF55"><b>Registro.hpp</b></font>
│   ├── <font color="#5555FF"><b>secao_2</b></font>
│   │   ├── Autor.hpp
│   │   ├── HashAutor.hpp
│   │   ├── HashRegistro.hpp
│   │   └── Primo.hpp
│   ├── <font color="#5555FF"><b>secao_3</b></font>
│   │   ├── ArvoreB.h
│   │   ├── AVP.hpp
│   │   ├── NoB.h
│   │   └── noVP.hpp
│   └── <font color="#55FF55"><b>txtLivros.hpp</b></font>
├── <span style="background-color:#00AA00"><font color="#0000AA">io</font></span>
│   ├── <font color="#5555FF"><b>secao_1</b></font>
│   │   ├── <font color="#55FF55"><b>entrada.txt</b></font>
│   │   ├── saida.txt
│   │   └── <font color="#5555FF"><b>stats</b></font>
│   │       ├── stats_comp.txt
│   │       ├── stats_tempo.txt
│   │       └── stats_trocas.txt
│   ├── <font color="#5555FF"><b>secao_2</b></font>
│   │   └── <font color="#5555FF"><b>stats</b></font>
│   │       └── freq_autores.txt
│   └── <font color="#5555FF"><b>secao_3</b></font>
│       ├── <font color="#55FF55"><b>entrada.txt</b></font>
│       ├── saidaBusca.txt
│       ├── saidaInsercao.txt
│       └── <font color="#5555FF"><b>stats</b></font>
│           ├── <font color="#5555FF"><b>busca</b></font>
│           │   ├── stats_comp.txt
│           │   ├── stats_tempo.txt
│           │   └── stats_trocas.txt
│           └── <font color="#5555FF"><b>insercao</b></font>
│               ├── stats_comp.txt
│               ├── stats_tempo.txt
│               └── stats_trocas.txt
├── <font color="#55FF55"><b>README.md</b></font>
└── <span style="background-color:#00AA00"><font color="#0000AA">src</font></span>
    ├── <font color="#55FF55"><b>csvLivros.cpp</b></font>
    ├── <font color="#55FF55"><b>DataFrameLivros.cpp</b></font>
    ├── <font color="#55FF55"><b>main.cpp</b></font>
    ├── metricas.cpp
    ├── <font color="#55FF55"><b>Registro.cpp</b></font>
    ├── <font color="#5555FF"><b>secao_2</b></font>
    │   ├── Autor.cpp
    │   ├── HashAutor.cpp
    │   ├── HashRegistro.cpp
    │   └── Primo.cpp
    ├── <font color="#5555FF"><b>secao_3</b></font>
    │   ├── ArvoreB.cpp
    │   ├── AVP.cpp
    │   ├── NoB.cpp
    │   └── noVP.cpp
    └── <font color="#55FF55"><b>txtLivros.cpp</b></font></pre>


## Entrega:

- **PARTE 1** (Seção 1): **23/10**
- **PARTE 2** (Seções 2 e 3): **25/11**

## Integrantes:

- Patrick Rudgéri Pilato Lemes
- Dauane Joice Nascimento de Almeida
- Larissa de Lima e Silva
- Luciana Paixão Motta