#include "costumer.h"
#include "cards.h"

Costumer costumers[COSTUMER_AMOUNT];

void InitCostumers() {
    costumers[0] = Costumer("pbtmcnz", 60.0f);
    costumers[1] = Costumer("nomosnz", 90.0f);
    costumers[2] = Costumer("bpkbnz", 60.0f);
}

void DrawCostumers() {
    for(int i=0; i<COSTUMER_AMOUNT; i++) 
        costumers[i].draw({COSTUMER_DIV.x + i*COSTUMER_DIV.width/COSTUMER_AMOUNT, COSTUMER_DIV.y});
}

void Costumer::draw(Vector2 pos) {
    DrawTextureEx(COSTUMER_TEXTURE, pos, 0.0f, 2.0f, WHITE);
    this->order.draw({pos.x + COSTUMER_TEXTURE.width*2 + 10, pos.y});
}

