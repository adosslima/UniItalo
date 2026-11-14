#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include "atendimento.h"
#include "servico.h"
#include "util.h"
#include "data.h"
#include "pet.h"
#include "tela.h"
#include "tutor.h"
#include "exame.h"
#include "vacina.h"
#include "veterinario.h"

#define ARQUIVO_ATENDIMENTOS "C:\\VetCare\\Dados\\Atendimento.json"
#define ARQUIVO_DASHBOARD "C:\\VetCare\\Dados\\DashBoard.json"

/*
---------------------------------
Função Buscar Indice
---------------------------------
*/
static int buscarIndice(int codigo)
{
    for (int i = 0; i < totalAtendimentos; i++)
    {
        if (atendimentos[i].codAtendimento == codigo)
            return i;
    }

    return -1;
}

/*
---------------------------------
Função Incluir
---------------------------------
*/
void incluirServico(void)
{
    SetConsoleOutputCP(437);

    int codAtendimento = 0;
    int indice = 0;

    char valFormatado[64];
    char valTexto[85];
    char codTexto[12];

    char nomeValido[50] = {0};
    char nomeImpresso[20] = {0};

    int64_t valorExame1 = 0;
    int64_t valorExame2 = 0;
    int64_t valorExame3 = 0;
    int64_t valorExame4 = 0;
    int64_t totalExames = 0;

    int64_t valorVacina1 = 0;
    int64_t valorVacina2 = 0;
    int64_t valorVacina3 = 0;
    int64_t valorVacina4 = 0;
    int64_t totalVacinas = 0;

    carregarAtendimentos();

    telaLimpar();
    telaDesenharBox(0, 0, 85, 24);
    telaEscreverCentralizado("SERVICOS - Inclusao", 0, 85, 3);

    telaEscrever(3, 5, "Cod.Atendimento: ");
    telaEscrever(3, 6, "Dat.Atendimento: ");
    telaEscrever(38, 5, "Cod.Veterinario: ");
    telaEscrever(38, 6, "Cod.Tutor......: ");
    telaEscrever(38, 7, "Cod.Pet........: ");

    telaEscrever(3, 9, "Cod.Exame: ");
    telaEscrever(3, 10, "Cod.Exame: ");
    telaEscrever(3, 11, "Cod.Exame: ");
    telaEscrever(3, 12, "Cod.Exame: ");

    telaEscrever(43, 9, "Cod.Vacina: ");
    telaEscrever(43, 10, "Cod.Vacina: ");
    telaEscrever(43, 11, "Cod.Vacina: ");
    telaEscrever(43, 12, "Cod.Vacina: ");

    telaEscrever(47, 15, "Valor Atendimento: ");
    telaEscrever(47, 16, "Valor Exames.....: ");
    telaEscrever(47, 17, "Valor Vacinas....: ");
    telaEscrever(47, 18, "Valor Total......: ");

    telaPosicionarCursor(20, 5);
    scanf("%d", &codAtendimento);

    indice = buscarIndice(codAtendimento);

    if (indice == -1)
    {
        telaEscreverCentralizado("Atendimento nao cadastrado", 0, 85, 22);
        getchar();
        getchar();
        return;
    }

    telaEscrever(20, 6, atendimentos[indice].dataAtendimento);

    snprintf(codTexto, sizeof(codTexto), "%d", atendimentos[indice].codVeterinario);
    telaEscrever(55, 5, codTexto);

    snprintf(codTexto, sizeof(codTexto), "%d", atendimentos[indice].codTutor);
    telaEscrever(55, 6, codTexto);

    snprintf(codTexto, sizeof(codTexto), "%d", atendimentos[indice].codPet);
    telaEscrever(55, 7, codTexto);

    snprintf(codTexto, sizeof(codTexto), "%d", atendimentos[indice].codExame1);
    telaEscrever(14, 9, codTexto);

    snprintf(codTexto, sizeof(codTexto), "%d", atendimentos[indice].codExame2);
    telaEscrever(14, 10, codTexto);

    snprintf(codTexto, sizeof(codTexto), "%d", atendimentos[indice].codExame3);
    telaEscrever(14, 11, codTexto);

    snprintf(codTexto, sizeof(codTexto), "%d", atendimentos[indice].codExame4);
    telaEscrever(14, 12, codTexto);

    snprintf(codTexto, sizeof(codTexto), "%d", atendimentos[indice].codVacina1);
    telaEscrever(55, 9, codTexto);

    snprintf(codTexto, sizeof(codTexto), "%d", atendimentos[indice].codVacina2);
    telaEscrever(55, 10, codTexto);

    snprintf(codTexto, sizeof(codTexto), "%d", atendimentos[indice].codVacina3);
    telaEscrever(55, 11, codTexto);

    snprintf(codTexto, sizeof(codTexto), "%d", atendimentos[indice].codVacina4);
    telaEscrever(55, 12, codTexto);

    formatarMoeda(atendimentos[indice].valAtendimento, valFormatado, sizeof(valFormatado));
    snprintf(valTexto, sizeof(valTexto), "Valor Atendimento: %s", valFormatado);
    telaEscrever(47, 15, valTexto);

    formatarMoeda(atendimentos[indice].totExame, valFormatado, sizeof(valFormatado));
    snprintf(valTexto, sizeof(valTexto), "Valor Exames.....: %s", valFormatado);
    telaEscrever(47, 16, valTexto);

    formatarMoeda(atendimentos[indice].totVacina, valFormatado, sizeof(valFormatado));
    snprintf(valTexto, sizeof(valTexto), "Valor Vacinas....: %s", valFormatado);
    telaEscrever(47, 17, valTexto);

    formatarMoeda(atendimentos[indice].totAtendimento, valFormatado, sizeof(valFormatado));
    snprintf(valTexto, sizeof(valTexto), "Valor Total......: %s", valFormatado);
    telaEscrever(47, 18, valTexto);

    validarVeterinario(atendimentos[indice].codVeterinario, nomeValido);
    strncpy(nomeImpresso, nomeValido, 20);
    telaEscrever(58, 5, nomeImpresso);

    validarTutor(atendimentos[indice].codTutor, nomeValido);
    strncpy(nomeImpresso, nomeValido, 20);
    telaEscrever(58, 6, nomeImpresso);

    validarPet(atendimentos[indice].codPet, nomeValido);
    strncpy(nomeImpresso, nomeValido, 20);
    telaEscrever(58, 7, nomeImpresso);

    // Exame 1
    if (atendimentos[indice].codExame1 > 0)
    {
        validarExame(atendimentos[indice].codExame1, nomeValido, &valorExame1);

        strncpy(nomeImpresso, nomeValido, 20);
        telaEscrever(17, 9, nomeImpresso);
    }
    else
    {
        telaEscrever(17, 9, "NENHUM");
    }

    // Exame 2
    if (atendimentos[indice].codExame2 > 0)
    {
        validarExame(atendimentos[indice].codExame2, nomeValido, &valorExame2);

        strncpy(nomeImpresso, nomeValido, 20);
        telaEscrever(17, 10, nomeImpresso);
    }
    else
    {
        telaEscrever(17, 10, "NENHUM");
    }

    // Exame 3
    if (atendimentos[indice].codExame3 > 0)
    {
        validarExame(atendimentos[indice].codExame3, nomeValido, &valorExame3);

        strncpy(nomeImpresso, nomeValido, 20);
        telaEscrever(17, 11, nomeImpresso);
    }
    else
    {
        telaEscrever(17, 11, "NENHUM");
    }

    // Exame 4
    if (atendimentos[indice].codExame4 > 0)
    {
        validarExame(atendimentos[indice].codExame4, nomeValido, &valorExame4);

        strncpy(nomeImpresso, nomeValido, 20);
        telaEscrever(17, 12, nomeImpresso);
    }
    else
    {
        telaEscrever(17, 12, "NENHUM");
    }

    // Vacina 1
    if (atendimentos[indice].codVacina1 > 0)
    {
        validarVacina(atendimentos[indice].codVacina1, nomeValido, &valorVacina1);

        strncpy(nomeImpresso, nomeValido, 20);
        telaEscrever(58, 9, nomeImpresso);
    }
    else
    {
        telaEscrever(58, 9, "NENHUMA");
    }

    // Vacina 2
    if (atendimentos[indice].codVacina2 > 0)
    {
        validarVacina(atendimentos[indice].codVacina2, nomeValido, &valorVacina2);

        strncpy(nomeImpresso, nomeValido, 20);
        telaEscrever(58, 10, nomeImpresso);
    }
    else
    {
        telaEscrever(58, 10, "NENHUMA");
    }

    // Vacina 3
    if (atendimentos[indice].codVacina3 > 0)
    {
        validarVacina(atendimentos[indice].codVacina3, nomeValido, &valorVacina3);

        strncpy(nomeImpresso, nomeValido, 20);
        telaEscrever(58, 11, nomeImpresso);
    }
    else
    {
        telaEscrever(58, 11, "NENHUMA");
    }

    // Vacina 4
    if (atendimentos[indice].codVacina4 > 0)
    {
        validarVacina(atendimentos[indice].codVacina4, nomeValido, &valorVacina4);

        strncpy(nomeImpresso, nomeValido, 20);
        telaEscrever(58, 12, nomeImpresso);
    }
    else
    {
        telaEscrever(58, 12, "NENHUMA");
    }

    valorExame1 = 0;
    valorExame2 = 0;
    valorExame3 = 0;
    valorExame4 = 0;
    totalExames = 0;

    // Exame 1
    do
    {
        telaEscrever(3, 9, "Cod.Exame: ");
        scanf("%d", &atendimentos[indice].codExame1);

    } while (atendimentos[indice].codExame1 > 0 && validarExame(atendimentos[indice].codExame1, nomeValido, &valorExame1) == 0);

    telaPosicionarCursor(17, 9);
    printf("%*s", 22, "");

    if (atendimentos[indice].codExame1 == 0)
    {
        telaEscrever(17, 9, "NENHUM");
    }
    else
    {
        strncpy(nomeImpresso, nomeValido, 20);
        telaEscrever(17, 9, nomeImpresso);
    }

    // Exame 2
    do
    {
        telaEscrever(3, 10, "Cod.Exame: ");
        scanf("%d", &atendimentos[indice].codExame2);

    } while (atendimentos[indice].codExame2 > 0 && validarExame(atendimentos[indice].codExame2, nomeValido, &valorExame2) == 0);

    telaPosicionarCursor(17, 10);
    printf("%*s", 22, "");

    if (atendimentos[indice].codExame2 == 0)
    {
        telaEscrever(17, 10, "NENHUM");
    }
    else
    {
        strncpy(nomeImpresso, nomeValido, 20);
        telaEscrever(17, 10, nomeImpresso);
    }

    // Exame 3
    do
    {
        telaEscrever(3, 11, "Cod.Exame: ");
        scanf("%d", &atendimentos[indice].codExame3);

    } while (atendimentos[indice].codExame3 > 0 && validarExame(atendimentos[indice].codExame3, nomeValido, &valorExame3) == 0);

    telaPosicionarCursor(17, 11);
    printf("%*s", 22, "");

    if (atendimentos[indice].codExame3 == 0)
    {
        telaEscrever(17, 11, "NENHUM");
    }
    else
    {
        strncpy(nomeImpresso, nomeValido, 20);
        telaEscrever(17, 11, nomeImpresso);
    }

    // Exame 4
    do
    {
        telaEscrever(3, 12, "Cod.Exame: ");
        scanf("%d", &atendimentos[indice].codExame4);

    } while (atendimentos[indice].codExame4 > 0 && validarExame(atendimentos[indice].codExame4, nomeValido, &valorExame4) == 0);

    telaPosicionarCursor(17, 12);
    printf("%*s", 22, "");

    if (atendimentos[indice].codExame4 == 0)
    {
        telaEscrever(17, 12, "NENHUM");
    }
    else
    {
        strncpy(nomeImpresso, nomeValido, 20);
        telaEscrever(17, 12, nomeImpresso);
    }

    totalExames = valorExame1 + valorExame2 + valorExame3 + valorExame4;

    atendimentos[indice].valExame1 = valorExame1;
    atendimentos[indice].valExame2 = valorExame2;
    atendimentos[indice].valExame3 = valorExame3;
    atendimentos[indice].valExame4 = valorExame4;
    atendimentos[indice].totExame = totalExames;

    telaPosicionarCursor(47, 16);
    printf("%*s", 30, "");

    formatarMoeda(totalExames, valFormatado, sizeof(valFormatado));
    snprintf(valTexto, sizeof(valTexto), "Valor Exames.....: %s", valFormatado);
    telaEscrever(47, 16, valTexto);

    valorVacina1 = 0;
    valorVacina2 = 0;
    valorVacina3 = 0;
    valorVacina4 = 0;
    totalVacinas = 0;

    // Vacina 1
    do
    {
        telaEscrever(43, 9, "Cod.Vacina: ");
        scanf("%d", &atendimentos[indice].codVacina1);

    } while (atendimentos[indice].codVacina1 > 0 && validarVacina(atendimentos[indice].codVacina1, nomeValido, &valorVacina1) == 0);

    telaPosicionarCursor(58, 9);
    printf("%*s", 22, "");

    if (atendimentos[indice].codVacina1 == 0)
    {
        telaEscrever(58, 9, "NENHUMA");
    }
    else
    {
        strncpy(nomeImpresso, nomeValido, 20);
        telaEscrever(58, 9, nomeImpresso);
    }

    // Vacina 2
    do
    {
        telaEscrever(43, 10, "Cod.Vacina: ");
        scanf("%d", &atendimentos[indice].codVacina2);

    } while (atendimentos[indice].codVacina2 > 0 && validarVacina(atendimentos[indice].codVacina2, nomeValido, &valorVacina2) == 0);

    telaPosicionarCursor(58, 10);
    printf("%*s", 22, "");

    if (atendimentos[indice].codVacina2 == 0)
    {
        telaEscrever(58, 10, "NENHUMA");
    }
    else
    {
        strncpy(nomeImpresso, nomeValido, 20);
        telaEscrever(58, 10, nomeImpresso);
    }

    // Vacina 3
    do
    {
        telaEscrever(43, 11, "Cod.Vacina: ");
        scanf("%d", &atendimentos[indice].codVacina3);

    } while (atendimentos[indice].codVacina3 > 0 && validarVacina(atendimentos[indice].codVacina3, nomeValido, &valorVacina3) == 0);

    telaPosicionarCursor(58, 11);
    printf("%*s", 22, "");

    if (atendimentos[indice].codVacina3 == 0)
    {
        telaEscrever(58, 11, "NENHUMA");
    }
    else
    {
        strncpy(nomeImpresso, nomeValido, 20);
        telaEscrever(58, 11, nomeImpresso);
    }

    // Vacina 4
    do
    {
        telaEscrever(43, 12, "Cod.Vacina: ");
        scanf("%d", &atendimentos[indice].codVacina4);

    } while (atendimentos[indice].codVacina4 > 0 && validarVacina(atendimentos[indice].codVacina4, nomeValido, &valorVacina4) == 0);

    telaPosicionarCursor(58, 12);
    printf("%*s", 22, "");

    if (atendimentos[indice].codVacina4 == 0)
    {
        telaEscrever(58, 12, "NENHUMA");
    }
    else
    {
        strncpy(nomeImpresso, nomeValido, 20);
        telaEscrever(58, 12, nomeImpresso);
    }

    totalVacinas = valorVacina1 + valorVacina2 + valorVacina3 + valorVacina4;

    atendimentos[indice].valVacina1 = valorVacina1;
    atendimentos[indice].valVacina2 = valorVacina2;
    atendimentos[indice].valVacina3 = valorVacina3;
    atendimentos[indice].valVacina4 = valorVacina4;
    atendimentos[indice].totVacina = totalVacinas;

    telaPosicionarCursor(47, 17);
    printf("%*s", 30, "");

    formatarMoeda(totalVacinas, valFormatado, sizeof(valFormatado));
    snprintf(valTexto, sizeof(valTexto), "Valor Vacinas....: %s", valFormatado);
    telaEscrever(47, 17, valTexto);

    salvarAtendimentos();
    salvarDashBoard();

    telaEscreverCentralizado("Servico cadastrado!", 0, 85, 22);
    getchar();
    getchar();
}
