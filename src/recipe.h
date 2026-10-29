#ifndef RECIPE_H
#define RECIPE_H

#include "constants.h"
#include "utils.h"
#include "cards.h"

#define RECIPE_TICKET_W 160
#define RECIPE_TICKET_H 24
#define RECIPE_FONT_SIZE 18

struct RecipeItem {
    Ingredient item;
    RecipeItem* next;
};

struct Recipe {
    RecipeItem* start;
    int size;

    Recipe(std::string s): start(nullptr), size(0) {
        RecipeItem* prev = (RecipeItem*) malloc(sizeof(RecipeItem));
        prev->item = BREAD_B;
        this->start = prev;
        for(int i=0; s[i]!=0; i++) {
            RecipeItem* newItem = (RecipeItem*) malloc(sizeof(RecipeItem));
            newItem->item = CharToItem(s[i]);
            newItem->next = nullptr;
            prev->next = newItem;
            this->size++;
            prev = newItem;
        }
    }

    void draw(Vector2 pos);
    bool check(Card* stack);
    void propagate(std::function<void(RecipeItem*, int)> f);
};

#endif