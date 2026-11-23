#include "costumer.h"
#include "cards.h"
#include "reasings.h"
#include "avl.h"
#include "queue.h"
#include "dynamic_vector.h"
#include "utils.h"
#include "ui.h"
#include <raymath.h>

using namespace std;

Costumer costumers[COSTUMER_AMOUNT];
Costumer emptyCostumer;
Queue<Costumer> costumerQueue;
DynamicVector<TextPopUp> popUps;

Vector2 GetCostumerPos(int i) {
    return {COSTUMER_DIV.x + i*COSTUMER_DIV.width/COSTUMER_AMOUNT, COSTUMER_DIV.y};
}

Rectangle GetCostumerRec(Vector2 pos) {
    return {pos.x, pos.y + COSTUMER_TEXTURE_H, COSTUMER_TEXTURE_W, COSTUMER_DIV.height - COSTUMER_TEXTURE_H};
}

Costumer& GetCollisionCostumer(Rectangle rec) {
    for(int i=0; i<COSTUMER_AMOUNT; i++) {
        if(costumers[i].state == EMPTY || costumers[i].state == ARRIVING || costumers[i].state == LEAVING) continue;
        if(CheckCollisionRecs(GetCostumerRec(GetCostumerPos(i)), rec)) return costumers[i];
    }
    return emptyCostumer;
}

Costumer GetRandomCostumer(int difficulty) {
    difficulty = (int) Clamp(1.0, (float) difficulty, 4.0);
    float d = RandomFloat(difficulty*2.0f, (difficulty+1)*2.0f);
    return GetCostumerByDifficulty(d);
}

void ScheduleNextCostumer(float time) {
    if(costumerQueue.empty()) return;
    auto f = [](){
        for(int i=0; i<COSTUMER_AMOUNT; i++) {
            if(costumers[i].state == EMPTY && !costumerQueue.empty()) {
                costumers[i] = costumerQueue.pop();
                break;
            }
        }
    };

    Schedule(-1, time, f);
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

    for(int i=0; i<COSTUMER_AMOUNT; i++) costumers[i].state = EMPTY;
    costumers[1] = costumerQueue.pop();
    ScheduleNextCostumer(15.0f);
    ScheduleNextCostumer(40.0f);
}

void DrawCostumers() {
    for(int i=0; i<COSTUMER_AMOUNT; i++) costumers[i].draw(GetCostumerPos(i));
    for(int i=0; i<popUps.size; i++) popUps[i].draw();
}

void UpdateCostumers() {
    for(int i=0; i<COSTUMER_AMOUNT; i++) costumers[i].update();
    for(int i=0; i<popUps.size; i++) {
        if(!popUps[i].keepAlive()) popUps.remove(i);
        else popUps[i].update();
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
        float scale = EaseQuadIn(this->timer, 0.0f, 1.0f, COSTUMER_WALK_DURATION);
        DrawTextureEx(texture, pos, 0.0f, scale, WHITE);
        break;
    }
    case LEAVING: {
        float scale = EaseQuadOut(this->timer, 1.0f, -1.0f, COSTUMER_WALK_DURATION);
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
            ScheduleNextCostumer(RandomFloat(2.0f, 5.0f));
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
    float score = this->difficulty * this->state;

    this->state = LEAVING;
    this->timer = 0.0f;

    string scoreStr = "+" + to_string((int)(score)) + "." + to_string((int)((score - (int)score)*100.0f));
    TextPopUp popUp(GetMousePosition(), scoreStr);
    popUps.insert(popUp);

    return score;
}
