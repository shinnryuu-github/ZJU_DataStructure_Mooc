#include <stdio.h>
#include <stdlib.h>

#define INFINITE 114515
#define MAXNUM 101

typedef int vertex;

typedef struct{
    vertex v1, v2;
    int weight;
} enode;
typedef enode *edge;

typedef struct{
    int nv, ne;
    int Gmatrix[MAXNUM][MAXNUM];
} gnode;
typedef gnode *graph;

graph creat_graph(int n){
    graph g = malloc(sizeof(gnode));
    g->nv = n;
    g->ne = 0;
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++)
            g->Gmatrix[i][j] = INFINITE;
    }
    for (int i = 1; i <= n; i++)
        g->Gmatrix[i][i] = 0;
    return g;
}

void insert(graph g, edge e){
    g->ne++;
    g->Gmatrix[e->v1][e->v2] = g->Gmatrix[e->v2][e->v1] = e->weight;
}

graph build_graph(){
    int nv, ne;
    scanf("%d %d", &nv, &ne);
    graph g = creat_graph(nv);
    for (int i = 0; i < ne; i++){
        edge e = malloc(sizeof(enode));
        scanf("%d %d %d", &e->v1, &e->v2, &e->weight);
        insert(g, e);
    }
    return g;
}

void Floyd(graph g, int dist[][MAXNUM]){
    for (int i = 1; i <= g->nv; i++){
        for (int j = 1; j <= g->nv; j++){
            dist[i][j] = g->Gmatrix[i][j];
        }
    }
    for (int k = 1; k <= g->nv; k++){
        for (int i = 1; i <= g->nv; i++){
            for (int j = 1; j <= g->nv; j++){
                if(dist[i][k] + dist[k][j] < dist[i][j]){
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
        }
    }
    }
}

int find_best(int dist[][MAXNUM], int nv)
{
    int max_dist[nv + 1];
    for (int i = 1; i <= nv; i++){
        int max = dist[i][1];
        for (int j = 1; j <= nv; j++){
            if (dist[i][j] > max)
                max = dist[i][j];
        }
        max_dist[i] = max;
    }
    int min = max_dist[1], index = 1;
    for (int i = 1; i <= nv; i++){
        if (max_dist[i] < min){
            min = max_dist[i];
            index = i;
        }
    }
    if (min == INFINITE){
        printf("0");
    }
    else{
        printf("%d %d", index, min);
    }
}

int main(){
    graph g = build_graph();
    int dist[g->nv + 1][MAXNUM];
    Floyd(g, dist);
    find_best(dist, g->nv);
}