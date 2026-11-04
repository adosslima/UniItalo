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
        telaEscreverCentralizado("Erro ao abrir o arquivo JSON!", 0, 50, 22);
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
    telaEscrever(5, linha, "VETCARE - MANUTENCAO DE ESPECIES - Listagem");
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
    telaEscrever(8, linha, "ESPECIE");
    telaEscrever(largura - 1, linha, "|");

    linha++;

    telaPosicionarCursor(0, linha);
    printf("|");

    for (int i = 0; i < largura - 2; i++)
        printf("-");

    printf("|");

    linha++;

    for (int i = 0; i < totalEspecies; i++)
    {
        telaEscrever(0, linha, "|");
        snprintf(codigo, sizeof(codigo), "%d", especies[i].codEspecie);

        telaEscrever(1, linha, codigo);
        telaEscrever(8, linha, especies[i].nomeEspecie);

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
    printf("%d", totalEspecies);
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
    telaDesenharBox(0, 0, 80, 24);
    telaEscreverCentralizado("MANUTENCAO DE ESPECIES - Exclusao", 0, 80, 3);

    int codigo = 0;
    telaEscreverCentralizado("Codigo da Especie: ", 0, 80, 5);
    scanf("%d", &codigo);

    int indice = buscarIndice(codigo);

    if (indice == -1)
    {
        telaEscreverCentralizado("Especie nao encontrada!", 0, 80, 22);
        getchar();
        getchar();
        return;
    }

    char resposta[1];
    char mensagem[80];
    snprintf(mensagem, sizeof(mensagem), "Confrima excluir %s?", especies[indice].nomeEspecie);

    telaEscreverCentralizado(mensagem, 0, 80, 22);
    scanf("%s", resposta);

    if (resposta[0] != 'S' && resposta[0] != 's')
        return;

    for (int i = indice; i < totalEspecies - 1; i++)
        especies[i] = especies[i + 1];

    totalEspecies--;

    salvarEspecies();

    telaEscreverCentralizado("Especie excluida!", 0, 80, 22);
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
    telaDesenharBox(0, 0, 80, 24);
    telaEscreverCentralizado("MANUTENCAO DE ESPECIES - Alteracao", 0, 80, 3);

    telaEscreverCentralizado("Codigo da Especie: ", 0, 80, 5);
    telaEscreverCentralizado("Nome atual.......: ", 0, 80, 6);
    telaEscreverCentralizado("Novo nome........: ", 0, 80, 7);

    int codigo = 0;
    telaEscreverCentralizado("Codigo da Especie: ", 0, 80, 5);
    scanf("%d", &codigo);

    int indice = buscarIndice(codigo);

    if (indice == -1)
    {
        telaEscreverCentralizado("Especie nao encontrada!", 0, 80, 22);
        getchar();
        return;
    }

    telaEscreverCentralizado("Nome atual.......: ", 0, 80, 6);
    printf("%s", especies[indice].nomeEspecie);

    char novoNome[50];
    telaEscreverCentralizado("Novo nome........: ", 0, 80, 7);
    scanf(" %49[^\n]", novoNome);

    strcpy(especies[indice].nomeEspecie, novoNome);
    salvarEspecies();

    telaEscreverCentralizado("Especie alterada!", 0, 80, 22);
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
    telaDesenharBox(0, 0, 80, 24);
    telaEscreverCentralizado("MANUTENCAO DE ESPECIES - Alteracao", 0, 80, 3);

    if (totalEspecies >= MAX_ESPECIES)
    {
        telaEscreverCentralizado("Limite de especies atingido!", 0, 80, 22);
        getchar();
        return;
    }

    Especie nova = {0};
    nova.codEspecie = proximoCodigo;

    telaEscreverCentralizado("Codigo da Especie: ", 0, 80, 5);
    telaEscreverCentralizado("Nome da Especie  : ", 0, 80, 6);

    telaEscreverCentralizado("Codigo da Especie: ", 0, 80, 5);
    printf("%d", nova.codEspecie);

    char nome[50];
    telaEscreverCentralizado("Nome da Especie  : ", 0, 80, 6);
    scanf(" %49[^\n]", nome);

    strcpy(nova.nomeEspecie, nome);

    especies[totalEspecies++] = nova;
    proximoCodigo++;

    salvarEspecies();

    telaEscreverCentralizado("Especie cadastrada!", 0, 80, 22);
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
Função Pública Validar Espécie
---------------------------------
*/
int validarEspecie(int codigo, char *nome)
{
    carregarEspecies();

    int indice = buscarIndice(codigo);

    if (indice == -1)
    {
        nome[0] = '\0';
        return 0;
    }

    strcpy(nome, especies[indice].nomeEspecie);

    return 1;
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
        telaDesenharBox(0, 0, 80, 24);
        telaEscreverCentralizado("MANUTENCAO ESPECIE", 0, 80, 3);

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
            telaEscreverCentralizado("Opcao Invalida.", 0, 80, 22);
            getchar();
            getchar();
            break;
        }

    } while (opcao != 0);
}
