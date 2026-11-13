#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "vacina.h"
#include "tela.h"

#define ARQUIVO_VACINAS "C:\\VetCare\\Dados\\Vacina.json"

static Vacina vacinas[MAX_VACINAS];
static int totalVacinas = 0;
static int proximoCodigo = 1;

/*
---------------------------------
Função Carregar
---------------------------------
*/
static void carregarVacinas(void)
{
    FILE *arquivo = fopen(ARQUIVO_VACINAS, "r");

    totalVacinas = 0;
    proximoCodigo = 1;

    if (arquivo == NULL)
        return;

    char linha[200];
    Vacina vacina = {0};

    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        if (strstr(linha, "\"codVacina\"") != NULL)
        {
            sscanf(linha, " \"codVacina\": %d", &vacina.codVacina);
        }

        if (strstr(linha, "\"nomeVacina\"") != NULL)
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
                        strncpy(vacina.nomeVacina, inicio, sizeof(vacina.nomeVacina) - 1);
                        vacina.nomeVacina[sizeof(vacina.nomeVacina) - 1] = '\0';
                    }
                }
            }
        }

        if (strstr(linha, "\"dataValidade\"") != NULL)
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
                        strncpy(vacina.dataValidade, inicio, sizeof(vacina.dataValidade) - 1);
                        vacina.dataValidade[sizeof(vacina.dataValidade) - 1] = '\0';
                    }
                }
            }
        }

        if (strstr(linha, "\"valorVacina\"") != NULL)
        {
            sscanf(linha, " \"valorVacina\": %" SCNd64, &vacina.valorVacina);
        }

        if (strstr(linha, "\"estoqueVacina\"") != NULL)
        {
            sscanf(linha, " \"estoqueVacina\": %d", &vacina.estoqueVacina);

            if (totalVacinas < MAX_VACINAS)
            {
                vacinas[totalVacinas++] = vacina;

                if (vacina.codVacina >= proximoCodigo)
                    proximoCodigo = vacina.codVacina + 1;
            }

            vacina = (Vacina){0};
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
    for (int i = 0; i < totalVacinas; i++)
    {
        if (vacinas[i].codVacina == codigo)
            return i;
    }
    return -1;
}

/*
---------------------------------
Função Pública Validar Vacina
---------------------------------
*/
int validarVacina(int codigo, char *nome, int64_t *valorVacina)
{
    carregarVacinas();

    int indice = buscarIndice(codigo);

    if (indice == -1)
    {
        nome[0] = '\0';
        valorVacina = 0;
        return 0;
    }

    strcpy(nome, vacinas[indice].nomeVacina);
    *valorVacina = vacinas[indice].valorVacina;

    return 1;
}

/*
---------------------------------
Função Listar
---------------------------------
*/
void listarVacinas(void)
{
    carregarVacinas();

    char codigo[10];
    char valor[10];
    char estoque[10];

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
    telaEscreverCentralizado("VETCARE - VACINAS - Listagem", 0, 70, linha);
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
    telaEscrever(59, linha, "VALIDADE");
    telaEscrever(70, linha, "VALOR");
    telaEscrever(77, linha, "ESTOQUE");
    telaEscrever(largura - 1, linha, "|");

    linha++;

    telaPosicionarCursor(0, linha);
    printf("|");

    for (int i = 0; i < largura - 2; i++)
        printf("-");

    printf("|");

    linha++;

    for (int i = 0; i < totalVacinas; i++)
    {
        telaEscrever(0, linha, "|");
        snprintf(codigo, sizeof(codigo), "%d", vacinas[i].codVacina);
        snprintf(valor, sizeof(valor), "%" PRId64, vacinas[i].valorVacina);
        snprintf(estoque, sizeof(estoque), "%d", vacinas[i].estoqueVacina);

        telaEscrever(1, linha, codigo);
        telaEscrever(8, linha, vacinas[i].nomeVacina);
        telaEscrever(59, linha, vacinas[i].dataValidade);
        telaEscrever(70, linha, valor);
        telaEscrever(77, linha, estoque);

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
    printf("%d", totalVacinas);
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
