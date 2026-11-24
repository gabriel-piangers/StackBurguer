#include "ui.h"
#include "utils.h"
#include "reasings.h"

using namespace std;

void DrawTitle(string text) {
    Vector2 pos = GetTitlePos(text, TITLE_FONT_SIZE);
    DrawText(text.c_str(), pos.x, pos.y, TITLE_FONT_SIZE, WHITE);
}

Vector2 GetTitlePos(string text, float fs) {
    return {(GetMonitorWidth(GetCurrentMonitor()) - MeasureText(text.c_str(), fs))/2.0f, TITLE_HEIGHT};
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

void AnimatedText::draw() {
    for(int i=0; i<this->text.size(); i++) {
        DrawText(TextSubtext(this->text.c_str(), i, 1), this->glyphPos[i].x, this->glyphPos[i].y, this->fontSize, this->color);
    }
}

void AnimatedText::update() {
    this->time += GetFrameTime();

    switch (this->animation) {
    case WAVING: {
        for(int i=0; i<this->text.size(); i++) {
            float curTime = fmod(this->time + i*this->offset, this->duration);
            if (curTime < this->duration/2.0f) this->glyphPos[i].y = EaseSineIn(curTime, this->pos.y, this->delta, this->duration);
            else this->glyphPos[i].y = EaseSineOut(curTime, this->pos.y + this->delta, -this->delta, this->duration);
        }
        break;
    }
    case SHAKING:{
        for (unsigned int i = 0; i < this->text.size(); i++) {
            float curTime = fmod(this->time + i*this->offset, this->duration);;
            if(curTime <= GetFrameTime()) {
                this->glyphDelta[i].x = RandomFloat(-this->delta/10.0f, this->delta/10.0f);
                this->glyphDelta[i].y = RandomFloat(-this->delta/10.0f, this->delta/10.0f);
            }

            float halfDuration = this->duration/2.0f;
            if (curTime < (halfDuration)) {
                glyphPos[i].x = EaseLinearNone(curTime, this->glyphStartPos[i].x, this->glyphDelta[i].x, halfDuration);
                glyphPos[i].y = EaseLinearNone(curTime, this->pos.y, this->glyphDelta[i].y, halfDuration);
            }
            else {
                glyphPos[i].x = EaseLinearNone(curTime - halfDuration, this->glyphStartPos[i].x + this->glyphDelta[i].x, -this->glyphDelta[i].x, halfDuration);
                glyphPos[i].y = EaseLinearNone(curTime - halfDuration, this->pos.y + this->glyphDelta[i].y, -this->glyphDelta[i].y, halfDuration);
            }
        }
    }
    default:
        break;
    }
}

void AnimatedText::init(Vector2 _pos) {
    this->pos = _pos;
    glyphStartPos.clear();
    glyphPos.clear();
    float offsetX = 0.0f;
    for(int i=0; i<this->text.size(); i++) {
        glyphPos.insert({this->pos.x + offsetX, this->pos.y});
        glyphStartPos.insert({this->pos.x + offsetX, this->pos.y});
        offsetX += MeasureText(TextSubtext(this->text.c_str(), i, 1), this->fontSize) + 0.1*this->fontSize;
        
        if(this->animation == SHAKING) {
            glyphDelta.insert({RandomFloat(-this->delta/10.0f, this->delta/10.0f),  RandomFloat(-this->delta/10.0f, this->delta/10.0f)});
        }
    }
}