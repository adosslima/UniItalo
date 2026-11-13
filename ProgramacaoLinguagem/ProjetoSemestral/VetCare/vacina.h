#include <inttypes.h>

#define VACINCA_H

#define MAX_VACINAS 1000

typedef struct
{
    int codVacina;
    char nomeVacina[50];
    char dataValidade[11];
    int64_t valorVacina;
    int estoqueVacina;
} Vacina;

void listarVacinas(void);
int validarVacina(int codigo, char *nome, int64_t *valorVacina);
