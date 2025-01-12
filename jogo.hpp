#ifndef JOGO_HPP
#define JOGO_HPP
#include <iostream>
#include <fstream>  // Para manipulação de arquivos
#include <string>   // Para trabalhar com strings
#include <cstdlib>  // Para rand() e srand()
#include <ctime>    // Para time()
#include <chrono>   // Para std::chrono
using namespace std;

// Estruturas
struct No {
    string palavra;
    No *eloA, *eloP;
    bool usada;
};

struct LDE {
    No *comeco;
    No *fim;
};

// Funções para manipular a lista encadeada
void inicializarLDE(LDE &lista);
bool inserirLDE(LDE &lista, string palavra);
void mostrarLDE(LDE lista, char ordem);
bool retirarLDE(LDE &lista, string valor);
int tamLista(LDE &lista);
int gerarNumeroAleatorio(int tam);
string definirPalavraJogo(LDE &lista); 

// Funções para carregar e salvar palavras em arquivo
void carregarPalavrasDoArquivo(LDE &lista, const string &nomeArquivo);
void salvarPalavrasNoArquivo(LDE &lista, const string &nomeArquivo);

// Funções do jogo
void verificarPalavra(string palavra, string chute);
void menu(LDE &lista);

#endif
