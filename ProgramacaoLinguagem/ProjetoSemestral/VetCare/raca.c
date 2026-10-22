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
        telaEscrever(5, 18, "Erro ao abrir o arquivo JSON!");
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

    telaLimpar();
    telaDesenharBox(2, 1, 70, 20);
    telaEscrever(5, 3, "VETCARE - MANUTENCAO DE RACAS - Listagem");

    telaEscrever(5, 6, "CODIGO");
    telaEscrever(20, 6, "RACA");
    telaEscrever(5, 7, "-------------------------------");

    for (int i = 0; i < totalRacas; i++)
    {
        snprintf(codigo, sizeof(codigo), "%d", racas[i].codRaca);

        telaEscrever(5, 8 + i, codigo);
        telaEscrever(20, 8 + i, racas[i].nomeRaca);
    }

    telaEscrever(5, 19, "Total: ");
    printf("%d", totalRacas);

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
    telaLimpar();
    telaDesenharBox(2, 1, 70, 20);
    telaEscrever(5, 3, "VETCARE - MANUTENCAO DE RACAS - Exclusao");

    int codigo = 0;
    telaEscrever(5, 5, "Codigo da Raca: ");
    scanf("%d", &codigo);

    int indice = buscarIndice(codigo);

    if (indice == -1)
    {
        telaEscrever(5, 18, "Raca nao encontrada!");
        getchar();
        getchar();
        return;
    }

    telaEscrever(5, 17, "Confirma ");
    printf("excluir %s? (S/N): ", racas[indice].nomeRaca);

    char resposta[1];
    scanf("%s", resposta);

    if (resposta[0] != 'S' && resposta[0] != 's')
        return;

    for (int i = indice; i < totalRacas - 1; i++)
        racas[i] = racas[i + 1];

    totalRacas--;

    salvarRacas();

    telaEscrever(5, 18, "Raca excluida!");
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
    telaLimpar();
    telaDesenharBox(2, 1, 70, 20);
    telaEscrever(5, 3, "VETCARE - MANUTENCAO DE RACAS - Alteracao");

    int codigo = 0;
    telaEscrever(5, 5, "Codigo da Raca: ");
    scanf("%d", &codigo);

    int indice = buscarIndice(codigo);

    if (indice == -1)
    {
        telaEscrever(5, 18, "Raca nao encontrada!");
        getchar();
        return;
    }

    telaEscrever(5, 6, "Nome atual: ");
    printf("%s", racas[indice].nomeRaca);

    char novoNome[50];
    telaEscrever(5, 7, "Novo nome: ");
    scanf(" %49[^\n]", novoNome);

    strcpy(racas[indice].nomeRaca, novoNome);
    salvarRacas();

    telaEscrever(5, 18, "Raca alterada!");
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
    telaLimpar();
    telaDesenharBox(2, 1, 70, 20);
    telaEscrever(5, 3, "VETCARE - MANUTENCAO DE RACAS - Inclusao");

    if (totalRacas >= MAX_RACAS)
    {
        telaEscrever(5, 18, "Limite de racas atingido!");
        getchar();
        return;
    }

    Raca nova = {0};
    nova.codRaca = proximoCodigo;

    telaEscrever(5, 5, "Codigo da Raca: ");
    printf("%d", nova.codRaca);

    char nome[50];
    telaEscrever(5, 6, "Nome da Raca: ");
    scanf(" %49[^\n]", nome);

    strcpy(nova.nomeRaca, nome);

    racas[totalRacas++] = nova;
    proximoCodigo++;

    salvarRacas();

    telaEscrever(5, 18, "Raca cadastrada!");
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

        telaDesenharBox(2, 1, 70, 20);

        telaEscrever(5, 3, "VETCARE - MANUTENCAO DE RACAS");

        telaEscrever(5, 5, "1 - Incluir");
        telaEscrever(5, 6, "2 - Alterar");
        telaEscrever(5, 7, "3 - Excluir");
        telaEscrever(5, 8, "4 - Listar");
        telaEscrever(5, 10, "0 - Voltar");

        telaEscrever(5, 16, "Escolha uma opcao: ");
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
            telaEscrever(5, 18, "Opcao invalida!");
            getchar();
            getchar();
            break;
        }

    } while (opcao != 0);
}
