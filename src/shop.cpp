#include "shop.h"
#include "dynamic_vector.h"

Ingredient sellingItems[] = {BREAD_B, BREAD_T, KETCHUP, MUSTARD, PICKLES, LETTUCE, TOMATO, ONIONS, SWISS_CHEESE, CHEDDAR, HAMBURGUER_RAW, BACON_RAW, EGG_RAW};
DynamicVector<ShopItem> shopItems;

void InitShop() {
    shopItems.clear();
    for(int i=0; i < sizeof(sellingItems)/sizeof(Ingredient); i++) {
        int split = 7;
        if(i<split) {
            ShopItem item({CARD_TABLE.x - (GAME_MARGIN + SHOP_ITEM_W), CARD_TABLE.y + (SHOP_ITEM_H + SHOP_ITEM_PAD)*i}, sellingItems[i]);
            shopItems.insert(item);
        } else {
            ShopItem item({CARD_TABLE.x + CARD_TABLE.width + GAME_MARGIN, CARD_TABLE.y + (SHOP_ITEM_H + SHOP_ITEM_PAD)*(i-split)}, sellingItems[i]);
            shopItems.insert(item);
        }
    }
}

void UpdateShop() {
    for(int i=0; i<shopItems.size; i++) {
        shopItems[i].update();
    }
}

void DrawShop() {
    for(int i=0; i<shopItems.size; i++) {
        shopItems[i].draw();
    }
}

void ShopItem::update() {
    if(CheckCollisionPointRec(GetMousePosition(), this->rec)) {
        this->hover = true;
    } else {
        this->hover = false;
    }

    if(this->hover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Card* nCard = AddCard(this->item, {this->rec.x, this->rec.y});
        PickCard(nCard);
    }
}

void ShopItem::draw() {
    DrawRectangleRec(this->rec, cParams[this->item].bgColor);
    DrawTexture(cParams[this->item].texture, this->rec.x + SHOP_ITEM_PAD, this->rec.y + SHOP_ITEM_PAD, WHITE);
}