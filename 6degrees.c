#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXNUM 1000

bool visited[MAXNUM + 1];

typedef int vertex;

typedef struct _qnode{
    vertex v;
    struct _qnode *next;
} *qnode;

typedef struct _queue{
    qnode head, rear;
} *queue;

queue creat_q(){
    queue q = malloc(sizeof(struct _queue));
    q->head = q->rear = NULL;
    return q;
}

bool is_empty(queue q){
    return q->head == NULL;
}

queue enqueue(queue q, vertex v){
    qnode ptr = malloc(sizeof(struct _qnode));
    ptr->v = v;
    ptr->next = NULL;
    if (is_empty(q)){
        q->head = q->rear = ptr;
    }
    else{
        q->rear->next = ptr;
        q->rear = ptr;
    }
    return q;
}

vertex dequeue(queue q){
    if (is_empty(q)){
        return -1;
    }
    vertex r = q->head->v;
    qnode ptr = q->head;
    q->head = ptr->next;
    free(ptr);
    return r;
}

typedef struct _adjnode{
    vertex v;
    struct _adjnode *next;
} *adjnode;

typedef struct _vnode{
    adjnode firstedge;
} *vnode;

typedef struct _edge{
    vertex v1, v2;
} *edge;

typedef struct _gnode{
    int nv, ne;
    vnode *G;
} *graph;

graph creat_g(int N){
    graph g = malloc(sizeof(struct _gnode));
    g->nv = N;
    g->ne = 0;
    g->G = malloc((N + 1) * sizeof(vnode));
    for (int i = 1; i < N + 1; i++){
        g->G[i] = malloc(sizeof(struct _vnode));
        g->G[i]->firstedge = NULL;
    }
    return g;
}

void insert_edge(graph g, edge e){
    g->ne++;
    adjnode new1 = malloc(sizeof(struct _adjnode));
    new1->v = e->v2;
    new1->next = g->G[e->v1]->firstedge;
    g->G[e->v1]->firstedge = new1;
    adjnode new2 = malloc(sizeof(struct _adjnode));
    new2->v = e->v1;
    new2->next = g->G[e->v2]->firstedge;
    g->G[e->v2]->firstedge = new2;
}

graph build_g()
{
    int N, M;
    scanf("%d %d", &N, &M);
    graph g = creat_g(N);
    for (int i = 0; i < M; i++){
        edge e = malloc(sizeof(struct _edge));
        scanf("%d %d", &e->v1, &e->v2);
        insert_edge(g, e);
    }
    return g;
}

int BFS(graph g, vertex v, bool visited[]){
    int count = 1, level = 0;
    vertex last = v, tail;
    queue q = creat_q();
    visited[v] = true;
    enqueue(q, v);
    while (!is_empty(q)){
        vertex v2 = dequeue(q);
        for (adjnode w = g->G[v2]->firstedge; w; w = w->next){
            if(!visited[w->v]){
                visited[w->v] = true;
                count++;
                enqueue(q, w->v);
                tail = w->v;
            }
        }
        if (v2 == last){
            level++;
            last = tail;
        }
        if (level == 6)
            break;
    }
    return count;
}

void refresh(){
    for (int i = 0; i < MAXNUM + 1; i++){
        visited[i] = false;
    }
}

void SDS(graph g){
    for (int i = 1; i <= g->nv; i++){
        int count = BFS(g, i, visited);
        printf("%d: %.2f%\n", i, 100 * count / (float)g->nv);
        refresh();
    }
}

int main(){
    graph g = build_g();
    SDS(g);
}