#include <stdio.h>
#include <stdlib.h>

#define MAXNUM 501
#define INFINITY 114514

typedef struct _enode{
    int v1, v2, lenth, cost;
} *edge;

typedef struct _gnode{
    int nv, ne, start, end;
    int lenth[MAXNUM][MAXNUM], cost[MAXNUM][MAXNUM];
} *graph;

graph creat_graph(int nv, int ne, int start, int end){
    graph g = malloc(sizeof(struct _gnode));
    g->ne = ne;
    g->nv = nv;
    g->start = start;
    g->end = end;
    for (int i = 0; i < nv; i++){
        for (int j = 0; j < g->nv; j++){
            g->lenth[i][j] = g->cost[i][j] = INFINITY;
        }
        g->lenth[i][i] = g->cost[i][i] = 0;
    }
    return g;
}

void insert_edge(graph g, edge e){
    g->lenth[e->v1][e->v2] = g->lenth[e->v2][e->v1] = e->lenth;
    g->cost[e->v1][e->v2] = g->cost[e->v2][e->v1] = e->cost;
}

graph build_graph(){
    int n, m, s, d;
    scanf("%d %d %d %d", &n, &m, &s, &d);
    graph g = creat_graph(n, m, s, d);
    for (int i = 0; i < g->ne; i++){
        int v1, v2, lenth, cost;
        scanf("%d %d %d %d", &v1, &v2, &lenth, &cost);
        edge newedge = malloc(sizeof(struct _enode));
        newedge->v1 = v1;
        newedge->v2 = v2;
        newedge->cost = cost;
        newedge->lenth = lenth;
        insert_edge(g, newedge);
    }
    return g;
}

void dijkstra(graph g, int dist[], int path[], int total_cost[], int s){
    int collected[g->nv];
    for (int i = 0; i < g->nv; i++){
        collected[i] = 0;
        dist[i] = g->lenth[s][i];
        total_cost[i] = g->cost[s][i];
        if (g->lenth[s][i] < INFINITY){
            path[i] = s;
        }
        else{
            path[i] = -1;
        }
    }
    collected[s] = 1;
    dist[s] = 0;
    path[s] = -1;
    for (int i = 0; i < g->nv - 1; i++){
        int mindist = INFINITY, minv, mincost = INFINITY;
        for (int j = 0; j < g->nv; j++){
            if (!collected[j] && dist[j] < mindist){
                minv = j;
                mindist = dist[j];
                mincost = total_cost[j];
            }
            else if (!collected[j] && dist[j] == mindist && total_cost[j] < mincost){
                minv = j;
                mindist = dist[j];
                mincost = total_cost[j];
            }
        }
        collected[minv] = 1;
        for (int k = 0; k < g->nv; k++){
            if (!collected[k] && g->lenth[minv][k] < INFINITY){
                if (dist[minv] + g->lenth[minv][k] < dist[k]){
                    dist[k] = dist[minv] + g->lenth[minv][k];
                    total_cost[k] = total_cost[minv] + g->cost[minv][k];
                    path[k] = minv;
                }
                else if (dist[minv] + g->lenth[minv][k] == dist[k] && total_cost[minv] + g->cost[minv][k] < total_cost[k]){
                    dist[k] = dist[minv] + g->lenth[minv][k];
                    total_cost[k] = total_cost[minv] + g->cost[minv][k];
                    path[k] = minv;
                }
            }
        }
    }
}

int main(){
    graph g = build_graph();
    int total_lenth[g->nv], path[g->nv], total_cost[g->nv];
    dijkstra(g, total_lenth, path, total_cost, g->start);
    printf("%d %d", total_lenth[g->end], total_cost[g->end]);
}