#include <iostream>
#include "jogo.hpp"
using namespace std;
#include <cstdlib>  // Para rand() e srand()

void inicializarLDE(LDE &lista) {
	lista.comeco = nullptr;
	lista.fim = nullptr;
}
bool inserirLDE(LDE &lista, string palavra) {
    No *novo = new No;

    if (novo == nullptr) return false;  // Verifica se a alocação falhou
    novo->palavra = palavra;
    novo->eloA = nullptr;
    novo->eloP = nullptr;
    novo->usada = false;  // Atribuí o valor inicial para o campo 'usada'

    // Caso a lista esteja vazia, o novo nó será o primeiro (início e fim)
    if (lista.comeco == nullptr) {
        lista.comeco = novo;
        lista.fim = novo;
    }
    else {
        // Inserir no final: ajustar os ponteiros da lista
        lista.fim->eloP = novo;  // O próximo do atual fim aponta para o novo nó
        novo->eloA = lista.fim;  // O anterior do novo nó aponta para o antigo fim
        lista.fim = novo;        // Atualiza o fim da lista para o novo nó
    }

    return true;
}
void mostrarLDE(LDE lista, char ordem) {
	No *atual = lista.comeco;
	while (atual != nullptr) {
		cout << atual->palavra << endl;
		atual = atual->eloP;
	}
}
bool retirarLDE(LDE &lista, string valor) {
	No *atual = lista.comeco;
	while (atual != nullptr) {
		if (atual->palavra == valor) {
			if (atual->eloA != nullptr) {
				atual->eloA->eloP = atual->eloP;
			} else {
				lista.comeco = atual->eloP;
			}
			if (atual->eloP != nullptr) {
				atual->eloP->eloA = atual->eloA;
			} else {
				lista.fim = atual->eloA;
			}
			delete atual;
			return true;
		}
		atual = atual->eloP;
	}
	return false;
}
string definirPalavraJogo(LDE &lista) {
    No *atual = lista.comeco;
    int tam = tamLista(lista);
    string palavraSelecionada;

    bool palavraJaUsada = true;
    int pos;

    // Loop para garantir que uma palavra não usada seja escolhida
    while (palavraJaUsada) {
        pos = gerarNumeroAleatorio(tam);
        atual = lista.comeco;

        // Percorre até a posição aleatória gerada
        for (int j = 0; j < pos; ++j) {
            atual = atual->eloP;
        }

        // Verifica se a palavra já foi usada
        if (!atual->usada) {
            palavraJaUsada = false; // Palavra não foi usada, pode sair do loop
        }
    }

    // Marca a palavra como usada
    atual->usada = true;

    // Retorna a palavra selecionada
    palavraSelecionada = atual->palavra;

    return palavraSelecionada;
}
int tamLista(LDE &lista) {
	int contador = 0;
	No *atual = lista.comeco;
	while (atual != nullptr) {
		contador++;
		atual = atual->eloP;
	}
	return contador;
}
int gerarNumeroAleatorio(int tam) {
	unsigned int seed = std::chrono::steady_clock::now().time_since_epoch().count();
	srand(seed);
	return rand() % tam;
}
void carregarPalavrasDoArquivo(LDE &lista, const string &nomeArquivo) {
	ifstream arquivo(nomeArquivo);
	string palavra;
	if (arquivo.is_open()) {
		while (getline(arquivo, palavra)) {
			inserirLDE(lista, palavra);
		}
		arquivo.close();
	} /*else {
        cout << "Erro ao abrir o arquivo. carregar" << endl;
    } */
}
void salvarPalavrasNoArquivo(LDE &lista, const string &nomeArquivo) {
	ofstream arquivo(nomeArquivo);
	No *aux = lista.comeco;
	if (arquivo.is_open()) {
		while (aux != NULL) {
			arquivo << aux->palavra << endl;
			aux = aux->eloP;
		}
		arquivo.close();
	} else {
		cout << "Erro ao salvar no arquivo.salvar" << endl;
	}
}
void ganhou(){
    cout<<"\n\n________________VOCÊ GANHOU O JOGO!________________"<<endl;
    exit(0);
}
void perdeu(){
    cout<<"\n\n________________VOCÊ PERDEU O JOGO!________________"<<endl;
    exit(0);
}
void apresentaTentativa(string gabarito){
    for (int i=0; i<=4; i++){
        cout<<"["<<gabarito[i]<<"] ";
    }
    cout<<"  ";
}
string verificaTentativa(string palavra, string palavraCerta){
    string gabarito = palavra;
    if(palavra == palavraCerta){
        return gabarito;
    }
    
    for (int i=0; i<=4; i++){
        for (int j=0; j<=4; j++){
            if (palavra[i] == palavraCerta[j]){
                gabarito[i]='#';
            }
        }
    }
    
    for (int i=0; i<=4; i++){
        if (palavra[i] == palavraCerta[i]){
            gabarito[i]=palavraCerta[i];
        } else if(gabarito[i] != '#' && gabarito[i] != palavraCerta[i]){
            gabarito[i]='*';
        }
    }
    
    return gabarito;
}
LDE novaTentativa(LDE tentativasUsuario){
    string pTentativa;
    bool pValida=false;
    while (!pValida){
        cout<<"Digite uma palavra: ";
        cin>>pTentativa;
        if(pTentativa.length() == 5) pValida=true;
    }
    
    inserirLDE(tentativasUsuario, pTentativa);
    return tentativasUsuario;
}
void percorrerTentativas(LDE tentativasUsuario, int quantPalavras, string palavraCerta1, string palavraCerta2 = "", string palavraCerta3 = "", string palavraCerta4 = "") {
    No *atual = tentativasUsuario.comeco;
    string palavra, tentativa;
    bool acertou1 = false, acertou2 = false, acertou3 = false, acertou4 = false;

    // Percorre a lista de tentativas do usuário
    while (atual != nullptr) {
        palavra = atual->palavra;

        // Verifica cada palavra dependendo da quantidade de palavras
        if (quantPalavras >= 1) {
            tentativa = verificaTentativa(palavra, palavraCerta1);
            cout << "\n01: ";
            apresentaTentativa(tentativa);
            if (tentativa == palavraCerta1) {
                acertou1 = true; // Jogador acertou a primeira palavra
            }
        }

        if (quantPalavras >= 2) {
            tentativa = verificaTentativa(palavra, palavraCerta2);
            cout << "02: ";
            apresentaTentativa(tentativa);
            if (tentativa == palavraCerta2) {
                acertou2 = true; // Jogador acertou a segunda palavra
            }
        }

        if (quantPalavras >= 3) {
            tentativa = verificaTentativa(palavra, palavraCerta3);
            cout << "03: ";
            apresentaTentativa(tentativa);
            if (tentativa == palavraCerta3) {
                acertou3 = true; // Jogador acertou a terceira palavra
            }
        }

        if (quantPalavras == 4) {
            tentativa = verificaTentativa(palavra, palavraCerta4);
            cout << "04: ";
            apresentaTentativa(tentativa);
            if (tentativa == palavraCerta4) {
                acertou4 = true; // Jogador acertou a quarta palavra
            }
        }

        atual = atual->eloP; // Move para a próxima tentativa
    }

    // Valida se o jogador acertou todas as palavras
    if (quantPalavras == 1 && acertou1) {
        ganhou();
    } else if (quantPalavras == 2 && acertou1 && acertou2) {
        ganhou();
    } else if (quantPalavras == 3 && acertou1 && acertou2 && acertou3) {
        ganhou();
    } else if (quantPalavras == 4 && acertou1 && acertou2 && acertou3 && acertou4) {
        ganhou();
    }
}

