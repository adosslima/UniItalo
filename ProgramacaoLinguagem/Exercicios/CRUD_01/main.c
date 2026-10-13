#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char nome[40];
	int idade;
} Aluno;

void menu() {
	printf("========= Menu ==========\n");
	printf("1 - Cadastro\n");
	printf("2 - Listar\n");
	printf("3 - Buscar\n");
	printf("4 - Alterar\n");
	printf("5 - Excluir\n");
	printf("6 - Sair\n");
	printf("=========================\n");
	printf("");
}

void cadastrar(Aluno *ptr) {
	for (int i=0; i < 2; i++) {
		printf("Qual o nome do aluno: ");
		scanf(" %39[^\n]", (ptr + i)->nome);

		printf("Qual a idade do aluno: ");
		scanf(" %d", &((ptr + i)->idade));
	}
}

void listar(Aluno *ptr) {
	for (int i=0; i < 2; i++) {
		printf("Nome do aluno  [%d]: %s\n", i, (ptr + i)->nome);
		printf("Idade do aluno [%d]: %d\n", i, (ptr + i)->idade);
		printf(" ");
	}
}

void buscar(Aluno *ptr) {
	char nomeBusca[40];

	printf("Entre com o nome de busca: ");
	scanf(" %39[^\n]", nomeBusca);

	for (int i=0; i < 2; i++) {
		if (strcmp((ptr+1)->nome, nomeBusca) == 0) {
			printf("Nome atual: %s", (ptr+i)->nome);
			printf("Idade atual: %s", (ptr+i)->idade);
			printf("\n");
		} 
		else {
			printf("Registro não encontrado");
		}
	}
}

void alterar(Aluno *ptr) {
	char nomeBusca[40];

	printf("Entre com o nome de busca: ");
	scanf(" %39[^\n]", nomeBusca);

	for (int i=0; i < 2; i++) {

		if (strcmp((ptr+i)->nome, nomeBusca) == 0) {
			printf("Nome atual: %s", (ptr+i)->nome);
			printf("Idade atual: %d", (ptr+i)->idade);
			printf("\n");

			printf("Entre com os novos dados\n");

			printf("Qual o novo nome: \n");
			scanf(" %39[^\n]", (ptr+i)->nome);
			printf("Qual a nova idade:");
			scanf(" %d", &(ptr+i)->idade);

			printf("Dados alterados com sucesso...");
		} 
		else {
			printf("Registro não encontrado");
		}
	}
}

void excluir() {

}

void sair() {
	printf("Saindo do sistema...\n");
	exit(0);
}

int main() {
	int op = 0;

	Aluno alunos[2];
	Aluno *ptr;

	ptr = alunos;

	do {
		menu();
		printf("Entre com a opção de menu: ");
		scanf("%d", &op);

		switch (op) {
		case 1:
			cadastrar(ptr);
			break;
		case 2:
			listar(ptr);
			break;
		case 3:
			buscar(ptr);
			break;
		case 4:
			alterar(ptr);
			break;
		case 5:
			excluir();
			break;
		case 6:
			sair();
			break;
		}
	} while (op != 6);

	return 0;
}
