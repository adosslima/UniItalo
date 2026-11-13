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
        telaEscreverCentralizado("Erro ao abrir o arquivo JSON!", 0, 50, 22);
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
    telaEscreverCentralizado("VETCARE - MANUTENCAO DE VETERINARIOS - Listagem", 0, 70, linha);
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
    telaEscrever(8, linha, "VETERINARIO");

    telaEscrever(largura - 1, linha, "|");

    linha++;

    telaPosicionarCursor(0, linha);
    printf("|");

    for (int i = 0; i < largura - 2; i++)
        printf("-");

    printf("|");

    linha++;

    for (int i = 0; i < totalVeterinarios; i++)
    {
        telaEscrever(0, linha, "|");
        snprintf(codigo, sizeof(codigo), "%d", veterinarios[i].codVeterinario);

        telaEscrever(5, linha, codigo);
        telaEscrever(8, linha, veterinarios[i].nomeVeterinario);

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
    printf("%d", totalVeterinarios);
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
    int codigo = 0;
    int indice = 0;
    char resposta[1];
    char mensagem[80];

    telaLimpar();
    telaDesenharBox(0, 0, 80, 24);
    telaEscreverCentralizado("MANUTENCAO DE VETERINARIOS - Exclusao", 0, 80, 3);

    telaEscrever(10, 10, "Codigo do Veterinario: ");
    scanf("%d", &codigo);

    indice = buscarIndice(codigo);

    if (indice == -1)
    {
        telaEscreverCentralizado("Veterinario nao encontrado!", 0, 80, 22);
        getchar();
        getchar();
        return;
    }

    snprintf(mensagem, sizeof(mensagem), "Confirma excluir [%s]?", veterinarios[indice].nomeVeterinario);

    telaEscreverCentralizado(mensagem, 0, 80, 22);
    scanf("%s", resposta);

    if (resposta[0] != 'S' && resposta[0] != 's')
        return;

    for (int i = indice; i < totalVeterinarios - 1; i++)
        veterinarios[i] = veterinarios[i + 1];

    totalVeterinarios--;

    salvarVeterinarios();

    telaEscreverCentralizado("Veterinario excluido!", 0, 80, 22);
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
    int codigo = 0;
    int indice = 0;
    char novoNome[50];

    telaLimpar();
    telaDesenharBox(0, 0, 80, 24);
    telaEscreverCentralizado("MANUTENCAO DE VETERINARIOS - Alteracao", 0, 80, 3);

    telaEscrever(10, 10, "Codigo do Veterinario: ");
    telaEscrever(10, 11, "Nome atual...........: ");
    telaEscrever(10, 12, "Novo nome............: ");

    telaEscrever(10, 10, "Codigo do Veterinario: ");
    scanf("%d", &codigo);

    indice = buscarIndice(codigo);

    if (indice == -1)
    {
        telaEscrever(5, 18, "Veterinario nao encontrado!");
        getchar();
        return;
    }

    telaEscrever(10, 11, "Nome atual...........: ");
    printf("%s", veterinarios[indice].nomeVeterinario);

    telaEscrever(10, 12, "Novo nome............: ");
    scanf(" %49[^\n]", novoNome);

    strcpy(veterinarios[indice].nomeVeterinario, novoNome);
    salvarVeterinarios();

    telaEscreverCentralizado("Veterinario alterado!", 0, 80, 22);
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
    Veterinario nova = {0};
    nova.codVeterinario = proximoCodigo;
    char nome[50];

    telaLimpar();
    telaDesenharBox(0, 0, 80, 24);
    telaEscreverCentralizado("MANUTENCAO DE VETERINARIOS - Alteracao", 0, 80, 3);

    if (totalVeterinarios >= MAX_VETERINARIOS)
    {
        telaEscreverCentralizado("Limite de veterinarios atingido!", 0, 80, 22);
        getchar();
        return;
    }

    telaEscrever(10, 10, "Codigo da Veterinario: ");
    telaEscrever(10, 11, "Nome da Veterinario..: ");

    telaEscrever(10, 10, "Codigo da Veterinario: ");
    printf("%d", nova.codVeterinario);

    telaEscrever(10, 11, "Nome da Veterinario..: ");
    scanf(" %49[^\n]", nome);

    strcpy(nova.nomeVeterinario, nome);

    veterinarios[totalVeterinarios++] = nova;
    proximoCodigo++;

    salvarVeterinarios();

    telaEscreverCentralizado("Veterinario cadastrado!", 0, 80, 22);
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
Função Pública Validar Veterinário
---------------------------------
*/
int validarVeterinario(int codigo, char *nome)
{
    carregarVeterinarios();

    int indice = buscarIndice(codigo);

    if (indice == -1)
    {
        nome[0] = '\0';
        return 0;
    }

    strcpy(nome, veterinarios[indice].nomeVeterinario);

    return 1;
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
        telaDesenharBox(0, 0, 80, 24);
        telaEscreverCentralizado("MANUTENCAO VETERINARIO", 0, 80, 3);

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
            telaEscreverCentralizado("Opcao Invalida!", 0, 80, 22);
            getchar();
            getchar();
            break;
        }

    } while (opcao != 0);
}
