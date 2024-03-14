#include "raylib.h"
#include "menu.h"
#include "jogo.h"

int main()
{

    SetConfigFlags(FLAG_VSYNC_HINT); // isso veio no codigo q os monitores deram, n mexi

    InitWindow(screenWidth, screenHeight, "Jogo"); // inicializa a janela do jogo

    GameState currentState = MENU;
    InitAudioDevice();

    while (!WindowShouldClose() && currentState != EXIT)
    { // loop principal do jogo

        switch (currentState)
        {
        case MENU:
            currentState = MenuState(); // Atualiza o estado com base na seleção do usuário
            break;
        case GAMEPLAY:
            currentState = GameplayState(); // Atualiza o estado com base na lógica do jogo
            break;
        case CREDITS:
            currentState = CreditsState(); // Abre a tela de créditos
            break;
        case GAMEOVER:
            currentState = GameOver(); // Em caso de morte, abre a tela de game over
            break;
        case EXIT:
            CloseWindow();
            return 0;
        }
    }
    CloseWindow(); // fecha a janela

    return 0;
}
