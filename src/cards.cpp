#include "cards.h"
#include "costumer.h"

using namespace std;

CardList cards;
Card* cardPicked = nullptr;
int idCount = 0;

void ResetCards() {
    cards.clear();
}

void InitCards() {
    ClearEventSystem();
    cardPicked = nullptr;
    ResetCards();
    AddCard(GRILL, {CARD_TABLE.x, CARD_TABLE.y});
    AddCard(GRILL, {CARD_TABLE.x + CARD_W + 10.0f, CARD_TABLE.y});
    AddCard(CUTTING, {CARD_TABLE.x + (CARD_W + 10.0f)*2.0f, CARD_TABLE.y});
}

Card* AddCard(Ingredient item, Vector2 pos) {
    Card* nCard = new Card(pos, item);
    if(!nCard) return nullptr;

    cards.insert(nCard);
    idCount++;
    return nCard;
}

void PickCard(Card* c) {
    if(cardPicked) return;
    c->pickup(&cardPicked);
}

void UpdateCards() {
    auto f = [](Card* c, int i) {
        if(c->active) c->update(&cardPicked);
    };
    cards.propagate(f, true);

    Card* cur = cardPicked;
    while(cur){
        cur->update(&cardPicked);
        cur = cur->next;
    }
}

void DrawCards() {
    auto f = [](Card* c, int i) {
        if(c->active && !c->picked) c->draw();
    };
    cards.propagate(f);

    Card* cur = cardPicked;
    while(cur){
        cur->draw();
        cur = cur->next;
    }
}

Card* GetCollisionCards(Card* c) {
    CardNode* cur = cards.last;
    while(cur) {
        if(cur->card->active && !cur->card->prev) {
            Rectangle col = GetCollisionRec(cur->card->getStackRec(), c->getStackRec());
            if(col.width * col.height >= CARD_H * CARD_W * MIN_COLISION_PCT) return cur->card;
        }
        cur = cur->prev;
    }
    return nullptr;
}

