#include "ui.h"

using namespace std;

void DrawTitle(std::string text) {
    float fontSize = 48.0f;
    DrawText(text.c_str(), (GetScreenWidth() - MeasureText(text.c_str(), fontSize))/2, 100.0f, fontSize, WHITE);
}

void Button::draw() {
    DrawRectangleRec(this->rec, this->hover ? ColorLerp(this->color, HOVER_COLOR, 0.5) : this->color);
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
    }

    if(this->hover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        this->event();
    }
}