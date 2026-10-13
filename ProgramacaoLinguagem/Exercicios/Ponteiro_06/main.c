#include <stdio.h>
#include <string.h>


struct Aluno {
	char nome[30];
	int idade;
};

int main() {
	struct Aluno aluno;
	struct Aluno *ptr;
	
	ptr = &aluno;

	strcpy(ptr->nome, "Italo Brasileiro");
	ptr->idade = 40;


	printf("Nome: %s \n", ptr->nome);
	printf("Idade: %d \n", ptr->idade);

	return 0;
}
