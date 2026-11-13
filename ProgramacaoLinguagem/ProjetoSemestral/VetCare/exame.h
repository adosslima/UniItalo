#include <stdint.h>

#define EXAME_H

#define MAX_EXAMES 1000

typedef struct
{
    int codExame;
    char nomeExame[50];
    int64_t valorExame;
} Exame;

void listarExames(void);
int validarExame(int codigo, char *nome, int64_t *valorExame);
