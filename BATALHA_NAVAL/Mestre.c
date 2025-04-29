#include <stdio.h>
#define TAMANHO_TABULEIRO 10
#define TAMANHO_HABILIDADE 5
#define TAMANHO_NAVIO 3
#define AFETADO_CONE 5
#define AFETADO_OCTAEDRO 5
#define AFETADO_CRUZ 5
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
            if (tabuleiro[i][j] == NAVIO) {
                printf(" %d ", NAVIO);
            } else if (tabuleiro[i][j] == AFETADO_CONE) {
                printf(" %d ", AFETADO_CONE);
            } else if (tabuleiro[i][j] == AFETADO_OCTAEDRO) {
                printf(" %d ", AFETADO_OCTAEDRO);
            } else if (tabuleiro[i][j] == AFETADO_CRUZ) {
                printf(" %d ", AFETADO_CRUZ);
            } else {
                printf(" %d ", AGUA);
            }
        }
        printf("\n");
    }
    printf("\n");
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

void gerarCone(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (i + (j >= 2 ? j - 2 : 2 - j) <= 2) {
                matriz[i][j] = AFETADO_CONE;
            } else {
                matriz[i][j] = AGUA;
            }
        }
    }
}

void gerarOctaedro(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            int di = i - 2;
            if (di < 0) di = -di;
            int dj = j - 2;
            if (dj < 0) dj = -dj;
            if (di + dj <= 2) {
                matriz[i][j] = AFETADO_OCTAEDRO;
            } else {
                matriz[i][j] = AGUA;
            }
        }
    }
}

void gerarCruz(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (i == 2 || j == 2) { 
                matriz[i][j] = AFETADO_CRUZ;
            } else {
                matriz[i][j] = AGUA;
            }
        }
    }
}

void aplicarHabilidade(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], int linhaCentro, int colCentro) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            int linhaTabuleiro = linhaCentro + i - 2; 
            int colTabuleiro = colCentro + j - 2;  

            if (linhaTabuleiro >= 0 && linhaTabuleiro < TAMANHO_TABULEIRO &&
                colTabuleiro >= 0 && colTabuleiro < TAMANHO_TABULEIRO) {
                if (matriz[i][j] == AFETADO_CRUZ) {
                    tabuleiro[linhaTabuleiro][colTabuleiro] = AFETADO_CRUZ;
                } else if (matriz[i][j] == AFETADO_CONE) {
                    tabuleiro[linhaTabuleiro][colTabuleiro] = AFETADO_CONE;
                } else if (matriz[i][j] == AFETADO_OCTAEDRO) {
                    tabuleiro[linhaTabuleiro][colTabuleiro] = AFETADO_OCTAEDRO;
                }
            }
        }
    }
}

int main() {
    inicializarTabuleiro();

    if (podePosicionarHorizontal(0, 3)) {
        posicionarHorizontal(0, 3);
    }
    if (podePosicionarVertical(5, 7)) {
        posicionarVertical(5, 7);
    }
    if (podePosicionarDiagonalPrincipal(5, 0)) {
        posicionarDiagonalPrincipal(5, 0);
    }
    if (podePosicionarDiagonalSecundaria(2, TAMANHO_TABULEIRO - 1)) {
        posicionarDiagonalSecundaria(2, TAMANHO_TABULEIRO - 1);
    }

    int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];

    gerarCruz(habilidade);
    aplicarHabilidade(habilidade, 2, 2); 

    gerarCone(habilidade);
    aplicarHabilidade(habilidade, 3, 7); 

    gerarOctaedro(habilidade);
    aplicarHabilidade(habilidade, 6, 4); 

    imprimirTabuleiro();

    return 0;
}
