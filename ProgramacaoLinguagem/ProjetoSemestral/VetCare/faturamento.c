#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdint.h>
#include <inttypes.h>
#include "atendimento.h"
#include "util.h"
#include "data.h"
#include "pet.h"
#include "tela.h"
#include "tutor.h"
#include "exame.h"
#include "vacina.h"
#include "veterinario.h"
#include "faturamento.h"

#define ARQUIVO_ATENDIMENTOS "C:\\VetCare\\Dados\\Atendimento.json"

Faturamento faturamentos[MAX_FATURAMENTOS];
static int totalFaturamentos = 0;

/*
---------------------------------
Função Buscar Indice
---------------------------------
*/
static int buscarIndice(const char *data)
{
    for (int i = 0; i < totalFaturamentos; i++)
    {
        if (strcmp(faturamentos[i].data, data) == 0)
        {
            return i;
        }
    }

    return -1;
}

/*
---------------------------------
 Função EMITIR RELATÓRIO
---------------------------------
*/
void emitirFaturamento(void)
{
    SetConsoleOutputCP(437);

    carregarAtendimentos();

    totalFaturamentos = 0;

    int indice = 0;
    int linha = 9;

    char quantidade[11];
    char valFormatado[64];
    char valTexto[85];

    int64_t totQtdAtendimento = 0;
    int64_t totValAtentimento = 0;
    int64_t totValVacina = 0;
    int64_t totValExame = 0;
    int64_t totValData = 0;

    Faturamento faturamento = {0};

    for (int i = 0; i < totalAtendimentos; i++)
    {
        indice = buscarIndice(atendimentos[i].dataAtendimento);

        if (indice == -1)
        {
            if (totalFaturamentos >= MAX_FATURAMENTOS)
            {
                telaEscreverCentralizado("Limite de faturamentos atingido!", 0, 85, 22);
                return;
            }

            indice = totalFaturamentos++;

            faturamento = (Faturamento){0};
        }
        else
        {
            faturamento = faturamentos[indice];
        }

        snprintf(faturamento.data, sizeof(faturamento.data), "%s", atendimentos[i].dataAtendimento);
        faturamento.qtdAtendimento++;
        faturamento.totAtendimento += atendimentos[i].valAtendimento;
        faturamento.totVacina += atendimentos[i].totVacina;
        faturamento.totExame += atendimentos[i].totExame;
        faturamento.totData += atendimentos[i].valAtendimento + atendimentos[i].totVacina + atendimentos[i].totExame;

        faturamentos[indice] = faturamento;
    }

    telaLimpar();
    telaDesenharBox(0, 0, 80, 24);
    telaEscreverCentralizado("FATURAMENTO", 0, 80, 3);

    telaEscrever(18, 5, "Qtd                           Valor");
    telaEscrever(14, 6, "------------ ---------------------------------------------------");
    telaEscrever(6, 7, "Data    Atendimentos Atendimentos    Exames      Vacinas       Total");
    telaEscrever(3, 8, "---------- ------------ ------------ ------------ ------------ ------------");

    for (int i = 0; i < totalFaturamentos; i++)
    {
        telaPosicionarCursor(0, linha);
        printf("%c", 186);
        printf("%*s", 78, " ");
        telaPosicionarCursor(79, linha);
        printf("%c", 186);

        telaEscrever(3, linha, faturamentos[i].data);

        snprintf(quantidade, sizeof(quantidade), "%d", faturamentos[i].qtdAtendimento);
        telaEscrever(21, linha, quantidade);

        formatarMoeda(faturamentos[i].totAtendimento, valFormatado, sizeof(valFormatado));
        snprintf(valTexto, sizeof(valTexto), "%s", valFormatado);
        telaEscrever(27, linha, valTexto);

        formatarMoeda(faturamentos[i].totExame, valFormatado, sizeof(valFormatado));
        snprintf(valTexto, sizeof(valTexto), "%s", valFormatado);
        telaEscrever(40, linha, valTexto);

        formatarMoeda(faturamentos[i].totVacina, valFormatado, sizeof(valFormatado));
        snprintf(valTexto, sizeof(valTexto), "%s", valFormatado);
        telaEscrever(53, linha, valTexto);

        formatarMoeda(faturamentos[i].totData, valFormatado, sizeof(valFormatado));
        snprintf(valTexto, sizeof(valTexto), "%s", valFormatado);
        telaEscrever(66, linha, valTexto);

        linha++;

        totQtdAtendimento += faturamentos[i].qtdAtendimento;
        totValAtentimento += faturamentos[i].totAtendimento;
        totValExame += faturamentos[i].totExame;
        totValVacina += faturamentos[i].totVacina;
        totValData += faturamentos[i].totData;
    }

    telaPosicionarCursor(0, linha);
    printf("%c", 186);
    printf("%*s", 78, " ");
    telaPosicionarCursor(79, linha);
    printf("%c", 186);

    telaEscrever(3, linha, "---------- ------------ ------------ ------------ ------------ ------------");

    linha++;
    telaPosicionarCursor(0, linha);
    printf("%c", 186);
    printf("%*s", 78, " ");
    telaPosicionarCursor(79, linha);
    printf("%c", 186);

    telaEscrever(3, linha, "TOTAL");

    snprintf(quantidade, sizeof(quantidade), "%" PRId64, totQtdAtendimento);
    telaEscrever(21, linha, quantidade);

    formatarMoeda(totValAtentimento, valFormatado, sizeof(valFormatado));
    snprintf(valTexto, sizeof(valTexto), "%s", valFormatado);
    telaEscrever(27, linha, valTexto);

    formatarMoeda(totValExame, valFormatado, sizeof(valFormatado));
    snprintf(valTexto, sizeof(valTexto), "%s", valFormatado);
    telaEscrever(40, linha, valTexto);

    formatarMoeda(totValVacina, valFormatado, sizeof(valFormatado));
    snprintf(valTexto, sizeof(valTexto), "%s", valFormatado);
    telaEscrever(53, linha, valTexto);

    formatarMoeda(totValData, valFormatado, sizeof(valFormatado));
    snprintf(valTexto, sizeof(valTexto), "%s", valFormatado);
    telaEscrever(66, linha, valTexto);

    linha++;
    telaPosicionarCursor(0, linha);
    printf("%c", 186);
    printf("%*s", 78, " ");
    telaPosicionarCursor(79, linha);
    printf("%c", 186);

    if (linha >= 22)
        telaEscreverCentralizado("Pressione [ENTER]", 0, 80, linha);
    else
        telaEscreverCentralizado("Pressione [ENTER]", 0, 80, 22);

    linha++;

    if (linha >= 24)
    {
        telaPosicionarCursor(0, linha);
        printf("%c", 200); // ╚

        for (int i = 0; i < 80 - 2; i++)
            printf("%c", 205); // ═

        printf("%c", 188); // ╝
    }

    getchar();
    getchar();
}
