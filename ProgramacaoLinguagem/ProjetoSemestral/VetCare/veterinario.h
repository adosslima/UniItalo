#define VETERINARIO_H

#define MAX_VETERINARIOS 100

typedef struct
{
    int codVeterinario;
    char nomeVeterinario[50];
} Veterinario;

void menuVeterinarios(void);
