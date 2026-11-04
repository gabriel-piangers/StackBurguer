#include <vector>
#include "constants.h"
#include "cards.h"
#include "costumer.h"

using namespace std;

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
    
    COSTUMER_HAPPY_TEXTURE = LoadTexture("assets/costumer_happy.png");
    COSTUMER_NORMAL_TEXTURE = LoadTexture("assets/costumer_normal.png");
    COSTUMER_MAD_TEXTURE = LoadTexture("assets/costumer_mad.png");
    COSTUMER_BACK_TEXTURE = LoadTexture("assets/costumer_back.png");
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

int main () {
    // Initialization
    InitWindow(SCREEN_W, SCREEN_H, "My first RAYLIB program!");
    SetTargetFPS(60);
    LoadTextures();
    InitCards();
    InitCostumers();

    while (WindowShouldClose() == false) {
        // Update
        UpdateCards();
        UpdateCostumers();
        
        // Draw
        BeginDrawing();
            ClearBackground(BLACK);
            DrawRectangleLinesEx(CARD_TABLE, 2, RED);
            DrawRectangleLinesEx(COSTUMER_DIV, 2, PURPLE);
            DrawCostumers();
            DrawCards();
        EndDrawing();
    }

    // De-initialization
    UnloadTextures();
    CloseWindow();
}