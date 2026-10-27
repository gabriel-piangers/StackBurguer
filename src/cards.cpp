#include "cards.h"

Card cards[MAX_CARDS];
Card* cardPicked = nullptr;

void ResetCards() {
    for(int i=0; i<MAX_CARDS; i++) cards[i].active = false;
}

void InitCards() {
    ResetCards();
    InsertCard(BREAD_B, {200, 700});
    InsertCard(BREAD_T, {200, 400});
    InsertCard(CHEDDAR, {400, 700});
    InsertCard(TOMATO, {600, 700});
    InsertCard(HAMBURGUER_RAW, {800, 700});
    InsertCard(BACON_RAW, {1000, 700});
    InsertCard(LETTUCE, {400, 400});
    InsertCard(PICKLES, {600, 400});
    InsertCard(ONIONS, {800, 400});
    InsertCard(EGG, {1000, 400});
    InsertCard(GRILL, {1200, 700});
    InsertCard(CUTTING, {1200, 400});
}

bool InsertCard(Ingredient item, Vector2 pos) {
    for(int i=0; i<MAX_CARDS; i++) {
        if(!cards[i].active) {
            cards[i] = Card(pos, item);
            return true;
        }
    }
    return false;
}

void UpdateCards() {
    for(int i=0; i<MAX_CARDS; i++) cards[i].update(&cardPicked);
    if(cardPicked && !cardPicked->picked) cardPicked = nullptr; // Safely changes picked card
}

void DrawCards() {
    for(int i=0; i<MAX_CARDS; i++) if(!cards[i].picked) cards[i].draw();
    Card* cur = cardPicked;
    while(cur){
        cur->draw();
        cur = cur->next;
    }
}

Card* GetCollisionCards(Card* c) {
    for(int i=0; i<MAX_CARDS; i++) {
        if(!cards[i].active || cards[i].prev || &cards[i] == c) continue;
        if(CheckCollisionRecs(cards[i].getStackRec(), c->getStackRec())) return &cards[i];
    }
    return nullptr;
}

// Card methods implementation
void Card::draw() {
    if(!this->active) return;
    float scale = picked ? CARD_PICKUP_SCALE : 1.0f;
    Rectangle rec = getRec();

    DrawRectanglePro(rec, {0, 0}, 0, this->bgColor());

    // Header
    DrawText(this->title().c_str(), rec.x + CARD_PAD, rec.y + CARD_PAD, CARD_TITLE_SIZE*scale, BLACK);
    DrawLine(rec.x, rec.y + (CARD_TITLE_SIZE + 2*CARD_PAD)*scale, rec.x + CARD_W*scale, rec.y + (CARD_TITLE_SIZE + 2*CARD_PAD)*scale, BLACK);

    // Body
    if(!this->next) {
        DrawRectangle(rec.x + CARD_PAD*scale, rec.y + (CARD_HEADER_H + CARD_PAD)*scale, (CARD_W - CARD_PAD*2)*scale, (CARD_H - CARD_HEADER_H - CARD_PAD*2)*scale, WHITE);
        DrawTextureEx(this->getTexture(), {rec.x + (CARD_W - this->getTexture().width)*scale/2, rec.y + (CARD_H + CARD_HEADER_H - this->getTexture().height)*scale/2}, 0.0f, scale, WHITE);
    }
}

void Card::update(Card** cPicked) {
    if(!this->active) return;

    // --- Independent update (All cards) ---
    Vector2 mousePos = GetMousePosition();
    Rectangle rec = getRec();
    if(CheckCollisionPointRec(mousePos, rec)) this->hover = true;
    else this->hover = false;
    if(this->hover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !*cPicked) { 
        this->pickup(cPicked);
    }

    // Card event update
    if(this->eventTime() && this->next) this->timeCounter += GetFrameTime();
    else this->timeCounter = 0.0f;
    if(this->next && this->timeCounter >= this->eventTime()) {
        this->event()(this->next); // This sintax looks weird but event() returns a function so it works
        this->timeCounter = 0.0f;
    }

    // Debugging
    if(hover && IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        std::cout << "size: " << this->size << "\n";
        auto f = [](Card* c, int i) {
            std::cout << i << ": " << c->title() << "\n"; 
        };
        this->propagate(f);
    }

    // --- Stack update (only the first card of the stack) ---
    if(prev) return;

    if(*cPicked == this && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        this->place();
    }

    if(picked) {
        this->pos.x = mousePos.x + this->offset.x;
        this->pos.y = mousePos.y + this->offset.y;
        auto f = [this](Card* c, int i) {
            c->pos.x = this->pos.x; 
            c->pos.y = this->pos.y + i*CARD_HEADER_H; 
        };
        this->propagate(f);
    }
}

