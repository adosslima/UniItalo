#include <stdio.h>
#include <string.h>
#include "especie.h"
#include "tela.h"

#define ARQUIVO_ESPECIES "C:\\VetCare\\Dados\\Especie.json"

static Especie especies[MAX_ESPECIES];
static int totalEspecies = 0;
static int proximoCodigo = 1;

/*
---------------------------------
 Função SALVAR
---------------------------------
*/
static void salvarEspecies(void)
{
    FILE *arquivo = fopen(ARQUIVO_ESPECIES, "w");

    if (arquivo == NULL)
    {
        telaEscrever(5, 18, "Erro ao abrir o arquivo JSON!");
        getchar();
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

/*
---------------------------------
Função Listar
---------------------------------
*/
static void listarEspecies(void)
{
    char codigo[10];

    telaLimpar();
    telaDesenharBox(2, 1, 70, 20);
    telaEscrever(5, 3, "VETCARE - MANUTENCAO DE ESPECIES - Listagem");

    telaEscrever(5, 6, "CODIGO");
    telaEscrever(20, 6, "ESPECIE");
    telaEscrever(5, 7, "-------------------------------");

    for (int i = 0; i < totalEspecies; i++)
    {
        snprintf(codigo, sizeof(codigo), "%d", especies[i].codEspecie);
        
        telaEscrever(5, 8 + i, codigo);
        telaEscrever(20, 8 + i, especies[i].nomeEspecie);
    }

    telaEscrever(5,19,"Total: ");
    printf("%d", totalEspecies);

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
    for (int i = 0; i < totalEspecies; i++)
    {
        if (especies[i].codEspecie == codigo)
            return i;
    }
    return -1;
}

/*
---------------------------------
Função Excluir
---------------------------------
*/
static void excluirEspecie(void)
{
    telaLimpar();
    telaDesenharBox(2, 1, 70, 20);
    telaEscrever(5, 3, "VETCARE - MANUTENCAO DE ESPECIES - Exclusao");

    int codigo = 0;
    telaEscrever(5, 5, "Codigo da Especie: ");
    scanf("%d", &codigo);

    int indice = buscarIndice(codigo);

    if (indice == -1)
    {
        telaEscrever(5, 18, "Especie nao encontrada!");
        getchar();
        getchar();
        return;
    }

    telaEscrever(5, 17, "Confirma ");
    printf("excluir %s? (S/N): ", especies[indice].nomeEspecie);

    char resposta[1];
    scanf("%s", resposta);

    if (resposta[0] != 'S' && resposta[0] != 's')
        return;

    for (int i = indice; i < totalEspecies - 1; i++)
        especies[i] = especies[i + 1];

    totalEspecies--;

    salvarEspecies();

    telaEscrever(5, 18, "Especie excluida!");
    getchar();
    getchar();
}

/*
---------------------------------
Função Alterar
---------------------------------
*/
static void alterarEspecie(void)
{
    telaLimpar();
    telaDesenharBox(2, 1, 70, 20);
    telaEscrever(5, 3, "VETCARE - MANUTENCAO DE ESPECIES - Alteracao");

    int codigo = 0;
    telaEscrever(5, 5, "Codigo da Especie: ");
    scanf("%d", &codigo);

    int indice = buscarIndice(codigo);

    if (indice == -1)
    {
        telaEscrever(5, 18, "Especie nao encontrada!");
        getchar();
        return;
    }

    telaEscrever(5, 6, "Nome atual: ");
    printf("%s", especies[indice].nomeEspecie);

    char novoNome[50];
    telaEscrever(5, 7, "Novo nome: ");
    scanf(" %49[^\n]", novoNome);

    strcpy(especies[indice].nomeEspecie, novoNome);
    salvarEspecies();

    telaEscrever(5, 18, "Especie alterada!");
    getchar();
    getchar();
}

/*
---------------------------------
 Função INCLUIR
---------------------------------
*/
static void incluirEspecie(void)
{
    telaLimpar();
    telaDesenharBox(2, 1, 70, 20);
    telaEscrever(5, 3, "VETCARE - MANUTENCAO DE ESPECIES - Inclusao");

    if (totalEspecies >= MAX_ESPECIES)
    {
        telaEscrever(5, 18, "Limite de especies atingido!");
        getchar();
        return;
    }

    Especie nova = {0};
    nova.codEspecie = proximoCodigo;

    telaEscrever(5, 5, "Codigo da Especie: ");
    printf("%d", nova.codEspecie);

    char nome[50];
    telaEscrever(5, 6, "Nome da Especie: ");
    scanf(" %49[^\n]", nome);

    strcpy(nova.nomeEspecie, nome);

    especies[totalEspecies++] = nova;
    proximoCodigo++;

    salvarEspecies();

    telaEscrever(5, 18, "Especie cadastrada!");
    getchar();
    getchar();
}

/*
---------------------------------
Função Carregar
---------------------------------
*/
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

/*
---------------------------------
 Função Menu
---------------------------------
*/
void menuEspecies(void)
{
    carregarEspecies();

    int opcao;

    do
    {
        telaLimpar();

        telaDesenharBox(2, 1, 70, 20);

        telaEscrever(5, 3, "VETCARE - MANUTENCAO DE ESPECIES");

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
            incluirEspecie();
            break;

        case 2:
            alterarEspecie();
            break;

        case 3:
            excluirEspecie();
            break;

        case 4:
            listarEspecies();
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
