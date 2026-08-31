#include <stdio.h>

int main()
{
    float distancia = 0;
    float consumida = 0;
    float preco = 0;

    printf("Informe a distancia percorrida: ");
    scanf("%f", &distancia);

    printf("Informe a quantidade de gasolina consumida: ");
    scanf("%f", &consumida);

    printf("Informe o preco da gasolina: ");
    scanf("%f", &preco);

    printf("\nDistancia: %.2f\n", distancia);
    printf("Consumo: %.2f\n", consumida);
    printf("Preco: %.2f\n", preco);

    printf("\nConsumo medio = %.2f km/l\n", distancia / consumida);
    printf("Custo total = %.2f\n", preco * consumida);
    printf("Custo por quilometro = %.2f\n", (preco * consumida) / distancia);

    return 0;
}