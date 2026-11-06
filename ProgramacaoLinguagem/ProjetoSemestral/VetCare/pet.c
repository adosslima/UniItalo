#include <stdio.h>
#include <string.h>
#include "data.h"
#include "pet.h"
#include "tela.h"
#include "tutor.h"
#include "especie.h"
#include "raca.h"

#define ARQUIVO_PETS "C:\\VetCare\\Dados\\Pet.json"

static Pet pets[MAX_PETS];
static int totalPets = 0;
static int proximoCodigo = 1;

/*
---------------------------------
 Função SALVAR
---------------------------------
*/
static void salvarPets(void)
{
    FILE *arquivo = fopen(ARQUIVO_PETS, "w");

    if (arquivo == NULL)
    {
        telaEscreverCentralizado("Erro ao abrir o arquivo JSON!", 0, 50, 22);
        getchar();
        return;
    }

    fprintf(arquivo, "[\n");

    for (int i = 0; i < totalPets; i++)
    {
        fprintf(arquivo,
                "    {\n"
                "        \"codPet\": %d,\n"
                "        \"codTutor\": %d,\n"
                "        \"codEspecie\": %d,\n"
                "        \"codRaca\": %d,\n"
                "        \"nomePet\": \"%s\",\n"
                "        \"dataNascimento\": \"%s\"\n"
                "    }%s\n",
                pets[i].codPet,
                pets[i].codTutor,
                pets[i].codEspecie,
                pets[i].codRaca,
                pets[i].nomePet,
                pets[i].dataNascimento,
                i < totalPets - 1 ? "," : "");
    }

    fprintf(arquivo, "]\n");
    fclose(arquivo);
}

/*
---------------------------------
Função Buscar Indice
---------------------------------
*/
static int buscarIndice(int codigo)
{
    for (int i = 0; i < totalPets; i++)
    {
        if (pets[i].codPet == codigo)
            return i;
    }
    return -1;
}

/*
---------------------------------
Função Excluir
---------------------------------
*/
static void excluirPet(void)
{
    int codigo = 0;
    int indice = 0;
    char resposta[1];
    char mensagem[80];

    telaLimpar();
    telaDesenharBox(0, 0, 80, 24);
    telaEscreverCentralizado("MANUTENCAO DE PETS - Exclusao", 0, 80, 3);

    telaEscrever(10, 10, "Codigo do Pet: ");
    scanf("%d", &codigo);

    indice = buscarIndice(codigo);

    if (indice == -1)
    {
        telaEscreverCentralizado("Pet nao encontrado!", 0, 80, 22);
        getchar();
        getchar();
        return;
    }

    snprintf(mensagem, sizeof(mensagem), "Confirma excluir [%s]?", pets[indice].nomePet);

    telaEscreverCentralizado(mensagem, 0, 80, 22);
    scanf("%s", resposta);

    if (resposta[0] != 'S' && resposta[0] != 's')
        return;

    for (int i = indice; i < totalPets - 1; i++)
        pets[i] = pets[i + 1];

    totalPets--;

    salvarPets();

    telaEscreverCentralizado("Pet excluido!", 0, 80, 22);
    getchar();
    getchar();
}

/*
---------------------------------
 Função INCLUIR
---------------------------------
*/
static void incluirPet(void)
{
    Pet nova = {0};
    nova.codPet = proximoCodigo;
    Data nascimento = {0};
    char nome[50];
    char nomeValido[50] = {0};
    int erro = 0;

    telaLimpar();
    telaDesenharBox(0, 0, 80, 24);
    telaEscreverCentralizado("MANUTENCAO DE PETS - Inclusao", 0, 80, 3);

    if (totalPets >= MAX_PETS)
    {
        telaEscreverCentralizado("Limite de pets atingido!", 0, 80, 22);
        getchar();
        return;
    }

    telaEscrever(5, 6, "Codigo do Pet..................: ");
    telaEscrever(5, 7, "Codigo do Tutor................: ");
    telaEscrever(5, 8, "Codigo da Especie..............: ");
    telaEscrever(5, 9, "Codigo do Raca.................: ");
    telaEscrever(5, 10, "Nome do Pet....................: ");
    telaEscrever(5, 11, "Data de nascimento (AAAA-MM-DD): ");

    telaEscrever(5, 6, "Codigo do Pet..................: ");
    printf("%d", nova.codPet);

    do
    {
        nova.codTutor = 0;

        telaEscrever(5, 7, "Codigo do Tutor................: ");
        scanf("%d", &nova.codTutor);
    } while (validarTutor(nova.codTutor, nomeValido) == 0);

    telaEscrever(42, 7, nomeValido);

    do
    {
        nova.codEspecie = 0;

        telaEscrever(5, 8, "Codigo da Especie..............: ");
        scanf("%d", &nova.codEspecie);
    } while (validarEspecie(nova.codEspecie, nomeValido) == 0);

    telaEscrever(42, 8, nomeValido);

    do
    {
        nova.codRaca = 0;

        telaEscrever(5, 9, "Codigo do Raca.................: ");
        scanf("%d", &nova.codRaca);
    } while (validarRaca(nova.codRaca, nomeValido) == 0);

    telaEscrever(42, 9, nomeValido);

    telaEscrever(5, 10, "Nome do Pet....................: ");
    scanf(" %49[^\n]", nome);

    strcpy(nova.nomePet, nome);

    do
    {
        telaEscrever(5, 11, "Data de nascimento (AAAA-MM-DD): ");

        if (scanf("%d-%d-%d",
                  &nascimento.ano,
                  &nascimento.mes,
                  &nascimento.dia) != 3)
        {
            telaEscreverCentralizado("Formato de data invalido!", 0, 80, 22);
            getchar();
            getchar();

            erro = 1;
        }
        else
        {
            erro = 0;
        }
    } while (erro == 1);

    snprintf(
        nova.dataNascimento,
        sizeof(nova.dataNascimento),
        "%04d-%02d-%02d",
        nascimento.ano,
        nascimento.mes,
        nascimento.dia);

    pets[totalPets++] = nova;
    proximoCodigo++;

    salvarPets();

    telaEscreverCentralizado("Pet cadastrado!", 0, 80, 22);
    getchar();
    getchar();
}

