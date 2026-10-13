
#include <stdio.h>
#include "tela.h"

int main(void)
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

    telaEscrever(5, 16, "Pressione ENTER para continuar...");

    getchar();

    return 0;
}
