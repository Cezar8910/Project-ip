#include "inimigos.h"
#include "raylib.h"

void inicializaInimigos(Inimigo_solo *ini_solo, Inimigo_voa *ini_voa)
{
    for (int inimigos = 0; inimigos < Quant_inimigos; inimigos++)
    {
        ini_solo[inimigos].ativo = false; // inicializa todos os inimigos como inativos
        ini_voa[inimigos].ativo = false;
    }
}

void spawnaCapetinha(Inimigo_solo *solo, int alturaChao)
{
    int flagCapet = 1;
    for (int cont = 0; cont < Quant_inimigos && flagCapet; cont++)
    { // procura um bixinho inativo da direção e posição aleatoria a ele
        if (!solo[cont].ativo)
        {
            solo[cont].ativo = true;
            solo[cont].solo_retan.height = 50;
            solo[cont].solo_retan.width = 50;
            solo[cont].direcao = GetRandomValue(0, 1);
            if (!solo[cont].direcao)
                solo[cont].direcao = -1;
            solo[cont].solo_retan.x = GetRandomValue(0, GetScreenWidth());
            solo[cont].solo_retan.y = (GetScreenHeight() - alturaChao - 30);
            flagCapet = 0;
        }
    }
}

void spawnaMorceguinhos(Inimigo_voa *voa, int alturaChao)
{
    int flagMorceg = 1;
    for (int cont2 = 0; cont2 < Quant_inimigos && flagMorceg; cont2++)
    { // mesma logica do solo mas no ar
        if (!voa[cont2].ativo)
        {
            voa[cont2].ativo = true;
            voa[cont2].voa_retan.height = 50;
            voa[cont2].voa_retan.width = 50;
            voa[cont2].voa_retan.x = GetScreenWidth();
            voa[cont2].voa_retan.y = GetRandomValue(0, GetScreenHeight() - alturaChao - 80);
            voa[cont2].vida = GetRandomValue(2, 4);
            voa[cont2].TempoAdicional = voa[cont2].vida;
            flagMorceg = 0;
        }
    }
}

void desenhaMorceguinhos(Inimigo_voa *voa)
{
    for (int i = 0; i < Quant_inimigos; i++)
    {
        if (voa[i].ativo)
        {
            DrawTexture(voa[i].texturaMorcego, voa[i].voa_retan.x, voa[i].voa_retan.y, RAYWHITE);
        }
    }
}

void desenhaCapetinha(Inimigo_solo *solo)
{
    for (int i = 0; i < Quant_inimigos; i++)
    {
        if (solo[i].ativo)
        {
            DrawTexture(solo[i].texturaCapetinha, solo[i].solo_retan.x, solo[i].solo_retan.y, RAYWHITE);
        }
    }
}