#include <stdio.h>
#include <stdlib.h>

typedef struct _tnode{
    int data, height;
    struct _tnode *left, *right;
} tnode;

typedef tnode *AVL;

typedef struct _snode{
    AVL data;
    struct _snode *next;
}snode;

typedef struct _queue{
    snode *head, *rear;
}queue;

int is_empty(queue *s){
    if (!s->head){
        return 1;
    }
    return 0;
}

queue *push(queue *s, AVL t){
    snode *ptr = malloc(sizeof(snode));
    ptr->data = t;
    ptr->next = NULL;
    if (is_empty(s)){
        s->head = s->rear = ptr;
    } else {
        s->rear->next = ptr;
        s->rear = ptr;
    }
    return s;
}

AVL pop(queue *s){
    snode *ptr = s->head;
    AVL r = ptr->data;
    s->head = s->head->next;
    if (!s->head){
        s->rear = NULL;
    }
    free(ptr);
    return r;
}

int max(int a, int b){
    return (a > b) ? a : b;
}

int get_height(AVL t){
    if (!t){
        return 0;
    }
    return max(get_height(t->left), get_height(t->right)) + 1;
}

AVL LL(AVL t){
    AVL ptr = t->left;
    t->left = ptr->right;
    ptr->right = t;
    t->height = max(get_height(t->left), get_height(t->right)) + 1;
    ptr->height = max(get_height(ptr->left), get_height(ptr->right)) + 1;
    return ptr;
}

AVL RR(AVL t){
    AVL ptr = t->right;
    t->right = ptr->left;
    ptr->left = t;
    t->height = max(get_height(t->left), get_height(t->right)) + 1;
    ptr->height = max(get_height(ptr->left), get_height(ptr->right)) + 1;
    return ptr;
}

AVL LR(AVL t){
    t->left = RR(t->left);
    t = LL(t);
    return t;
}

AVL RL(AVL t){
    t->right = LL(t->right);
    t = RR(t);
    return t;
}

AVL insert(AVL t, int d){
    if (!t){
        AVL temp = malloc(sizeof(tnode));
        temp->data = d;
        temp->left = temp->right = NULL;
        return temp;
    }
    else{
        if (d < t->data){
            t->left = insert(t->left, d);
            if (get_height(t->left) - get_height(t->right) >= 2){
                if (d < t->left->data){
                    t = LL(t);
                }
                else{
                    t = LR(t);
                }
            }
        }
        else if (d > t->data){
            t->right = insert(t->right, d);
            if (get_height(t->left) - get_height(t->right) <= -2){
                if (d > t->right->data){
                    t = RR(t);
                }
                else{
                    t = RL(t);
                }
            }
        }
    }
    t->height = max(get_height(t->right), get_height(t->left)) + 1;
    return t;
}

void sort(int nums[], int N){
    for (int i = 0; i < N; i++){
        int min = nums[i], index = i;
        for (int j = i; j < N; j++){
            if (nums[j] < min){
                min = nums[j];
                index = j;
            }
        }
        nums[index] = nums[i];
        nums[i] = min;
    }
}

int power(int a, int b){
    if(b == 0){
        return 1;
    }
    return a * power(a, b - 1);
}

int min(int N){
    int r = 1;
    while (N > power(2, r) - 1)
    {
        r++;
    }
    return r - 1;
}

int main(){
    int N;
    scanf("%d", &N);
    int inputs[N];
    for (int i = 0; i < N; i++){
        scanf("%d", &inputs[i]);
    }
    sort(inputs, N);
    int n = min(N);
    int remain = N - power(2, n) + 1;
    int p1[power(2, n) - 1], p2[remain];
    for (int i = 0; i < remain; i++){
        p2[i] = inputs[2 * i];
    }
    for (int i = 0; i < remain; i++){
        p1[i] = inputs[2 * i + 1];
    }
    for (int i = remain; i < power(2, n) - 1; i++){
        p1[i] = inputs[N + 1 + i - power(2, n)];
    }
    AVL t = NULL;
    for (int i = 0; i < power(2, n) - 1; i++){
        t = insert(t, p1[i]);
    }
    for (int i = 0; i < remain; i++){
        t = insert(t, p2[i]);
    }
    int out[N], count = 0;
    queue *s = malloc(sizeof(queue));
    s->head = s->rear = NULL;
    s = push(s, t);
    while (!is_empty(s)){
        AVL ptr = pop(s);
        out[count] = ptr->data;
        count++;
        if (ptr->left) 
            s = push(s, ptr->left);
        if (ptr->right)
            s = push(s, ptr->right);
    }
    for (int i = 0; i < N - 1; i++){
        printf("%d ", out[i]);
    }
    printf("%d", out[N - 1]);
}