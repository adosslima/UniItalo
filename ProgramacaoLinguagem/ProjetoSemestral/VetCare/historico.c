#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "data.h"
#include "pet.h"
#include "tela.h"
#include "tutor.h"
#include "especie.h"
#include "raca.h"
#include "veterinario.h"
#include "exame.h"
#include "vacina.h"
#include "atendimento.h"

#define ARQUIVO_ATENDIMENTOS "C:\\VetCare\\Dados\\Atendimento.json"

/*
 */
void consultarHistorico(void)
{
    SetConsoleOutputCP(437);

    carregarAtendimentos();

    telaLimpar();
    telaDesenharBox(0, 0, 80, 24);
    telaEscreverCentralizado("HISTORICO ATENDIMENTOS", 0, 80, 3);

    int codPet = 0;
    int linha = 9;
    char nomeValido[50] = {0};
    char nomeImpresso[20] = {0};
    int64_t valor = 0;

    do
    {
        codPet = 0;

        telaEscrever(2, 5, "Cod.Pet: ");
        scanf("%d", &codPet);
    } while (codPet > 0 && validarPet(codPet, nomeValido) == 0);

    if (codPet == 0)
        return;

    telaEscrever(17, 5, nomeValido);

    telaEscrever(3, 7, "Cod.At");
    telaEscrever(10, 7, "Data");
    telaEscrever(21, 7, "Veterinario");
    telaEscrever(45, 7, "Exames");
    telaEscrever(62, 7, "Vacinas");

    telaEscrever(3, 8, "------");
    telaEscrever(10, 8, "----------");
    telaEscrever(21, 8, "-----------------------");
    telaEscrever(45, 8, "----------------");
    telaEscrever(62, 8, "----------------");

    for (int i = 0; i < totalAtendimentos; i++)
    {
        if (atendimentos[i].codPet == codPet)
        {
            telaPosicionarCursor(0, linha);
            printf("%c", 186);
            printf("%*s", 78, " ");
            telaPosicionarCursor(79, linha);
            printf("%c", 186);

            telaEscreverInt(3, linha, atendimentos[i].codAtendimento);
            telaEscrever(10, linha, atendimentos[i].dataAtendimento);

            validarVeterinario(atendimentos[i].codVeterinario, nomeValido);
            strncpy(nomeImpresso, nomeValido, 15);
            telaEscrever(21, linha, nomeImpresso);

            // Exame1
            if (atendimentos[i].codExame1 > 0)
            {
                validarExame(atendimentos[i].codExame1, nomeValido, &valor);

                strncpy(nomeImpresso, nomeValido, 15);
                telaEscrever(45, linha, nomeImpresso);
            }
            else
            {
                telaEscrever(45, linha, "NENHUM");
            }

            // Vacina 1
            if (atendimentos[i].codVacina1 > 0)
            {
                validarVacina(atendimentos[i].codVacina1, nomeValido, &valor);

                strncpy(nomeImpresso, nomeValido, 15);
                telaEscrever(62, linha, nomeImpresso);
            }
            else
            {
                telaEscrever(62, linha, "NENHUMA");
            }

            linha++;
            telaPosicionarCursor(0, linha);
            printf("%c", 186);
            printf("%*s", 78, " ");
            telaPosicionarCursor(79, linha);
            printf("%c", 186);

            // Exame2
            if (atendimentos[i].codExame2 > 0)
            {
                validarExame(atendimentos[i].codExame2, nomeValido, &valor);

                strncpy(nomeImpresso, nomeValido, 15);
                telaEscrever(45, linha, nomeImpresso);
            }
            else
            {
                telaEscrever(45, linha, "NENHUM");
            }

            // Vacina 2
            if (atendimentos[i].codVacina2 > 0)
            {
                validarVacina(atendimentos[i].codVacina2, nomeValido, &valor);

                strncpy(nomeImpresso, nomeValido, 15);
                telaEscrever(62, linha, nomeImpresso);
            }
            else
            {
                telaEscrever(62, linha, "NENHUMA");
            }

            linha++;
            telaPosicionarCursor(0, linha);
            printf("%c", 186);
            printf("%*s", 78, " ");
            telaPosicionarCursor(79, linha);
            printf("%c", 186);

            // Exame3
            if (atendimentos[i].codExame3 > 0)
            {
                validarExame(atendimentos[i].codExame3, nomeValido, &valor);

                strncpy(nomeImpresso, nomeValido, 15);
                telaEscrever(45, linha, nomeImpresso);
            }
            else
            {
                telaEscrever(45, linha, "NENHUM");
            }

            // Vacina 3
            if (atendimentos[i].codVacina3 > 0)
            {
                validarVacina(atendimentos[i].codVacina3, nomeValido, &valor);

                strncpy(nomeImpresso, nomeValido, 15);
                telaEscrever(62, linha, nomeImpresso);
            }
            else
            {
                telaEscrever(62, linha, "NENHUMA");
            }

            linha++;
            telaPosicionarCursor(0, linha);
            printf("%c", 186);
            printf("%*s", 78, " ");
            telaPosicionarCursor(79, linha);
            printf("%c", 186);

            // Exame4
            if (atendimentos[i].codExame4 > 0)
            {
                validarExame(atendimentos[i].codExame4, nomeValido, &valor);

                strncpy(nomeImpresso, nomeValido, 15);
                telaEscrever(45, linha, nomeImpresso);
            }
            else
            {
                telaEscrever(45, linha, "NENHUM");
            }

            // Vacina 4
            if (atendimentos[i].codVacina4 > 0)
            {
                validarVacina(atendimentos[i].codVacina4, nomeValido, &valor);

                strncpy(nomeImpresso, nomeValido, 15);
                telaEscrever(62, linha, nomeImpresso);
            }
            else
            {
                telaEscrever(62, linha, "NENHUMA");
            }

            linha++;
            telaPosicionarCursor(0, linha);
            printf("%c", 186);
            printf("%*s", 78, " ");
            telaPosicionarCursor(79, linha);
            printf("%c", 186);

            linha++;
        }
    }

    telaPosicionarCursor(0, linha);
    printf("%c", 186);
    printf("%*s", 78, " ");
    telaPosicionarCursor(79, linha);
    printf("%c", 186);

    telaEscreverCentralizado("Pressione [ENTER]", 0, 80, linha);

    linha++;

    if (linha >= 24)
    {
        telaPosicionarCursor(0, linha);
        printf("%c", 200); // ╚

        for (int i = 0; i < 80 - 2; i++)
            printf("%c", 205); // ═

        printf("%c", 188); // ╝
    }

    getchar();
    getchar();
}
