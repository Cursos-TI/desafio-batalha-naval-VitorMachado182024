#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3

int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

void inicializarTabuleiro() {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

void imprimirTabuleiro() {
    printf("    ");
    for (int col = 0; col < TAMANHO_TABULEIRO; col++) {
        printf(" %c ", 'A' + col);
    }
    printf("\n");

    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d |", i + 1);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf(" %d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int podePosicionarHorizontal(int linha, int coluna) {
    if (coluna + TAMANHO_NAVIO - 1 >= TAMANHO_TABULEIRO) return 0;
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linha][coluna + i] != AGUA) return 0;
    }
    return 1;
}

int podePosicionarVertical(int linha, int coluna) {
    if (linha + TAMANHO_NAVIO - 1 >= TAMANHO_TABULEIRO) return 0;
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linha + i][coluna] != AGUA) return 0;
    }
    return 1;
}

int podePosicionarDiagonalPrincipal(int linha, int coluna) {
    if (linha + TAMANHO_NAVIO - 1 >= TAMANHO_TABULEIRO || coluna + TAMANHO_NAVIO - 1 >= TAMANHO_TABULEIRO) return 0;
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linha + i][coluna + i] != AGUA) return 0;
    }
    return 1;
}

int podePosicionarDiagonalSecundaria(int linha, int coluna) {
    if (linha + TAMANHO_NAVIO - 1 >= TAMANHO_TABULEIRO || coluna - (TAMANHO_NAVIO - 1) < 0) return 0;
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linha + i][coluna - i] != AGUA) return 0;
    }
    return 1;
}

void posicionarHorizontal(int linha, int coluna) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha][coluna + i] = NAVIO;
    }
}

void posicionarVertical(int linha, int coluna) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha + i][coluna] = NAVIO;
    }
}

void posicionarDiagonalPrincipal(int linha, int coluna) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha + i][coluna + i] = NAVIO;
    }
}

void posicionarDiagonalSecundaria(int linha, int coluna) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha + i][coluna - i] = NAVIO;
    }
}

int main() {
    inicializarTabuleiro();

    if (podePosicionarHorizontal(2, 3)) {
        posicionarHorizontal(2, 3);
    }
    if (podePosicionarVertical(5, 7)) {
        posicionarVertical(5, 7);
    }
    if (podePosicionarDiagonalPrincipal(4, 0)) {
        posicionarDiagonalPrincipal(4, 0);
    }
    if (podePosicionarDiagonalSecundaria(1, TAMANHO_TABULEIRO - 1)) {
        posicionarDiagonalSecundaria(1, TAMANHO_TABULEIRO - 1);
    }

    imprimirTabuleiro();

    return 0;
}
