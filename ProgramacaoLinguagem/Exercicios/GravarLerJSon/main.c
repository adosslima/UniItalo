#include <stdio.h>

int main()
{
    FILE *arquivo; // cria um ponteiro para arquivo do tipo FILE

    char nome[2][50] = {"Lucas", "Anne"};
    int idade[2] = {20, 24};

    // Cria/abre o arquivo dados.json para escrita
    arquivo = fopen("dados.json", "w");

    // Verifica se o arquivo foi aberto corretamente
    if (arquivo == NULL)
    {
        printf("Erro ao criar o arquivo!\n");
        return 1;
    }

    // Grava o JSON no arquivo
    fprintf(arquivo, "[\n");

    fprintf(arquivo, "  {\n");
    fprintf(arquivo, "    \"nome\": \"%s\",\n", nome[0]);
    fprintf(arquivo, "    \"idade\": %d\n", idade[0]);
    fprintf(arquivo, "  },\n");

    fprintf(arquivo, "  {\n");
    fprintf(arquivo, "    \"nome\": \"%s\",\n", nome[1]);
    fprintf(arquivo, "    \"idade\": %d\n", idade[1]);
    fprintf(arquivo, "  }\n");

    fprintf(arquivo, "]\n");

    // Fecha o arquivo
    fclose(arquivo);

    printf("Arquivo dados.json criado com sucesso!\n");

    return 0;
}