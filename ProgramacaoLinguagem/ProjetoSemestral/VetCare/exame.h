#define EXAME_H

#define MAX_EXAMES 1000

typedef struct
{
    int codExame;
    char nomeExame[50];
    int valorExame;
} Exame;

void listarExames(void);
