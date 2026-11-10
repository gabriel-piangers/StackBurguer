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
    Recipe order;
    float patience;
    float timer;
    float difficulty;
    COSTUMER_STATE state;

    Costumer(): state(EMPTY) {}

    Costumer(std::string s, int _patience):
        order(Recipe(s)), patience(_patience), difficulty(GetCostumerDifficulty(s, _patience)), state(ARRIVING) {}

    void draw(Vector2 pos);
    void update();
    float score();
};

// Make it a separeted class with template structure
struct QueueNode {
    Costumer costumer;
    QueueNode* next;

    QueueNode(Costumer c): costumer(c), next(nullptr) {}
};

struct Queue {
    int size;
    QueueNode* start;
    QueueNode* end;

    Queue(): size(0), start(nullptr), end(nullptr) {}

    void insert(Costumer costumer);
    Costumer pop();
    void clear();
    bool empty();
};

// Exports
void InitCostumers();
void DrawCostumers();
void UpdateCostumers();
bool IsGameOver();
Costumer& GetCollisionCostumer(Rectangle rec);

#endif