/*
---------------------------------
Função Carregar
---------------------------------
*/
static void carregarPets(void)
{
    FILE *arquivo = fopen(ARQUIVO_PETS, "r");

    totalPets = 0;
    proximoCodigo = 1;

    if (arquivo == NULL)
        return;

    char linha[200];
    Pet pet = {0};

    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        if (strstr(linha, "\"codPet\"") != NULL)
        {
            sscanf(linha, " \"codPet\": %d", &pet.codPet);
        }

        if (strstr(linha, "\"codTutor\"") != NULL)
        {
            sscanf(linha, " \"codTutor\": %d", &pet.codTutor);
        }

        if (strstr(linha, "\"codEspecie\"") != NULL)
        {
            sscanf(linha, " \"codEspecie\": %d", &pet.codEspecie);
        }

        if (strstr(linha, "\"codRaca\"") != NULL)
        {
            sscanf(linha, " \"codRaca\": %d", &pet.codRaca);
        }

        if (strstr(linha, "\"nomePet\"") != NULL)
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
                        strncpy(pet.nomePet, inicio, sizeof(pet.nomePet) - 1);
                        pet.nomePet[sizeof(pet.nomePet) - 1] = '\0';
                    }
                }
            }
        }

        if (strstr(linha, "\"dataNascimento\"") != NULL)
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
                        strncpy(pet.dataNascimento, inicio, sizeof(pet.dataNascimento) - 1);
                        pet.dataNascimento[sizeof(pet.dataNascimento) - 1] = '\0';
                    }
                }
            }

            if (totalPets < MAX_PETS)
            {
                pets[totalPets++] = pet;

                if (pet.codPet >= proximoCodigo)
                    proximoCodigo = pet.codPet + 1;
            }

            pet = (Pet){0};
        }
    }

    fclose(arquivo);
}

/*
---------------------------------
Função Listar
---------------------------------
*/
void listarPets(void)
{
    carregarPets();

    char codigo[10];

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
    telaEscreverCentralizado("VETCARE - MANUTENCAO DE PETS - Listagem", 0, 70, linha);
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
    telaEscrever(29, linha, "ESPECIE");
    telaEscrever(50, linha, "RACA");
    telaEscrever(71, linha, "TUTOR");
    telaEscrever(largura - 1, linha, "|");

    linha++;

    telaPosicionarCursor(0, linha);
    printf("|");

    for (int i = 0; i < largura - 2; i++)
        printf("-");

    printf("|");

    linha++;

    char nomeValido[50];
    char nome[50];

    for (int i = 0; i < totalPets; i++)
    {
        telaEscrever(0, linha, "|");
        snprintf(codigo, sizeof(codigo), "%d", pets[i].codPet);

        telaEscrever(1, linha, codigo);
        telaEscrever(8, linha, pets[i].nomePet);

        validarEspecie(pets[i].codEspecie, nomeValido);
        strncpy(nome, nomeValido, 20);
        telaEscrever(29, linha, nome);

        validarRaca(pets[i].codRaca, nomeValido);
        strncpy(nome, nomeValido, 20);
        telaEscrever(50, linha, nome);

        validarTutor(pets[i].codTutor, nomeValido);
        strncpy(nome, nomeValido, 20);
        telaEscrever(71, linha, nome);

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
    printf("%d", totalPets);
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
 Função Menu
---------------------------------
*/
void menuPets(void)
{
    carregarPets();

    int opcao;

    do
    {
        telaLimpar();
        telaDesenharBox(0, 0, 80, 24);
        telaEscreverCentralizado("MANUTENCAO PET", 0, 80, 3);

        telaEscreverCentralizado("1 - Incluir", 0, 80, 5);
        telaEscreverCentralizado("2 - Excluir", 0, 80, 6);
        telaEscreverCentralizado("3 - Listar ", 0, 80, 7);
        telaEscreverCentralizado("0 - Voltar ", 0, 80, 8);

        telaEscreverCentralizado("Escolha uma opcao: ", 0, 80, 16);
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            incluirPet();
            break;

        case 2:
            excluirPet();
            break;

        case 3:
            listarPets();
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
