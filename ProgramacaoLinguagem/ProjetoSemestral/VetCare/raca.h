#define RACA_H

#define MAX_RACAS 100

typedef struct
{
    int codRaca;
    char nomeRaca[50];
} Raca;

void menuRacas(void);
