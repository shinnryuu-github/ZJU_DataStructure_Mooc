#include <stdio.h>
#include <stdlib.h>

typedef struct _tnode{
    int flag, data;
    struct _tnode *left, *right;
} tnode;

typedef tnode *tree;

void insert(tree *t, int data){
    if (!*t){
        *t = malloc(sizeof(tnode));
        (*t)->data = data;
        (*t)->flag = 0;
        (*t)->left = (*t)->right = NULL;
    }
    else{
        if (data < (*t)->data){
            insert(&(*t)->left, data);
        }
        else if (data > (*t)->data){
            insert(&(*t)->right, data);
        }
        else{
            return;
        }
    }
}

tree creat_t(int N){
    tree t = NULL;
    for (int i = 0; i < N; i++){
        int d;
        scanf("%d", &d);
        insert(&t, d);
    }
    return t;
}

void reset(tree *t){
    if (!(*t)){
        return;
    }
    (*t)->flag = 0;
    reset(&(*t)->left);
    reset(&(*t)->right);
}

void delete(tree *t){
    if (!(*t)){
        return;
    }
    delete (&(*t)->left);
    delete (&(*t)->right);
    free(*t);
}

int check(tree *t, int d){
    if ((*t)->flag){
        if (d < (*t)->data){
            return check(&(*t)->left, d);
        }
        else if (d > (*t)->data){
            return check(&(*t)->right, d);
        }
        else{
            return 0;
        }
    }
    else {
        if (d == (*t)->data){
            (*t)->flag = 1;
            return 1;
        }
        else {
            return 0;
        }
    }
}

int judge(tree *t, int N){
    int r = 1;
    for (int i = 0; i < N; i++){
        int d;
        scanf("%d", &d);
        if (!check(t, d)){
            r = 0;
        }
    }
    return r;
}

int main(){
    int N, L;
    scanf("%d", &N);
    while (N){
        scanf("%d", &L);
        tree t = creat_t(N);
        for (int i = 0; i < L; i++){
            if (judge(&t, N)){
                printf("Yes\n");
            }
            else{
                printf("No\n");
            }
            reset(&t);
        }
        scanf("%d", &N);
        delete (&t);
    }
}