void jogo(LDE &lista) {
    int qPalavras, qTentativas = 1;

    LDE tentativasUsuario;
    inicializarLDE(tentativasUsuario);

    cout << "Quantidade palavras\n[1]  [2]  [3]  [4]\n";
    cin >> qPalavras;
    system("clear");

    if (qPalavras == 1) {
        string palavraCerta1 = definirPalavraJogo(lista);
        cout << "Palavra escolhida: " << palavraCerta1 << endl;

        while (qTentativas < 7) {
            tentativasUsuario = novaTentativa(tentativasUsuario);
            system("clear");
            percorrerTentativas(tentativasUsuario, qPalavras, palavraCerta1);
            cout << "\n";
            qTentativas++;
        }
        perdeu(); // Se chegar aqui, o jogador não acertou todas as palavras
    }

    if (qPalavras == 2) {
        string palavraCerta1 = definirPalavraJogo(lista);
        string palavraCerta2 = definirPalavraJogo(lista);
        cout << "Palavras escolhidas: " << palavraCerta1 << " e " << palavraCerta2 << endl;

        while (qTentativas < 9) {
            tentativasUsuario = novaTentativa(tentativasUsuario);
            system("clear");
            percorrerTentativas(tentativasUsuario, qPalavras, palavraCerta1, palavraCerta2);
            cout << "\n";
            qTentativas++;
        }
        perdeu(); // Se chegar aqui, o jogador não acertou todas as palavras
    }

    if (qPalavras == 3) {
        string palavraCerta1 = definirPalavraJogo(lista);
        string palavraCerta2 = definirPalavraJogo(lista);
        string palavraCerta3 = definirPalavraJogo(lista);
        cout << "Palavras escolhidas: " << palavraCerta1 << ", " << palavraCerta2 << " e " << palavraCerta3 << endl;

        while (qTentativas < 11) {
            tentativasUsuario = novaTentativa(tentativasUsuario);
            system("clear");
            percorrerTentativas(tentativasUsuario, qPalavras, palavraCerta1, palavraCerta2, palavraCerta3);
            cout << "\n";
            qTentativas++;
        }
        perdeu(); // Se chegar aqui, o jogador não acertou todas as palavras
    }

    if (qPalavras == 4) {
        string palavraCerta1 = definirPalavraJogo(lista);
        string palavraCerta2 = definirPalavraJogo(lista);
        string palavraCerta3 = definirPalavraJogo(lista);
        string palavraCerta4 = definirPalavraJogo(lista);
        cout << "Palavras escolhidas: " << palavraCerta1 << ", " << palavraCerta2 << ", " << palavraCerta3 << " e " << palavraCerta4 << endl;

        while (qTentativas < 13) {
            tentativasUsuario = novaTentativa(tentativasUsuario);
            system("clear");
            percorrerTentativas(tentativasUsuario, qPalavras, palavraCerta1, palavraCerta2, palavraCerta3, palavraCerta4);
            cout << "\n";
            qTentativas++;
        }
        perdeu(); // Se chegar aqui, o jogador não acertou todas as palavras
    }
}

