#include <stdio.h>
#include <string.h>
#include "veterinario.h"
#include "tela.h"

#define ARQUIVO_VETRINARIOS "C:\\VetCare\\Dados\\Veterinario.json"

static Veterinario veterinarios[MAX_VETERINARIOS];
static int totalVeterinarios = 0;
static int proximoCodigo = 1;

/*
---------------------------------
 Função SALVAR
---------------------------------
*/
static void salvarVeterinarios(void)
{
    FILE *arquivo = fopen(ARQUIVO_VETRINARIOS, "w");

    if (arquivo == NULL)
    {
        telaEscrever(5, 18, "Erro ao abrir o arquivo JSON!");
        getchar();
        return;
    }

    fprintf(arquivo, "[\n");

    for (int i = 0; i < totalVeterinarios; i++)
    {
        fprintf(arquivo,
                "    {\n"
                "        \"codVeterinario\": %d,\n"
                "        \"nomeVeterinario\": \"%s\"\n"
                "    }%s\n",
                veterinarios[i].codVeterinario,
                veterinarios[i].nomeVeterinario,
                i < totalVeterinarios - 1 ? "," : "");
    }

    fprintf(arquivo, "]\n");
    fclose(arquivo);
}

/*
---------------------------------
Função Listar
---------------------------------
*/
static void listarVeterinarios(void)
{
    char codigo[10];

    telaLimpar();
    telaDesenharBox(2, 1, 70, 20);
    telaEscrever(5, 3, "VETCARE - MANUTENCAO DE VETERINARIOS - Listagem");

    telaEscrever(5, 6, "CODIGO");
    telaEscrever(20, 6, "VETERINARIO");
    telaEscrever(5, 7, "-------------------------------");

    for (int i = 0; i < totalVeterinarios; i++)
    {
        snprintf(codigo, sizeof(codigo), "%d", veterinarios[i].codVeterinario);
        
        telaEscrever(5, 8 + i, codigo);
        telaEscrever(20, 8 + i, veterinarios[i].nomeVeterinario);
    }

    telaEscrever(5,19,"Total: ");
    printf("%d", totalVeterinarios);

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
    for (int i = 0; i < totalVeterinarios; i++)
    {
        if (veterinarios[i].codVeterinario == codigo)
            return i;
    }
    return -1;
}

/*
---------------------------------
Função Excluir
---------------------------------
*/
static void excluirVeterinario(void)
{
    telaLimpar();
    telaDesenharBox(2, 1, 70, 20);
    telaEscrever(5, 3, "VETCARE - MANUTENCAO DE VETERINARIOS - Exclusao");

    int codigo = 0;
    telaEscrever(5, 5, "Codigo do Veterinario: ");
    scanf("%d", &codigo);

    int indice = buscarIndice(codigo);

    if (indice == -1)
    {
        telaEscrever(5, 18, "Veterinario nao encontrado!");
        getchar();
        getchar();
        return;
    }

    telaEscrever(5, 17, "Confirma ");
    printf("excluir %s? (S/N): ", veterinarios[indice].nomeVeterinario);

    char resposta[1];
    scanf("%s", resposta);

    if (resposta[0] != 'S' && resposta[0] != 's')
        return;

    for (int i = indice; i < totalVeterinarios - 1; i++)
        veterinarios[i] = veterinarios[i + 1];

    totalVeterinarios--;

    salvarVeterinarios();

    telaEscrever(5, 18, "Veterinario excluido!");
    getchar();
    getchar();
}

/*
---------------------------------
Função Alterar
---------------------------------
*/
static void alterarVeterinario(void)
{
    telaLimpar();
    telaDesenharBox(2, 1, 70, 20);
    telaEscrever(5, 3, "VETCARE - MANUTENCAO DE VETERINARIOS - Alteracao");

    int codigo = 0;
    telaEscrever(5, 5, "Codigo do Veterinario: ");
    scanf("%d", &codigo);

    int indice = buscarIndice(codigo);

    if (indice == -1)
    {
        telaEscrever(5, 18, "Veterinario nao encontrado!");
        getchar();
        return;
    }

    telaEscrever(5, 6, "Nome atual: ");
    printf("%s", veterinarios[indice].nomeVeterinario);

    char novoNome[50];
    telaEscrever(5, 7, "Novo nome: ");
    scanf(" %49[^\n]", novoNome);

    strcpy(veterinarios[indice].nomeVeterinario, novoNome);
    salvarVeterinarios();

    telaEscrever(5, 18, "Veterinario alterado!");
    getchar();
    getchar();
}

/*
---------------------------------
 Função INCLUIR
---------------------------------
*/
static void incluirVeterinario(void)
{
    telaLimpar();
    telaDesenharBox(2, 1, 70, 20);
    telaEscrever(5, 3, "VETCARE - MANUTENCAO DE VETERINARIOS - Inclusao");

    if (totalVeterinarios >= MAX_VETERINARIOS)
    {
        telaEscrever(5, 18, "Limite de veterinarios atingido!");
        getchar();
        return;
    }

    Veterinario nova = {0};
    nova.codVeterinario = proximoCodigo;

    telaEscrever(5, 5, "Codigo do Veterinario: ");
    printf("%d", nova.codVeterinario);

    char nome[50];
    telaEscrever(5, 6, "Nome do Veterinario: ");
    scanf(" %49[^\n]", nome);

    strcpy(nova.nomeVeterinario, nome);

    veterinarios[totalVeterinarios++] = nova;
    proximoCodigo++;

    salvarVeterinarios();

    telaEscrever(5, 18, "Veterinario cadastrado!");
    getchar();
    getchar();
}

/*
---------------------------------
Função Carregar
---------------------------------
*/
static void carregarVeterinarios(void)
{
    FILE *arquivo = fopen(ARQUIVO_VETRINARIOS, "r");

    totalVeterinarios = 0;
    proximoCodigo = 1;

    if (arquivo == NULL)
        return;

    char linha[200];
    Veterinario veterinario = {0};

    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        if (strstr(linha, "\"codVeterinario\"") != NULL)
        {
            sscanf(linha, " \"codVeterinario\": %d", &veterinario.codVeterinario);
        }

        if (strstr(linha, "\"nomeVeterinario\"") != NULL)
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
                        strncpy(veterinario.nomeVeterinario, inicio, sizeof(veterinario.nomeVeterinario) - 1);
                        veterinario.nomeVeterinario[sizeof(veterinario.nomeVeterinario) - 1] = '\0';
                    }
                }
            }

            if (totalVeterinarios < MAX_VETERINARIOS)
            {
                veterinarios[totalVeterinarios++] = veterinario;

                if (veterinario.codVeterinario >= proximoCodigo)
                    proximoCodigo = veterinario.codVeterinario + 1;
            }

            veterinario = (Veterinario){0};
        }
    }

    fclose(arquivo);
}

/*
---------------------------------
 Função Menu
---------------------------------
*/
void menuVeterinarios(void)
{
    carregarVeterinarios();

    int opcao;

    do
    {
        telaLimpar();

        telaDesenharBox(2, 1, 70, 20);

        telaEscrever(5, 3, "VETCARE - MANUTENCAO DE VETERINARIOS");

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
            incluirVeterinario();
            break;

        case 2:
            alterarVeterinario();
            break;

        case 3:
            excluirVeterinario();
            break;

        case 4:
            listarVeterinarios();
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
