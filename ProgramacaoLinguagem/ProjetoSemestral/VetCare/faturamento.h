#include <stdint.h>
#define FATURAMENTO_H

#define MAX_FATURAMENTOS 1000

typedef struct
{
    char data[11];
    int qtdAtendimento;
    int64_t totAtendimento;
    int64_t totVacina;
    int64_t totExame;
    int64_t totData;
} Faturamento;

void emitirFaturamento(void);
