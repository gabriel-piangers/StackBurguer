#ifndef QUEUE_H
#define QUEUE_H

template <typename T>
struct QueueNode {
    T data;
    QueueNode* next;

    QueueNode(T item): data(item), next(nullptr) {}
};

template <typename T>
struct Queue {
    int size;
    QueueNode<T>* start;
    QueueNode<T>* end;

    Queue(): size(0), start(nullptr), end(nullptr) {}

    inline void insert(T item) {
        QueueNode<T>* node = new QueueNode<T>(item);
        if(!this->start) {
            this->start = node;
            this->end = node;
        } else {
            this->end->next = node;
            this->end = node;
        }
        
        this->size++;
    }

    inline T pop() {
        if(!this->start) {
            std::cerr << "[ERROR] Attempted to remove from a empty queue\n";
        }

        QueueNode<T>* node = this->start;
        T item = node->data;
        
        this->start = this->start->next;
        delete node;
        this->size--;

        return item;
    }

    inline void clear() {
        QueueNode<T>* cur = this->start;
        while(cur) {
            QueueNode<T>* prev = cur;
            cur = cur->next;
            delete prev;
        }

        this->start = nullptr;
        this->end = nullptr;
        this->size = 0;
    }

    inline bool empty() {
        return this->size == 0;
    }
};


#endif