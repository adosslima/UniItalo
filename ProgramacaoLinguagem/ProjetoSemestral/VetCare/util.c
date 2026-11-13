#include <stdio.h>
#include <stdint.h>
#include <string.h>

void formatarMoeda(int64_t valor, char *resultado, size_t tamanho)
{
    char numero[32];
    char formatado[48];
    char invertido[48];

    // Trabalhamos com o valor absoluto em centavos.
    // Esta expressao tambem trata corretamente INT64_MIN.
    uint64_t absoluto = valor < 0
        ? (uint64_t)(-(valor + 1)) + 1
        : (uint64_t)valor;

    uint64_t reais = absoluto / 100;
    unsigned int centavos = (unsigned int)(absoluto % 100);

    snprintf(numero, sizeof(numero), "%llu",
             (unsigned long long)reais);

    int j = 0;
    int contador = 0;

    // Percorre os digitos de tras para frente.
    for (int i = (int)strlen(numero) - 1; i >= 0; i--)
    {
        if (contador == 3)
        {
            invertido[j++] = '.';
            contador = 0;
        }

        invertido[j++] = numero[i];
        contador++;
    }

    // Inverte novamente para obter a ordem correta.
    int k = 0;

    for (int i = j - 1; i >= 0; i--)
        formatado[k++] = invertido[i];

    formatado[k] = '\0';

    snprintf(resultado, tamanho, "%sR$ %s,%02u",
             valor < 0 ? "-" : "",
             formatado,
             centavos);
}
