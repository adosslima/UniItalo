#define TELA_H

void telaLimpar(void);

void telaPosicionarCursor(int x, int y);

void telaEscrever(int x, int y, const char* texto);

void telaDesenharBox(
    int x,
    int y,
    int largura,
    int altura
);
