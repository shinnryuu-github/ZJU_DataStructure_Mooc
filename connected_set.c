#include <stdio.h>
#include <stdlib.h>

#define MAXVERTEX 20

typedef int vertex;

typedef struct _enode{
    vertex v1, v2;
} enode;

typedef enode *edge;

typedef struct{
    int nv, ne;
    int GM[MAXVERTEX][MAXVERTEX];
} Gnode;

typedef Gnode *Mgraph;

Mgraph creat_g(int nv){
    Mgraph r = malloc(sizeof(Gnode));
    r->ne = 0;
    r->nv = nv;
    for (int i = 0; i < nv; i++){
        for (int j = 0; j < nv; j++)
            r->GM[i][j] = 0;
    }
    return r;
}

void insert_edge(Mgraph g, edge e){
    g->ne++;
    g->GM[e->v1][e->v2] = g->GM[e->v2][e->v1] = 1;
}

Mgraph build_g(int n){
    int m;
    Mgraph r = creat_g(n);
    scanf("%d", &m);
    for (int i = 0; i < m; i++){
        int v1, v2;
        scanf("%d %d", &v1, &v2);
        edge e = malloc(sizeof(enode));
        e->v1 = v1;
        e->v2 = v2;
        insert_edge(r, e);
    }
    return r;
}

void DFS(Mgraph g, vertex v, int visited[]){
    printf("%d ", v);
    visited[v] = 1;
    for (int i = 0;i < g->nv; i++){
        if (g->GM[v][i] && !visited[i])
            DFS(g, i, visited);
    }
}

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

void enqueue(queue q, vertex v){
    qnode ptr = malloc(sizeof(struct _qnode));
    ptr->v = v;
    ptr->next = NULL;
    if (!q->head){
        q->head = q->rear = ptr;
    }
    else{
        q->rear->next = ptr;
        q->rear = ptr;
    }
}

vertex dequeue(queue q){
    vertex r = q->head->v;
    qnode ptr = q->head;
    q->head = q->head->next;
    free(ptr);
    return r;
}

void BFS(Mgraph g, vertex v, int visited[]){
    queue q = creat_q();
    printf("%d ", v);
    visited[v] = 1;
    enqueue(q, v);
    while (q->head){
        vertex temp = dequeue(q);
        for (vertex w = 0; w < g->nv; w++){
            if (!visited[w] && g->GM[temp][w]){
                printf("%d ", w);
                visited[w] = 1;
                enqueue(q, w);
            }
        }
    }
}

int main(){
    int n;
    scanf("%d", &n);
    Mgraph g = build_g(n);
    int visited[n];
    for (int i = 0; i < n; i++){
        visited[i] = 0;
    }
    for (int i = 0; i < n; i++){
        if(!visited[i]){
            printf("{ ");
            DFS(g, i, visited);
            printf("}\n");
        }
    }
    for (int i = 0; i < n; i++){
        visited[i] = 0;
    }
    for (int i = 0; i < n; i++){
        if(!visited[i]){
            printf("{ ");
            BFS(g, i, visited);
            printf("}\n");
        }
    }
}   