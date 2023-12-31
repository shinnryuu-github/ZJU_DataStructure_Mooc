#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _tnode{
    int data;
    struct _tnode *left, *right;
}tnode;

typedef tnode *tree;

typedef struct _snode{
    tnode *data;
    struct _snode *next;
} snode;

typedef snode *stack;

// l_r 0->左， 1->右
void add(tnode *n, tnode *ps, int l_r){
    if (!l_r)
        ps->left = n;
    else
        ps->right = n;
}

stack creat_stack(){
    stack s = malloc(sizeof(snode));
    s->next = NULL;
    return s;
}

void push(stack *s, tnode *n){
    snode *temp = malloc(sizeof(snode));
    temp->data = n;
    temp->next = *s;
    *s = temp;
}

tnode *pop(stack *s){
    if (!(*s)->next){
        return NULL;
    }
    snode *ptr = (*s);
    tnode *r = (*s)->data;
    (*s) = (*s)->next;
    free(ptr);
    return r;
}

tree creat_t(){
    stack s = creat_stack();
    int N;
    scanf("%d", &N);
    int l_r = 0;
    tree T = malloc(sizeof(tnode));
    T->left = T->right = NULL;
    tnode *ps = T;
    for (int i = 0; i < 2 * N; i++){
        char str[5];
        int n;
        scanf("%s", &str);
        if (!strcmp(str, "Push")){
            scanf("%d", &n);
            tnode *ptr = malloc(sizeof(tnode));
            ptr->data = n;
            ptr->left = ptr->right = NULL;
            add(ptr, ps, l_r);
            push(&s, ptr);
            ps = (!l_r)? ps->left : ps->right;
            l_r = 0;
        }
        else if (!strcmp(str, "Pop")){
            l_r = 1;
            ps = pop(&s);
        }
    }
    tnode *ptr = T;
    T = T->left;
    free(ptr);
    return T;
}

void postoder(tree T){
    tree ptr = T, last = NULL;
    stack s = creat_stack();
    int out[50], count = 0;
    while (ptr || s->next){
        while (ptr){
            push(&s, ptr);
            ptr = ptr->left;
        }
        ptr = pop(&s);
        if (ptr->right && ptr->right != last){
            push(&s, ptr);
            ptr = ptr->right;
        }
        else{
            out[count] = ptr->data;
            count++;
            last = ptr;
            ptr = NULL;
        }
    }
    for (int i = 0; i < count - 1; i++){
        printf("%d ", out[i]);
    }
    printf("%d", out[count - 1]);
}

int main(){
    tree T = creat_t();
    postoder(T);
}