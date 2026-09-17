#include <stdio.h>

int main()
{
	int idProduto[5] = {1001,1002,1003,1004,1005};
	char texto[5][20] = {"Fone de Ouvido", "Teclado Mecânico", "Mouse sem fio", "Monitor 24", "Cadeira Escritório"};
	int quantidade[5] = {1,1,2,1,1};
	float valorUnitario[5] = {150,250,60,600,300};
	float valorTotal[5] = {1500,250,120,600,300};
	
	int tamanho = sizeof(idProduto) / sizeof(idProduto[0]);
	
	printf("Tamanho do Array: %d\n", tamanho);

	for (int i = 0; i < tamanho; i++) {
		//printf("%d\n", idProduto[i]);
		//printf("%s\n", texto[i]);
		//printf("%d\n", quantidade[i]);
		//printf("%.2f\n", valorUnitario[i]);
		//printf("%.2f\n", valorTotal[i]);

		printf("%d %s %d %.2f %.2f\n", idProduto[i], texto[i], quantidade[i], valorUnitario[i], valorTotal[i]);
	}

	return 0;
}
