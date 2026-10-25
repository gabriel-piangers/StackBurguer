#include <vector>
#include "constants.h"
#include "cards.h"

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

void LoadTextures() {
    BREAD_B_TEXTURE = LoadTexture("assets/items/Tomato.png");
    BREAD_T_TEXTURE = LoadTexture("assets/items/Tomato.png");
    KETCHUP_TEXTURE = LoadTexture("assets/items/Tomato.png");
    MUSTARD_TEXTURE = LoadTexture("assets/items/Tomato.png");
    PICKLES_TEXTURE = LoadTexture("assets/items/Tomato.png");
    LETTUCE_TEXTURE = LoadTexture("assets/items/Tomato.png");
    TOMATO_TEXTURE = LoadTexture("assets/items/Tomato.png");
    TOMATO_SLICES_TEXTURE = LoadTexture("assets/items/Tomato.png");
    ONIONS_TEXTURE = LoadTexture("assets/items/Onion.png");
    ONIONS_SLICES_TEXTURE = LoadTexture("assets/items/Onion.png");
    SWISS_CHEESE_TEXTURE = LoadTexture("assets/items/Tomato.png");
    CHEDDAR_TEXTURE = LoadTexture("assets/items/Tomato.png");
    HAMBURGUER_RAW_TEXTURE = LoadTexture("assets/items/Hamburguer.png");
    HAMBURGUER_TEXTURE = LoadTexture("assets/items/Hamburguer.png");
    BACON_RAW_TEXTURE = LoadTexture("assets/items/Bacon.png");
    BACON_TEXTURE = LoadTexture("assets/items/Bacon.png");
    EGG_RAW_TEXTURE = LoadTexture("assets/items/Tomato.png");
    EGG_TEXTURE = LoadTexture("assets/items/Tomato.png");
    GRILL_TEXTURE = LoadTexture("assets/items/Tomato.png");
    CUTTING_TEXTURE = LoadTexture("assets/items/Tomato.png");
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
}

int main () {
    // Initialization
    InitWindow(SCREEN_W, SCREEN_H, "My first RAYLIB program!");
    SetTargetFPS(60);
    LoadTextures();
    InitCards();

    while (WindowShouldClose() == false) {
        // Update
        UpdateCards();
        
        // Draw
        BeginDrawing();
            ClearBackground(BLACK);
            DrawRectangleLinesEx(CARD_TABLE, 2, RED);
            DrawCards();
        EndDrawing();
    }

    // De-initialization
    UnloadTextures();
    CloseWindow();
}