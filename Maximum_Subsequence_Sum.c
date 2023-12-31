#include <stdio.h>

int main(){
    int K;
    scanf("%d", &K);
    int nums[K];
    for (int i = 0; i < K; i++){
        scanf("%d", &nums[i]);
    }
    int max = 0, now = 0, i1 = 0, i2 = 0, j1 = 0, j2 = 0;
    for (int i = 0; i < K; i++){
        now += nums[i];
        if (nums[i] == 0 && max == 0){
            i1 = j1;
            i2 = j2;
        }
        if (now > max){
            max = now;
            i1 = j1;
            i2 = j2;
            i2 = i;
        }
        if (now < 0){
            now = 0;
            j1 = j2 = i + 1;
        }
    }
    if (max == 0){
        if (nums[i1] != 0){
        i1 = 0;
        i2 = K - 1;
        }
    }
    printf("%d %d %d", max, nums[i1], nums[i2]);
}