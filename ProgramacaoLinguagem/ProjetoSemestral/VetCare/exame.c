#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include "tela.h"
#include "exame.h"

#define ARQUIVO_EXAMES "C:\\VetCare\\Dados\\Exame.json"

static Exame exames[MAX_EXAMES];
static int totalExames = 0;
static int proximoCodigo = 1;

/*
---------------------------------
Função Carregar
---------------------------------
*/
static void carregarExames(void)
{
    FILE *arquivo = fopen(ARQUIVO_EXAMES, "r");

    totalExames = 0;
    proximoCodigo = 1;

    if (arquivo == NULL)
        return;

    char linha[200];
    Exame exame = {0};

    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        if (strstr(linha, "\"codExame\"") != NULL)
        {
            sscanf(linha, " \"codExame\": %d", &exame.codExame);
        }

        if (strstr(linha, "\"nomeExame\"") != NULL)
        {
            char *inicio = strchr(linha, ':');

            if (inicio != NULL)
            {
                inicio = strchr(inicio, '"');

                if (inicio != NULL)
                {
                    inicio++;

                    char *fim = strchr(inicio, '"');

                    if (fim != NULL)
                    {
                        *fim = '\0';
                        strncpy(exame.nomeExame, inicio, sizeof(exame.nomeExame) - 1);
                        exame.nomeExame[sizeof(exame.nomeExame) - 1] = '\0';
                    }
                }
            }
        }

        if (strstr(linha, "\"valorExame\"") != NULL)
        {
            sscanf(linha, " \"valorExame\": %" SCNd64, &exame.valorExame);

            if (totalExames < MAX_EXAMES)
            {
                exames[totalExames++] = exame;

                if (exame.codExame >= proximoCodigo)
                    proximoCodigo = exame.codExame + 1;
            }

            exame = (Exame){0};
        }
    }

    fclose(arquivo);
}

/*
---------------------------------
Função Buscar Indice
---------------------------------
*/
static int buscarIndice(int codigo)
{
    for (int i = 0; i < totalExames; i++)
    {
        if (exames[i].codExame == codigo)
            return i;
    }
    return -1;
}

/*
---------------------------------
Função Pública Validar Exame
---------------------------------
*/
int validarExame(int codigo, char *nome, int64_t *valorExame)
{
    carregarExames();

    int indice = buscarIndice(codigo);

    if (indice == -1)
    {
        nome[0] = '\0';
        valorExame = 0;
        return 0;
    }

    strcpy(nome, exames[indice].nomeExame);
    *valorExame = exames[indice].valorExame;

    return 1;
}

/*
---------------------------------
Função Listar
---------------------------------
*/
void listarExames(void)
{
    carregarExames();

    char codigo[10];
    char valor[10];

    int linha = 2;
    int largura = 92;

    telaLimpar();

    telaPosicionarCursor(0, linha);
    printf("+");

    for (int i = 0; i < largura - 2; i++)
        printf("=");

    printf("+");

    linha++;

    telaEscrever(0, linha, "|");
    telaEscreverCentralizado("VETCARE - EXAMES - Listagem", 0, 70, linha);
    telaEscrever(largura - 1, linha, "|");

    linha++;

    telaPosicionarCursor(0, linha);
    printf("+");

    for (int i = 0; i < largura - 2; i++)
        printf("=");

    printf("+");

    linha++;

    telaEscrever(0, linha, "|");
    telaEscrever(1, linha, "CODIGO");
    telaEscrever(8, linha, "NOME");
    telaEscrever(59, linha, "VALOR");
    telaEscrever(largura - 1, linha, "|");

    linha++;

    telaPosicionarCursor(0, linha);
    printf("|");

    for (int i = 0; i < largura - 2; i++)
        printf("-");

    printf("|");

    linha++;

    for (int i = 0; i < totalExames; i++)
    {
        telaEscrever(0, linha, "|");
        snprintf(codigo, sizeof(codigo), "%d", exames[i].codExame);
        snprintf(valor, sizeof(valor), "%" PRId64, exames[i].valorExame);

        telaEscrever(1, linha, codigo);
        telaEscrever(8, linha, exames[i].nomeExame);
        telaEscrever(59, linha, valor);

        telaEscrever(largura - 1, linha, "|");
        linha++;
    }

    telaPosicionarCursor(0, linha);
    printf("|");

    for (int i = 0; i < largura - 2; i++)
        printf("-");

    printf("|");

    linha++;

    telaEscrever(0, linha, "|");
    telaEscrever(1, linha, "Total: ");
    printf("%d", totalExames);
    telaEscrever(largura - 1, linha, "|");

    linha++;

    telaPosicionarCursor(0, linha);
    printf("+");

    for (int i = 0; i < largura - 2; i++)
        printf("=");

    printf("+");

    getchar();
    getchar();
}
