#include "utils.h"
#include "cards.h"

Ingredient CharToItem(char c) {
    switch (c) {
        case 'z':
            return BREAD_T;
        case 'k':
            return KETCHUP;
        case 'm':
            return MUSTARD;
        case 'p':
            return PICKLES;
        case 'a':
            return LETTUCE;
        case 's':
            return SWISS_CHEESE;
        case 'q':
            return CHEDDAR;
        case 'c':
            return ONIONS_SLICES;
        case 't':
            return TOMATO_SLICES;
        case 'n':
            return HAMBURGUER;
        case 'o':
            return EGG;
        case 'b':
            return BACON;
        default:
            return BREAD_B;
    }
}

Ingredient GetUnpreparedItem(Ingredient item) {
    switch (item) {
        case ONIONS_SLICES:
            return ONIONS;
        case TOMATO_SLICES:
            return TOMATO;
        case HAMBURGUER:
            return HAMBURGUER_RAW;
        case EGG:
            return EGG_RAW;
        case BACON:
            return BACON_RAW;
        default:
            return item;
    }
}

float GetCostumerDifficulty(std::string recipe, float patience) {
    float difficulty = 1.0f; // Accounts for the bottom bread
    for(int i=0; recipe[i]!=0; i++) {
        Ingredient item = GetUnpreparedItem(CharToItem(recipe[i]));
        difficulty += cParams[item].prepTime + pow(cParams[item].rarity, 2);
    }
    difficulty /= (patience/10.0f);
    return difficulty;
}