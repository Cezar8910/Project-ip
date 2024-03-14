// menu.c
#include "raylib.h"
#include "menu.h"
#include "jogo.h"
#include "inimigos.h"
#include "armas.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pontuacao.h"

GameState MenuState()
{
    /* InitAudioDevice(); */

    // carrega a musica do menu
    Music menuMusic = LoadMusicStream("recursos/audio/CyberpunkSonata.mp3");
    menuMusic.looping = true;
    SetMusicVolume(menuMusic, 3.0f);
    PlayMusicStream(menuMusic);

    // carrega o efeito sonoro dos botoes do menu
    Sound menuSoundEffect = LoadSound("recursos/audio/MenuSoundEffect.wav");
    SetSoundVolume(menuSoundEffect, 2.0f);

    // Carrega a imagem de fundo do menu
    Image backgroundImage = LoadImage("recursos/texturas/backgroundMenu.png");
    ImageResize(&backgroundImage, screenWidth, screenHeight);
    Texture2D backgroundMenu = LoadTextureFromImage(backgroundImage);
    UnloadImage(backgroundImage); // Descarrega a imagem da memória, pois não é mais necessária

    // Define os retângulos dos botões do menu principal
    Rectangle playButton = {screenWidth / 2 - 100, 300, 200, 50};
    Rectangle creditsButton = {screenWidth / 2 - 100, 370, 200, 50};
    Rectangle exitButton = {screenWidth / 2 - 100, 440, 200, 50};

    Color normalColor = WHITE; // Cor normal dos botões
    Color hoverColor = GRAY;   // Cor quando o mouse está sobre o botão

    int MaxPont = carregarPontuacaoMaxima();

    while (!WindowShouldClose())
    {
        UpdateMusicStream(menuMusic);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Desenha a imagem de fundo
        DrawTexture(backgroundMenu, 0, 0, WHITE);

        // Desenha o título
        DrawText("AeroInvaders 1.0", screenWidth / 2 - MeasureText("AeroInvaders 1.0", 60) / 2, 150, 60, BLACK);

        // Desenha pontuação maxima na tela se for maior que 0
        if (MaxPont > 0)
            DrawText(TextFormat("Recorde: %d pts", MaxPont), screenWidth - MeasureText(TextFormat("Recorde: %d pts", MaxPont), 40) - 30, 20, 40, WHITE);

        // Lógica para fazer o hover nos botões
        if (CheckCollisionPointRec(GetMousePosition(), playButton))
        {
            DrawRectangleRec(playButton, hoverColor);
            DrawRectangleLinesEx(playButton, 3, BLACK);
        }
        else
        {
            DrawRectangleRec(playButton, normalColor);
            DrawRectangleLinesEx(playButton, 3, BLACK);
        }

        if (CheckCollisionPointRec(GetMousePosition(), creditsButton))
        {
            DrawRectangleRec(creditsButton, hoverColor);
            DrawRectangleLinesEx(creditsButton, 3, BLACK);
        }
        else
        {
            DrawRectangleRec(creditsButton, normalColor);
            DrawRectangleLinesEx(creditsButton, 3, BLACK);
        }

        if (CheckCollisionPointRec(GetMousePosition(), exitButton))
        {
            DrawRectangleRec(exitButton, hoverColor);
            DrawRectangleLinesEx(exitButton, 3, BLACK);
        }
        else
        {
            DrawRectangleRec(exitButton, normalColor);
            DrawRectangleLinesEx(exitButton, 3, BLACK);
        }

        // Desenha os textos dos botões
        DrawText("Jogar", playButton.x + 70, playButton.y + 15, 20, BLACK);
        DrawText("História e créditos", creditsButton.x + 4, creditsButton.y + 15, 20, BLACK);
        DrawText("Sair", exitButton.x + 75, exitButton.y + 15, 20, BLACK);

        // Verifica se algum botão foi clicado
        if (CheckCollisionPointRec(GetMousePosition(), playButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            PlaySound(menuSoundEffect);
            return GAMEPLAY;
        }
        else if (CheckCollisionPointRec(GetMousePosition(), creditsButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            PlaySound(menuSoundEffect);
            return CREDITS;
        }
        else if (CheckCollisionPointRec(GetMousePosition(), exitButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            PlaySound(menuSoundEffect);
            return EXIT;
        }

        EndDrawing();
    }

    UnloadMusicStream(menuMusic);
    UnloadSound(menuSoundEffect);
    // Descarrega a textura da imagem de fundo após sair do loop
    UnloadTexture(backgroundMenu);

    return MENU;
}

GameState GameplayState()
{
    // carrega a musica principal do jogo
    Music mainMusic = LoadMusicStream("recursos/audio/SystemOverload.mp3");
    mainMusic.looping = true;
    SetMusicVolume(mainMusic, 2.0f);
    PlayMusicStream(mainMusic);

    // carrega o efeito sonoro do tiro
    Sound shootSoundEffect = LoadSound("recursos/audio/ShootSoundEffect.wav");
    SetSoundVolume(shootSoundEffect, 2.0f);

    // texturas/assets
    // carrega textura da nave espacial/jogador
    Image naveImage = LoadImage("recursos/texturas/nave.png");
    Image *naveImagePtr = &naveImage;
    ImageResize(naveImagePtr, 90, 90);
    Texture2D nave = LoadTextureFromImage(*naveImagePtr);

    // carrega textura do morcego
    Image morcegoImage = LoadImage("recursos/texturas/morcego.png");
    Image *morcegoImagePtr = &morcegoImage;
    ImageResize(morcegoImagePtr, 60, 60);
    Texture2D morcego = LoadTextureFromImage(*morcegoImagePtr);

    // carrega textura do capetinha
    Image capetinhaImage = LoadImage("recursos/texturas/capetinha.png");
    Image *capetinhaImagePtr = &capetinhaImage;
    ImageResize(capetinhaImagePtr, 60, 60);
    Texture2D capetinha = LoadTextureFromImage(*capetinhaImagePtr);

    // carrega textura dos projeteis para baixo
    Image projetilImage = LoadImage("recursos/texturas/arma.png");
    Image *projetilImagePtr = &projetilImage;
    ImageResize(projetilImagePtr, 50, 50);
    Texture2D projetil = LoadTextureFromImage(*projetilImagePtr);

    // carrega textura dos projeteis para frente
    Image projetilFImage = LoadImage("recursos/texturas/armaFrente.png");
    Image *projetilFImagePtr = &projetilFImage;
    ImageResize(projetilFImagePtr, 50, 50);
    Texture2D projetilF = LoadTextureFromImage(*projetilFImagePtr);

    // carrega fundo principal do jogo
    Image backgroundImage = LoadImage("recursos/texturas/mainbackground.png");
    Image *backgroundImagePtr = &backgroundImage;
    ImageResize(backgroundImagePtr, 1280, 720);
    Texture2D background = LoadTextureFromImage(*backgroundImagePtr);

    // criacao dos inimigos
    Inimigo_solo capetinhas[Quant_inimigos];
    Inimigo_voa morceguinhos[Quant_inimigos];
    float velocidadeCapetinhas = 200.0f;
    float velocidadeMorceguinhos = 200.0f;
    inicializaInimigos(capetinhas, morceguinhos); // funcao para inicializar os inimigos

    // Criação dos projeteis
    Projetil projeteis[Quant_projeteis];
    Projetil projeteisFrente[Quant_projeteis];
    const float velocidadeProjeteis = 800.0f;
    inicializaProjeteis(projeteis, projeteisFrente);

    // garante que a textura vai ser adicionada a cada inimigo
    for (int i = 0; i < Quant_inimigos; i++)
    {
        morceguinhos[i].texturaMorcego = morcego;
        capetinhas[i].texturaCapetinha = capetinha;
    }

    // garante que a textura vai ser adicionada a cada projetil
    for (int i = 0; i < Quant_projeteis; i++)
    {
        projeteis[i].texturaProjetil = projetil;
        projeteisFrente[i].texturaProjetil = projetilF;
    }

    /* const int screenWidth = GetScreenWidth(); // salvando duas variáveis para tamanho da tela
    const int screenHeight = GetScreenHeight(); */
    int alturaSolo = 150;

    Rectangle player = {50, 50, 40, 40};   // Posição do jogador(também uma struct rectangle)
    const float velocidadePlayer = 500.0f; // Velocidade do jogador

    // Define a taxa de quadros que o jogo vai rodar
    SetTargetFPS(60);

    bool apertaEspaco = false; // Variável que auxilia o jogador a só atirar uma vez a cada espaço pressionado
    bool apertaR = false;      // Mesma coisa para atirar para frente
    bool isPaused = false;     // Variável para identificar que o jogo foi pausado

    // variaveis relacionadas aos inimigos
    int tempoDificuldade = 10; // a cada 10 segundos a dificuldade aumenta, alguns limites foram impostos
    float tempoCapetinhas = 0; // tempo q nasce o primeiro capetinha e a cada 1 segundo spawna capetinha(aumentando a frequencia quanto mais o jogador jogar)
    float alterarTempoCapetinha = 2;
    float tempoMorceguinhos = 4; // tempo que nasce o primeiro morceguinho, aumenta a frequencia cada 7 segundos(mas menos)
    float alterarTempoMorceguinhos = 5;

    // variavel que indica o tempo da partida
    int tempoJogo = 30;
    int contadorTempo = 1; // variavel para fazer 1 segundo passar
    char tempoTexto[10] = {0};

    char coordenadas[500] = {0};

    // variável da pontuacao
    int pontuacao = 0;
    char pontuacaoTexto[20] = {0};

    double time = GetTime();
    double inicioGameplay = time;
    double tempoPausaTotal = 0;
    double tempoPausaAux = 0;
    int pontMaxima = carregarPontuacaoMaxima();

    while (!WindowShouldClose() && !IsKeyPressed(KEY_CAPS_LOCK))
    { // loop principal do jogo

        UpdateMusicStream(mainMusic);

        double delta = GetFrameTime();
        time = GetTime() - inicioGameplay - tempoPausaTotal;

        if (time > tempoDificuldade)
        { // a cada 10 segundos aumenta a velocidade dos inimigos e do spawn
            tempoDificuldade += 10;
            velocidadeCapetinhas += 30;
            velocidadeMorceguinhos += 30;
            if (alterarTempoCapetinha >= 0.3)
                alterarTempoCapetinha -= 0.3; // no começo os bixos do solo spawnam a cada 2 segundos, mas diminui gradualmente até 1 a cada 0.3 segundos dps de muito tempo
            if (alterarTempoMorceguinhos >= 1.5)
                alterarTempoMorceguinhos -= 0.3;
        }

        if (time > contadorTempo)
        { // a cada segundo tira um segundo do tempo limite do personagem
            tempoJogo--;
            contadorTempo++;
        }

        // spawnador de inimigos chao
        if (time > tempoCapetinhas)
        {
            tempoCapetinhas += alterarTempoCapetinha;
            spawnaCapetinha(capetinhas, alturaSolo);
        }

        // spawnador de inimigos voadores
        if (time > tempoMorceguinhos)
        { // voadores como são mais fortes aparecem a cada 5 segundos sempre
            tempoMorceguinhos += alterarTempoMorceguinhos;
            spawnaMorceguinhos(morceguinhos, alturaSolo);
        }

        // movimentacao dos inimigos(os dois no mesmo for)
        for (int iniMove = 0; iniMove < Quant_inimigos; iniMove++)
        { // checa qual inimigo ta ativo e move ele, alem disso deleta ele se sair da tela
            if (capetinhas[iniMove].ativo)
            {
                if (capetinhas[iniMove].solo_retan.x <= screenWidth && capetinhas[iniMove].solo_retan.x >= 0)
                    capetinhas[iniMove].solo_retan.x += capetinhas[iniMove].direcao * delta * velocidadeCapetinhas;
                else
                    capetinhas[iniMove].ativo = false;
            }

            if (morceguinhos[iniMove].ativo)
            {
                if (morceguinhos[iniMove].voa_retan.x >= 0)
                    morceguinhos[iniMove].voa_retan.x -= delta * velocidadeMorceguinhos;
                else
                    morceguinhos[iniMove].ativo = false;
            }
        }

        // Pause do jogo
        if (IsKeyPressed(KEY_P) && !isPaused)
        {
            isPaused = true;

            tempoPausaAux = GetTime();

            // gera a imagem do menu de pause
            Image backgroundImage = LoadImage("recursos/texturas/mainbackground.png");
            ImageResize(&backgroundImage, screenWidth, screenHeight);
            Texture2D backgroundMenuPause = LoadTextureFromImage(backgroundImage);
            UnloadImage(backgroundImage);

            Rectangle continuePlayButton = {screenWidth / 2 - 100, 300, 200, 50};
            Rectangle backToMenuButton = {screenWidth / 2 - 100, 400, 200, 50};

            Color normalColor = WHITE;
            Color hoverColor = GRAY;

            while (!WindowShouldClose() && isPaused)
            {
                BeginDrawing();
                ClearBackground(RAYWHITE);

                // Desenha a imagem de fundo
                DrawTexture(backgroundMenuPause, 0, 0, WHITE);

                // Lógica para fazer o hover nos botões
                if (CheckCollisionPointRec(GetMousePosition(), continuePlayButton))
                {
                    DrawRectangleRec(continuePlayButton, hoverColor);
                    DrawRectangleLinesEx(continuePlayButton, 3, BLACK);
                }
                else
                {
                    DrawRectangleRec(continuePlayButton, normalColor);
                    DrawRectangleLinesEx(continuePlayButton, 3, BLACK);
                }

                if (CheckCollisionPointRec(GetMousePosition(), backToMenuButton))
                {
                    DrawRectangleRec(backToMenuButton, hoverColor);
                    DrawRectangleLinesEx(backToMenuButton, 3, BLACK);
                }
                else
                {
                    DrawRectangleRec(backToMenuButton, normalColor);
                    DrawRectangleLinesEx(backToMenuButton, 3, BLACK);
                }

                // Desenha os textos dos botões
                DrawText("Voltar ao Jogo", continuePlayButton.x + 25, continuePlayButton.y + 15, 20, BLACK);
                DrawText("Voltar ao menu", backToMenuButton.x + 25, backToMenuButton.y + 15, 20, BLACK);

                if (CheckCollisionPointRec(GetMousePosition(), continuePlayButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    tempoPausaTotal += GetTime() - tempoPausaAux;
                    isPaused = false;
                }

                else if (CheckCollisionPointRec(GetMousePosition(), backToMenuButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    return MENU;
                }
                EndDrawing();
            }
            UnloadTexture(backgroundMenuPause);
        }

        // Movimentação do jogador
        if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
            player.y -= velocidadePlayer * delta;
        if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
            player.y += velocidadePlayer * delta;
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
            player.x += velocidadePlayer * delta;
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
            player.x -= velocidadePlayer * delta;

        // Restrições para manter o jogador dentro da tela
        if (player.x > screenWidth - 50)
            player.x = screenWidth - 50;
        if (player.x < 25)
            player.x = 25;
        if (player.y > (screenHeight - alturaSolo - 50))
            player.y = screenHeight - alturaSolo - 50;
        if (player.y < 0)
            player.y = 0;

        // Atirar projéteis para frente
        if (IsKeyDown(KEY_R) && !apertaR)
        {
            PlaySound(shootSoundEffect);
            atiraFrente(projeteisFrente, &apertaR, &player);
        }
        // isso aq é pra vc só consguir atirar uma vez a cada aperto da tecla
        if (IsKeyReleased(KEY_R))
            apertaR = false;

        // Atirar projéteis para baixo
        if (IsKeyDown(KEY_SPACE) && !apertaEspaco)
        {
            PlaySound(shootSoundEffect);
            atiraBaixo(projeteis, &apertaEspaco, &player);
        }
        if (IsKeyReleased(KEY_SPACE))
            apertaEspaco = false;

        // Movimentação dos projéteis e checagem de colisões
        for (int n = 0; n < Quant_projeteis; n++)
        {
            if (projeteis[n].ativo)
            {
                for (int o = 0; o < Quant_inimigos; o++)
                {
                    if (CheckCollisionRecs(projeteis[n].projetil_retan, capetinhas[o].solo_retan))
                    {
                        capetinhas[o].ativo = false;
                        capetinhas[o].solo_retan.height = 0;
                        capetinhas[o].solo_retan.width = 0;
                        projeteis[n].ativo = false;
                        tempoJogo++;
                        pontuacao += 10;
                    }

                    if (CheckCollisionRecs(projeteis[n].projetil_retan, morceguinhos[o].voa_retan))
                    {
                        projeteis[n].ativo = false;
                        if (morceguinhos[o].vida == 1)
                        {
                            morceguinhos[o].ativo = false;
                            morceguinhos[o].voa_retan.height = 0;
                            morceguinhos[o].voa_retan.width = 0;
                            tempoJogo += morceguinhos[o].TempoAdicional * 0.5;
                            pontuacao += 10 * morceguinhos[o].TempoAdicional;
                        }
                        else
                            morceguinhos[o].vida--;
                    }
                }

                if ((projeteis[n].projetil_retan.y <= screenHeight - alturaSolo) && projeteis[n].ativo)
                    projeteis[n].projetil_retan.y += velocidadeProjeteis * delta;
                else
                    projeteis[n].ativo = false;
            }

            if (projeteisFrente[n].ativo)
            {
                for (int p = 0; p < Quant_inimigos; p++)
                {
                    if (CheckCollisionRecs(projeteisFrente[n].projetil_retan, capetinhas[p].solo_retan))
                    {
                        capetinhas[p].ativo = false;
                        capetinhas[p].solo_retan.height = 0;
                        capetinhas[p].solo_retan.width = 0;
                        projeteisFrente[n].ativo = false;
                        tempoJogo++;
                        pontuacao += 10;
                    }

                    if (CheckCollisionRecs(projeteisFrente[n].projetil_retan, morceguinhos[p].voa_retan))
                    {
                        projeteisFrente[n].ativo = false;
                        if (morceguinhos[p].vida == 1)
                        {
                            morceguinhos[p].ativo = false;
                            morceguinhos[p].voa_retan.height = 0;
                            morceguinhos[p].voa_retan.width = 0;
                            tempoJogo += morceguinhos[p].TempoAdicional * 0.5;
                            pontuacao += 10 * morceguinhos[p].TempoAdicional;
                        }
                        else
                            morceguinhos[p].vida--;
                    }
                }

                if ((projeteisFrente[n].projetil_retan.x <= screenWidth) && projeteisFrente[n].ativo)
                {

                    projeteisFrente[n].projetil_retan.x += velocidadeProjeteis * delta;
                }
                else
                {

                    projeteisFrente[n].ativo = false;
                }
            }
        }

        // colisão do personagem com os inimigos
        for (int ini = 0; ini < Quant_inimigos; ini++)
        {

            if (capetinhas[ini].ativo)
            {
                if (CheckCollisionRecs(player, capetinhas[ini].solo_retan))
                {
                    if (pontuacao > pontMaxima)
                    {
                        pontMaxima = pontuacao;
                        salvarPontuacaoMaxima(pontMaxima);
                    }
                    return GAMEOVER;
                }
            }

            if (morceguinhos[ini].ativo)
            {
                if (CheckCollisionRecs(player, morceguinhos[ini].voa_retan))
                {
                    if (pontuacao > pontMaxima)
                    {
                        pontMaxima = pontuacao;
                        salvarPontuacaoMaxima(pontMaxima);
                    }
                    return GAMEOVER;
                }
            }
        }

        if (tempoJogo == 0)
        {

            return GAMEOVER;
        }

        DrawRectangle(0, screenHeight - alturaSolo, screenWidth, alturaSolo, BLANK); // chao
        BeginDrawing();                                                              // aqui começa a desenhar na tela
        ClearBackground(RAYWHITE);

        DrawTextureEx(background, (Vector2){0, 0}, 0.0f, 1.0f, WHITE);

        DrawTexture(nave, player.x, player.y, RAYWHITE);

        desenhaMorceguinhos(morceguinhos);
        desenhaCapetinha(capetinhas);
        desenhaProjeteis(projeteis, projeteisFrente);

        sprintf(coordenadas, "player (%02.02f, %02.02f)", player.x, player.y); // isso aqui mostra as coordenadas do jogador, tiraremos futuramente
        DrawText(coordenadas, 10, 10, 20, DARKGRAY);
        sprintf(tempoTexto, "%d", tempoJogo);
        DrawText(tempoTexto, screenWidth - 80, 10, 60, DARKGRAY);
        sprintf(pontuacaoTexto, "%d", pontuacao);
        DrawText(pontuacaoTexto, screenWidth - 280, 10, 60, DARKBLUE);

        // Desenho dos objetos na tela
        DrawRectangleRec(player, BLANK); // jogador

        for (int l = 0; l < Quant_projeteis; l++)
        { // projeteis do jogador
            if (projeteis[l].ativo)
                DrawRectangleRec(projeteis[l].projetil_retan, BLANK);
            if (projeteisFrente[l].ativo)
                DrawRectangleRec(projeteisFrente[l].projetil_retan, BLANK);
        }

        for (int k = 0; k < Quant_inimigos; k++)
        {
            if (capetinhas[k].ativo)
                DrawRectangleRec(capetinhas[k].solo_retan, BLANK);
            if (morceguinhos[k].ativo)
                DrawRectangleRec(morceguinhos[k].voa_retan, BLANK);
        }

        EndDrawing(); // finaliza o que tem q desenhar
    }

    UnloadMusicStream(mainMusic);
    UnloadSound(shootSoundEffect);
    CloseAudioDevice();

    UnloadTexture(nave);
    UnloadTexture(background);
    UnloadTexture(morcego);
    UnloadTexture(capetinha);
    return GAMEPLAY;
}

GameState CreditsState()
{
    Image backgroundImage = LoadImage("recursos/texturas/backgroundCredits.png");
    ImageResize(&backgroundImage, screenWidth, screenHeight);
    Texture2D backgroundMenu = LoadTextureFromImage(backgroundImage);
    UnloadImage(backgroundImage);

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_E))
        {
            return MENU;
            UnloadTexture(backgroundMenu);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTexture(backgroundMenu, 0, 0, WHITE);
        DrawText("Esse é um jogo desenvolvido pelos estudantes de Engenharia da Computação do Cin de 2023.2:", 50, 80, 20, WHITE);
        DrawText("Arthur Alves", 50, 100, 20, WHITE);
        DrawText("Cezar Galvão", 50, 120, 20, WHITE);
        DrawText("Eduardo Alves", 50, 140, 20, WHITE);
        DrawText("Manoel David", 50, 160, 20, WHITE);
        DrawText("Marcos Alexandre", 50, 180, 20, WHITE);
        DrawText("Matheus Barbosa", 50, 200, 20, WHITE);
        DrawText("Você é um estudante do cin e está trabalhando em um sensor de ondas de rádio muito mais eficiente que qualquer", 50, 260, 20, WHITE);
        DrawText("outro já feito pela humanidade. Um dia, em um fim de espediente no laboratório, você recebe um sinal de ataque", 50, 280, 20, WHITE);
        DrawText("no seu super sensor!! Sem pestanejar você pega uma nave no porão do cin e parte para o espaço, seu objetivo é se ", 50, 300, 20, WHITE);
        DrawText("manter vivo o máximo possível derrotar todos os inimigos que aparecerem, quanto mais você derrotar menos sobram", 50, 320, 20, WHITE);
        DrawText("para destruir a humanidade, boa sorte! Seu sacrifício não será esquecido.", 50, 340, 20, WHITE);
        DrawText("Aperte E para voltar ao menu", 50, 650, 20, WHITE);

        EndDrawing();
    }
    UnloadTexture(backgroundMenu);

    return MENU;
}

GameState GameOver()
{
    // gerar a imagem do jogo para a tela de game over
    Image backgroundImage = LoadImage("recursos/texturas/mainbackground.png");
    ImageResize(&backgroundImage, screenWidth, screenHeight);
    Texture2D backgroundGameOver = LoadTextureFromImage(backgroundImage);
    UnloadImage(backgroundImage);

    Rectangle retryButton = {screenWidth / 2 - 100, 300, 250, 60};
    Rectangle backToMenuButton = {screenWidth / 2 - 100, 400, 250, 60};

    Color normalColor = WHITE;
    Color hoverColor = GRAY;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Desenha a imagem de fundo
        DrawTexture(backgroundGameOver, 0, 0, WHITE);

        DrawText("GAME OVER", screenWidth / 2 - MeasureText("GAME OVER", 80) / 2, 100, 80, WHITE);

        // Lógica para fazer o hover nos botões
        if (CheckCollisionPointRec(GetMousePosition(), retryButton))
        {
            DrawRectangleRec(retryButton, hoverColor);
            DrawRectangleLinesEx(retryButton, 3, BLACK);
        }
        else
        {
            DrawRectangleRec(retryButton, normalColor);
            DrawRectangleLinesEx(retryButton, 3, BLACK);
        }

        if (CheckCollisionPointRec(GetMousePosition(), backToMenuButton))
        {
            DrawRectangleRec(backToMenuButton, hoverColor);
            DrawRectangleLinesEx(backToMenuButton, 3, BLACK);
        }
        else
        {
            DrawRectangleRec(backToMenuButton, normalColor);
            DrawRectangleLinesEx(backToMenuButton, 3, BLACK);
        }

        // Desenha os textos dos botões
        DrawText("Tentar Novamente", retryButton.x + 30, retryButton.y + 15, 20, BLACK);
        DrawText("Voltar ao menu", backToMenuButton.x + 40, backToMenuButton.y + 15, 20, BLACK);

        if (CheckCollisionPointRec(GetMousePosition(), retryButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            return GAMEPLAY;
        }

        else if (CheckCollisionPointRec(GetMousePosition(), backToMenuButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {

            /* ClearWindowState(GameOver()); */
            return MENU;
        }
        EndDrawing();
    }
    UnloadTexture(backgroundGameOver);

    return MENU;
}