// Card methods implementation
void Card::draw() {
    if(!this->active) return;
    float scale = picked ? CARD_PICKUP_SCALE : 1.0f;
    Rectangle rec = getRec(true); // Full rec

    DrawRectangleRounded(rec, 0.1f, 100, this->getColor());
    DrawRectangleRoundedLinesEx(rec, 0.1f, 100, 2.0f, BLACK);

    // Header
    DrawText(this->getTitle().c_str(), rec.x + CARD_PAD, rec.y + CARD_PAD, CARD_TITLE_SIZE*scale, BLACK);
    DrawLineEx({rec.x, rec.y + (CARD_TITLE_SIZE + 2*CARD_PAD)*scale}, {rec.x + CARD_W*scale, rec.y + (CARD_TITLE_SIZE + 2*CARD_PAD)*scale}, 2.0f, BLACK);

    // Body
    if(!this->next) {
        DrawRectangleRounded({rec.x + CARD_PAD*scale, rec.y + (CARD_HEADER_H + CARD_PAD)*scale, (CARD_W - CARD_PAD*2)*scale, (CARD_H - CARD_HEADER_H - CARD_PAD*2)*scale}, 0.1f, 100, WHITE);
        DrawTextureEx(this->getTexture(), {rec.x + (CARD_W - this->getTexture().width)*scale/2, rec.y + (CARD_H + CARD_HEADER_H - this->getTexture().height)*scale/2}, 0.0f, scale, WHITE);
        if(this->rotten) {
            DrawTextureEx(
                ROTTEN_TAG_TEXTURE,
                {
                    rec.x + CARD_W*scale - (CARD_PAD*2.0f + ROTTEN_TAG_TEXTURE.width)*scale, 
                    rec.y + CARD_H*scale - (CARD_PAD*2.0f + ROTTEN_TAG_TEXTURE.height)*scale
                },
                0.0f, scale, WHITE);
        }
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
    if(!this->getRarity() && this->next) this->timeCounter += GetFrameTime();
    else this->timeCounter = 0.0f;
    if(this->next && this->timeCounter >= this->next->getPrepTime()) {
        this->getEvent()(this->next); // This sintax looks weird but getEvent() returns a function so it works
        this->timeCounter = 0.0f;
    }

    // Debugging
    if(hover && IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        cout << "Id: " << this->id << " | size: " << this->size << "\n";
        auto f = [](Card* c, int i) {
            cout << i << ": " << c->getTitle() << "\n"; 
        };
        this->propagate(f);
    }

    // --- Stack update (only the first card of the stack) ---
    if(prev) return;

    if(*cPicked == this && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        this->place(cPicked);
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

string Card::getTitle() {
    return cParams[this->type].title;
}

Color Card::getColor() {
    return cParams[this->type].bgColor;
}

Texture2D Card::getTexture() {
    return cParams[this->type].texture;
}

int Card::getRarity() {
    return cParams[this->type].rarity;
}

float Card::getPrepTime() {
    return cParams[this->type].prepTime;
}

float Card::getRotTime() {
    return cParams[this->type].rotTime;
}

function<void(Card*)> Card::getEvent() {
    return cParams[this->type].event;
}

Rectangle Card::getRec(bool full) {
    float scale = this->picked ? CARD_PICKUP_SCALE : 1.0f;
    return (Rectangle) {this->pos.x - CARD_W*(scale - 1.0f)/2, this->pos.y - CARD_H*(scale - 1.0f)/2, CARD_W*scale, !full && this->next ? CARD_HEADER_H*scale : CARD_H*scale};
}
Rectangle Card::getStackRec(int extraSize) {
    return (Rectangle) {this->pos.x, this->pos.y, CARD_W, CARD_H + CARD_HEADER_H*(this->size + extraSize - 1)};
}

void Card::setType(Ingredient nType) {
    this->type = nType;
    if(this->getRotTime()) {
        Schedule(this->id, this->getRotTime(), [this, nType]() {
            if(this->type != nType) return;
            cout << this->getTitle() << " has rotten\n";
            this->rotten = true;
        });
    }
}

void Card::place(Card** cPicked) {
    bool valid = true;
    Costumer& costumerCol = GetCollisionCostumer(this->getRec());
    if(costumerCol.state != EMPTY) { // Valid collision with Costumer Rec
        if(costumerCol.order.check(this)) {
            AddScore(costumerCol.score());
            
            this->destroy();
            *cPicked = nullptr;
            return;
        } 
        valid = false;
    } else {
        Card* cardCol = GetCollisionCards(this);
        valid = this->isPositionValid(cardCol);
        if(cardCol && valid) cardCol->insert(this);
    }

    if(!valid && !this->prev && this->lastPrev) { // Returns to previous state
        Card* first = this->lastPrev->propagate([](Card* c, int i) {}, true);
        first->insert(this);
    }

    auto f = [this, valid](Card* c, int i) {
        c->picked = false;
        cards.insert(c);
        if(!valid) {
            c->pos.x = this->lastPos.x; 
            c->pos.y = this->lastPos.y + i*CARD_HEADER_H;
        }
    };
    this->propagate(f);
    *cPicked = nullptr;
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
        cards.remove(c->id);
    };
    this->propagate(f);
}

void Card::insert(Card* card) {
    Card* last = this->propagate([card](Card* c, int i) {c->size += card->size;});
    if(last == card) return; // avoids self insertion 
    cout << card->getTitle() << " inserted on " << this->getTitle() << "\n";
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
        && (!cardCol || this->getRarity())) return true;
    return false;
}

void Card::destroy() {
    auto f = [](Card* c, int i) {
        Unschedule(c->id);
        c->active = false;
    };
    this->propagate(f);
}

Card* Card::propagate(function<void(Card*, int)> f, bool reverse) {
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

// CardList methods implementation
void CardList::insert(Card* c) {
    CardNode* node = new CardNode(c);
    if(!this->last) {
        this->first = node;
        this->last = node;
    } else {
        node->prev = this->last;
        this->last->next = node;
        this->last = node;
    }
    map.insert(node->card->id, node);
    this->size++;
}

Card* CardList::remove(int id) {
    CardNode** nodeptr = this->map.get(id);
    if(!nodeptr) {
        cout << "[ERROR] Removing a non existent node\n";
        return nullptr;
    }
    
    CardNode* node = *nodeptr;
    if(!node) return nullptr;
    
    if(node->prev) node->prev->next = node->next;
    else this->first = node->next;
    
    if(node->next) node->next->prev = node->prev;
    else this->last = node->prev;
    
    node->prev = nullptr;
    node->next = nullptr;  
    
    this->size--;   
    this->map.remove(id);
    return node->card;
}

void CardList::clear() {
    CardNode* cur = this->first;
    while(cur) {
        CardNode* next = cur->next;
        delete this->remove(cur->card->id);
        cur = next;
    }
    this->size = 0;
}

void CardList::propagate(function<void(Card*, int)> f, bool reverse) {
    CardNode* cur = reverse ? this->last : this->first;
    int i=0;
    while(cur) {
        f(cur->card, i);
        cur = reverse ? cur->prev : cur->next;
        i++;
    }
}