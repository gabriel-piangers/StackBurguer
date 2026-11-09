#ifndef DYNAMIC_VECTOR_H
#define DYNAMIC_VECTOR_H

#include <cstdlib>

template <typename T>
struct DynamicVector {
    int size;
    int capacity;
    T* data;

    DynamicVector(int _capacity = 2): size(0), capacity(_capacity) {
        if(_capacity > 2) {
            this->data = (T*) new T[_capacity];
        } else {
            this->data = (T*) new T[2];
        }
    }

    inline void insert(T item) {
        if(this->size == this->capacity) this->reserve(this->capacity*2);

        this->data[this->size] = item;
        this->size++;
    }

    inline T& operator[](int index) {
        if(index >= this->size) {
            std::cerr << "[ERROR] attempt to access an out of bounds index\n";
        }
        return data[index];
    }

    inline void reserve(int nCapacity) {
        if(nCapacity < this->size) {
            std::cerr << "[ERROR] can't reserve less than the current vector size\n";
            return;
        }

        T* nData = (T*) new T[nCapacity];
        for(int i=0; i<this->size; i++) nData[i] = this->data[i];

        delete[] this->data;
        this->data = nData;
        this->capacity = nCapacity;
    }

};


#endif
