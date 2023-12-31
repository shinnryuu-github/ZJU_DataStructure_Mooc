#include <stdio.h>
#include <stdlib.h>

int count[51] = {0};

int main(){
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; i++){
        int lenth;
        scanf("%d", &lenth);
        count[lenth]++;
    }
    for (int i = 0; i <= 50; i++){
        if (count[i]){
            printf("%d:%d\n", i, count[i]);
        }
    }
}