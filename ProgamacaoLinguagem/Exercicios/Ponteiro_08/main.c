#include <stdio.h>
#include <string.h>


struct Aluno {
	char nome[30];
	int idade;
};

int main() {
	struct Aluno aluno[2];
	struct Aluno *ptr;
	
	ptr = aluno;

	strcpy(ptr->nome, "Italo Brasileiro");
	ptr->idade = 50;

	strcpy((ptr+1)->nome, "ADS - Noturno");
	(ptr+1)->idade = 30;


	printf("Nome: %s \n", ptr->nome);
	printf("Idade: %d \n", ptr->idade);

	printf("Nome: %s \n", (ptr+1)->nome);
	printf("Idade: %d \n", (ptr+1)->idade);

	return 0;
}
