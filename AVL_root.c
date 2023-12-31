#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
    int height, data;
    struct _node *left, *right;
} node;

typedef node *AVL;

int max(int a, int b){
    return (a > b) ? a : b;
}

int get_height(AVL t){
    if (!t)
        return 0;
    return max(get_height(t->left), get_height(t->right)) + 1;
}

void LL(AVL *t){
    AVL left = (*t)->left;
    (*t)->left = left->right;
    left->right = (*t);
    (*t)->height = max(get_height((*t)->left), get_height((*t)->right)) + 1;
    left->height = max(get_height(left->left), get_height(left->right)) + 1;
    (*t) = left;
}

void RR(AVL *t){
    AVL right = (*t)->right;
    (*t)->right = right->left;
    right->left = (*t);
    (*t)->height = max(get_height((*t)->left), get_height((*t)->right)) + 1;
    right->height = max(get_height(right->left), get_height(right->right)) + 1;
    (*t) = right;
}

void LR(AVL *t){
    RR(&(*t)->left);
    LL(t);
}

void RL(AVL *t){
    LL(&(*t)->right);
    RR(t);
}

void insert(AVL *t, int data){
    node *temp = malloc(sizeof(node));
    temp->data = data;
    temp->left = temp->height = NULL;
    if (!(*t)){
        (*t) = temp;
        (*t)->height = 1;
    }
    else if (data < (*t)->data){
        insert(&(*t)->left, data);
        if (get_height((*t)->left) - get_height((*t)->right) >= 2){
            if (data < (*t)->left->data){
                LL(t);
            }
            else {
                LR(t);
            }
        }
    }
    else if (data > (*t)->data){
        insert(&(*t)->right, data);
        if (get_height((*t)->left) - get_height((*t)->right) <= -2){
            if (data > (*t)->right->data){
                RR(t);
            }
            else {
                RL(t);
            }
        }
    }
    (*t)->height = max(get_height((*t)->left), get_height((*t)->right)) + 1;
}

AVL creat(int N){
    AVL r = NULL;
    for (int i = 0; i < N; i++){
        int d;
        scanf("%d", &d);
        insert(&r, d);
    }
    return r;
}

int main(){
    int N;
    scanf("%d", &N);
    AVL t = creat(N);
    printf("%d", t->data);
}