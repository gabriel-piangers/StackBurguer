#include <vector>
#include "constants.h"
#include "cards.h"

using namespace std;

int main () {
    // Initialization
    InitWindow(SCREEN_W, SCREEN_H, "My first RAYLIB program!");
    SetTargetFPS(60);
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
    CloseWindow();
}