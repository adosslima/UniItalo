#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10

// Estrutura do item que armazena os dados
struct Livro {
	char nome[50];
	int emprestado; // 0-Emprestado, 1-Disponível
	int codigo;
 };

void cadastrarLivro(struct Livro livro[], int *quantidade) {

    if (*quantidade >= MAX) {
        printf("Estoque cheio");
        return;
    }

    char nome[50];

	printf("\n *** Cadastro do Livro ***");
	printf("\nEntre com o código do livro:");
	scanf("%d", livro[*quantidade].codigo);

	printf("\nEntre com o nome do livro:");
	scanf("%s",nome);

	strcpy(livro[*quantidade].nome, nome);
	
	livro[*quantidade].emprestado = 0;
	
	(*quantidade)++;
}

void listarLivro() {
}

void emprestarLivro() {
}

void devolverLivro() {
}

int main()
{
	struct Livro livro[MAX];
	int opcao = 0;
	int quantidade = 0;

	do {
		printf("\n************************");
		printf("\n** Sistema Biblioteca **");
		printf("\n************************");
		printf("\n1-Cadastrar Livro       ");
		printf("\n2-Listar Livros         ");
		printf("\n3-Emprestar Livro       ");
		printf("\n4-Devolver Livro        ");
		printf("\n5-Sair                  ");
		printf("\n************************");

		printf("\n\nEscolha a opção do Menu: ");
		scanf("%d", &opcao);

		switch (opcao) {
		case 1:
			cadastrarLivro(livro, &quantidade);
			break;
		case 2:
			listarLivro();
			break;
		case 3:
			emprestarLivro();
			break;
		case 4:
			devolverLivro();
			break;
		default:
			printf("\nSaindo...");
			exit(0);
		}

	} while (opcao != 5);

	return 0;
}

