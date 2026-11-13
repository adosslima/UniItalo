#include <time.h>
#include "data.h"

Data obterDataAtual(void)
{
    Data data = {0};

    time_t agora = time(NULL);

    struct tm *dataSistema = localtime(&agora);

    if (dataSistema == NULL)
        return data;

    data.dia = dataSistema->tm_mday;
    data.mes = dataSistema->tm_mon + 1;
    data.ano = dataSistema->tm_year + 1900;

    return data;
}
