#define TUTOR_H

#define MAX_TUTORES 100

typedef struct
{
    int codTutor;
    char nomeTutor[50];
} Tutor;

void menuTutores(void);
