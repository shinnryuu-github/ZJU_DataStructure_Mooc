#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 1001
#define MINDATA -100001

typedef struct{
    int size, capacity, *data;
} _minheap;

typedef _minheap *minheap;

minheap creat(){
    minheap h = (minheap)malloc(sizeof(_minheap));
    h->capacity = MAXSIZE;
    h->size = 0;
    h->data = malloc(sizeof(int) * (h->capacity + 1));
    h->data[0] = MINDATA;
    return h;
}

void insert(minheap h, int x){
    int i = ++h->size;
    for (; h->data[i / 2] > x; i /= 2){
        h->data[i] = h->data[i / 2];
    }
    h->data[i] = x;
}

void percdown(minheap h, int p){
    int x = h->data[p], parent = p, child;
    for (; 2 * parent <= h->size; parent = child){
        child = parent * 2;
        if (child + 1 <= h->size && h->data[child] > h->data[child + 1])
            child++;
        if (h->data[child] > x)
            break;
        else{
            h->data[parent] = h->data[child];
        }
    }
    h->data[parent] = x;
}

void build(minheap h){
    for (int i = h->size / 2; i > 0; i--){
        percdown(h, i);
    }
}

void print(minheap h, int p){
    int i = p;
    for (; i / 2 > 0; i /= 2){
        printf("%d ", h->data[i]);
    }
    printf("%d", h->data[1]);
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    int inputs[n], count = 0;
    for (int i = 0; i < n; i++){
        scanf("%d", &inputs[count++]);
    }
    minheap h = creat();
    for (int i = 1; i <= count; i++){
        insert(h, inputs[i - 1]);
    }
    for (int i = 0; i < m - 1; i++){
        int p;
        scanf("%d", &p);
        print(h, p);
        printf("\n");
    }
    int p;
        scanf("%d", &p);
        print(h, p);
}