void menu(LDE &lista) {
	int opcao;
	do {
		cout << "\n ***** Menu *****\n";
		cout << "1. Adicionar palavra\n";
		cout << "2. Remover palavra\n";
		cout << "3. Mostrar lista de palavras\n";
		cout << "4. Jogar\n";
		cout << "5. Sair\n";
		cout << "Escolha uma opção: ";
		cin >> opcao;

		// Verifica se a entrada foi invaliida
		if (!cin) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Opção inválida. Tente novamente.\n";
			continue;
		}
        
        system("clear");

		switch(opcao) {
		case 1: {
			string novaPalavra;
			cout << "Digite a palavra para adicionar: ";
			cin >> novaPalavra;
			inserirLDE(lista, novaPalavra);
			break;
		}
		case 2: {
			string palavraRemover;
			cout << "Digite a palavra para remover: ";
			cin >> palavraRemover;
			retirarLDE(lista, palavraRemover);
			break;
		}
		case 3: {
			mostrarLDE(lista, 'C');
			break;
		}
		case 4: {
			jogo(lista);
			break;
		}
		case 5: {
			cout << "Saindo...\n";
			break;
		}
		default: {
			menu(lista);
			break;
		}
		}
	} while (opcao != 5);
}
int main() {
	LDE lista1;

	// Inicializar a lista
	inicializarLDE(lista1);

	// Carregar palavras de um arquivo
	carregarPalavrasDoArquivo(lista1, "palavras.txt");

	// Exibir o menu para o usuC!rio
	menu(lista1);

	// Salvar palavras no arquivo ao finalizar
	salvarPalavrasNoArquivo(lista1, "palavras.txt");

	return 0;
}

 