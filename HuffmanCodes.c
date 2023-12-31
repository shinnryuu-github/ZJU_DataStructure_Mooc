#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct _tnode{
    char data, *code;
    int weight;
    struct _tnode *left, *right;
}tnode;

typedef tnode *huffman;

typedef struct{
    int capacity, size;
    huffman *data;
} _minheap;

typedef _minheap *minheap;

minheap creat_h(int N){
    minheap h = malloc(sizeof(_minheap));
    h->size = 0;
    h->capacity = N;
    h->data = malloc(sizeof(huffman) * (h->capacity + 1));
    huffman min_weight = malloc(sizeof(tnode));
    min_weight->weight = -1;
    h->data[0] = min_weight;
    return h;
}

bool is_full(minheap h){
    return h->size == h->capacity;
}

bool is_empty(minheap h){
    return h->size == 0;
}

void insert(minheap h, huffman t){
    if (is_full(h))
        return;
    int i = ++h->size;
    for (; h->data[i / 2]->weight > t->weight; i /= 2){
        h->data[i] = h->data[i / 2];
    }
    h->data[i] = t;
}

void percdown(minheap h, int p){
    huffman x = h->data[p];
    int parent = p, child;
    for (; parent * 2 <= h->size; parent = child){
        child = 2 * parent;
        if (child + 1 <= h->size && h->data[child]->weight > h->data[child + 1]->weight)
            child++;
        if (x->weight <= h->data[child]->weight)
            break;
        else
            h->data[parent] = h->data[child];
    }
    h->data[parent] = x;
}

huffman delete(minheap h){
    if (is_empty(h))
        return NULL;
    huffman r = h->data[1];
    huffman x = h->data[h->size--];
    int parent = 1, child;
    for (; parent * 2 <= h->size; parent = child){
        child = 2 * parent;
        if (child + 1 <= h->size && h->data[child]->weight > h->data[child + 1]->weight)
            child++;
        if (x->weight <= h->data[child]->weight)
            break;
        else
            h->data[parent] = h->data[child];
    }
    h->data[parent] = x;
    return r;
}

void build(minheap h){
    for (int i = h->size / 2; i > 0; i--){
        percdown(h, i);
    }
}

void free_h(minheap h){
    free(h->data);
    free(h);
}

huffman creat_t(char *inputs, int *weights, int N){
    minheap h = creat_h(N);
    for (int i = 0; i < N; i++){
        huffman ptr = malloc(sizeof(tnode));
        ptr->data = inputs[i];
        ptr->weight = weights[i];
        ptr->left = ptr->right = NULL;
        ptr->code = NULL;
        h->data[i + 1] = ptr;
        h->size++;
    }
    build(h);
    while (h->size > 1){
        huffman a = delete (h);
        huffman b = delete (h);
        huffman new = malloc(sizeof(tnode));
        new->left = a;
        new->right = b;
        new->data = '#';
        new->weight = a->weight + b->weight;
        insert(h, new);
    }
    huffman r = delete(h);
    free_h(h);
    return r;
}

int WPL(huffman t, int d){
    if (!t){
        return 0;
    }
    if (t->data == '#'){
        return WPL(t->left, d + 1) + WPL(t->right, d + 1);
    }
    return t->weight * d + WPL(t->left, d + 1) + WPL(t->right, d + 1);
}

int is_ok(char *s, char *p){
    int lenp = strlen(p), lens = strlen(s);
    if (lenp > lens){
        return 1;
    }
    int r = 0;
    for (int i = 0; i < lenp; i++){
        if (p[i] != s[i]){
            r = 1;
            break;
        }
    }
    return r;
}

void check(int  N, int total, int *weight){
    char *codes[N];
    for (int i = 0; i < N; i++) {
        codes[i] = malloc(64 * sizeof(char));
    }
    int sum = 0;
    for (int i = 0; i < N; i++){
        char d;
        scanf("%c", &d);
        getchar();
        scanf("%s", codes[i]);
        sum += strlen(codes[i]) * weight[i];
    }
    if (sum != total){
        printf("No\n");
        for (int i = 0; i < N; i++) {
            free(codes[i]);
        }
        return;
    }
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if (j != i){
                if (!is_ok(codes[i], codes[j])){
                    printf("No\n");
                    for (int i = 0; i < N; i++) {
                        free(codes[i]);
                    }
                    return;
                }
            }
        }
    }

    printf("Yes\n");
    for (int i = 0; i < N; i++) {
        free(codes[i]);
    }
}

void free_tree(huffman t) {
    if (t) {
        free_tree(t->left);
        free_tree(t->right);
        free(t->code);
        free(t);
    }
}

int main(){
    int N, M;
    scanf("%d", &N);
    getchar();
    char inputs[N];
    int weights[N];
    for (int i = 0; i < N; i++){
        scanf("%c %d", &inputs[i], &weights[i]);
        getchar();
    }
    huffman t = creat_t(inputs, weights, N);
    int total = WPL(t, 0);
    scanf("%d", &M);
    getchar();
    for (int i = 0; i < M; i++){
        check(N, total, weights);
    }
    free_tree(t);
}