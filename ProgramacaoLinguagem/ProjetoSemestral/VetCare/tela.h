#define TELA_H

void telaLimpar(void);

void telaPosicionarCursor(int x, int y);

void telaEscrever(int x, int y, const char* texto);

void telaEscreverInt(int x, int y, const int valor);

void telaEscreverCentralizado(const char *texto, int xInicial, int largura, int linha);

void telaDesenharBox(
    int x,
    int y,
    int largura,
    int altura
);
