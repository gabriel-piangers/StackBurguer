#include "constants.h"
#include "history.h"
#include "cards.h"
#include "costumer.h"
#include "avl.h"
#include "ui.h"

using namespace std;

GameState curGameState = MAIN_MENU;
Game game;

Rectangle COSTUMER_DIV;
Rectangle CARD_TABLE;
Rectangle MENU_DIV;
Rectangle RETURN_BTN_REC;
Rectangle MENU_BTN_REC;

Texture2D BREAD_B_TEXTURE;
Texture2D BREAD_T_TEXTURE;
Texture2D KETCHUP_TEXTURE;
Texture2D MUSTARD_TEXTURE;
Texture2D PICKLES_TEXTURE;
Texture2D LETTUCE_TEXTURE;
Texture2D TOMATO_TEXTURE;
Texture2D TOMATO_SLICES_TEXTURE;
Texture2D ONIONS_TEXTURE;
Texture2D ONIONS_SLICES_TEXTURE;
Texture2D SWISS_CHEESE_TEXTURE;
Texture2D CHEDDAR_TEXTURE;
Texture2D HAMBURGUER_RAW_TEXTURE;
Texture2D HAMBURGUER_TEXTURE;
Texture2D BACON_RAW_TEXTURE;
Texture2D BACON_TEXTURE;
Texture2D EGG_RAW_TEXTURE;
Texture2D EGG_TEXTURE;
Texture2D GRILL_TEXTURE;
Texture2D CUTTING_TEXTURE;

Texture2D COSTUMER_HAPPY_TEXTURE;
Texture2D COSTUMER_NORMAL_TEXTURE;
Texture2D COSTUMER_MAD_TEXTURE;
Texture2D COSTUMER_BACK_TEXTURE;

void LoadTextures() {
    BREAD_B_TEXTURE = LoadTexture("assets/items/Bottom_bread.png");
    BREAD_T_TEXTURE = LoadTexture("assets/items/Top_bread.png");
    KETCHUP_TEXTURE = LoadTexture("assets/items/Ketchup.png");
    MUSTARD_TEXTURE = LoadTexture("assets/items/Mustard.png");
    PICKLES_TEXTURE = LoadTexture("assets/items/Pickles.png");
    LETTUCE_TEXTURE = LoadTexture("assets/items/Lettuce.png");
    TOMATO_TEXTURE = LoadTexture("assets/items/Tomato.png");
    TOMATO_SLICES_TEXTURE = LoadTexture("assets/items/Tomato_slices.png");
    ONIONS_TEXTURE = LoadTexture("assets/items/Onion.png");
    ONIONS_SLICES_TEXTURE = LoadTexture("assets/items/Onion_slices.png");
    SWISS_CHEESE_TEXTURE = LoadTexture("assets/items/Swiss_cheese.png");
    CHEDDAR_TEXTURE = LoadTexture("assets/items/Cheddar_cheese.png");
    HAMBURGUER_RAW_TEXTURE = LoadTexture("assets/items/Hamburguer_raw.png");
    HAMBURGUER_TEXTURE = LoadTexture("assets/items/Hamburguer.png");
    BACON_RAW_TEXTURE = LoadTexture("assets/items/Bacon_raw.png");
    BACON_TEXTURE = LoadTexture("assets/items/Bacon.png");
    EGG_RAW_TEXTURE = LoadTexture("assets/items/Egg.png");
    EGG_TEXTURE = LoadTexture("assets/items/Fried_egg.png");
    GRILL_TEXTURE = LoadTexture("assets/items/Grill.png");
    CUTTING_TEXTURE = LoadTexture("assets/items/Cutting_board.png");
    
    COSTUMER_HAPPY_TEXTURE = LoadTexture("assets/Costumer_happy.png");
    COSTUMER_NORMAL_TEXTURE = LoadTexture("assets/Costumer_normal.png");
    COSTUMER_MAD_TEXTURE = LoadTexture("assets/Costumer_mad.png");
    COSTUMER_BACK_TEXTURE = LoadTexture("assets/Costumer_back.png");
}

void UnloadTextures() {
    UnloadTexture(BREAD_B_TEXTURE);
    UnloadTexture(BREAD_T_TEXTURE);
    UnloadTexture(KETCHUP_TEXTURE);
    UnloadTexture(MUSTARD_TEXTURE);
    UnloadTexture(PICKLES_TEXTURE);
    UnloadTexture(LETTUCE_TEXTURE);
    UnloadTexture(TOMATO_TEXTURE);
    UnloadTexture(TOMATO_SLICES_TEXTURE);
    UnloadTexture(ONIONS_TEXTURE);
    UnloadTexture(ONIONS_SLICES_TEXTURE);
    UnloadTexture(SWISS_CHEESE_TEXTURE);
    UnloadTexture(CHEDDAR_TEXTURE);
    UnloadTexture(HAMBURGUER_RAW_TEXTURE);
    UnloadTexture(HAMBURGUER_TEXTURE);
    UnloadTexture(BACON_RAW_TEXTURE);
    UnloadTexture(BACON_TEXTURE);
    UnloadTexture(EGG_RAW_TEXTURE);
    UnloadTexture(EGG_TEXTURE);
    UnloadTexture(GRILL_TEXTURE);
    UnloadTexture(CUTTING_TEXTURE);
    UnloadTexture(COSTUMER_HAPPY_TEXTURE);
    UnloadTexture(COSTUMER_NORMAL_TEXTURE);
    UnloadTexture(COSTUMER_MAD_TEXTURE);
    UnloadTexture(COSTUMER_BACK_TEXTURE);
}

