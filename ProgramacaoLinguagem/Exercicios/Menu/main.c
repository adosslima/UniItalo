#include <stdio.h>

int main()
{
	int opcao = 0;

	while (opcao != 9) {
		printf("*** Menu ***\n");
		printf("1 - Novo\n");
		printf("2 - Abrir\n");
		printf("3 - Salvar\n");
		printf("4 - Imprimir\n");
		printf("9 - Sair\n");

        printf("Entre com a opção desejada: ");
		scanf("%d", &opcao);
		
		if ((opcao >= 1 && opcao <= 4) || opcao == 9) {
		    switch (opcao) {
		        case 1: printf("Novo\n"); break;
		        case 2: printf("Abrir\n"); break;
		        case 3: printf("Salvar\n"); break;
		        case 4: printf("Imprimir\n"); break;
		        default: printf("Sair\n");
		    }
		} else {
		    printf("Opção - Inválida\n");
		}
	}

	return 0;
}
