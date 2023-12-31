#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define empty -1
#define deleted 1
#define Legitimate 0

typedef struct _node{
    int info, data;
} node;

typedef struct _hash{
    int size;
    node *tbl;
} *hash;

int is_prime(int x){
    for (int i = 2; i <= sqrt(x); i++){
        if (x % i == 0)
            return 0;
    }
    return 1;
}

int next_prime(int x){
    for (int i = 1;;i++){
        if (is_prime(x + i)){
            return x + i;
        }
    }
}

hash build_hash(int N){
    hash h = malloc(sizeof(struct _hash));
    h->size = next_prime(N);
    h->tbl = malloc(sizeof(node) * h->size);
    for (int i = 0; i < h->size; i++){
        h->tbl[i].info = empty;
    }
    return h;
}

int hash_pos(hash h, int x){
    return x % h->size;
}


int find(hash h, int x){
    int pos = hash_pos(h, x);
    int newpos = pos, count = 1;
    while (h->tbl[newpos].info != empty && h->tbl[newpos].data != x){
        newpos = (pos + count * count) % h->size;
        count++;
    }
    return newpos;
}

int insert(hash h, int x){
    int pos = find(h, x);
    if (h->tbl[pos].info != Legitimate){
        h->tbl[pos].data = x;
        h->tbl[pos].info = Legitimate;
        return pos;
    }
    else{
        return -1;
    }
}

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    hash h = build_hash(N);
    int result[M];
    for (int i = 0; i < M; i++){
        int x;
        scanf("%d", &x);
        result[i] = insert(h, x);
    }
    for (int i = 0; i < M - 1; i++){
        if (result[i] == -1)
            printf("- ");
        else
            printf("%d ", result[i]);
    }
    if (result[M - 1] == -1)
        printf("-");
    else
        printf("%d", result[M - 1]);
}