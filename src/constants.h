#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <raylib.h>
#include <iostream>
#include <string>
#include <functional>

#define SCREEN_W 1600
#define SCREEN_H 900

const Rectangle CARD_TABLE = {200, 300, 1200, 600};
const Rectangle COSTUMER_DIV = {200, 50, 1200, 250};

// Textures
extern Texture2D BREAD_B_TEXTURE;
extern Texture2D BREAD_T_TEXTURE;
extern Texture2D KETCHUP_TEXTURE;
extern Texture2D MUSTARD_TEXTURE;
extern Texture2D PICKLES_TEXTURE;
extern Texture2D LETTUCE_TEXTURE;
extern Texture2D TOMATO_TEXTURE;
extern Texture2D TOMATO_SLICES_TEXTURE;
extern Texture2D ONIONS_TEXTURE;
extern Texture2D ONIONS_SLICES_TEXTURE;
extern Texture2D SWISS_CHEESE_TEXTURE;
extern Texture2D CHEDDAR_TEXTURE;
extern Texture2D HAMBURGUER_RAW_TEXTURE;
extern Texture2D HAMBURGUER_TEXTURE;
extern Texture2D BACON_RAW_TEXTURE;
extern Texture2D BACON_TEXTURE;
extern Texture2D EGG_RAW_TEXTURE;
extern Texture2D EGG_TEXTURE;
extern Texture2D GRILL_TEXTURE;
extern Texture2D CUTTING_TEXTURE;

extern Texture2D COSTUMER_TEXTURE;

// Enums
enum Ingredient {
    BREAD_B,
    BREAD_T,
    KETCHUP,
    MUSTARD,
    PICKLES,
    LETTUCE,
    TOMATO,
    TOMATO_SLICES,
    ONIONS,
    ONIONS_SLICES,
    SWISS_CHEESE,
    CHEDDAR,
    HAMBURGUER_RAW,
    HAMBURGUER,
    BACON_RAW,
    BACON,
    EGG_RAW,
    EGG,
    GRILL,
    CUTTING
};

#endif