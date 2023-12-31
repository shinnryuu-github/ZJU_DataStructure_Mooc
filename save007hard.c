#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXNUM 101
#define INFINITE 1000

typedef struct _queue{
    int head, rear, n;
    int *v;
} *queue;

queue creat_queue(int n){
    queue q = malloc(sizeof(struct _queue));
    q->n = n;
    q->head = q->rear = 0;
    q->v = malloc(sizeof(int) * n);
    return q;
}

void enqueuq(queue q, int v){
    if ((q->rear + 1) % q->n == q->head){
        return;
    }
    q->rear = (q->rear + 1) % q->n;
    q->v[q->rear] = v;
}

int dequeue(queue q){
    if (q->rear == q->head){
        return -1;
    }
    q->head = (q->head + 1) % q->n;
    return q->v[q->head];
}

typedef struct _stack{
    int head;
    int *stack;
} *stack;

stack creat_stack(int n){
    stack s = malloc(sizeof(struct _stack));
    s->stack = malloc(sizeof(int) * n);
    s->head = 0;
    return s;
}

void push(stack s, int v){
    s->stack[++s->head] = v;
}

int pop(stack s){
    return s->stack[s->head--];
}

typedef struct _pnode{
    int x, y;
} point;

typedef struct _gnode{
    int np, d;
    point points[MAXNUM];
    float matix[MAXNUM][MAXNUM];
} *graph;

float distance(point p1, point p2, int d){
    float dis = sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
    if (dis <= d){
        return dis;
    }
    return INFINITE;
}

graph creat_graph(int n, int d){
    graph g = malloc(sizeof(struct _gnode));
    g->np = n;
    g->d = d;
    for (int i = 0; i < g->np; i++){
        g->points[i].x = g->points[i].y = 0;
        for (int j = 0; j < g->np; j++){
            g->matix[i][j] = INFINITE;
        }
        g->matix[i][i] = 0;
    }
    return g;
}

graph build_graph(){
    int n, d;
    scanf("%d %d", &n, &d);
    graph g = creat_graph(n, d);
    for (int i = 0; i < n; i++){
        int x, y;
        scanf("%d %d", &x, &y);
        g->points[i].x = x;
        g->points[i].y = y;
    }
    for (int i = 0; i < n; i++){
        if (sqrt(g->points[i].x * g->points[i].x + g->points[i].y * g->points[i].y) <= 7.5 || abs(g->points[i].x ) == 50 || abs(g->points[i].y) == 50){
            for (int j = 0; j < n; j++)
                g->matix[i][j] = INFINITE;
        } 
        else {
            for (int j = 0; j < n; j++){
                g->matix[i][j] = distance(g->points[i], g->points[j], d);
            }
        }
    }
    return g;
}

int find_start(graph g, int d, int start[]){
    int count = 0;
    point p0 = {0, 0};
    for (int i = 0; i < g->np; i++){
        if (distance(p0, g->points[i], d + 7.5) < INFINITE && distance(p0, g->points[i], d + 7.5) > 0){
            start[count++] = i;
        }
    }
    return count;
}

int find_end(graph g, int d, int end[]){
    int count = 0;
    for (int i = 0; i < g->np; i++){
        if (abs(g->points[i].x) != 50 || abs(g->points[i].y) != 50){
            if (abs(g->points[i].x) >= 50 - d || abs(g->points[i].y) >= 50 - d){
                end[count++] = i;
            }
        }
    }
    return count;
}

void bfs(graph g, int path[], int dist[], int s){
    for (int i = 0; i < g->np; i++){
        path[i] = -1;
        dist[i] = -1;
    }
    queue q = creat_queue(MAXNUM);
    dist[s] = 1;
    path[s] = -1;
    enqueuq(q, s);
    while (q->head != q->rear){
        int v = dequeue(q);
        for (int i = 0; i < g->np; i++){
            if (g->matix[v][i] != INFINITE && g->matix[v][i] != 0 && dist[i] == -1){
                dist[i] = dist[v] + 1;
                path[i] = v;
                enqueuq(q, i);
            }
        }
    }
}

void sort(graph g, int start[], int count1){
    for (int i = 0; i < count1; i++){
        float min_first = sqrt(pow(g->points[start[i]].x, 2) + pow(g->points[start[i]].y, 2));
        int index = i;
        for (int j = i; j < count1; j++){
            if (sqrt(pow(g->points[start[j]].x, 2) + pow(g->points[start[j]].y, 2)) < min_first){
                min_first = sqrt(pow(g->points[start[j]].x, 2) + pow(g->points[start[j]].y, 2));
                index = j;
            }
        }
        int temp = start[i];
        start[i] = start[index];
        start[index] = temp;
    }
}

int main(){
    graph g = build_graph();
    if (g->d >= 42.5){
        printf("1");
        return 0;
    }
    int start[g->np], end[g->np];
    int count1 = find_start(g, g->d, start), count2 = find_end(g, g->d, end);
    sort(g, start, count1);
    int path[g->np], dist[g->np], real_path[g->np], min = INFINITE, real_out;
    for (int i = 0; i < count1; i++){
        bfs(g, path, dist, start[i]);
        int min_dist = INFINITE, out;
        for (int j = 0; j < count2; j++){
            if (dist[end[j]] < min_dist && dist[end[j]] != -1){
                min_dist = dist[end[j]];
                out = end[j];
            }
        }
        if (min_dist < min){
            min = min_dist;
            real_out = out;
            for (int k = 0; k < g->np; k++){
                real_path[k] = path[k];
            }
        }
    }
    if (min == INFINITE)
        printf("0");
    else {
        printf("%d\n", min + 1);
        stack s = creat_stack(MAXNUM);
        for (int i = real_out; i != -1; i = real_path[i]){
            push(s, i);
        }
        while (s->head){
            int p = pop(s);
            printf("%d %d\n", g->points[p].x, g->points[p].y);
        }
    }
}