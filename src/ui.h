#ifndef UI_H
#define UI_H

#include "constants.h"
#include "dynamic_vector.h"

#define HOVER_COLOR (Color) {32, 32, 32, 255}
#define INACTIVE_COLOR (Color) {0, 0, 0, 255}
#define TITLE_HEIGHT 100
#define TITLE_FONT_SIZE 48.0f
#define TEXT_POP_UP_DELTA 80.0f

enum TextAnimation {
    WAVING,
    SHAKING,
};

struct Button {
    Rectangle rec;
    Color color;
    float fontSize;
    bool hover;
    bool active;
    std::string text;
    std::function<void()> event;

    Button(): rec({0.0f, 0.0f, 0.0f, 0.0f}), active(false) {}

    Button(Rectangle r, std::string s, std::function<void()> e, float fs = 18, Color c = WHITE):
        rec(r), color(c), fontSize(fs), hover(false), active(true), text(s), event(e) {} 

    void draw();
    void update();
};

struct TextPopUp {
    Vector2 startPos;
    Vector2 pos;
    std::string text;
    Color color;
    float time;
    float fontSize;
    float duration;

    TextPopUp(): text(""), time(0.0f), duration(0.0f) {}
    
    TextPopUp(Vector2 _pos, std::string _text, Color _color = GREEN, float _fs = 18, float _duration = 2.0f): 
        startPos(_pos), pos(_pos), text(_text), color(_color), time(0.0f), fontSize(_fs), duration(_duration) {}

    void draw();
    void update();
    bool keepAlive();
};

struct AnimatedText {
    TextAnimation animation;
    Vector2 pos;
    DynamicVector<Vector2> glyphStartPos;
    DynamicVector<Vector2> glyphPos;
    std::string text;
    float time;
    float delta;
    float offset;
    float duration;
    float fontSize;
    Color color;

    AnimatedText(): text("") {}

    AnimatedText(TextAnimation _animation, Vector2 _pos, std::string _text, float _delta = 30.0f, float _offset = 1.0f, float _duration = 2.0f, float _fs = 18.0f, Color _color = WHITE):
        animation(_animation), pos(_pos), glyphStartPos(), glyphPos(), text(_text), time(0.0f), delta(_delta), offset(_offset), duration(_duration), fontSize(_fs), color(_color) {
        this->setPos(_pos);
    } 

    void draw();
    void update();
    void setPos(Vector2 nPos);
};

// Exports
void DrawTitle(std::string text);
Vector2 GetTitlePos(std::string text, float fs = TITLE_FONT_SIZE);
void DrawHUD(float time, float score);

#endif