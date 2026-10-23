#define PET_H

#define MAX_PETS 100

typedef struct
{
    int codPet;
    int codTutor;
    int codEspecie;
    int codRaca;
    char nomePet[50];
    char dataNascimento[11];
} Pet;

void menuPets(void);
