#include "costumer.h"
#include "cards.h"
#include "reasings.h"
#include "avl.h"
#include "queue.h"
#include <raymath.h>

Costumer costumers[COSTUMER_AMOUNT];
Costumer emptyCostumer;
Queue<Costumer> costumerQueue;

Vector2 GetCostumerPos(int i) {
    return {COSTUMER_DIV.x + i*COSTUMER_DIV.width/COSTUMER_AMOUNT, COSTUMER_DIV.y};
}

Rectangle GetCostumerRec(Vector2 pos) {
    return {pos.x, pos.y + COSTUMER_TEXTURE_H, COSTUMER_TEXTURE_W, COSTUMER_DIV.height - COSTUMER_TEXTURE_H};
}

Costumer& GetCollisionCostumer(Rectangle rec) {
    for(int i=0; i<COSTUMER_AMOUNT; i++) {
        if(costumers[i].state != EMPTY && CheckCollisionRecs(GetCostumerRec(GetCostumerPos(i)), rec)) return costumers[i];
    }
    return emptyCostumer;
}

Costumer GetRandomCostumer(int difficulty) {
    difficulty = (int) Clamp(1.0, (float) difficulty, 4.0);
    std::uniform_real_distribution<float> dist(2.0f*difficulty, 2.0f*difficulty + 2.0f);
    float d = dist(rng);

    return GetCostumerByDifficulty(d);
}

void InitCostumers() {
    costumerQueue.clear();
    costumerQueue.insert(GetRandomCostumer(1)); // Easy
    costumerQueue.insert(GetRandomCostumer(1)); // Easy
    costumerQueue.insert(GetRandomCostumer(1)); // Easy
    costumerQueue.insert(GetRandomCostumer(2)); // Medium
    costumerQueue.insert(GetRandomCostumer(2)); // Medium
    costumerQueue.insert(GetRandomCostumer(2)); // Medium
    costumerQueue.insert(GetRandomCostumer(3)); // Hard
    costumerQueue.insert(GetRandomCostumer(3)); // Hard
    costumerQueue.insert(GetRandomCostumer(4)); // Very hard

    costumers[0] = costumerQueue.pop();
    costumers[1] = costumerQueue.pop();
    costumers[2] = costumerQueue.pop();
}

void DrawCostumers() {
    for(int i=0; i<COSTUMER_AMOUNT; i++) costumers[i].draw(GetCostumerPos(i));
}

void UpdateCostumers() {
    for(int i=0; i<COSTUMER_AMOUNT; i++) {
        if(costumers[i].state != EMPTY) costumers[i].update();
        else if(!costumerQueue.empty()) costumers[i] = costumerQueue.pop();
    }
}

bool IsGameOver() {
    if(!costumerQueue.empty()) return false;
    
    bool gameOver = true;
    for(int i=0; i<COSTUMER_AMOUNT; i++) {
        if(costumers[i].state != EMPTY) gameOver = false;
    }

    return gameOver;
}

Texture2D GetCostumerTexture(COSTUMER_STATE state) {
    switch (state) {
    case NORMAL:
        return COSTUMER_NORMAL_TEXTURE;
    case MAD:
        return COSTUMER_MAD_TEXTURE;
    case LEAVING:
        return COSTUMER_BACK_TEXTURE;            
    default:
        return COSTUMER_HAPPY_TEXTURE;
    }
}

void Costumer::draw(Vector2 pos) {
    if(this->state == EMPTY) return; // emptyCostumer
    Texture2D texture = GetCostumerTexture(this->state);
    switch (state) {
    case ARRIVING: {
        float scale = EaseLinearIn(this->timer, 0.0f, 1.0f, COSTUMER_WALK_DURATION);
        DrawTextureEx(texture, pos, 0.0f, scale, WHITE);
        break;
    }
    case LEAVING: {
        float scale = EaseLinearIn(this->timer, 1.0f, -1.0f, COSTUMER_WALK_DURATION);
        DrawTextureEx(texture, pos, 0.0f, scale, WHITE);
        break;
    }
    default:
        DrawTextureEx(texture, pos, 0.0f, 1.0f, this->patience>0.0f ? WHITE : RED);
        this->order.draw({pos.x + COSTUMER_TEXTURE_W + 10, pos.y});
        DrawRectangleLinesEx(GetCostumerRec(pos), 1.0f, GREEN);
        break;
    }
}

void Costumer::update() {
    if(this->state == EMPTY) return; // emptyCostumer
    this->timer += GetFrameTime();

    switch (this->state) {
    case ARRIVING:
        if(this->timer >= COSTUMER_WALK_DURATION) {
            this->timer = 0.0f;
            this->state = HAPPY;
        }
        break;
    case LEAVING:
        if(this->timer >= COSTUMER_WALK_DURATION) {
            this->timer = 0.0f;
            this->state = EMPTY;
        }
        break;
    default:
        if(this->timer <= this->patience*0.5f) {
            this->state = HAPPY;
        } else if(this->timer <= this->patience*0.75f) {
            this->state = NORMAL;
        } else if(this->timer <= this->patience) {
            this->state = MAD;
        } else {
            this->timer = 0.0f;
            this->state = LEAVING;
        }
    }
}

float Costumer::score() {
    this->state = LEAVING;
    this->timer = 0.0f;
    return this->difficulty * this->state;
}
