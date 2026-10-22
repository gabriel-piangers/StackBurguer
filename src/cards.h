#ifndef CARDS_H
#define CARDS_H

#include "constants.h"

// Defines
#define CARD_W 130
#define CARD_H 180
#define CARD_TITLE_SIZE 18
#define CARD_TITLE_PAD 5
#define CARD_HEADER_H (CARD_TITLE_SIZE + CARD_TITLE_PAD*2)
#define CARD_PICKUP_SCALE 1.2f
#define MAX_CARDS 50

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
    bool isPositionValid(Card* cardCol);
    Card* propagate(std::function<void(Card*, int)> f, bool reverse = false);
};

// Commom for all cards of the same type (no need to keep track for every copy)
struct CardParams {
    std::string title;
    Color bgColor;
    float eventTime;
    std::function<void(Card*)> event;
};

// Constants
const CardParams cParams[] = {
    { // BREAD_B
        "Bottom Bread", BEIGE, 0.0f, [](Card* c){}
    },
    { // BREAD_T
        "Top Bread", BEIGE, 0.0f, [](Card* c){}
    },
    { // KETCHUP
        "Ketchup", RED, 0.0f, [](Card* c){}
    },
    { // MUSTARD 
        "Mustard", YELLOW, 0.0f, [](Card* c){}
    },
    { // PICKLES
        "Pickles", LIME, 0.0f, [](Card* c){}
    },
    { // LETTUCE,
        "Lettuce", GREEN, 0.0f, [](Card* c){}
    },
    { // TOMATO    
        "Tomato", RED, 0.0f, [](Card* c){}
    },
    { // TOMATO_SLICES   
        "Sliced Tomato", RED, 0.0f, [](Card* c){}
    }, 
    { // ONIONS 
        "Onion", LIGHTGRAY, 0.0f, [](Card* c){}
    },
    { // ONIONS_SLICES
        "Sliced Onion", LIGHTGRAY, 0.0f, [](Card* c){}
    },
    { // SWISS_CHEESE
        "Swiss Cheese", GOLD, 0.0f, [](Card* c){}
    },
    { // CHEDDAR 
        "Cheddar", ORANGE, 0.0f, [](Card* c){}
    },
    { // HAMBURGUER_RAW
        "Hamburguer", PINK, 0.0f, [](Card* c){}
    },
    { // HAMBURGUER,
        "Hamburguer", DARKBROWN, 0.0f, [](Card* c){}
    },
    { // BACON_RAW
        "Bacon", PINK, 0.0f, [](Card* c){}
    },
    { // BACON
        "Bacon", DARKBROWN, 0.0f, [](Card* c){}
    },
    { // EGG_RAW
        "Egg", WHITE, 0.0f, [](Card* c){}
    },
    { // EGG_FRIED
        "Fried Egg", WHITE, 0.0f, [](Card* c){}
    },
    { // GRILL
        "Grill", GRAY, 3.0f, [](Card* c){
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
        "Cutting board", BROWN, 1.0f, [](Card* c){
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
bool InsertCard(Ingredient item, Vector2 pos);
Card* GetCollisionCards(Card* c);
void InitSlots();
void DrawSlots();

#endif