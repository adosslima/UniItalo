#include <stdio.h>

void alterar(int *numero) {
	*numero = 50;
}

int main()
{
	int valor = 10;
	alterar(&valor);
	printf("%d",valor);

	return 0;
}
