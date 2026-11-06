#include <stdio.h>
#include <string.h>
#include "raca.h"
#include "tela.h"

#define ARQUIVO_RACAS "C:\\VetCare\\Dados\\Raca.json"

static Raca racas[MAX_RACAS];
static int totalRacas = 0;
static int proximoCodigo = 1;

/*
---------------------------------
 Função SALVAR
---------------------------------
*/
static void salvarRacas(void)
{
    FILE *arquivo = fopen(ARQUIVO_RACAS, "w");

    if (arquivo == NULL)
    {
        telaEscreverCentralizado("Erro ao abrir o arquivo JSON!", 0, 50, 22);
        getchar();
        return;
    }

    fprintf(arquivo, "[\n");

    for (int i = 0; i < totalRacas; i++)
    {
        fprintf(arquivo,
                "    {\n"
                "        \"codRaca\": %d,\n"
                "        \"nomeRaca\": \"%s\"\n"
                "    }%s\n",
                racas[i].codRaca,
                racas[i].nomeRaca,
                i < totalRacas - 1 ? "," : "");
    }

    fprintf(arquivo, "]\n");
    fclose(arquivo);
}

/*
---------------------------------
Função Listar
---------------------------------
*/
static void listarRacas(void)
{
    char codigo[10];

    int linha = 2;
    int largura = 70;

    telaLimpar();

    telaPosicionarCursor(0, linha);
    printf("+");

    for (int i = 0; i < largura - 2; i++)
        printf("=");

    printf("+");

    linha++;

    telaEscrever(0, linha, "|");
    telaEscreverCentralizado("VETCARE - MANUTENCAO DE RACAS - Listagem", 0, 70, linha);
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
    telaEscrever(8, linha, "RACA");
    telaEscrever(largura - 1, linha, "|");

    linha++;

    telaPosicionarCursor(0, linha);
    printf("|");

    for (int i = 0; i < largura - 2; i++)
        printf("-");

    printf("|");

    linha++;

    for (int i = 0; i < totalRacas; i++)
    {
        telaEscrever(0, linha, "|");
        snprintf(codigo, sizeof(codigo), "%d", racas[i].codRaca);

        telaEscrever(1, linha, codigo);
        telaEscrever(7, linha, racas[i].nomeRaca);

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
    printf("%d", totalRacas);
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

/*
---------------------------------
Função Buscar Indice
---------------------------------
*/
static int buscarIndice(int codigo)
{
    for (int i = 0; i < totalRacas; i++)
    {
        if (racas[i].codRaca == codigo)
            return i;
    }
    return -1;
}

/*
---------------------------------
Função Excluir
---------------------------------
*/
static void excluirRaca(void)
{
    int codigo = 0;
    int indice = 0;
    char resposta[1];
    char mensagem[80];

    telaLimpar();
    telaDesenharBox(0, 0, 80, 24);
    telaEscreverCentralizado("MANUTENCAO DE RACAS - Exclusao", 0, 80, 3);

    telaEscrever(10, 10, "Codigo da Raca: ");
    scanf("%d", &codigo);

    indice = buscarIndice(codigo);

    if (indice == -1)
    {
        telaEscreverCentralizado("Raca nao encontrada!", 0, 80, 22);
        getchar();
        getchar();
        return;
    }

    snprintf(mensagem, sizeof(mensagem), "Confirma excluir [%s]?", racas[indice].nomeRaca);

    telaEscreverCentralizado(mensagem, 0, 80, 22);
    scanf("%s", resposta);

    if (resposta[0] != 'S' && resposta[0] != 's')
        return;

    for (int i = indice; i < totalRacas - 1; i++)
        racas[i] = racas[i + 1];

    totalRacas--;

    salvarRacas();

    telaEscreverCentralizado("Raca excluida!", 0, 80, 22);
    getchar();
    getchar();
}

/*
---------------------------------
Função Alterar
---------------------------------
*/
static void alterarRaca(void)
{
    int codigo = 0;
    int indice = 0;
    char novoNome[50];

    telaLimpar();
    telaDesenharBox(0, 0, 80, 24);
    telaEscreverCentralizado("MANUTENCAO DE RACAS - Alteracao", 0, 80, 3);

    telaEscrever(10, 10, "Codigo da Raca...: ");
    telaEscrever(10, 11, "Nome atual.......: ");
    telaEscrever(10, 12, "Novo nome........: ");

    telaEscrever(10, 10, "Codigo da Raca...: ");
    scanf("%d", &codigo);

    indice = buscarIndice(codigo);

    if (indice == -1)
    {
        telaEscreverCentralizado("Raca nao encontrada!", 0, 80, 22);
        getchar();
        return;
    }

    telaEscrever(10, 11, "Nome atual.......: ");
    printf("%s", racas[indice].nomeRaca);

    telaEscrever(10, 12, "Novo nome........: ");
    scanf(" %49[^\n]", novoNome);

    strcpy(racas[indice].nomeRaca, novoNome);
    salvarRacas();

    telaEscreverCentralizado("Raca alterada!", 0, 80, 22);
    getchar();
    getchar();
}

/*
---------------------------------
 Função INCLUIR
---------------------------------
*/
static void incluirRaca(void)
{
    Raca nova = {0};
    nova.codRaca = proximoCodigo;
    char nome[50];

    telaLimpar();
    telaDesenharBox(0, 0, 80, 24);
    telaEscreverCentralizado("MANUTENCAO DE RACAS - Alteracao", 0, 80, 3);

    if (totalRacas >= MAX_RACAS)
    {
        telaEscreverCentralizado("Limite de racas atingido!", 0, 80, 22);
        getchar();
        return;
    }

    telaEscrever(10, 10, "Codigo da Raca: ");
    telaEscrever(10, 11, "Nome da Raca  : ");

    telaEscrever(10, 10, "Codigo da Raca: ");
    printf("%d", nova.codRaca);

    telaEscrever(10, 11, "Nome da Raca  : ");
    scanf(" %49[^\n]", nome);

    strcpy(nova.nomeRaca, nome);

    racas[totalRacas++] = nova;
    proximoCodigo++;

    salvarRacas();

    telaEscreverCentralizado("Raca cadastrada!", 0, 80, 22);
    getchar();
    getchar();
}

/*
---------------------------------
Função Carregar
---------------------------------
*/
static void carregarRacas(void)
{
    FILE *arquivo = fopen(ARQUIVO_RACAS, "r");

    totalRacas = 0;
    proximoCodigo = 1;

    if (arquivo == NULL)
        return;

    char linha[200];
    Raca raca = {0};

    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        if (strstr(linha, "\"codRaca\"") != NULL)
        {
            sscanf(linha, " \"codRaca\": %d", &raca.codRaca);
        }

        if (strstr(linha, "\"nomeRaca\"") != NULL)
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
                        strncpy(raca.nomeRaca, inicio, sizeof(raca.nomeRaca) - 1);
                        raca.nomeRaca[sizeof(raca.nomeRaca) - 1] = '\0';
                    }
                }
            }

            if (totalRacas < MAX_RACAS)
            {
                racas[totalRacas++] = raca;

                if (raca.codRaca >= proximoCodigo)
                    proximoCodigo = raca.codRaca + 1;
            }

            raca = (Raca){0};
        }
    }

    fclose(arquivo);
}

