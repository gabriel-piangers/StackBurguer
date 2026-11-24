#ifndef SHOP_H
#define SHOP_H

#include "constants.h"
#include "cards.h"

#define SHOP_SIZE 13
#define SHOP_ITEM_W 84.0f
#define SHOP_ITEM_H 84.0f
#define SHOP_ITEM_PAD 10.0f

struct ShopItem {
    Rectangle rec;
    Ingredient item;
    int price;
    bool hover;

    ShopItem(): item(BREAD_B) {}
    ShopItem(Vector2 _pos, Ingredient _item): rec({_pos.x, _pos.y, SHOP_ITEM_W, SHOP_ITEM_H}), item(_item), price(cParams[_item].rarity), hover(false) {}

    void update();
    void draw();
};

// Exports
void InitShop();
void UpdateShop();
void DrawShop();

#endif