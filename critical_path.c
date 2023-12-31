#include <stdio.h>
#include <stdlib.h>

#define MAXNUM 101
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
    int nv, earlist[MAXNUM], latest[MAXNUM], in_degree[MAXNUM], out_degree[MAXNUM], G[MAXNUM][MAXNUM];
} *graph;

graph creat_graph(int nv){
    graph g = malloc(sizeof(struct _gnode));
    g->nv = nv;
    for (int i = 1; i <= nv; i++){
        g->earlist[i] = 0;
        g->in_degree[i] = 0;
        g->latest[i] = INFINITY;
        g->out_degree[i] = 0;
        for (int j = 1; j <= nv; j++){
            g->G[i][j] = INFINITY;
        }
    }
    return g;
}

void insert_edge(graph g, edge e){
    g->G[e->v1][e->v2] = e->weight;
    g->in_degree[e->v2]++;
    g->out_degree[e->v1]++;
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

int top_sort(graph g, int top_order[]){
    queue q = creat_queue(g->nv + 1);
    for (int i = 1; i <= g->nv; i++){
        if (!g->in_degree[i])
            enqueue(q, i);
    }
    int min = 0, cnt = 0;
    while (q->head != q->rear){
        int w = deququq(q);
        top_order[cnt++] = w;
        for (int i = 1; i <= g->nv; i++){
            if (g->G[w][i] != INFINITY){
                if (--(g->in_degree[i]) == 0)
                    enqueue(q, i);
                if (g->earlist[w] + g->G[w][i] > g->earlist[i])
                    g->earlist[i] = g->earlist[w] + g->G[w][i];
            }
        }
    }
    if (cnt == g->nv)
    {
        for (int i = 1; i <= cnt; i++)
        {
            if (g->earlist[i] > min)
            {
                min = g->earlist[i];
            }
        }
        return min;
    }
    else{
        return -1;
    }
}

int bottom_sort(graph g, int bottom_order[]){
    queue q = creat_queue(g->nv + 1);
    for (int i = 1; i <= g->nv; i++){
        if (!g->out_degree[i])
            enqueue(q, i);
    }
    int min = 0, cnt = 0;
    while (q->head != q->rear){
        int w = deququq(q);
        bottom_order[cnt++] = w;
        for (int i = 1; i <= g->nv; i++){
            if (g->G[i][w] != INFINITY){
                if (--(g->out_degree[i]) == 0)
                    enqueue(q, i);
                if (g->latest[w] - g->G[i][w] < g->latest[i])
                    g->latest[i] = g->latest[w] - g->G[i][w];
            }
        }
    }
}

int main(){
    graph g = build_graph();
    int top_order[g->nv], bottom_order[g->nv];
    int cost = top_sort(g, top_order);
    if (cost == -1)
        printf("0");
    else {
        printf("%d\n", cost);
        for (int i = 1; i <= g->nv; i++){
            g->latest[i] = cost;
        }
        bottom_sort(g, bottom_order);
        for (int i = 1; i <= g->nv; i++){
            for (int j = g->nv; j >= 1; j--){
                if (g->G[i][j] < INFINITY && g->latest[j] - g->earlist[i] - g->G[i][j] <= 0)
                    printf("%d->%d\n", i, j);
            }
        }
    }
}