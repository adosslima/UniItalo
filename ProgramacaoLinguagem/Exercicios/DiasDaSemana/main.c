#include <stdio.h>

int main()
{
	int dia = 0;

	printf("Entre com o dia da semana: \"1\" e \"7\":\n");
	scanf("%d", &dia);

	if (dia < 1 || dia > 7)
	{
		printf("Você digitou um número inválido!");
	}
	else
	{
		printf("O dia da semana escolhido foi: %d-", dia);

		switch (dia) {
		case 1:
			printf("Domingo");
			break;
		case 2:
			printf("Segunda-feira");
			break;
		case 3:
			printf("Terça-feira");
			break;
		case 4:
			printf("Quarta-feira");
			break;
		case 5:
			printf("Quinta-feira");
			break;
		case 6:
			printf("Sexta-feira");
			break;
		default:
			printf("Sábado");
		}
	}

	return 0;
}
