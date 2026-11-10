#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <raylib.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <functional>
#include <random>
#include <chrono>

#define MENU_DIV_H 600
#define MENU_DIV_W 900
#define TABLE_W 1400
#define TABLE_H 700
#define COSTUMER_DIV_H 250
#define TABLE_PAD 20 
#define GAME_MARGIN 50

extern Rectangle COSTUMER_DIV;
extern Rectangle CARD_TABLE;
extern Rectangle MENU_DIV;
extern Rectangle RETURN_BTN_REC;

const unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
static std::default_random_engine rng(seed);

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

extern Texture2D COSTUMER_HAPPY_TEXTURE;
extern Texture2D COSTUMER_NORMAL_TEXTURE;
extern Texture2D COSTUMER_MAD_TEXTURE;
extern Texture2D COSTUMER_BACK_TEXTURE;

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

enum GameState {
    MAIN_MENU,
    START_GAME,
    IN_GAME,
    GAME_OVER,
    HISTORY,
    EXIT
};


// Structs
struct Game {
    float score;
    float time;
    std::string userName;
};

#endif