#include <stdio.h>

int main()
{
    int opcoes[5] = {100,200,300,400,500};
    int tamanho = sizeof(opcoes) / sizeof(opcoes[0]); 

    printf("Tamanho do Array: %d\n", tamanho);

    for (int i = 0; i < tamanho; i++) {
        printf("Elemento: %d Valor: %d \n", i, opcoes[i]);
    }
    
    return 0;
}
