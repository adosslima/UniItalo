#include <stdio.h>

int alterar(int numero) {
	numero = numero * numero;
	return numero;
}

int main()
{
	int valor = 10;
	valor = alterar(valor);
	printf("%d",valor);

	return 0;
}
