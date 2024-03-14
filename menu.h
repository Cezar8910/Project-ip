#ifndef MENU_H
#define MENU_H

#include "raylib.h"
#include "jogo.h"

#define screenWidth 1280
#define screenHeight 720

GameState MenuState();
GameState GameplayState();
GameState CreditsState();
GameState GameOver();

#endif