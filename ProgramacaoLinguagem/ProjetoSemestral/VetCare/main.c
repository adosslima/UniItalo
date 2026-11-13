#include <stdio.h>
#include "tela.h"
#include "especie.h"
#include "raca.h"
#include "tutor.h"
#include "veterinario.h"
#include "pet.h"
#include "vacina.h"
#include "exame.h"
#include "atendimento.h"

void menuCadastros(void)
{
    int opcao;

    do
    {
        telaLimpar();
        telaDesenharBox(0, 0, 80, 24);
        telaEscreverCentralizado("MENU CADASTROS", 0, 80, 3);

        telaEscreverCentralizado("1 - Cadastrar Especie    ", 0, 80, 5);
        telaEscreverCentralizado("2 - Cadastrar Raca       ", 0, 80, 6);
        telaEscreverCentralizado("3 - Cadastrar Tutor      ", 0, 80, 7);
        telaEscreverCentralizado("4 - Cadastrar Veterinario", 0, 80, 8);
        telaEscreverCentralizado("5 - Cadastrar Pet        ", 0, 80, 9);
        telaEscreverCentralizado("0 - Voltar               ", 0, 80, 10);

        telaEscreverCentralizado("Escolha uma opcao: ", 0, 80, 16);
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            menuEspecies();
            break;

        case 2:
            menuRacas();
            break;

        case 3:
            menuTutores();
            break;

        case 4:
            menuVeterinarios();
            break;

        case 5:
            menuPets();
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

void menuListegam(void)
{
    int opcao;

    do
    {
        telaLimpar();
        telaDesenharBox(0, 0, 80, 24);
        telaEscreverCentralizado("MENU LISTAGENS", 0, 80, 3);

        telaEscreverCentralizado("1 - Listar Pets          ", 0, 80, 5);
        telaEscreverCentralizado("2 - Listar Vacinas       ", 0, 80, 6);
        telaEscreverCentralizado("3 - Listar Exames        ", 0, 80, 7);
        telaEscreverCentralizado("0 - Voltar               ", 0, 80, 8);

        telaEscreverCentralizado("Escolha uma opcao: ", 0, 80, 16);
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            listarPets();
            break;

        case 2:
            listarVacinas();
            break;

        case 3:
            listarExames();
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

int main(void)
{
    int opcao;

    do
    {
        telaLimpar();
        telaDesenharBox(0, 0, 80, 24);
        telaEscreverCentralizado("MENU PRINCIPAL", 0, 80, 3);

        telaEscreverCentralizado("1 - Cadastrar             ", 0, 80, 5);
        telaEscreverCentralizado("2 - Listagem              ", 0, 80, 6);
        telaEscreverCentralizado("3 - Pesquisar Pet         ", 0, 80, 7);
        telaEscreverCentralizado("4 - Registrar Atendimento ", 0, 80, 8);
        telaEscreverCentralizado("5 - Registrar Servico     ", 0, 80, 9);
        telaEscreverCentralizado("6 - Consultar Historico   ", 0, 80, 10);
        telaEscreverCentralizado("7 - Relatorio Atendimentos", 0, 80, 11);
        telaEscreverCentralizado("8 - Faturamento           ", 0, 80, 12);
        telaEscreverCentralizado("9 - Sair                  ", 0, 80, 13);

        telaEscreverCentralizado("Escolha uma opcao: ", 0, 80, 16);
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            menuCadastros();
            break;

        case 2:
            menuListegam();
            break;

        case 3:
            pesquisarPets();
            break;

        case 4:
            incluirAtendimento();
            break;

        case 9:
            telaLimpar();
            break;

        default:
            telaEscreverCentralizado("Opcao Invalida.", 0, 80, 22);
            getchar();
            getchar();
            break;
        }

    } while (opcao != 9);

    return 0;
}
