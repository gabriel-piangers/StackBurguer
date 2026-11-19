#include "ui.h"
#include "reasings.h"

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

void TextPopUp::draw() {
    if(this->time <= this->duration) {
        DrawText(this->text.c_str(), this->pos.x, this->pos.y, this->fontSize, this->color);
    }
}

void TextPopUp::update() {
    this->time += GetFrameTime();
    this->pos.y = EaseLinearIn(this->time, startPos.y, -TEXT_POP_UP_DELTA, this->duration);
    float fadeTime = this->time - this->duration/2.0f;
    if(fadeTime >= 0) this->color.a = (int) EaseQuadOut(fadeTime, 255, -255, this->duration/2.0f);
}

bool TextPopUp::keepAlive() {
    if(this->time > this->duration) return false;
    return true;
}