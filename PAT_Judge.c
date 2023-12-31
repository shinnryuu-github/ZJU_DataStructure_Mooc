#include <stdio.h>
#include <stdlib.h>

typedef struct _user{
    int is_summit, *problems, total, perfect;
} *user;

void merge(int A[], int Tmp[], int data[], int data2[], int L, int R, int Rend){
    int Lend = R - 1, num = Rend - L + 1, ptr = L;
    while (L <= Lend && R <= Rend){
        if (data[A[L]] > data[A[R]])
            Tmp[ptr++] = A[L++];
        else if (data[A[L]] < data[A[R]])
            Tmp[ptr++] = A[R++];
        else{
            if (data2[A[L]] >= data2[A[R]])
                Tmp[ptr++] = A[L++];
            else
                Tmp[ptr++] = A[R++];
        }
    }
    while (L <= Lend)
        Tmp[ptr++] = A[L++];
    while (R <= Rend)
        Tmp[ptr++] = A[R++];
    for (int k = 0; k < num; k++, Rend--)
        A[Rend] = Tmp[Rend];
}

void Msort(int A[], int Tmp[], int data[], int data2[], int L, int R){
    if (L < R){
        int mid = (L + R) / 2;
        Msort(A, Tmp, data, data2, L, mid);
        Msort(A, Tmp, data, data2, mid + 1, R);
        merge(A, Tmp, data, data2, L, mid + 1, R);
    }
}

void MergeSort(int A[], int data[], int data2[], int N){
    int *Tmp = malloc(sizeof(int) * (N + 1));
    Msort(A, Tmp, data, data2, 1, N);
    free(Tmp);
}

int main(){
    int N, K, M;
    scanf("%d %d %d", &N, &K, &M);
    int rank[N + 1];
    user users[N + 1];
    for (int i = 1; i <= N; i++){
        rank[i] = i;
        users[i] = malloc(sizeof(struct _user));
        users[i]->total = users[i]->perfect = users[i]->is_summit = 0;
        users[i]->problems = malloc(sizeof(int) * (K + 1));
        for (int j = 1; j <= K; j++)
            users[i]->problems[j] = -2;
    }
    int points[K + 1];
    for (int i = 1; i <= K; i++)
        scanf("%d", &points[i]);
    for (int i = 0; i < M; i++){
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        if (c != -1)
            users[a]->is_summit = 1;
        if (c > users[a]->problems[b])
            users[a]->problems[b] = c;
    }
    for (int i = 1; i <= N; i++){
        for (int j = 1; j <= K; j++){
            if (users[i]->problems[j] >= 0)
                users[i]->total += users[i]->problems[j];
            if (users[i]->problems[j] == points[j])
                users[i]->perfect++;
        }
    }
    int total[N + 1], perfect[N + 1];
    for (int i = 1; i <= N; i++){
        total[i] = users[i]->total;
        perfect[i] = users[i]->perfect;
    }
    MergeSort(rank, total, perfect, N);
    int r = 1;
    for (int i = 1; i <= N; i++){
        if (users[rank[i]]->is_summit){
            printf("%d %05d %d ", r, rank[i], users[rank[i]]->total);
            for (int j = 1; j <= K - 1; j++){
                if (users[rank[i]]->problems[j] != -2){
                    if (users[rank[i]]->problems[j] <= 0)
                        printf("0 ");
                    else
                        printf("%d ", users[rank[i]]->problems[j]);
                }
                else
                    printf("- ");
            }
            if (users[rank[i]]->problems[K] != -2){
                    if (users[rank[i]]->problems[K] <= 0)
                        printf("0");
                    else
                        printf("%d", users[rank[i]]->problems[K]);
                }
            else
                printf("-");
            printf("\n");
        }
        if (i < N && total[rank[i]] != total[rank[i + 1]])
            r = i + 1;
    }
    for (int i = 1; i <= N; i++)
        free(users[i]);
}