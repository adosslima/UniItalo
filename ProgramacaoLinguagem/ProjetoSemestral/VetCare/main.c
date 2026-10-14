#include <stdio.h>
#include "tela.h"
#include "especie.h"

void menuCadastros(void)
{
    int opcao;

    do
    {
        telaLimpar();
        telaDesenharBox(2, 1, 70, 20);

        telaEscrever(5, 3, "VETCARE - CADASTROS");

        telaEscrever(5, 5, "1 - Cadastrar Especie");
        telaEscrever(5, 6, "2 - Cadastrar Raca");
        telaEscrever(5, 7, "3 - Cadastrar Tutor");
        telaEscrever(5, 8, "4 - Cadastrar Pet");
        telaEscrever(5, 10, "0 - Voltar");

        telaEscrever(5, 13, "Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            menuEspecies();
            break;

        case 2:
            telaEscrever(5, 15, "Cadastrar Raca");
            break;

        case 3:
            telaEscrever(5, 15, "Cadastrar Tutor");
            break;

        case 4:
            telaEscrever(5, 15, "Cadastrar Pet");
            break;

        case 0:
            break;

        default:
            telaEscrever(5, 15, "Opcao invalida!");
            break;
        }

        if (opcao != 0)
        {
            telaEscrever(5, 17, "Pressione ENTER...");
            getchar();
            getchar();
        }

    } while (opcao != 0);
}

int main(void)
{
    int opcao;

    do
    {
        telaLimpar();
        telaDesenharBox(2, 1, 70, 20);

        telaEscrever(5, 3, "VETCARE - SISTEMA DE GESTAO");

        telaEscrever(5, 5, "1 - Cadastrar");
        telaEscrever(5, 6, "2 - Listar Pets");
        telaEscrever(5, 7, "3 - Pesquisar Pet");
        telaEscrever(5, 8, "4 - Registrar Atendimento");
        telaEscrever(5, 9, "5 - Registrar Servico");
        telaEscrever(5, 10, "6 - Consultar Historico");
        telaEscrever(5, 11, "7 - Relatorio Atendimentos");
        telaEscrever(5, 12, "8 - Faturamento");
        telaEscrever(5, 13, "9 - Sair");

        telaEscrever(5, 16, "Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            menuCadastros();
            break;

        case 9:
            break;

        default:
            telaEscrever(5, 18,
                         "Funcionalidade nao implementada.");

            getchar();
            getchar();
            break;
        }

    } while (opcao != 9);

    return 0;
}
