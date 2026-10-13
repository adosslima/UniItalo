#include <stdio.h>

int main()
{
    float distanciaPercorrida = 0;
    float consumoCada100 = 0;
    float precoEnergiaEletrica = 0;
    
    printf("Informe a distância percorrida em quilômetros:");
    scanf("%f", &distanciaPercorrida);

    printf("Informe o consumo médio do veículo em kWh a cada 100 km:");
    scanf("%f", &consumoCada100);

    printf("Informe o preço da energia elétrica em R$/kWh:");
    scanf("%f", &precoEnergiaEletrica);


    float energiaConsumida = (distanciaPercorrida * consumoCada100) / 100;
    float custoTotal = energiaConsumida * precoEnergiaEletrica;
    float custoProKm = custoTotal / distanciaPercorrida;

    printf("Quantidade de energia consumida durante a viagem: %.2f \n", energiaConsumida);
    printf("Custo total da energia utilizada: %.2f \n", custoTotal);
    printf("Custo de energia por quilômetro percorrido: %.2f \n", custoProKm);

    return 0;
}