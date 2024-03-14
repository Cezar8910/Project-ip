#ifndef INIMIGOS_H
#define INIMIGOS_H
#include "raylib.h"
#define Quant_inimigos 20

typedef struct
{
    Rectangle solo_retan; // alem disso usei essa struct pois tem uma função que detecta colisão entre retangulos, mais facil assim
    bool ativo;
    int direcao; // inimigos no solo spawnam num local aleatorio do solo e vão para esquerda ou direita
    Texture2D texturaCapetinha;

} Inimigo_solo;

typedef struct
{
    Rectangle voa_retan;
    bool ativo;
    int vida;           // inimigos voadores podem levar mais de um tiro(botei entre 2 e 4 mas da pra mudar) e a quantidade de tiros que aguenta é igual a quantidade de tempo adicionado ao timer
    int TempoAdicional; // variável que iguala a vida para adicionar tempo ao timer mais facilmente
    Texture2D texturaMorcego;
} Inimigo_voa;

void inicializaInimigos(Inimigo_solo *ini_solo, Inimigo_voa *ini_voa);
void spawnaCapetinha(Inimigo_solo *solo, int alturaChao);
void spawnaMorceguinhos(Inimigo_voa *voa, int alturaChao);
void desenhaMorceguinhos(Inimigo_voa *ini_voa);
void desenhaCapetinha(Inimigo_solo *ini_solo);

#endif