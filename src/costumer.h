#ifndef COSTUMER_H
#define COSTUMER_H

#include "constants.h"
#include "recipe.h"
#include "utils.h"

#define COSTUMER_AMOUNT 3
#define COSTUMER_TEXTURE_H 128
#define COSTUMER_TEXTURE_W 128
#define COSTUMER_WALK_DURATION 2 //seconds

enum COSTUMER_STATE {
    ARRIVING,
    MAD, // 1
    NORMAL, // 2
    HAPPY, // 3
    LEAVING,
    EMPTY
};

struct Costumer {
    Vector2 pos;
    Recipe order;
    float patience;
    float timer;
    float difficulty;
    COSTUMER_STATE state;

    Costumer(): state(EMPTY) {}

    Costumer(Vector2 _pos, std::string s, int _patience):
        pos(_pos), order(Recipe(s)), patience(_patience), difficulty(GetCostumerDifficulty(s, _patience)), state(ARRIVING) {}

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