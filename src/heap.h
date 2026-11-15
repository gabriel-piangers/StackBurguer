#ifndef HEAP_H
#define HEAP_H

#include <functional>
#include "dynamic_vector.h"

template <typename T>
struct Heap {
    DynamicVector<T> data;
    std::function<bool(T&, T&)> comp;
    int size;

    Heap(std::function<bool(T&, T&)> _comp): data(), comp(_comp), size(0) {}

    inline void siftUp(int i) {
        int parent = (i - 1)/2;
        while(i >= 0 && comp(this->data[i], this->data[parent])) {
            T tmp = this->data[i];
            this->data[i] = this->data[parent];
            this->data[parent] = tmp;

            i = parent;
            parent = i/2;
        }
    }

    inline void siftDown(int i) {
        int l = i*2 + 1, r = i*2 + 2, winner = i;
        if(l <= this->size && comp(this->data[l], this->data[winner])) winner = l;
        if(r <= this->size && comp(this->data[r], this->data[winner])) winner = r;

        if(winner != i) {
            T tmp = this->data[i];
            this->data[i] = this->data[winner];
            this->data[winner] = tmp;

            this->siftDown(winner);
        }
    }

    inline void insert(T& item) {
        this->data.insert(item);
        this->siftUp(this->size++); 
    }

    inline T pop() {
        this->data.size--;
        this->size--;
        T item = this->data[0];
        this->data[0] = this->data[this->size];
        this->siftDown(0);

        return item;
    }

    inline T top() {
        return this->data[0];
    }

    inline void remove(std::function<bool(T&)> f) {
        for(int i=this->size-1; i>=0; i--) {
            if(f(this->data[i])) {
                this->size--;
                this->data.size--;
                
                if(i < this->size) {
                    this->data[i] = this->data[this->size];
                    siftDown(i);
                }
            }
        }
    }

    inline bool empty() {
        return this->size == 0;
    }

    inline void clear() {
        this->size = 0;
        this->data.clear();
    }
};

#endif