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
    COORD origem = {0, 0};

    FillConsoleOutputCharacterA(
        console, ' ', tamanho, origem, &escritos);

    FillConsoleOutputAttribute(
        console, info.wAttributes,
        tamanho, origem, &escritos);

    SetConsoleCursorPosition(console, origem);
}

void telaPosicionarCursor(int x, int y)
{
    COORD posicao = {
        (SHORT)x,
        (SHORT)y};

    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        posicao);
}

void telaEscrever(int x, int y, const char *texto)
{
    telaPosicionarCursor(x, y);
    printf("%s", texto);
}

void telaDesenharBox(
    int x,
    int y,
    int largura,
    int altura)
{
    SetConsoleOutputCP(437);

    int linha = y;

    if (largura < 2 || altura < 2)
        return;

    // Primeira linha do box
    telaPosicionarCursor(x, linha);
    printf("%c", 201); // ╔

    for (int i = 0; i < largura - 2; i++)
        printf("%c", 205); // ═

    printf("%c", 187); // ╗

    // Segunda linha do box com título
    linha++;
    telaPosicionarCursor(x, linha);
    printf("%c", 186); // ║

    telaEscreverCentralizado("VETCARE - SISTEMA DE GESTAO", 0, 80, linha);

    telaPosicionarCursor(x + largura - 1, linha);
    printf("%c", 186); // ║

    // Terceira linha do box com traço duplo e conectores
    linha++;
    telaPosicionarCursor(x, linha);
    printf("%c", 204); // ╠

    for (int i = 0; i < largura - 2; i++)
        printf("%c", 205); // ═

    printf("%c", 185); // ╣

    // Quarta linha até a penúltima
    linha++;

    for (int i = linha; i < altura - 1; i++)
    {
        telaPosicionarCursor(x, linha);
        printf("%c", 186); // ║

        telaPosicionarCursor(x + largura - 1, linha);
        printf("%c", 186); // ║

        linha++;
    }

    telaPosicionarCursor(x, linha);
    printf("%c", 200); // ╚

    for (int i = 0; i < largura - 2; i++)
        printf("%c", 205); // ═

    printf("%c", 188); // ╝
}

void telaEscreverCentralizado(const char *texto, int xInicial, int largura, int linha)
{
    int tamanhoTexto = strlen(texto);

    int coluna = xInicial + (largura - tamanhoTexto) / 2;

    if (coluna < xInicial)
        coluna = xInicial;

    telaPosicionarCursor(1, linha);
    printf("%78s", "");

    telaEscrever(coluna, linha, texto);
}