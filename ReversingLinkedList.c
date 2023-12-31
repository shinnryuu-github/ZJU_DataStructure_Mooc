#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
    int ad, data, next;
}node;

node Ns[100005];
node *List[100005];

int main(){
    int start, N, K;
    scanf("%d %d %d", &start, &N, &K);
    for (int i = 0; i < N; i++){
        int adr;
        scanf("%d", &adr);
        Ns[adr].ad = adr;
        scanf("%d %d", &Ns[adr].data, &Ns[adr].next);
    }
    int count = 0;
    while (start != -1){
        List[count++] = &Ns[start];
        start = Ns[start].next;
    }
    int n = count;
    for (int i = 0; i < n - n % K; i += K){
        for (int j = 0; j < K / 2; j++){
            node *temp = List[j + i];
            List[j + i] = List[i + K - 1 - j];
            List[i + K - 1 - j] = temp;
        }
    }
    for (int i = 0; i < count - 1; i++)
        {
            printf("%05d %d %05d\n", List[i]->ad, List[i]->data, List[i + 1]->ad);
        }
    printf("%05d %d -1", List[count - 1]->ad, List[count - 1]->data);
}