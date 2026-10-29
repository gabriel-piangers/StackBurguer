#include "utils.h"

Ingredient charToItem(char c) {
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