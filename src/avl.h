#ifndef AVL_H
#define AVL_H

#include "constants.h"
#include "utils.h"
#include "costumer.h"

#define DIFFICULTY_MARGIN 0.0001f

struct AVL_node {
    std::string order;
    float patience;
    float difficulty;
    int h;
    AVL_node* left;
    AVL_node* right;

    AVL_node(std::string& s, float p, float d): order(s), patience(p), difficulty(d), h(0), left(nullptr), right(nullptr) {}
};


struct AVL {
    AVL_node* root;

    AVL(): root(nullptr) {}
    AVL(AVL_node* _root): root(_root) {}

    void insert(std::string& order, float patience);
    AVL_node* search(float difficulty);
    void destroy();
};

// Exports
void InitAVL(std::string path);
Costumer GetCostumerByDifficulty(float d);

#endif 