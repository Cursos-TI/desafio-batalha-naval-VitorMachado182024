#include <stdio.h>

int tabuleiro[10][10];

void inicializarTabuleiro() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

void imprimirTabuleiro() {
    printf("    ");
    for (int col = 0; col < 10; ++col) {
        printf(" %c ", 'A' + col); 
    }
    printf("\n");

    for (int i = 0; i < 10; ++i) {
        printf("%2d |", i + 1); 
        for (int j = 0; j < 10; ++j) {
            printf("%2d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    inicializarTabuleiro();

    int linhaHorizontal = 2;
    int colunaHorizontal = 3;

    int linhaVertical = 5;
    int colunaVertical = 7;
 
    for (int i = 0; i < 3; ++i) {
        tabuleiro[linhaHorizontal][colunaHorizontal + i] = 3;
    }

    for (int i = 0; i < 3; ++i) {
        tabuleiro[linhaVertical + i][colunaVertical] = 3;
    }

    imprimirTabuleiro();

    return 0;
}
