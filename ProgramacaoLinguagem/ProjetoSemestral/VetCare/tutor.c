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

    telaLimpar();
    telaDesenharBox(2, 1, 70, 20);
    telaEscrever(5, 3, "VETCARE - MANUTENCAO DE TUTORES - Listagem");

    telaEscrever(5, 6, "CODIGO");
    telaEscrever(20, 6, "TUTOR");
    telaEscrever(5, 7, "-------------------------------");

    for (int i = 0; i < totalTutores; i++)
    {
        snprintf(codigo, sizeof(codigo), "%d", tutores[i].codTutor);
        
        telaEscrever(5, 8 + i, codigo);
        telaEscrever(20, 8 + i, tutores[i].nomeTutor);
    }

    telaEscrever(5,19,"Total: ");
    printf("%d", totalTutores);

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

        telaDesenharBox(2, 1, 70, 20);

        telaEscrever(5, 3, "VETCARE - MANUTENCAO DE TUTORES");

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
            telaEscrever(5, 18, "Opcao invalida!");
            getchar();
            getchar();
            break;
        }

    } while (opcao != 0);
}
