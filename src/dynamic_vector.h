#ifndef DYNAMIC_VECTOR_H
#define DYNAMIC_VECTOR_H

#include <algorithm>
#include <functional>

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

    inline void clear() {
        this->size = 0;
        this->reserve(2);
    }

    template <typename Comp, typename Swap>
    inline void sort(Comp _comp = [](T& t1, T& t2) {return t1 < t2;}, Swap _swap = [](T& t1, T& t2) {std::swap(t1, t2);}) {
        Quicksort(this->data, 0, this->size-1, _comp, _swap);
    }
};

template <typename T, typename Comp, typename Swap>
int Partition(T* A, int a, int b, Comp _comp, Swap _swap) {
    // Find the median
    int mid = (a+b)/2, median=a;
    if(_comp(A[mid], A[b]) ^ _comp(A[mid], A[a])) median = mid;
    else if (_comp(A[b], A[mid]) ^ _comp(A[b], A[a])) median = b;
    _swap(A[b], A[median]);

    // Partionate
    T pivot = A[b];
    int i=a-1, j;
    for(j=a; j<b; j++) {
        if(_comp(A[j], pivot)) {
            _swap(A[++i], A[j]);
        }
    }
    _swap(A[++i], A[b]);
    return i;
}

template <typename T, typename Comp, typename Swap>
void Quicksort(T* A, int a, int b, Comp _comp, Swap _swap) {
    if(a >= b) return;
    int p = Partition(A, a, b, _comp, _swap);
    Quicksort(A, a, p-1, _comp, _swap);
    Quicksort(A, p+1, b, _comp, _swap);
}


#endif
