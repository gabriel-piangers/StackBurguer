#include "recipe.h"

void Recipe::draw(Vector2 pos) {
    DrawRectangle(pos.x, pos.y, RECIPE_TICKET_W, RECIPE_TICKET_H, WHITE);
    DrawText("Recipe", pos.x + (RECIPE_TICKET_W - MeasureText("Recipe", RECIPE_FONT_SIZE))/2, pos.y + (RECIPE_TICKET_H - RECIPE_FONT_SIZE)/2, RECIPE_FONT_SIZE, BLACK);
    auto f = [pos](RecipeItem* item, int i) {
        DrawRectangle(pos.x, pos.y+i*RECIPE_TICKET_H, RECIPE_TICKET_W, RECIPE_TICKET_H, i%2==0 ? LIGHTGRAY : WHITE);
        const char* title = cParams[item->item].title.c_str();
        DrawText(title, pos.x + (RECIPE_TICKET_W - MeasureText(title, RECIPE_FONT_SIZE))/2, pos.y + i*RECIPE_TICKET_H + (RECIPE_TICKET_H - RECIPE_FONT_SIZE)/2, RECIPE_FONT_SIZE, BLACK);
    };
    this->propagate(f);
}

bool Recipe::check(Card* stack) {
    if(stack->size < this->size) return false;
    RecipeItem* cur = this->start;
    while(cur) {
        if(cur->item != stack->type) return false;
        cur = cur->next;
        stack = stack->next;
    }
    return true;
}

void Recipe::propagate(std::function<void(RecipeItem*, int)> f) {
    RecipeItem* cur = this->start;
    int i = 0;
    while(cur) {
        f(cur, i);
        cur = cur->next;
        i++;
    }
}