#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdint.h>
#include <inttypes.h>
#include "atendimento.h"
#include "util.h"
#include "data.h"
#include "pet.h"
#include "tela.h"
#include "tutor.h"
#include "exame.h"
#include "vacina.h"
#include "veterinario.h"

#define ARQUIVO_ATENDIMENTOS "C:\\VetCare\\Dados\\Atendimento.json"

static Atendimento atendimentos[MAX_ATENDIMENTOS];
static int totalAtendimentos = 0;
static int proximoCodigo = 1;

/*
---------------------------------
 Função SALVAR
---------------------------------
*/
static void salvarAtendimentos(void)
{
    FILE *arquivo = fopen(ARQUIVO_ATENDIMENTOS, "w");

    if (arquivo == NULL)
    {
        telaEscreverCentralizado("Erro ao abrir o arquivo JSON!", 0, 50, 22);
        getchar();
        return;
    }

    fprintf(arquivo, "[\n");

    for (int i = 0; i < totalAtendimentos; i++)
    {
        fprintf(arquivo,
                "    {\n"
                "        \"codAtendimento\": %d,\n"
                "        \"codVeterinario\": %d,\n"
                "        \"codTutor\": %d,\n"
                "        \"codPet\": %d,\n"
                "        \"dataAtendimento\": \"%s\"\n"
                "        \"codVacina1\": %d,\n"
                "        \"codVacina2\": %d,\n"
                "        \"codVacina3\": %d,\n"
                "        \"codVacina4\": %d,\n"
                "        \"valVacina1\": %" PRId64 ",\n"
                "        \"valVacina2\": %" PRId64 ",\n"
                "        \"valVacina3\": %" PRId64 ",\n"
                "        \"valVacina4\": %" PRId64 ",\n"
                "        \"totVacina\": %" PRId64 ",\n"
                "        \"codExame1\": %d,\n"
                "        \"codExame2\": %d,\n"
                "        \"codExame3\": %d,\n"
                "        \"codExame4\": %d,\n"
                "        \"valExame1\": %" PRId64 ",\n"
                "        \"valExame2\": %" PRId64 ",\n"
                "        \"valExame3\": %" PRId64 ",\n"
                "        \"valExame4\": %" PRId64 ",\n"
                "        \"totExame\": %" PRId64 ",\n"
                "        \"valAtendimento\": %" PRId64 ",\n"
                "        \"totAtendimento\": %" PRId64 ",\n"
                "    }%s\n",
                atendimentos[i].codAtendimento,
                atendimentos[i].codVeterinario,
                atendimentos[i].codTutor,
                atendimentos[i].codPet,
                atendimentos[i].dataAtendimento,
                atendimentos[i].codVacina1,
                atendimentos[i].codVacina2,
                atendimentos[i].codVacina3,
                atendimentos[i].codVacina4,
                atendimentos[i].valVacina1,
                atendimentos[i].valVacina2,
                atendimentos[i].valVacina3,
                atendimentos[i].valVacina4,
                atendimentos[i].totVacina,
                atendimentos[i].codExame1,
                atendimentos[i].codExame2,
                atendimentos[i].codExame3,
                atendimentos[i].codExame4,
                atendimentos[i].valExame1,
                atendimentos[i].valExame2,
                atendimentos[i].valExame3,
                atendimentos[i].valExame4,
                atendimentos[i].totExame,
                atendimentos[i].valAtendimento,
                atendimentos[i].totAtendimento,
                i < totalAtendimentos - 1 ? "," : "");
    }

    fprintf(arquivo, "]\n");
    fclose(arquivo);
}

