#include <stdint.h>
#define ATENDIMENTO_H

#define MAX_ATENDIMENTOS 100

typedef struct
{
    int codAtendimento;
    int codVeterinario;
    int codTutor;
    int codPet;
    char dataAtendimento[11];
    int codVacina1;
    int codVacina2;
    int codVacina3;
    int codVacina4;
    int64_t valVacina1;
    int64_t valVacina2;
    int64_t valVacina3;
    int64_t valVacina4;
    int64_t totVacina;
    int codExame1;
    int codExame2;
    int codExame3;
    int codExame4;
    int64_t valExame1;
    int64_t valExame2;
    int64_t valExame3;
    int64_t valExame4;
    int64_t totExame;
    int64_t valAtendimento;
    int64_t totAtendimento;
} Atendimento;

extern int totalAtendimentos;
extern Atendimento atendimentos[MAX_ATENDIMENTOS];

void carregarAtendimentos(void);
void incluirAtendimento(void);
void salvarAtendimentos(void);
void salvarDashBoard(void);