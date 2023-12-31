#include <stdio.h>

void swap(int sequence[], int x){
    int index = sequence[0];
    sequence[0] = sequence[x];
    sequence[x] = index;
}

int swap_sort(int sequnce[], int N){
    int count = 0;
    for (int i = 1; i < N; i++){
        if (sequnce[i] != i){
            if (sequnce[0] == 0) {
                swap(sequnce, i);
                count++;
            }
            while (sequnce[0] != 0){
                swap(sequnce, sequnce[0]);
                count++;
            }
        }
    }
    return count;
}

int main(){
    int N;
    scanf("%d", &N);
    int sequence[N];
    for (int i = 0; i < N; i++){
        int x;
        scanf("%d", &x);
        sequence[x] = i;
    }
    printf("%d", swap_sort(sequence, N));
}