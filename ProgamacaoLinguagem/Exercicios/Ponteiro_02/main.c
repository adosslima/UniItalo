#include <stdio.h>

int main()
{
	int idade = 25;
	int *p;

	p = &idade;

	printf("Valor da idade:%d\n", idade);
	printf("Endereço da idade:%p\n", &idade);
	printf("Endereço armazenamento em p:%p\n", p);

	printf("Valor acessado pelo ponteiro: %d\n", *p);

	return 0;
}
