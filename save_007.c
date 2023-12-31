#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

typedef struct{
    int x, y;
} point;

float distance(point p1, point p2){
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

bool is_jump(point p1, point p2, int maxd){
    return maxd >= distance(p1, p2);
}

bool is_safe(point p, int maxd){
    if (p.x - maxd <= -50)
        return true;
    if (p.x + maxd >= 50)
        return true;
    if (p.y - maxd <= -50)
        return true;
    if (p.y + maxd >= 50)
        return true;
    return false;
}

bool DFS(point crocodiles[], int index, bool visited[], int maxd, int N){
    visited[index] = true;
    bool answer = false;
    if (is_safe(crocodiles[index], maxd)){
        answer = true;
    }
    else{
        for (int i = 0; i < N; i++){
            if (!visited[i] && is_jump(crocodiles[index], crocodiles[i], maxd)){
                answer = DFS(crocodiles, i, visited, maxd, N);
                visited[i] = true;
                if (answer)
                    break;
            }
        }
    }
    return answer;
}

void save_007(){
    int N, D;
    scanf("%d %d", &N, &D);
    if (D + 7.5 >= 50){
        printf("Yes");
        return;
    }
    point crocodiles[N], O;
    O.y = O.x = 0;
    for (int i = 0; i < N; i++){
        scanf("%d %d", &crocodiles[i].x, &crocodiles[i].y);
    }
    bool visited[N];
    for (int i = 0; i < N; i++){
        visited[i] = false;
    }
    bool answer = false;
    for (int i = 0; i < N; i++){
        if (!visited[i] && distance(crocodiles[i], O) < 7.5 + D){
            answer = DFS(crocodiles, i, visited, D, N);
            if (answer)
                break;
        }
    }
    if (answer){
        printf("Yes");
    }
    else {
        printf("No");
    }
}

int main(){
    save_007();
}