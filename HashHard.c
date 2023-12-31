#include <stdio.h>
#include <stdlib.h>

int hash_pos(int N, int x){
    return x % N;
}

void insert_sort(int A[], int N){
    for (int i = 1; i < N; i++){
        int tmp = A[i], j;
        for (j = i; j > 0 && A[j - 1] > tmp; j--)
            A[j] = A[j - 1];
        A[j] = tmp;
    }
}

void insert(int A[], int x, int dist, int N, int y){
    int ypos;
    for (int i = 0; i < N; i++){
        if (A[i] == y){
            ypos = i;
            break;
        }
    }
    int pos = ypos + dist;
    while (x > A[pos]){
        pos++;
    }
    for (int i = N - 1; i > pos; i--)
        A[i] = A[i - 1];
    A[pos] = x;
}

int main(){
    int N;
    scanf("%d", &N);
    int tbl[N], correct[N], count = 0, sort[N], pos = 0, num = 0;
    for (int i = 0; i < N; i++){
        scanf("%d", &tbl[i]);
        if (tbl[i] >= 0){
            num++;
            if (hash_pos(N, tbl[i]) == i){
                correct[i] = 1;
                count++;
            }
            else
                correct[i] = 0;
        }
        else {
            correct[i] = 0;
        }
    }
    for (int i = 0; i < N; i++){
        if (correct[i])
            sort[pos++] = tbl[i];
    }
    insert_sort(sort, pos);
    for (int i = pos; i < num; i++)
        sort[i] = 114514;
    int pre;
    for (int i = 0; i < N; i++)
        if (!correct[i] && tbl[i] >= 0){
            pre = tbl[i - 1];
            break;
        }
    for (int i = 0; i < N; i++){
        if (!correct[i] && tbl[i] >= 0){
            insert(sort, tbl[i], 1, num, pre);
        }
        pre = tbl[i];
    }
    for (int i = 0; i < num - 1; i++)
        printf("%d ", sort[i]);
    printf("%d", sort[num - 1]);
}