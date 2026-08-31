#include <stdio.h>

int main()
{
    int pessoas;
    int dias;

    float distancia;
    float consumo;
    float precoGasolina;
    float diariaHotel;
    float alimentacaoPessoaDia;
    float passeiosPessoa;
    float estacionamentos;
    float pedagios;
    float compras;

    printf("Informe o numero de pessoas: ");
    scanf("%d", &pessoas);
    
    printf("Informe a duracao da viagem em dias: ");
    scanf("%d", &dias);
    
    printf("Informe a distancia total estimada: ");
    scanf("%f", &distancia);
    
    printf("Informe o consumo do automovel em km/L: ");
    scanf("%f", &consumo);
    
    printf("Informe o preco da gasolina: ");
    scanf("%f", &precoGasolina);
    
    printf("Informe a diaria media do hotel: ");
    scanf("%f", &diariaHotel);
    
    printf("Informe o custo de alimentacao por pessoa/dia: ");
    scanf("%f", &alimentacaoPessoaDia);
    
    printf("Informe o custo dos passeios por pessoa: ");
    scanf("%f", &passeiosPessoa);
    
    printf("Informe o custo com estacionamentos: ");
    scanf("%f", &estacionamentos);
    
    printf("Informe o custo com pedagios: ");
    scanf("%f", &pedagios);
    
    printf("Informe o custo com compras e lembrancas: ");
    scanf("%f", &compras);


    float litrosCombustivel = distancia / consumo;

    float custoCombustivel = litrosCombustivel * precoGasolina;

    float custoHotel = diariaHotel * dias;

    float custoAlimentacao = alimentacaoPessoaDia * pessoas * dias;

    float custoPasseios = passeiosPessoa * pessoas;

    float custoTotal = custoCombustivel
                    + custoHotel
                    + custoAlimentacao
                    + custoPasseios
                    + estacionamentos
                    + pedagios
                    + compras;

    printf("Custo total: %.2f \n", custoTotal);

    return 0;
}
