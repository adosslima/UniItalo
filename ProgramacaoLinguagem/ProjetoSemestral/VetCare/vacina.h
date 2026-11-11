#define VACINCA_H

#define MAX_VACINAS 1000

typedef struct
{
    int codVacina;
    char nomeVacina[50];
    char dataValidade[11];
    int valorVacina;
    int estoqueVacina;
} Vacina;

void listarVacinas(void);