void InitGame() {
    int curMon = GetCurrentMonitor();
    MENU_DIV = {(GetMonitorWidth(curMon) - MENU_DIV_W)/2.0f, (GetMonitorHeight(curMon) - MENU_DIV_H)/2.0f, MENU_DIV_W, MENU_DIV_H};   
    COSTUMER_DIV = {(GetMonitorWidth(curMon) - TABLE_W)/2.0f, GAME_MARGIN, TABLE_W, COSTUMER_DIV_H};
    CARD_TABLE = {(GetMonitorWidth(curMon) - TABLE_W)/2.0f, COSTUMER_DIV_H + GAME_MARGIN + TABLE_PAD, TABLE_W, TABLE_H};
    RETURN_BTN_REC = {MENU_DIV.x, MENU_DIV.y + MENU_DIV_H + 20.0f, 100.0f, 50.0f};
    MENU_BTN_REC = {(GetScreenWidth() - 300)/2.0f, (GetScreenHeight() - 50)/2.0f, 300.0f, 50.0f};
}

int main () {
    // Initialization
    InitWindow(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()), "My first RAYLIB program!");
    SetTargetFPS(60);
    ToggleBorderlessWindowed();

    InitGame();
    LoadTextures();
    InitHistory("data/historico.txt");
    InitAVL("data/pedidos.txt");

    while (!WindowShouldClose()) {
        if(!IsWindowFocused()) {
            MinimizeWindow();
        }

        switch (curGameState) {
        case MAIN_MENU: {
            Button playBtn(MENU_BTN_REC, "New Game", []() {curGameState = START_GAME;});
            Button historyBtn(MENU_BTN_REC, "History", []() {curGameState = HISTORY;});
            historyBtn.rec.y += 70.0f;
            Button exitBtn(MENU_BTN_REC, "Exit", []() {curGameState = EXIT;});
            exitBtn.rec.y += 2*70.0f;
            Button buttons[] = {playBtn, historyBtn, exitBtn};

            // Updated
            for(int i=0; i<3; i++) buttons[i].update();

            // Draw
            BeginDrawing();
                ClearBackground(BLACK);
                DrawTitle("DadoBurguer");
                for(int i=0; i<3; i++) {
                    buttons[i].draw();
                } 
                    
            EndDrawing();

            break;
        }
        case START_GAME: {
            InitCards();
            InitCostumers();
            game = {0.0f, 0.0f, "ME :/"};
            curGameState = IN_GAME;
        }
        case IN_GAME: {
            // Update
            if(IsGameOver()) curGameState = GAME_OVER;
            game.time += GetFrameTime();
            UpdateCards(game);
            UpdateCostumers();
            
            // Draw
            BeginDrawing();
                ClearBackground(BLACK);
                DrawRectangleLinesEx(CARD_TABLE, 2, RED);
                DrawRectangleLinesEx(COSTUMER_DIV, 2, PURPLE);
                DrawCostumers();
                DrawCards();

                //HUD
                const char* scoreTxt = TextFormat("Score: %.2f", game.score);
                const float fontSize = 20.0f;
                DrawText(scoreTxt, 25.0f, 25.0f, fontSize, RED);
                DrawText(TextFormat("Time: %.2f", game.time), 35.0f + MeasureText(scoreTxt, fontSize), 25.0f, fontSize, RED);
            EndDrawing();

            break;
        }
        case GAME_OVER: {
            Button playBtn(MENU_BTN_REC, "Play again", []() {curGameState = START_GAME;});
            Button menuBtn(MENU_BTN_REC, "Return to Menu", []() {curGameState = MAIN_MENU;});
            menuBtn.rec.y += 70.0f;
            
            // Update
            playBtn.update();
            menuBtn.update();

            // Draw
            BeginDrawing();
                ClearBackground(BLACK);
                DrawTitle("Game Over");
                DrawText(TextFormat("Score: %.2f", game.score), playBtn.rec.x, playBtn.rec.y - 50.0f, 24, RED);
                playBtn.draw();
                menuBtn.draw();
            EndDrawing();

            break;
        }
        case HISTORY: {
            Button returnBtn(RETURN_BTN_REC, "Return", []() {curGameState = MAIN_MENU;});

            // Update
            returnBtn.update();
            UpdateHistory();
            
            // Draw
            BeginDrawing();
                ClearBackground(BLACK);
                DrawTitle("History");
                DrawHistory();
                returnBtn.draw();
            EndDrawing();
            break;
        }
        case EXIT: {
            UnloadTextures();
            CloseWindow();
            return 0;
        }
        default:
            break;
        }
    }

    // De-initialization
    UnloadTextures();
    CloseWindow();
}