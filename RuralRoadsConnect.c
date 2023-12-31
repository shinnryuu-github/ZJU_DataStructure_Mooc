#include <stdio.h>
#include <stdlib.h>

#define MAXNUM 1001
#define INDINITY 114514


typedef struct _enode{
    int v1, v2, weight;
} *edge;

typedef struct _adjnode{
    int adjv, weight;
    struct _adjnode *next;
} *adjnode;

typedef struct _vnode{
    adjnode firstadj;
} vnode;

typedef struct _gnode{
    int nv, ne;
    vnode G[MAXNUM];
} *graph;

graph creat_graph(int nv, int ne){
    graph g = malloc(sizeof(struct _gnode));
    g->ne = ne;
    g->nv = nv;
    for (int i = 1; i <= g->nv; i++){
        g->G[i].firstadj = NULL;
    }
    return g;
}

void insert_edge(graph g, edge e){
    adjnode new1 = malloc(sizeof(struct _enode));
    new1->adjv = e->v2;
    new1->weight = e->weight;
    new1->next = g->G[e->v1].firstadj;
    g->G[e->v1].firstadj = new1;
    adjnode new2 = malloc(sizeof(struct _enode));
    new2->adjv = e->v1;
    new2->weight = e->weight;
    new2->next = g->G[e->v2].firstadj;
    g->G[e->v2].firstadj = new2;
}

graph build_graph(){
    int N, M;
    scanf("%d %d", &N, &M);
    graph g = creat_graph(N, M);
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

int find_min_dist(graph g, int dist[]){
    int min_dist = INDINITY, min_v;
    for (int i = 1; i <= g->nv; i++){
        if (dist[i] && dist[i] < min_dist){
            min_dist = dist[i];
            min_v = i;
        }
    }
    if (min_dist < INDINITY){
        return min_v;
    }
    return 0;
}

int find_dist(graph g, int v1, int v2){
    int dist = INDINITY;
    for (adjnode w = g->G[v1].firstadj; w; w = w->next){
        if (w->adjv == v2){
            dist = w->weight;
        }
    }
    return dist;
}

int Prim(graph g, int dist[]){
    int total = 0, cnt = 0;
    for (int i = 1; i <= g->nv; i++){
        dist[i] = find_dist(g, 1, i);
    }
    dist[1] = 0;
    cnt = 1;
    while (1){
        int w = find_min_dist(g, dist);
        if (!w)
            break;
        total += dist[w];
        dist[w] = 0;
        cnt++;
        for (adjnode adj = g->G[w].firstadj; adj; adj = adj->next){
            if (dist[adj->adjv] && adj->weight < dist[adj->adjv])
                dist[adj->adjv] = adj->weight;
        }
    }
    if (cnt < g->nv){
        return -1;
    }
    return total;
}

int main(){
    graph g = build_graph();
    int dist[g->nv + 1];
    int b = Prim(g, dist);
    printf("%d", b);
}