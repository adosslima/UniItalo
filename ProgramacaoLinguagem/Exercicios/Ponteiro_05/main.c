#include <stdio.h>
#include <string.h>


struct Aluno {
	char nome[30];
	int idade;
};

int main() {
	int index = 3;
	struct Aluno aluno[index];

	strcpy(aluno[0].nome, "Italo Brasileiro");
	aluno[0].idade = 50;

	strcpy(aluno[1].nome, "ADS - Noturno");
	aluno[1].idade = 30;

	strcpy(aluno[2].nome, "123456789012345678901234567890");
	aluno[2].idade = 30;

	printf("Nome: %s \n", aluno[0].nome);
	printf("Idade: %d \n", aluno[0].idade);

	printf("Nome: %s \n", aluno[1].nome);
	printf("Idade: %d \n", aluno[1].idade);

	printf("Nome: %s \n", aluno[2].nome);
	printf("Idade: %d \n", aluno[2].idade);

	return 0;
}
