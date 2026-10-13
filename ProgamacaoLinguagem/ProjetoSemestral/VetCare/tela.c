
#include "tela.h"
#include <stdio.h>
#include <windows.h>

void telaLimpar(void)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;

    if (!GetConsoleScreenBufferInfo(console, &info))
        return;

    DWORD tamanho =
        (DWORD)info.dwSize.X * info.dwSize.Y;

    DWORD escritos;
    COORD origem = { 0, 0 };

    FillConsoleOutputCharacterA(
        console, ' ', tamanho, origem, &escritos
    );

    FillConsoleOutputAttribute(
        console, info.wAttributes,
        tamanho, origem, &escritos
    );

    SetConsoleCursorPosition(console, origem);
}

void telaPosicionarCursor(int x, int y)
{
    COORD posicao = {
        (SHORT)x,
        (SHORT)y
    };

    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        posicao
    );
}

void telaEscrever(int x, int y, const char* texto)
{
    telaPosicionarCursor(x, y);
    printf("%s", texto);
}

void telaDesenharBox(
    int x,
    int y,
    int largura,
    int altura
)
{
    if (largura < 2 || altura < 2)
        return;

    telaPosicionarCursor(x, y);
    printf("+");

    for (int i = 0; i < largura - 2; i++)
        printf("-");

    printf("+");

    for (int i = 1; i < altura - 1; i++)
    {
        telaEscrever(x, y + i, "|");
        telaEscrever(x + largura - 1, y + i, "|");
    }

    telaPosicionarCursor(x, y + altura - 1);
    printf("+");

    for (int i = 0; i < largura - 2; i++)
        printf("-");

    printf("+");
}
