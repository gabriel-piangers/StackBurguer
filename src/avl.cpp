#include "avl.h"
#include "timer.h"
#include "hash_table.h"
#include "utils.h"
#include <fstream>
#include <random>

using namespace std;

AVL avl;
HashTable<int, AVL_node> cache;

void InitAVL(string path) {
    Timer timer;
    timer_iniciar(&timer);
    
    ifstream file(path); // read-only
    if(!file.is_open()) {
        cerr << "Error opening the file in path " << path << "\n";
        return;
    }
    string order;
    while(getline(file, order)) {
        getline(file, order);
        float patience = RandomFloat(45.0f, 90.0f);       
        avl.insert(order, patience);
    }

    file.close();
    cout << "InitAVL execution time: " << timer_parar(&timer) << " seconds\n";
}

int ApplyDifficultyMargin(float d) {
    return (int) (d/DIFFICULTY_MARGIN);
}

Costumer GetCostumerByDifficulty(float d) {
    AVL_node* cached = cache.get(ApplyDifficultyMargin(d));
    if(cached){
        cout << "Cache hit!\n";
        return Costumer(cached->order, cached->patience);
    }

    AVL_node* node = avl.search(d);
    Costumer costumer = Costumer(node->order, node->patience);
    cache.insert(ApplyDifficultyMargin(costumer.difficulty), *node);
    
    return costumer;
}

int GetFb(AVL_node* node) {
    if(!node) return 0;

    int lh = node->left ? node->left->h : -1;
    int rh = node->right ? node->right->h : -1;

    return lh - rh;
}

void updateHeight(AVL_node* node) {
    int lh = node->left ? node->left->h : -1;
    int rh = node->right ? node->right->h : -1;
    node->h = max(lh, rh) + 1;
}

void RotateL(AVL_node** root) {
    AVL_node* r = (*root)->right;
    AVL_node* rl = (*root)->right->left;
    (*root)->right = rl;
    r->left = *root;
    updateHeight(*root);
    updateHeight(r);

    *root = r;
}

void RotateR(AVL_node** root) {
    AVL_node* l = (*root)->left;
    AVL_node* lr = l->right;
    (*root)->left = lr;
    l->right = *root;
    updateHeight(*root);
    updateHeight(l);

    *root = l;
}


void balance(AVL_node** root) {
    int fb = GetFb((*root));

    if(fb >= 2 && GetFb((*root)->left) >= 0) {
        RotateR(root);
    } else if (fb >= 2) {
        RotateL(&(*root)->left);
        RotateR(root);
    } else if (fb <= -2 && GetFb((*root)->right) <= 0) {
        RotateL(root);
    } else if (fb <= -2) {
        RotateR(&(*root)->right);
        RotateL(root);
    }
}

void Insert(AVL_node** root, string& s, float p, float d) {
    if(!(*root)) {
        AVL_node* node = new AVL_node(s, p, d);
        (*root) = node;
    }
    else if (d < (*root)->difficulty) Insert(&(*root)->left, s, p, d);
    else Insert(&(*root)->right, s, p, d);
    
   updateHeight((*root));
   balance(root);
}

AVL_node* SearchClosest(AVL_node* root, float d) { // Retorna o mais proximo
    if(!root) return nullptr;
    if(abs(d - root->difficulty) < DIFFICULTY_MARGIN) return root;
    if(d < root->difficulty) return root->left ? SearchClosest(root->left, d) : root;
    
    return root->right ? SearchClosest(root->right, d) : root;
}

void Destroy(AVL_node* root) {
    if(!root) return;
    Destroy(root->left);
    Destroy(root->right);

    delete root;
}

void AVL::insert(string& s, float p) {
    float d = GetCostumerDifficulty(s, p);
    Insert(&this->root, s, p, d);
}

AVL_node* AVL::search(float d) {
    return SearchClosest(this->root, d);
}

void AVL::destroy() {
    Destroy(this->root);
    this->root = nullptr;
}