#include "ui.h"

using namespace std;

void DrawTitle(std::string text) {
    float fontSize = TITLE_FONT_SIZE;
    DrawText(text.c_str(), (GetScreenWidth() - MeasureText(text.c_str(), fontSize))/2, TITLE_HEIGHT, fontSize, WHITE);
}

void DrawRecord(int i, Record& record, Vector2 pos) {
    float fontSize = RECORD_FONT_SIZE;
    const char* indexTxt = TextFormat("%d.", i);
    DrawText(indexTxt, pos.x, pos.y, fontSize, WHITE);
    DrawText(record.name.c_str(), pos.x + 90.0f, pos.y, fontSize, WHITE);
    const char* scoreTxt = TextFormat("%.2f", record.score);
    DrawText(scoreTxt, pos.x + MENU_DIV_W - MeasureText(scoreTxt, fontSize), pos.y, fontSize, WHITE);
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
    }

    if(this->active && this->hover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        this->event();
    }
}