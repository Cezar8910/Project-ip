#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int carregarPontuacaoMaxima() {
    int pontuacaoMaxima = 0;
    FILE *arquivo = fopen("maxScore.txt", "r");
    if (arquivo != NULL) {
        fscanf(arquivo, "%d", &pontuacaoMaxima);
        fclose(arquivo);
    }
    return pontuacaoMaxima;
}

void salvarPontuacaoMaxima(int novaPontuacao) {
    FILE *arquivo = fopen("maxScore.txt", "w");
    if (arquivo != NULL) {
        fprintf(arquivo, "%d", novaPontuacao);
        fclose(arquivo);
    }
}