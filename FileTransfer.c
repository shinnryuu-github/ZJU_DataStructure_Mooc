#include <stdio.h>
#include <stdlib.h>

int find(int *A, int a){
    if (A[a - 1] < 0){
        return a;
    }
    return A[a - 1] = find(A, A[a - 1]);
}

void Union(int *A, int a, int b){
    if (A[a - 1] < A[b - 1]) {
        A[a - 1] += A[b - 1];
        A[b - 1] = a;       
    }
    else{
        A[b - 1] += A[a - 1];
        A[a - 1] = b;
    }
}

void connect(int *A, int a, int b){
    int roota = find(A, a), rootb = find(A, b);
    if (roota == rootb)
        return;
    Union(A, roota, rootb);
}

void check(int *A, int a, int b){
    int roota = find(A, a), rootb = find(A, b);
    if (roota == rootb)
        printf("Yes\n");
    else
        printf("No\n");
}

void whole_check(int *A, int N){
    int count = 0;
    for (int i = 0; i < N; i++){
        if (A[i] < 0){
            count++;
        }
    }
    if (count == 1){
        printf("The network is connected.\n");
    }
    else{
        printf("There are %d components.\n", count);
    }
}

int main(){
    int N;
    scanf("%d", &N);
    int A[N];
    for (int i = 0; i < N; i++){
        A[i] = -1;
    }
    char c;
    int a, b;
    do{
        scanf("%c", &c);
        switch (c){
        case 'I':
            scanf("%d %d", &a, &b);
            connect(A, a, b);
            break;       
        case 'C':
            scanf("%d %d", &a, &b);
            check(A, a, b);
            break;
        case 'S':
            whole_check(A, N);
            break;
        }
    }while(c != 'S');
}