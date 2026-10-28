#ifndef COSTUMER_H
#define COSTUMER_H

#include "constants.h"
#include "recipe.h"

#define COSTUMER_AMOUNT 3

struct Costumer {
    Vector2 pos;
    Recipe order;
    float patience;
    float difficulty;

    Costumer(): pos({0.0f, 0.0f}), order(Recipe("")), patience(0.0f), difficulty(0.0f) {}

    Costumer(Vector2 _pos, std::string s, int _patience): pos(_pos), order(Recipe(s)), patience(_patience), difficulty(0.0f) {}

    void draw();
    void update();
    float score();
    Rectangle getRec();
};

// Exports
void InitCostumers();
void DrawCostumers();
void UpdateCostumers();
Costumer& GetCollisionCostumer(Rectangle rec);

#endif