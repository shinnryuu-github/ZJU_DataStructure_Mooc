#include <stdio.h>
#include <stdlib.h>

#define MAXNUM 100
#define INFINITY 2147483647

typedef struct _qnode{
    int head, rear, size, *list;
} *queue;

queue creat_queue(int n){
    queue q = malloc(sizeof(struct _qnode));
    q->size = n;
    q->head = q->rear = 0;
    q->list = malloc(sizeof(int) * n);
    return q;
}

int enqueue(queue q, int v){
    if ((q->rear + 1) % q->size == q->head){
        return 0;
    }
    q->rear = (q->rear + 1) % q->size;
    q->list[q->rear] = v;
    return 1;
}

int deququq(queue q){
    if (q->rear == q->head){
        return -1;
    }
    q->head = (q->head + 1) % q->size;
    return q->list[q->head];
}

typedef struct _enode{
    int v1, v2, weight;
} *edge;

typedef struct _gnode{
    int nv, earlist[MAXNUM], in_degree[MAXNUM], G[MAXNUM][MAXNUM];
} *graph;

graph creat_graph(int nv){
    graph g = malloc(sizeof(struct _gnode));
    g->nv = nv;
    for (int i = 0; i < nv; i++){
        g->earlist[i] = 0;
        g->in_degree[i] = 0;
        for (int j = 0; j < nv; j++){
            g->G[i][j] = INFINITY;
        }
    }
    return g;
}

void insert_edge(graph g, edge e){
    g->G[e->v1][e->v2] = e->weight;
    g->in_degree[e->v2]++;
}

graph build_graph(){
    int N, M;
    scanf("%d %d", &N, &M);
    graph g = creat_graph(N);
    for (int i = 0; i < M; i++){
        int v1, v2, weight;
        scanf("%d %d %d", &v1, &v2, &weight);
        edge e = malloc(sizeof(struct _enode));
        e->v1 = v1;
        e->v2 = v2;
        e->weight = weight;
        insert_edge(g, e);
    }
    return g;
}

int top_sort(graph g){
    queue q = creat_queue(g->nv + 1);
    int top_order[g->nv];
    for (int i = 0; i < g->nv; i++){
        if (!g->in_degree[i])
            enqueue(q, i);
    }
    int min = 0, cnt = 0;
    while (q->head != q->rear){
        int w = deququq(q);
        top_order[cnt++] = w;
        for (int i = 0; i < g->nv; i++){
            if (g->G[w][i] != INFINITY){
                if (--(g->in_degree[i]) == 0)
                    enqueue(q, i);
                if (g->earlist[w] + g->G[w][i] > g->earlist[i])
                    g->earlist[i] = g->earlist[w] + g->G[w][i];
            }
        }
    }
    if (cnt == g->nv){
        for (int i = 0; i < cnt; i++){
            if (g->earlist[i] > min){
                min = g->earlist[i];
            }
        }
        return min;
    }
    else{
        return -1;
    }
}

int main(){
    graph g = build_graph();
    int cost = top_sort(g);
    if (cost == -1)
        printf("Impossible");
    else {
        printf("%d", cost);
    }
}