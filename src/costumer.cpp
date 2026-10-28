#include "costumer.h"
#include "cards.h"

Costumer costumers[COSTUMER_AMOUNT];
Costumer emptyCostumer;

Vector2 GetCostumerPos(int i) {
    return {COSTUMER_DIV.x + i*COSTUMER_DIV.width/COSTUMER_AMOUNT, COSTUMER_DIV.y};
}

Costumer& GetCollisionCostumer(Rectangle rec) {
    for(int i=0; i<COSTUMER_AMOUNT; i++) {
        if(CheckCollisionRecs(costumers[i].getRec(), rec)) return costumers[i];
    }
    return emptyCostumer;
}

void InitCostumers() {
    costumers[0] = Costumer(GetCostumerPos(0), "pbtmcnz", 30.0f);
    costumers[1] = Costumer(GetCostumerPos(1), "nomosnz", 90.0f);
    costumers[2] = Costumer(GetCostumerPos(2), "bpknz", 60.0f);
}

void DrawCostumers() {
    for(int i=0; i<COSTUMER_AMOUNT; i++) costumers[i].draw();
}

void UpdateCostumers() {
    for(int i=0; i<COSTUMER_AMOUNT; i++) costumers[i].update();
}

void Costumer::draw() {
    DrawTextureEx(COSTUMER_TEXTURE, this->pos, 0.0f, 2.0f, this->patience>0.0f ? WHITE : RED);
    this->order.draw({this->pos.x + COSTUMER_TEXTURE.width*2 + 10, this->pos.y});
    DrawRectangleLinesEx(this->getRec(), 1.0f, GREEN);
}

void Costumer::update() {
    this->patience = std::max(0.0f, this->patience - GetFrameTime());
}

float Costumer::score() {
    return pow(this->difficulty, 2) / (this->patience/10.0f);
}

Rectangle Costumer::getRec() {
    return {this->pos.x, this->pos.y + COSTUMER_TEXTURE.height*2.0f, COSTUMER_TEXTURE.width*2.0f, COSTUMER_DIV.height - COSTUMER_TEXTURE.height*2};
}