/*
---------------------------------
Função Carregar
---------------------------------
*/
static void carregarAtendimentos(void)
{
    FILE *arquivo = fopen(ARQUIVO_ATENDIMENTOS, "r");

    totalAtendimentos = 0;
    proximoCodigo = 1;

    if (arquivo == NULL)
        return;

    char linha[800];
    Atendimento atendimento = {0};

    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        if (strstr(linha, "\"codAtendimento\"") != NULL)
        {
            sscanf(linha, " \"codAtendimento\": %d", &atendimento.codAtendimento);
        }

        if (strstr(linha, "\"codVeterinario\"") != NULL)
        {
            sscanf(linha, " \"codVeterinario\": %d", &atendimento.codVeterinario);
        }

        if (strstr(linha, "\"codTutor\"") != NULL)
        {
            sscanf(linha, " \"codTutor\": %d", &atendimento.codTutor);
        }

        if (strstr(linha, "\"codPet\"") != NULL)
        {
            sscanf(linha, " \"codPet\": %d", &atendimento.codPet);
        }

        if (strstr(linha, "\"dataAtendimento\"") != NULL)
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
                        strncpy(atendimento.dataAtendimento, inicio, sizeof(atendimento.dataAtendimento) - 1);
                        atendimento.dataAtendimento[sizeof(atendimento.dataAtendimento) - 1] = '\0';
                    }
                }
            }
        }

        if (strstr(linha, "\"codVacina1\"") != NULL)
        {
            sscanf(linha, " \"codVacina1\": %d", &atendimento.codVacina1);
        }

        if (strstr(linha, "\"codVacina2\"") != NULL)
        {
            sscanf(linha, " \"codVacina2\": %d", &atendimento.codVacina2);
        }

        if (strstr(linha, "\"codVacina3\"") != NULL)
        {
            sscanf(linha, " \"codVacina3\": %d", &atendimento.codVacina3);
        }

        if (strstr(linha, "\"codVacina4\"") != NULL)
        {
            sscanf(linha, " \"codVacina4\": %d", &atendimento.codVacina4);
        }

        if (strstr(linha, "\"valVacina1\"") != NULL)
        {
            sscanf(linha, " \"valVacina1\": %" PRId64, &atendimento.valVacina1);
        }

        if (strstr(linha, "\"valVacina2\"") != NULL)
        {
            sscanf(linha, " \"valVacina2\": %" PRId64, &atendimento.valVacina2);
        }

        if (strstr(linha, "\"valVacina3\"") != NULL)
        {
            sscanf(linha, " \"valVacina3\": %" PRId64, &atendimento.valVacina3);
        }

        if (strstr(linha, "\"valVacina4\"") != NULL)
        {
            sscanf(linha, " \"valVacina4\": %" PRId64, &atendimento.valVacina4);
        }

        if (strstr(linha, "\"codExame1\"") != NULL)
        {
            sscanf(linha, " \"codExame1\": %d", &atendimento.codExame1);
        }

        if (strstr(linha, "\"codExame2\"") != NULL)
        {
            sscanf(linha, " \"codExame2\": %d", &atendimento.codExame2);
        }

        if (strstr(linha, "\"codExame3\"") != NULL)
        {
            sscanf(linha, " \"codExame3\": %d", &atendimento.codExame3);
        }

        if (strstr(linha, "\"codExame4\"") != NULL)
        {
            sscanf(linha, " \"codExame4\": %d", &atendimento.codExame4);
        }

        if (strstr(linha, "\"valExame1\"") != NULL)
        {
            sscanf(linha, " \"valExame1\": %" PRId64, &atendimento.valExame1);
        }

        if (strstr(linha, "\"valExame2\"") != NULL)
        {
            sscanf(linha, " \"valExame2\": %" PRId64, &atendimento.valExame2);
        }

        if (strstr(linha, "\"valExame3\"") != NULL)
        {
            sscanf(linha, " \"valExame3\": %" PRId64, &atendimento.valExame3);
        }

        if (strstr(linha, "\"valExame4\"") != NULL)
        {
            sscanf(linha, " \"valExame4\": %" PRId64, &atendimento.valExame4);
        }

        if (strstr(linha, "\"totAtendimento\"") != NULL)
        {
            sscanf(linha, " \"totAtendimento\": %" PRId64, &atendimento.totAtendimento);
        }

        if (strstr(linha, "\"valAtendimento\"") != NULL)
        {
            sscanf(linha, " \"valAtendimento\": %" PRId64, &atendimento.valAtendimento);

            if (totalAtendimentos < MAX_ATENDIMENTOS)
            {
                atendimentos[totalAtendimentos++] = atendimento;

                if (atendimento.codAtendimento >= proximoCodigo)
                    proximoCodigo = atendimento.codAtendimento + 1;
            }

            atendimento = (Atendimento){0};
        }
    }

    fclose(arquivo);
}

