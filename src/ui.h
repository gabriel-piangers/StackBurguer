#ifndef UI_H
#define UI_H

#include "constants.h"
#include "history.h"

#define HOVER_COLOR (Color) {32, 32, 32}
#define INACTIVE_COLOR (Color) {0, 0, 0}
#define TITLE_HEIGHT 100
#define TITLE_FONT_SIZE 48.0f
#define RECORD_FONT_SIZE 24.0f

struct Button {
    Rectangle rec;
    Color color;
    float fontSize;
    bool hover;
    bool active;
    std::string text;
    std::function<void()> event;

    Button(Rectangle r, std::string s, std::function<void()> e, float fs = 18, Color c = WHITE):
        rec(r), color(c), fontSize(fs), hover(false), active(true), text(s), event(e) {} 

    void draw();
    void update();
};

// Exports
void DrawTitle(std::string text);
void DrawRecord(int i, Record& record, Vector2 pos);

#endif