#include <stdint.h>
#define DASHBOARD_H

#define MAX_DASHBOARDS 100

typedef struct
{
    int qtdAtendimento;
    int64_t valAtendimento;
    int qtdVacina;
    int64_t valVacima;
    int qtdExame;
    int64_t valExame;
} DashBoard;
