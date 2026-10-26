#include <stdio.h>
#include <string.h>
#include "data.h"
#include "pet.h"
#include "tela.h"

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
        telaEscrever(5, 18, "Erro ao abrir o arquivo JSON!");
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
Função Listar
---------------------------------
*/
static void listarPets(void)
{
    char codigo[10];

    telaLimpar();
    telaDesenharBox(2, 1, 70, 20);
    telaEscrever(5, 3, "VETCARE - MANUTENCAO DE PETS - Listagem");

    telaEscrever(5, 6, "CODIGO");
    telaEscrever(20, 6, "PET");
    telaEscrever(5, 7, "-------------------------------");

    for (int i = 0; i < totalPets; i++)
    {
        snprintf(codigo, sizeof(codigo), "%d", pets[i].codPet);

        telaEscrever(5, 8 + i, codigo);
        telaEscrever(20, 8 + i, pets[i].nomePet);
    }

    telaEscrever(5, 19, "Total: ");
    printf("%d", totalPets);

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
    telaLimpar();
    telaDesenharBox(2, 1, 70, 20);
    telaEscrever(5, 3, "VETCARE - MANUTENCAO DE PETS - Exclusao");

    int codigo = 0;
    telaEscrever(5, 5, "Codigo do Pet: ");
    scanf("%d", &codigo);

    int indice = buscarIndice(codigo);

    if (indice == -1)
    {
        telaEscrever(5, 18, "Pet nao encontrado!");
        getchar();
        getchar();
        return;
    }

    telaEscrever(5, 17, "Confirma ");
    printf("excluir %s? (S/N): ", pets[indice].nomePet);

    char resposta[1];
    scanf("%s", resposta);

    if (resposta[0] != 'S' && resposta[0] != 's')
        return;

    for (int i = indice; i < totalPets - 1; i++)
        pets[i] = pets[i + 1];

    totalPets--;

    salvarPets();

    telaEscrever(5, 18, "Pet excluido!");
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
    telaLimpar();
    telaDesenharBox(2, 1, 70, 20);
    telaEscrever(5, 3, "VETCARE - MANUTENCAO DE PETS - Inclusao");

    if (totalPets >= MAX_PETS)
    {
        telaEscrever(5, 18, "Limite de pets atingido!");
        getchar();
        return;
    }

    Pet nova = {0};
    nova.codPet = proximoCodigo;

    telaEscrever(5, 5, "Codigo do Pet: ");
    printf("%d", nova.codPet);

    telaEscrever(5, 6, "Codigo do Tutor: ");
    scanf("%d", &nova.codTutor);

    telaEscrever(5, 7, "Codigo do Especia: ");
    scanf("%d", &nova.codEspecie);

    telaEscrever(5, 8, "Codigo do Raca: ");
    scanf("%d", &nova.codRaca);

    char nome[50];
    telaEscrever(5, 9, "Nome do Pet: ");
    scanf(" %49[^\n]", nome);

    strcpy(nova.nomePet, nome);

    Data nascimento = {0};
    int erro = 0;

    do
    {
        telaEscrever(5, 10, "Data de nascimento (AAAA-MM-DD): ");

        if (scanf("%d-%d-%d",
                  &nascimento.ano,
                  &nascimento.mes,
                  &nascimento.dia) != 3)
        {
            telaEscrever(5, 19, "Formato de data invalido!");
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

    telaEscrever(5, 18, "Pet cadastrado!");
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

        telaDesenharBox(2, 1, 70, 20);

        telaEscrever(5, 3, "VETCARE - MANUTENCAO DE PET");

        telaEscrever(5, 5, "1 - Incluir");
        telaEscrever(5, 6, "2 - Excluir");
        telaEscrever(5, 7, "3 - Listar");
        telaEscrever(5, 9, "0 - Voltar");

        telaEscrever(5, 16, "Escolha uma opcao: ");
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
            telaEscrever(5, 18, "Opcao invalida!");
            getchar();
            getchar();
            break;
        }

    } while (opcao != 0);
}
