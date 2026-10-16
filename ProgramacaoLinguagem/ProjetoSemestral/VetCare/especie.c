#include <stdio.h>
#include <string.h>
#include "especie.h"
#include "tela.h"

#define ARQUIVO_ESPECIES "Especie.json"

static Especie especies[MAX_ESPECIES];
static int totalEspecies = 0;
static int proximoCodigo = 1;

static int lerOpcao(void)
{
    char linha[30];
    int opcao;
    char extra;

    if (fgets(linha, sizeof(linha), stdin) == NULL)
        return -1;

    if (sscanf(linha, " %d %c", &opcao, &extra) != 1)
        return -1;

    return opcao;
}

static void salvarEspecies(void)
{
    FILE *arquivo = fopen(ARQUIVO_ESPECIES, "w");

    if (arquivo == NULL)
    {
        printf("\nErro ao abrir o arquivo JSON!\n");
        return;
    }

    fprintf(arquivo, "[\n");

    for (int i = 0; i < totalEspecies; i++)
    {
        fprintf(arquivo,
                "    {\n"
                "        \"codEspecie\": %d,\n"
                "        \"nomeEspecie\": \"%s\"\n"
                "    }%s\n",
                especies[i].codEspecie,
                especies[i].nomeEspecie,
                i < totalEspecies - 1 ? "," : "");
    }

    fprintf(arquivo, "]\n");
    fclose(arquivo);
}

static void carregarEspecies(void)
{
    FILE *arquivo = fopen(ARQUIVO_ESPECIES, "r");

    totalEspecies = 0;
    proximoCodigo = 1;

    if (arquivo == NULL)
        return;

    char linha[200];
    Especie especie = {0};

    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        if (strstr(linha, "\"codEspecie\"") != NULL)
        {
            sscanf(linha, " \"codEspecie\": %d", &especie.codEspecie);
        }

        if (strstr(linha, "\"nomeEspecie\"") != NULL)
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
                        strncpy(especie.nomeEspecie, inicio, sizeof(especie.nomeEspecie) - 1);
                        especie.nomeEspecie[sizeof(especie.nomeEspecie) - 1] = '\0';
                    }
                }
            }

            if (totalEspecies < MAX_ESPECIES)
            {
                especies[totalEspecies++] = especie;

                if (especie.codEspecie >= proximoCodigo)
                    proximoCodigo = especie.codEspecie + 1;
            }

            especie = (Especie){0};
        }
    }

    fclose(arquivo);
}

static int buscarIndice(int codigo)
{
    for (int i = 0; i < totalEspecies; i++)
    {
        if (especies[i].codEspecie == codigo)
            return i;
    }

    return -1;
}

static void incluirEspecie(void)
{
    if (totalEspecies >= MAX_ESPECIES)
    {
        printf("\nLimite de especies atingido!\n");
        return;
    }

    Especie nova = {0};

    nova.codEspecie = proximoCodigo;

    telaLimpar();

    telaDesenharBox(2, 1, 70, 20);

    telaEscrever(5, 3, "VETCARE - CADASTRO DE ESPECIES - Inclusão");

    telaEscrever(5, 5, "Código da Especie: ");
    printf("%d",nova.codEspecie);

    telaEscrever(5, 6, "Nome da Especie: ");
    scanf("%s", nova.nomeEspecie);

    if (strlen(nova.nomeEspecie) == 0)
    {
        printf("\nNome nao pode ser vazio!\n");
        return;
    }

    especies[totalEspecies++] = nova;
    proximoCodigo++;

    salvarEspecies();

    printf("\nEspecie cadastrada!\n");
}

static void listarEspecies(void)
{
    printf("\nCODIGO   ESPECIE\n");
    printf("-------------------------------\n");

    for (int i = 0; i < totalEspecies; i++)
    {
        printf("%-8d %s\n",
               especies[i].codEspecie,
               especies[i].nomeEspecie);
    }

    printf("\nTotal: %d\n", totalEspecies);
}

static void alterarEspecie(void)
{
    printf("\nCodigo da especie: ");
    int codigo = lerOpcao();

    int indice = buscarIndice(codigo);

    if (indice == -1)
    {
        printf("\nEspecie nao encontrada!\n");
        return;
    }

    printf("Nome atual: %s\n", especies[indice].nomeEspecie);
    printf("Novo nome: ");

    char novoNome[50];

    if (fgets(novoNome, sizeof(novoNome), stdin) == NULL)
        return;

    novoNome[strcspn(novoNome, "\n")] = '\0';

    if (strlen(novoNome) == 0)
    {
        printf("\nNome nao pode ser vazio!\n");
        return;
    }

    strcpy(especies[indice].nomeEspecie, novoNome);

    salvarEspecies();

    printf("\nEspecie alterada!\n");
}

static void excluirEspecie(void)
{
    printf("\nCodigo da especie: ");
    int codigo = lerOpcao();

    int indice = buscarIndice(codigo);

    if (indice == -1)
    {
        printf("\nEspecie nao encontrada!\n");
        return;
    }

    printf("Excluir %s? (S/N): ",
           especies[indice].nomeEspecie);

    char resposta[10];

    if (fgets(resposta, sizeof(resposta), stdin) == NULL)
        return;

    if (resposta[0] != 'S' && resposta[0] != 's')
        return;

    for (int i = indice; i < totalEspecies - 1; i++)
        especies[i] = especies[i + 1];

    totalEspecies--;

    salvarEspecies();

    printf("\nEspecie excluida!\n");
}

void menuEspecies(void)
{
    carregarEspecies();

    int opcao;

    do
    {
        telaLimpar();

        telaDesenharBox(2, 1, 70, 20);

        telaEscrever(5, 3, "VETCARE - CADASTRO DE ESPECIES");

        telaEscrever(5, 5, "1 - Incluir Especie");
        telaEscrever(5, 6, "2 - Listar Especies");
        telaEscrever(5, 7, "3 - Alterar Especie");
        telaEscrever(5, 8, "4 - Excluir Especie");
        telaEscrever(5, 10, "0 - Voltar");

        telaEscrever(5, 13, "Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            incluirEspecie();
            break;

        case 2:
            listarEspecies();
            break;

        case 3:
            alterarEspecie();
            break;

        case 4:
            excluirEspecie();
            break;

        case 0:
            break;

        default:
            telaEscrever(5, 15, "Opcao invalida!");
            break;
        }

    } while (opcao != 0);
}
