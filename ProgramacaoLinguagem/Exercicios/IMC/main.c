#include <stdio.h>

int main()
{
    char genero[] = "M";
    float altura = 1.68;
    float peso = 90;

    float calculo = (peso/(altura*altura));
    
    printf("Valor calculado %2.f\n",calculo);
    
    if (calculo <= 18.5) {
        printf("Magreza");
    } else if (calculo <= 24.9) {
        printf("Normal");
    } else if (calculo <= 29.9) {
        printf("Sobrepeso");
    } else if (calculo <= 34.9) {
        printf("Obesidade Grau I");
    } else if (calculo <= 39.9) {
        printf("Obesidade Grau II");
    } else {
        printf("Obesidade Grau III");
    }

    return 0;
}
