#include "constants.h"
#include "history.h"
#include "cards.h"
#include "costumer.h"
#include "shop.h"
#include "event_system.h"
#include "avl.h"
#include "ui.h"
#include "metrics.h"

using namespace std;

GameState curGameState = MAIN_MENU;
Game game;

Rectangle COSTUMER_DIV;
Rectangle CARD_TABLE;
Rectangle MENU_DIV;
Rectangle RETURN_BTN_REC;
Rectangle MENU_BTN_REC;

// Menu buttons and text
AnimatedText gameTitle(WAVING, {0, 0}, "Dado Burguer", 90.0f, 0.2f, 1.8f, 64.0f, GOLD);
AnimatedText gameOverTitle(SHAKING, {0, 0}, "Game Over", 40.0f, 0.3f, 1.0f, 64.0f, RED);
Button playBtn({0, 0, 0, 0}, "New Game", []() {curGameState = START_GAME;});
Button historyBtn({0, 0, 0, 0}, "History", []() {curGameState = HISTORY;});
Button exitBtn({0, 0, 0, 0}, "Exit", []() {curGameState = EXIT;});
Button continueBtn({0, 0, 0, 0}, "Continue", []() {curGameState = IN_GAME;});
Button menuBtn({0, 0, 0, 0}, "Return to Menu", []() {curGameState = MAIN_MENU;});
Button playAgainBtn({0, 0, 0, 0}, "Play again", []() {curGameState = START_GAME;});
Button returnBtn({0, 0, 0, 0}, "Return", []() {curGameState = MAIN_MENU;});

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

Texture2D ROTTEN_TAG_TEXTURE;

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
    
    ROTTEN_TAG_TEXTURE = LoadTexture("assets/Rotten_tag.png");

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
    UnloadTexture(ROTTEN_TAG_TEXTURE);
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

    gameTitle.setPos(GetTitlePos(gameTitle.text, gameTitle.fontSize));
    gameOverTitle.setPos(GetTitlePos(gameOverTitle.text, gameOverTitle.fontSize));
    playBtn.rec = MENU_BTN_REC;
    historyBtn.rec = MENU_BTN_REC;
    historyBtn.rec.y += 70.0f;
    exitBtn.rec = MENU_BTN_REC;
    exitBtn.rec.y += 2*70.0f;
    continueBtn.rec = MENU_BTN_REC;
    menuBtn.rec = MENU_BTN_REC;
    menuBtn.rec.y += 70.0f;
    playAgainBtn.rec = MENU_BTN_REC;
    returnBtn.rec = RETURN_BTN_REC;
}

void CloseGame() {
    UnloadTextures();
    SaveMetrics();
    CloseWindow();
}

void AddScore(float score) {
    game.score += score;
}

int main (int argc, char* argv[]) {
    string ordersPath = argc >= 2 ? argv[1] : "data/pedidos.txt";
    string historyPath = argc >= 3 ? argv[2] : "data/historico.txt"; 

    // Initialization
    InitWindow(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()), "My first RAYLIB program!");
    SetTargetFPS(60);
    ToggleBorderlessWindowed();
    SetExitKey(KEY_NULL);

    InitGame();
    LoadTextures();
    InitHistory(historyPath);
    InitAVL(ordersPath);    

    while (!WindowShouldClose()) {
        if(!IsWindowFocused()) {
            MinimizeWindow();
        }

        switch (curGameState) {
        case MAIN_MENU: {
            // Updated
            gameTitle.update();
            playBtn.update();
            historyBtn.update();
            exitBtn.update();

            // Draw
            BeginDrawing();
                ClearBackground(BACKGROUND_COLOR);
                gameTitle.draw();
                playBtn.draw();
                historyBtn.draw();
                exitBtn.draw();
                    
            EndDrawing();

            break;
        }
        case START_GAME: {
            InitCards();
            InitCostumers();
            InitShop();
            game = {0.0f, 0.0f, "ME :/"};
            curGameState = IN_GAME;
        }
        case IN_GAME: {
            // Update
            if(IsGameOver()) {
                AddRecord(game.userName, game.score);
                curGameState = GAME_OVER;
            } else if(IsKeyPressed(KEY_ESCAPE)) {
                curGameState = GAME_PAUSED;
            }

            game.time += GetFrameTime();
            UpdateCards();
            UpdateCostumers();
            UpdateShop();
            UpdateEventSystem();
            
            // Draw
            BeginDrawing();
                ClearBackground(BACKGROUND_COLOR);
                DrawRectangleLinesEx(CARD_TABLE, 2, RED);
                DrawRectangleLinesEx(COSTUMER_DIV, 2, PURPLE);
                DrawCostumers();
                DrawShop();
                DrawCards();
                DrawHUD(game.time, game.score);
               
            EndDrawing();

            break;
        }
        case GAME_PAUSED: {
            // Update
            continueBtn.update();
            menuBtn.update();

            BeginDrawing();
                ClearBackground(BACKGROUND_COLOR);
                DrawTitle("Game Paused");
                continueBtn.draw();
                menuBtn.draw();
                DrawHUD(game.time, game.score);
            EndDrawing();

            break;
        }
        case GAME_OVER: {            
            // Update
            gameOverTitle.update();
            playAgainBtn.update();
            menuBtn.update();

            // Draw
            BeginDrawing();
                ClearBackground(BACKGROUND_COLOR);
                DrawText(TextFormat("Score: %.2f", game.score), playAgainBtn.rec.x, playAgainBtn.rec.y - 50.0f, 24, RED);
                gameOverTitle.draw();
                playAgainBtn.draw();
                menuBtn.draw();
            EndDrawing();

            break;
        }
        case HISTORY: {
            // Update
            returnBtn.update();
            UpdateHistory();
            
            // Draw
            BeginDrawing();
                ClearBackground(BACKGROUND_COLOR);
                DrawTitle("History");
                DrawHistory();
                returnBtn.draw();
            EndDrawing();
            break;
        }
        case EXIT: {
            CloseGame();
            return 0;
        }
        default:
            break;
        }
    }

    // De-initialization
    CloseGame();
}