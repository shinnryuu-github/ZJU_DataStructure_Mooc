#include <stdio.h>
#include <stdlib.h>

#define INFINITY 114514

typedef struct _gnode{
    int nv, *indegree, **matirx, *data;
} *graph;

typedef struct _enode{
    int v1, v2;
} *edge;

graph creat_graph(int N){
    graph g = malloc(sizeof(struct _gnode));
    g->nv = N;
    g->indegree = malloc(sizeof(int) * N);
    g->matirx = malloc(sizeof(int*) * N);
    g->data = malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++){
        g->indegree[i] = 0;
        g->matirx[i] = malloc(sizeof(int) * N);
        for (int j = 0; j < N; j++)
            g->matirx[i][j] = INFINITY;
    }
    return g;
}

void insert_edge(graph g, edge e){
    g->matirx[e->v1][e->v2] = 1;
    g->indegree[e->v2]++;
}

int hash_pos(int x, int N){
    return x % N;
}

typedef struct _heap{
    int size, capacity, *data;
} *heap;

heap creat_heap(int N){
    heap h = malloc(sizeof(struct _heap));
    h->capacity = N;
    h->size = 0;
    h->data = malloc(sizeof(int) * (N + 1));
    h->data[0] = -1;
    return h;
}

void insert(heap h, int x){
    int i = ++h->size;
    for (; x < h->data[i / 2]; i /= 2)
        h->data[i] = h->data[i / 2];
    h->data[i] = x;
}

int delete(heap h){
    int r = h->data[1], parent, child, x = h->data[h->size--];
    for (parent = 1; 2 * parent <= h->size; parent = child){
        child = parent * 2;
        if (child + 1 <= h->size && h->data[child] > h->data[child + 1])
            child++;
        if (x <= h->data[child])
            break;
        else
            h->data[parent] = h->data[child];
    }
    h->data[parent] = x;
    return r;
}

void top_sort(graph g){
    int top_order[g->nv], cnt = 0;
    heap h = creat_heap(g->nv);
    for (int i = 0; i < g->nv; i++){
        if (g->indegree[i] == 0 && g->data[i] >= 0)
            insert(h, g->data[i]);
    }
    while (h->size){
        int v = delete (h);
        top_order[cnt++] = v;
        int p;
        for (int i = 0; i < g->nv; i++){
            if (v == g->data[i]){
                p = i;
                break;
            }
        }
        for (int i = 0; i < g->nv; i++){
            if (g->matirx[p][i] < INFINITY && g->data[i] >= 0){
                if (--g->indegree[i] == 0)
                    insert(h, g->data[i]);
            }
        }
    }
    for (int i = 0; i < cnt - 1; i++)
        printf("%d ", top_order[i]);
    printf("%d", top_order[cnt - 1]);
}

int main(){
    int N;
    scanf("%d", &N);
    int data[N];
    for (int i = 0; i < N; i++){
        scanf("%d", &data[i]);
    }
    graph g = creat_graph(N);
    for (int i = 0; i < N; i++){
        g->data[i] = data[i];
        if (data[i] >= 0){
            int dist = (i - hash_pos(data[i], N) + N) % N, p = hash_pos(data[i], N);
            for (int j = 0; j < dist; j++){
                edge e = malloc(sizeof(struct _enode));
                e->v1 = p;
                e->v2 = i;
                insert_edge(g, e);
                p = (p + 1) % N;
            }
        }
    }
    top_sort(g);
}