#include <stdio.h>
#include <string.h>
#include "tutor.h"
#include "tela.h"

#define ARQUIVO_TUTORES "C:\\VetCare\\Dados\\Tutor.json"

static Tutor tutores[MAX_TUTORES];
static int totalTutores = 0;
static int proximoCodigo = 1;

/*
---------------------------------
 Função SALVAR
---------------------------------
*/
static void salvarTutores(void)
{
    FILE *arquivo = fopen(ARQUIVO_TUTORES, "w");

    if (arquivo == NULL)
    {
        telaEscrever(5, 18, "Erro ao abrir o arquivo JSON!");
        getchar();
        return;
    }

    fprintf(arquivo, "[\n");

    for (int i = 0; i < totalTutores; i++)
    {
        fprintf(arquivo,
                "    {\n"
                "        \"codTutor\": %d,\n"
                "        \"nomeTutor\": \"%s\"\n"
                "    }%s\n",
                tutores[i].codTutor,
                tutores[i].nomeTutor,
                i < totalTutores - 1 ? "," : "");
    }

    fprintf(arquivo, "]\n");
    fclose(arquivo);
}

/*
---------------------------------
Função Listar
---------------------------------
*/
static void listarTutores(void)
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
    telaEscrever(5, linha, "VETCARE - MANUTENCAO DE TUTORES - Listagem");
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
    telaEscrever(8, linha, "TUTOR");
    telaEscrever(largura - 1, linha, "|");

    linha++;

    telaPosicionarCursor(0, linha);
    printf("|");

    for (int i = 0; i < largura - 2; i++)
        printf("-");

    printf("|");

    linha++;

    for (int i = 0; i < totalTutores; i++)
    {
        telaEscrever(0, linha, "|");
        snprintf(codigo, sizeof(codigo), "%d", tutores[i].codTutor);
        
        telaEscrever(5, linha, codigo);
        telaEscrever(8, linha, tutores[i].nomeTutor);

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
    telaEscrever(1,linha,"Total: ");
    printf("%d", totalTutores);
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
    for (int i = 0; i < totalTutores; i++)
    {
        if (tutores[i].codTutor == codigo)
            return i;
    }
    return -1;
}

/*
---------------------------------
Função Excluir
---------------------------------
*/
static void excluirTutor(void)
{
    telaLimpar();
    telaDesenharBox(2, 1, 70, 20);
    telaEscrever(5, 3, "VETCARE - MANUTENCAO DE TUTORES - Exclusao");

    int codigo = 0;
    telaEscrever(5, 5, "Codigo do Tutor: ");
    scanf("%d", &codigo);

    int indice = buscarIndice(codigo);

    if (indice == -1)
    {
        telaEscrever(5, 18, "Tutor nao encontrado!");
        getchar();
        getchar();
        return;
    }

    telaEscrever(5, 17, "Confirma ");
    printf("excluir %s? (S/N): ", tutores[indice].nomeTutor);

    char resposta[1];
    scanf("%s", resposta);

    if (resposta[0] != 'S' && resposta[0] != 's')
        return;

    for (int i = indice; i < totalTutores - 1; i++)
        tutores[i] = tutores[i + 1];

    totalTutores--;

    salvarTutores();

    telaEscrever(5, 18, "Tutor excluido!");
    getchar();
    getchar();
}

/*
---------------------------------
Função Alterar
---------------------------------
*/
static void alterarTutor(void)
{
    telaLimpar();
    telaDesenharBox(2, 1, 70, 20);
    telaEscrever(5, 3, "VETCARE - MANUTENCAO DE TUTORES - Alteracao");

    int codigo = 0;
    telaEscrever(5, 5, "Codigo do Tutor: ");
    scanf("%d", &codigo);

    int indice = buscarIndice(codigo);

    if (indice == -1)
    {
        telaEscrever(5, 18, "Tutor nao encontrado!");
        getchar();
        return;
    }

    telaEscrever(5, 6, "Nome atual: ");
    printf("%s", tutores[indice].nomeTutor);

    char novoNome[50];
    telaEscrever(5, 7, "Novo nome: ");
    scanf(" %49[^\n]", novoNome);

    strcpy(tutores[indice].nomeTutor, novoNome);
    salvarTutores();

    telaEscrever(5, 18, "Tutor alterado!");
    getchar();
    getchar();
}

/*
---------------------------------
 Função INCLUIR
---------------------------------
*/
static void incluirTutor(void)
{
    telaLimpar();
    telaDesenharBox(2, 1, 70, 20);
    telaEscrever(5, 3, "VETCARE - MANUTENCAO DE TUTORES - Inclusao");

    if (totalTutores >= MAX_TUTORES)
    {
        telaEscrever(5, 18, "Limite de tutores atingido!");
        getchar();
        return;
    }

    Tutor nova = {0};
    nova.codTutor = proximoCodigo;

    telaEscrever(5, 5, "Codigo do Tutor: ");
    printf("%d", nova.codTutor);

    char nome[50];
    telaEscrever(5, 6, "Nome do Tutor: ");
    scanf(" %49[^\n]", nome);

    strcpy(nova.nomeTutor, nome);

    tutores[totalTutores++] = nova;
    proximoCodigo++;

    salvarTutores();

    telaEscrever(5, 18, "Tutor cadastrado!");
    getchar();
    getchar();
}

/*
---------------------------------
Função Carregar
---------------------------------
*/
static void carregarTutores(void)
{
    FILE *arquivo = fopen(ARQUIVO_TUTORES, "r");

    totalTutores = 0;
    proximoCodigo = 1;

    if (arquivo == NULL)
        return;

    char linha[200];
    Tutor tutor = {0};

    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        if (strstr(linha, "\"codTutor\"") != NULL)
        {
            sscanf(linha, " \"codTutor\": %d", &tutor.codTutor);
        }

        if (strstr(linha, "\"nomeTutor\"") != NULL)
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
                        strncpy(tutor.nomeTutor, inicio, sizeof(tutor.nomeTutor) - 1);
                        tutor.nomeTutor[sizeof(tutor.nomeTutor) - 1] = '\0';
                    }
                }
            }

            if (totalTutores < MAX_TUTORES)
            {
                tutores[totalTutores++] = tutor;

                if (tutor.codTutor >= proximoCodigo)
                    proximoCodigo = tutor.codTutor + 1;
            }

            tutor = (Tutor){0};
        }
    }

    fclose(arquivo);
}

/*
---------------------------------
Função Pública Validar Tutor
---------------------------------
*/
int validarTutor(int codigo, char *nome)
{
    carregarTutores();

    int indice = buscarIndice(codigo);

    if (indice == -1)
    {
        nome[0] = '\0';
        return 0;
    }

    strcpy(nome, tutores[indice].nomeTutor);

    return 1;
}

/*
---------------------------------
 Função Menu
---------------------------------
*/
void menuTutores(void)
{
    carregarTutores();

    int opcao;

    do
    {
        telaLimpar();
        telaDesenharBox(0, 0, 80, 24);
        telaEscreverCentralizado("MANUTENCAO TUTOR", 0, 80, 3);

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
            incluirTutor();
            break;

        case 2:
            alterarTutor();
            break;

        case 3:
            excluirTutor();
            break;

        case 4:
            listarTutores();
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