/*
---------------------------------
Função Pública Validar Raça
---------------------------------
*/
int validarRaca(int codigo, char *nome)
{
    carregarRacas();

    int indice = buscarIndice(codigo);

    if (indice == -1)
    {
        nome[0] = '\0';
        return 0;
    }

    strcpy(nome, racas[indice].nomeRaca);

    return 1;
}

/*
---------------------------------
 Função Menu
---------------------------------
*/
void menuRacas(void)
{
    carregarRacas();

    int opcao;

    do
    {
        telaLimpar();
        telaDesenharBox(0, 0, 80, 24);
        telaEscreverCentralizado("MANUTENCAO RACA", 0, 80, 3);

        telaEscreverCentralizado("1 - Incluir", 0, 80, 5);
        telaEscreverCentralizado("2 - Alterar", 0, 80, 6);
        telaEscreverCentralizado("3 - Excluir", 0, 80, 7);
        telaEscreverCentralizado("4 - Listar ", 0, 80, 8);
        telaEscreverCentralizado("0 - Voltar ", 0, 80, 9);

        telaEscreverCentralizado("Escolha uma opcao: ", 0, 80, 16);
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            incluirRaca();
            break;

        case 2:
            alterarRaca();
            break;

        case 3:
            excluirRaca();
            break;

        case 4:
            listarRacas();
            break;

        case 0:
            break;

        default:
            telaEscreverCentralizado("Opcao Invalida.", 0, 80, 22);
            getchar();
            getchar();
            break;
        }

    } while (opcao != 0);
}
