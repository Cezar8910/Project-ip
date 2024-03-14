#ifndef ARMAS_H
#define ARMAS_H
#include "raylib.h"
#define Quant_projeteis 100

typedef struct
{
    Rectangle projetil_retan; // rectangle é um struct com largura altura e posição x,y(cheque raylib.h)
    bool ativo;
    Texture2D texturaProjetil;
} Projetil;

void inicializaProjeteis(Projetil *baixo, Projetil *frente);
void atiraFrente(Projetil *frente, bool *teclaR, Rectangle *jogador);
void atiraBaixo(Projetil *baixo, bool *teclaEspaco, Rectangle *jogador);
void desenhaProjeteis(Projetil *projetil, Projetil *projetilFrente);

#endif