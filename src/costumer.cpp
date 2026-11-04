#include "costumer.h"
#include "cards.h"
#include "reasings.h"

Costumer costumers[COSTUMER_AMOUNT];
Costumer emptyCostumer;

Vector2 GetCostumerPos(int i) {
    return {COSTUMER_DIV.x + i*COSTUMER_DIV.width/COSTUMER_AMOUNT, COSTUMER_DIV.y};
}

Costumer& GetCollisionCostumer(Rectangle rec) {
    for(int i=0; i<COSTUMER_AMOUNT; i++) {
        if(costumers[i].state != EMPTY && CheckCollisionRecs(costumers[i].getRec(), rec)) return costumers[i];
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

void Costumer::draw() {
    if(this->state == EMPTY) return; // emptyCostumer
    Texture2D texture = GetCostumerTexture(this->state);
    switch (state) {
    case ARRIVING: {
        float scale = EaseLinearIn(this->timer, 0.0f, 1.0f, COSTUMER_WALK_DURATION);
        DrawTextureEx(texture, this->pos, 0.0f, scale, WHITE);
        break;
    }
    case LEAVING: {
        float scale = EaseLinearIn(this->timer, 1.0f, -1.0f, COSTUMER_WALK_DURATION);
        DrawTextureEx(texture, this->pos, 0.0f, scale, WHITE);
        break;
    }
    default:
        DrawTextureEx(texture, this->pos, 0.0f, 1.0f, this->patience>0.0f ? WHITE : RED);
        this->order.draw({this->pos.x + COSTUMER_TEXTURE_W + 10, this->pos.y});
        DrawRectangleLinesEx(this->getRec(), 1.0f, GREEN);
        break;
    }
}

void Costumer::update() {
    if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        std::cout << this->state << '\n';
    }

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

Rectangle Costumer::getRec() {
    return {this->pos.x, this->pos.y + COSTUMER_TEXTURE_H, COSTUMER_TEXTURE_W, COSTUMER_DIV.height - COSTUMER_TEXTURE_H};
}

