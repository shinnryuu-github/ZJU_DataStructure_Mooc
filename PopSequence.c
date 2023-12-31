#include <stdio.h>
#include <stdlib.h>

int is_in(int p, int nums[], int pre){
    if (p > pre){
        return 0;
    }
    for (int i = pre; i >= p; i--){
        if (nums[i] == 0 && i > p)
        {
            return 0;
        }
    }
    return 1;
}

void check(int input[], int M, int N)
{
    int n = 1;
    int nums[N + 1];
    for (int i = 1; i <= N; i++){
        nums[i] = 0;
    }
    int pre = 0;
    while (n <= N){
        int p = input[n];
        if ((p < pre + 1 || p > M + n - 1 ) && (!is_in(p, nums, pre))){
            printf("NO\n");
            return;
        }
        pre = p;
        nums[p] = 1;
        n++;
    }
    printf("YES\n");
}

int main(){
    int M, N, K;
    scanf("%d %d %d", &M, &N, &K);
    int input[K + 1][N + 1];
    for (int i = 1; i <= K; i++){
        for (int j = 1; j <= N; j++){
            scanf("%d", &input[i][j]);
        }
    }
    for (int i = 1; i <= K; i++){
        check(input[i], M, N);
    }
}