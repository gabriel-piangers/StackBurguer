#ifndef COSTUMER_H
#define COSTUMER_H

#include "constants.h"
#include "recipe.h"

#define COSTUMER_AMOUNT 3

struct Costumer {
    Recipe order;
    float patience;
    float difficulty;

    Costumer(): order(Recipe("")), patience(0.0f), difficulty(0.0f) {}

    Costumer(std::string s, int _patience): order(Recipe(s)), patience(_patience), difficulty(0.0f) {}

    void draw(Vector2 pos);
};

// Exports
void InitCostumers();
void DrawCostumers();

#endif