#include "ui.h"

using namespace std;

void DrawTitle(std::string text) {
    float fontSize = TITLE_FONT_SIZE;
    DrawText(text.c_str(), (GetScreenWidth() - MeasureText(text.c_str(), fontSize))/2, TITLE_HEIGHT, fontSize, WHITE);
}

void DrawHUD(float time, float score) {
    const char* scoreTxt = TextFormat("Score: %.2f", score);
    const float fontSize = 20.0f;
    DrawText(scoreTxt, 25.0f, 25.0f, fontSize, RED);
    DrawText(TextFormat("Time: %.2f", time), 35.0f + MeasureText(scoreTxt, fontSize), 25.0f, fontSize, RED);
}

void Button::draw() {
    Color color;
    if(!this->active) color = ColorLerp(this->color, INACTIVE_COLOR, 0.5f);
    else if (this->hover) color = ColorLerp(this->color, HOVER_COLOR, 0.5f);
    else color = this->color;

    DrawRectangleRec(this->rec, color);
    DrawRectangleLinesEx(this->rec, 1.0f, BLACK);

    DrawText(
        this->text.c_str(),
        this->rec.x + (this->rec.width - MeasureText(this->text.c_str(), this->fontSize))/2,
        this->rec.y + (this->rec.height - this->fontSize)/2, 
        this->fontSize,
        BLACK
    );   
}

void Button::update() {
    if(CheckCollisionPointRec(GetMousePosition(), this->rec)) {
        this->hover = true;
    } else {
        this->hover = false;
    }

    if(this->active && this->hover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        this->event();
    }
}