#ifndef AVL_H
#define AVL_H

#include <string>
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

    AVL_node(std::string s, float p): order(s), patience(p), difficulty(GetCostumerDifficulty(s, p)), h(0), left(nullptr), right(nullptr) {}
};


struct AVL {
    AVL_node* root;

    AVL(): root(nullptr) {}
    AVL(AVL_node* _root): root(_root) {}

    void insert(std::string order, float patience);
    AVL_node* search(float difficulty);
    void destroy();
};

// Exports
void InitAVL(std::string path);
Costumer GetCostumerByDifficulty(float d);

#endif 