std::string Card::title() {
    return cParams[this->type].title;
}

Color Card::bgColor() {
    return cParams[this->type].bgColor;
}

Texture2D Card::getTexture() {
    return cParams[this->type].texture;
}

float Card::eventTime() {
    return cParams[this->type].eventTime;
}

std::function<void(Card*)> Card::event() {
    return cParams[this->type].event;
}

Rectangle Card::getRec() {
    float scale = this->picked ? CARD_PICKUP_SCALE : 1.0f;
    return (Rectangle) {this->pos.x - CARD_W*(scale - 1.0f)/2, this->pos.y - CARD_H*(scale - 1.0f)/2, CARD_W*scale, this->next ? CARD_HEADER_H*scale : CARD_H*scale};
}
Rectangle Card::getStackRec(int extraSize) {
    return (Rectangle) {this->pos.x, this->pos.y, CARD_W, CARD_H + CARD_HEADER_H*(this->size + extraSize - 1)};
}

// Place doesn't change cPicked to null because this needs to happen after all the cards update
void Card::place() {
    Card* cardCol = GetCollisionCards(this);
    bool valid = this->isPositionValid(cardCol);
    if(cardCol && valid) cardCol->insert(this);
    else if(!valid && !this->prev && this->lastPrev) { // Returns to previous state
        Card* first = this->lastPrev->propagate([](Card* c, int i) {}, true);
        first->insert(this);
    }

    auto f = [this, valid](Card* c, int i) {
        c->picked = false;
        if(!valid) {
            c->pos.x = this->lastPos.x; 
            c->pos.y = this->lastPos.y + i*CARD_HEADER_H;
        }
    };
    this->propagate(f);  
}

void Card::pickup(Card** cPicked) {
    this->lastPos = this->pos;
    this->lastPrev = this->prev;
    *cPicked = this;
    if(this->prev) {
        this->prev->propagate([this](Card* c, int i) {c->size -= this->size;}, true);
        this->prev->next = nullptr;
        this->prev = nullptr;
    }

    Vector2 mousePos = GetMousePosition();
    auto f = [this, mousePos](Card* c, int i) {
        c->picked = true;
        c->offset = {c->pos.x - mousePos.x, c->pos.y - mousePos.y};
    };
    this->propagate(f);
}

void Card::insert(Card* card) {
    Card* last = this->propagate([card](Card* c, int i) {c->size+=card->size;});
    if(last == card) return; // avoids self insertion 
    std::cout << card->title() << " inserted on " << this->title() << "\n";
    card->prev = last;
    last->next = card;
    auto f = [last](Card* c, int i) {
        c->pos.x = last->pos.x; 
        c->pos.y = last->pos.y + i*CARD_HEADER_H;
    };
    last->propagate(f);        
}

bool Card::isPositionValid(Card* cardCol) {
    Rectangle rec = cardCol ? cardCol->getStackRec(this->size) : this->getStackRec();
    Rectangle colRec = GetCollisionRec(rec, CARD_TABLE);
    if(colRec.width == rec.width && colRec.height == rec.height 
        && (!cardCol || !this->eventTime())) return true;
    return false;
}

Card* Card::propagate(std::function<void(Card*, int)> f, bool reverse) {
    Card* cur = this;
    Card* last = nullptr;
    int i=0;
    while(cur) {
        f(cur, i);
        last = cur;
        cur = reverse ? cur->prev : cur->next;
        i++;
    }
    return last;
}