/*
---------------------------------
Função Incluir
---------------------------------
*/
void incluirAtendimento(void)
{
    Atendimento nova = {0};
    Data hoje = obterDataAtual();

    char nomeValido[50] = {0};

    int64_t valorExame1 = 0;
    int64_t valorExame2 = 0;
    int64_t valorExame3 = 0;
    int64_t valorExame4 = 0;
    int64_t totalExames = 0;

    int64_t valorVacina1 = 0;
    int64_t valorVacina2 = 0;
    int64_t valorVacina3 = 0;
    int64_t valorVacina4 = 0;
    int64_t totalVacinas = 0;

    nova.codAtendimento = proximoCodigo;
    nova.valAtendimento = 15000;

    int64_t totalAtendimento = 0;

    char valorFormatado[64];
    char valorAtendimento[85];
    formatarMoeda(nova.valAtendimento, valorFormatado, sizeof(valorFormatado));
    snprintf(valorAtendimento, sizeof(valorAtendimento), "Valor Atendimento: %s", valorFormatado);

    snprintf(
        nova.dataAtendimento,
        sizeof(nova.dataAtendimento),
        "%04d-%02d-%02d",
        hoje.ano,
        hoje.mes,
        hoje.dia);

    carregarAtendimentos();

    telaLimpar();
    telaDesenharBox(0, 0, 85, 24);
    telaEscreverCentralizado("ATENDIMENTOS - Inclusao", 0, 80, 3);

    telaEscrever(3, 5, "Cod.Atendimento: ");
    printf("%d", nova.codAtendimento);

    telaEscrever(3, 6, "Dat.Atendimento: ");
    printf("%04d-%02d-%02d",
           hoje.ano,
           hoje.mes,
           hoje.dia);

    telaEscrever(38, 5, "Cod.Veterinario: ");
    telaEscrever(38, 6, "Cod.Tutor......: ");
    telaEscrever(38, 7, "Cod.Pet........: ");

    telaEscrever(3, 9, "Cod.Exame: ");
    telaEscrever(3, 10, "Cod.Exame: ");
    telaEscrever(3, 11, "Cod.Exame: ");
    telaEscrever(3, 12, "Cod.Exame: ");

    telaEscrever(43, 9, "Cod.Vacina: ");
    telaEscrever(43, 10, "Cod.Vacina: ");
    telaEscrever(43, 11, "Cod.Vacina: ");
    telaEscrever(43, 12, "Cod.Vacina: ");

    telaEscrever(46, 15, valorAtendimento);
    telaEscrever(46, 16, "Valor Exames.....: ");
    telaEscrever(46, 17, "Valor Vacinas....: ");
    telaEscrever(46, 18, "Valor Total......: ");

    // Veterinário
    do
    {
        nova.codVeterinario = 0;

        telaEscrever(38, 5, "Cod.Veterinario: ");
        scanf("%d", &nova.codVeterinario);
    } while (validarVeterinario(nova.codVeterinario, nomeValido) == 0);

    telaEscrever(58, 5, nomeValido);

    // Tutor
    do
    {
        nova.codTutor = 0;

        telaEscrever(38, 6, "Cod.Tutor......: ");
        scanf("%d", &nova.codTutor);
    } while (validarTutor(nova.codTutor, nomeValido) == 0);

    telaEscrever(58, 6, nomeValido);

    // Pet
    do
    {
        nova.codPet = 0;

        telaEscrever(38, 7, "Cod.Pet........: ");
        scanf("%d", &nova.codPet);
    } while (validarPet(nova.codPet, nomeValido) == 0);

    telaEscrever(58, 7, nomeValido);

    // Exame 1
    do
    {
        nova.codExame1 = 0;

        telaEscrever(3, 9, "Cod.Exame: ");
        scanf("%d", &nova.codExame1);

    } while (nova.codExame1 > 0 && validarExame(nova.codExame1, nomeValido, &valorExame1) == 0);

    if (nova.codExame1 == 0)
    {
        telaEscrever(17, 9, "NENHUM");
    }
    else
    {
        telaEscrever(17, 9, nomeValido);
    }

    // Exame 2
    do
    {
        nova.codExame2 = 0;

        telaEscrever(3, 10, "Cod.Exame: ");
        scanf("%d", &nova.codExame2);

    } while (nova.codExame2 > 0 && validarExame(nova.codExame2, nomeValido, &valorExame2) == 0);

    if (nova.codExame2 == 0)
    {
        telaEscrever(17, 10, "NENHUM");
    }
    else
    {
        telaEscrever(17, 10, nomeValido);
    }

    // Exame 3
    do
    {
        nova.codExame3 = 0;

        telaEscrever(3, 11, "Cod.Exame: ");
        scanf("%d", &nova.codExame3);

    } while (nova.codExame3 > 0 && validarExame(nova.codExame3, nomeValido, &valorExame3) == 0);

    if (nova.codExame3 == 0)
    {
        telaEscrever(17, 11, "NENHUM");
    }
    else
    {
        telaEscrever(17, 11, nomeValido);
    }

    // Exame 4
    do
    {
        nova.codExame4 = 0;

        telaEscrever(3, 12, "Cod.Exame: ");
        scanf("%d", &nova.codExame4);

    } while (nova.codExame4 > 0 && validarExame(nova.codExame4, nomeValido, &valorExame4) == 0);

    if (nova.codExame4 == 0)
    {
        telaEscrever(17, 12, "NENHUM");
    }
    else
    {
        telaEscrever(17, 12, nomeValido);
    }

    totalExames = valorExame1 + valorExame2 + valorExame3 + valorExame4;

    char valorExamesFormatado[64];
    char valorExames[85];
    formatarMoeda(totalExames, valorExamesFormatado, sizeof(valorExamesFormatado));
    snprintf(valorExames, sizeof(valorExames), "Valor Exames.....: %s", valorExamesFormatado);
    telaEscrever(46, 16, valorExames);

    // Vacina 1
    do
    {
        nova.codVacina1 = 0;

        telaEscrever(43, 9, "Cod.Vacina: ");
        scanf("%d", &nova.codVacina1);

    } while (nova.codVacina1 > 0 && validarVacina(nova.codVacina1, nomeValido, &valorVacina1) == 0);

    if (nova.codVacina1 == 0)
    {
        telaEscrever(58, 9, "NENHUMA");
    }
    else
    {
        telaEscrever(58, 9, nomeValido);
    }

    // Vacina 2
    do
    {
        nova.codVacina2 = 0;

        telaEscrever(43, 10, "Cod.Vacina: ");
        scanf("%d", &nova.codVacina2);

    } while (nova.codVacina2 > 0 && validarVacina(nova.codVacina2, nomeValido, &valorVacina2) == 0);

    if (nova.codVacina2 == 0)
    {
        telaEscrever(58, 10, "NENHUMA");
    }
    else
    {
        telaEscrever(58, 10, nomeValido);
    }

    // Vacina 3
    do
    {
        nova.codVacina3 = 0;

        telaEscrever(43, 11, "Cod.Vacina: ");
        scanf("%d", &nova.codVacina3);

    } while (nova.codVacina3 > 0 && validarVacina(nova.codVacina3, nomeValido, &valorVacina3) == 0);

    if (nova.codVacina3 == 0)
    {
        telaEscrever(58, 11, "NENHUMA");
    }
    else
    {
        telaEscrever(58, 11, nomeValido);
    }

    // Vacina 4
    do
    {
        nova.codVacina4 = 0;

        telaEscrever(43, 12, "Cod.Vacina: ");
        scanf("%d", &nova.codVacina4);

    } while (nova.codVacina4 > 0 && validarVacina(nova.codVacina4, nomeValido, &valorVacina4) == 0);

    if (nova.codVacina4 == 0)
    {
        telaEscrever(58, 12, "NENHUMA");
    }
    else
    {
        telaEscrever(58, 12, nomeValido);
    }

    totalVacinas = valorVacina1 + valorVacina2 + valorVacina3 + valorVacina4;

    char valorVacinasFormatado[64];
    char valorVacinas[85];
    formatarMoeda(totalVacinas, valorVacinasFormatado, sizeof(valorVacinasFormatado));
    snprintf(valorVacinas, sizeof(valorVacinas), "Valor Vacinas....: %s", valorVacinasFormatado);
    telaEscrever(46, 17, valorVacinas);

    totalAtendimento = nova.valAtendimento + totalExames + totalVacinas;

    char valorTotalFormatado[64];
    char valorTotal[85];
    formatarMoeda(totalAtendimento, valorTotalFormatado, sizeof(valorTotalFormatado));
    snprintf(valorTotal, sizeof(valorTotal), "Valor Total......: %s", valorTotalFormatado);
    telaEscrever(46, 18, valorTotal);

    nova.valExame1 = valorExame1;
    nova.valExame2 = valorExame2;
    nova.valExame3 = valorExame3;
    nova.valExame4 = valorExame4;

    nova.valVacina1 = valorVacina1;
    nova.valVacina2 = valorVacina2;
    nova.valVacina3 = valorVacina3;
    nova.valVacina4 = valorVacina4;

    nova.totExame = totalExames;
    nova.totVacina = totalVacinas;
    nova.totAtendimento = totalAtendimento;

    atendimentos[totalAtendimentos++] = nova;
    proximoCodigo++;

    salvarAtendimentos();

    telaEscreverCentralizado("Atendimento cadastrado!", 0, 80, 22);
    getchar();
    getchar();
}
