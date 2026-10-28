#ifndef CARDS_H
#define CARDS_H

#include "constants.h"

// Defines
#define CARD_W 130
#define CARD_H 180
#define CARD_TITLE_SIZE 18
#define CARD_PAD 6
#define CARD_HEADER_H (CARD_TITLE_SIZE + CARD_PAD*2)
#define CARD_PICKUP_SCALE 1.2f
#define MAX_CARDS 50

// Structs
struct Card{
    Vector2 pos;
    Vector2 lastPos;
    Vector2 offset;
    Ingredient type;
    bool picked;
    bool hover;
    bool active;
    int size;
    float timeCounter;
    Card* next;
    Card* prev;
    Card* lastPrev;

    Card() : active(false) {} // default constructor

    Card(Vector2 _pos, Ingredient _type): 
        pos({_pos.x, _pos.y}), lastPos({_pos.x, _pos.y}), offset({0, 0}), type(_type), picked(false), hover(false), active(true), size(1), timeCounter(0.0f), next(nullptr), prev(nullptr)  {}

    // Getters
    std::string title();
    Color bgColor();
    Texture2D getTexture();
    float eventTime();
    std::function<void(Card*)> event();
    Rectangle getRec();
    Rectangle getStackRec(int extraSize = 0);

    // Methods
    void draw();
    void update(Card** cPicked);
    void pickup(Card** cPicked);
    void place();
    void insert(Card* card);
    void destroy();
    bool isPositionValid(Card* cardCol);
    Card* propagate(std::function<void(Card*, int)> f, bool reverse = false);
};

// Commom for all cards of the same type (no need to keep track for every copy)
struct CardParams {
    std::string title;
    Color bgColor;
    Texture2D& texture;
    float eventTime;
    std::function<void(Card*)> event;
};

// Constants
const CardParams cParams[] = {
    { // BREAD_B
        "Bottom Bread", BEIGE, BREAD_B_TEXTURE, 0.0f, [](Card* c){}
    },
    { // BREAD_T
        "Top Bread", BEIGE, BREAD_T_TEXTURE, 0.0f, [](Card* c){}
    },
    { // KETCHUP
        "Ketchup", RED, KETCHUP_TEXTURE, 0.0f, [](Card* c){}
    },
    { // MUSTARD 
        "Mustard", YELLOW, MUSTARD_TEXTURE, 0.0f, [](Card* c){}
    },
    { // PICKLES
        "Pickles", LIME, PICKLES_TEXTURE, 0.0f, [](Card* c){}
    },
    { // LETTUCE,
        "Lettuce", GREEN, LETTUCE_TEXTURE, 0.0f, [](Card* c){}
    },
    { // TOMATO    
        "Tomato", RED, TOMATO_TEXTURE, 0.0f, [](Card* c){}
    },
    { // TOMATO_SLICES   
        "Sliced Tomato", RED, TOMATO_SLICES_TEXTURE, 0.0f, [](Card* c){}
    }, 
    { // ONIONS 
        "Onion", LIGHTGRAY, ONIONS_TEXTURE, 0.0f, [](Card* c){}
    },
    { // ONIONS_SLICES
        "Sliced Onion", LIGHTGRAY, ONIONS_SLICES_TEXTURE, 0.0f, [](Card* c){}
    },
    { // SWISS_CHEESE
        "Swiss Cheese", GOLD, SWISS_CHEESE_TEXTURE, 0.0f, [](Card* c){}
    },
    { // CHEDDAR 
        "Cheddar", ORANGE, CHEDDAR_TEXTURE, 0.0f, [](Card* c){}
    },
    { // HAMBURGUER_RAW
        "Hamburguer", PINK, HAMBURGUER_RAW_TEXTURE, 0.0f, [](Card* c){}
    },
    { // HAMBURGUER,
        "Hamburguer", DARKBROWN, HAMBURGUER_TEXTURE, 0.0f, [](Card* c){}
    },
    { // BACON_RAW
        "Bacon", PINK, BACON_RAW_TEXTURE, 0.0f, [](Card* c){}
    },
    { // BACON
        "Bacon", DARKBROWN, BACON_TEXTURE, 0.0f, [](Card* c){}
    },
    { // EGG_RAW
        "Egg", LIGHTGRAY, EGG_RAW_TEXTURE, 0.0f, [](Card* c){}
    },
    { // EGG
        "Fried Egg", LIGHTGRAY, EGG_TEXTURE, 0.0f, [](Card* c){}
    },
    { // GRILL
        "Grill", GRAY, GRILL_TEXTURE, 3.0f, [](Card* c){
            switch (c->type) {
                case HAMBURGUER_RAW:
                    c->type = HAMBURGUER;
                    break;
                case BACON_RAW:
                    c->type = BACON;
                    break;
                case EGG_RAW:
                    c->type = EGG;
                    break;
                default:
                    break;
            }
        }
    },
    { // CUTTING
        "Cutting board", BROWN, CUTTING_TEXTURE, 1.0f, [](Card* c){
            switch (c->type) {
                case TOMATO:
                    c->type = TOMATO_SLICES;
                    break;
                case ONIONS:
                    c->type = ONIONS_SLICES;
                    break;
                default:
                    break;
            }
        }
    },
};

// Exports
void InitCards();
void UpdateCards();
void DrawCards();
bool AddCard(Ingredient item, Vector2 pos);
Card* GetCollisionCards(Card* c);

#endif