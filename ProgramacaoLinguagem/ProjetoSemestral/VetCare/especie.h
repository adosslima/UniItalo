#define ESPECIE_H

#define MAX_ESPECIES 100

typedef struct
{
    int codEspecie;
    char nomeEspecie[50];
} Especie;

void menuEspecies(void);
