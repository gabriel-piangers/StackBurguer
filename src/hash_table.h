#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#define K 0.6180339887f // Golden ratio

template <typename Key>
int defaultHash(int m, Key key) {
    return (int) m*(K*key - floor(K*key));
}

template <typename Key, typename Value>
struct HashNode {
    Key key;
    Value value;
    HashNode* next;

    HashNode(Key _key, Value& _value): key(_key), value(_value), next(nullptr) {} 
};

template <typename Key, typename Value>
struct HashTable {
    HashNode<Key, Value>** data;
    int size;
    int capacity;

    HashTable(): data(nullptr), size(0), capacity(4) {
        this->data = new HashNode<Key, Value>*[this->capacity];
        for(int i=0; i<this->capacity; i++) this->data[i] = nullptr;
    }
    
    inline void insert(Key key, Value item) {
        if(this->get(key)) return;

        int index = defaultHash(this->capacity, key);
        HashNode<Key, Value>* node = new HashNode<Key, Value>(key, item);
        if(this->data[index]) {
            HashNode<Key, Value>* tmp = this->data[index];
            this->data[index] = node;
            node->next = tmp;
        } else this->data[index] = node;
        
        this->size++;

        if((float)this->size/(float)this->capacity >= 0.75) this->rehash();
    }

    inline void remove(Key key) {
        int index = defaultHash(this->capacity, key);
        if(this->data[index]) {
            HashNode<Key, Value>* cur = this->data[index];
            HashNode<Key, Value>* prev = nullptr;
            while(cur && cur->key!=key) {
                prev = cur;
                cur = cur->next;
            }
            if(cur) {
                if(prev) prev->next = cur->next;
                else if(cur->next) this->data[index] = cur->next; 
                delete cur;
            }
        }
    }

    inline Value* get(Key key) {
        int index = defaultHash(this->capacity, key);
        HashNode<Key, Value>* cur = this->data[index];

        while(cur) {
            if(cur->key == key) return &(cur->value);
            cur = cur->next;
        }   
        return nullptr;
    }

    inline void print() { //debugging
        for(int i=0; i<this->capacity; i++) {
            std::cout << i << ": ";
            if(this->data[i]) {
                HashNode<Key, Value>* cur = this->data[i];
                while(cur) {
                    std::cout << cur->key << " -> ";
                    cur = cur->next;
                }
            } else std::cout << "null";
            std::cout << "\n";
        }
    }

    inline void rehash() {
        int nCapacity = this->capacity*2;
        HashNode<Key, Value>** nData = new HashNode<Key, Value>*[nCapacity];
        for(int i=0; i<nCapacity; i++) nData[i] = nullptr;

        for(int i=0; i<this->capacity; i++) {
            HashNode<Key, Value>* cur = this->data[i];
            while(cur) {
                HashNode<Key, Value>* next = cur->next;
                cur->next = nullptr;
                
                int index = defaultHash(nCapacity, cur->key);
                if(nData[index]) {
                    HashNode<Key, Value>* tmp = nData[index];
                    nData[index] = cur;
                    cur->next = tmp;
                } else nData[index] = cur;

                cur = next;
            }
        }

        delete[] this->data;
        this->capacity = nCapacity;
        this->data = nData;
    }
};

#endif