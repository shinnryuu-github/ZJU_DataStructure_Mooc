#include <stdio.h>
#include <stdlib.h>

typedef struct _list{
    int size, *array;
} *list;

list build_list(){
    int n;
    scanf("%d", &n);
    list l = malloc(sizeof(struct _list));
    l->size = n;
    l->array = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++){
        scanf("%d", &l->array[i]);
    }
    return l;
}

void merge(int A[], int TmpA[], int L, int R, int REnd){
    int LEnd = R - 1, ptr = L, count = REnd - L + 1;
    while (L <= LEnd && R <= REnd){
        if (A[L] <= A[R])
            TmpA[ptr++] = A[L++];
        else
            TmpA[ptr++] = A[R++];
    }
    while (L <= LEnd)
        TmpA[ptr++] = A[L++];
    while (R <= REnd)
        TmpA[ptr++] = A[R++];
    for (int i = 0; i < count; i++, REnd--)
        A[REnd] = TmpA[REnd];
}

void merge_pass(int A[], int TmpA[], int N, int lenth){
    int i;
    for (i = 0; i < N - 2 * lenth; i += 2 * lenth){
        merge(A, TmpA, i, i + lenth, i + 2 * lenth - 1);
    }
    if (i + lenth < N)
        merge(A, TmpA, i, i + lenth, N - 1);
    else{
        for (int j = i; j < N; j++)
            TmpA[j] = A[j];
    }
}

int is_same(int A[], int B[], int N){
    for (int i = 0; i < N; i++){
        if (A[i] != B[i])
            return 0;
    }
    return 1;
}

int is_insert(list l, list mid){
    for (int i = 1; i < l->size; i++){
        int temp = l->array[i], j;
        for (j = i; j > 0 && l->array[j - 1] > temp; j--)
            l->array[j] = l->array[j - 1];
        l->array[j] = temp;
        if (is_same(l->array, mid->array, l->size))
            return i;
    }
    return 0;
}

int merge_lenth(list l, list mid){
    int *Tmp = malloc(sizeof(int) * l->size), lenth = 1;
    while (lenth < l->size){
        merge_pass(l->array, Tmp, l->size, lenth);
        lenth *= 2;
        if (is_same(l->array, mid->array, l->size)){
            return lenth;
        }
    }
    return 0;
}

int main(){
    list l = build_list(), temp = malloc(sizeof(struct _list)), mid = malloc(sizeof(struct _list));
    mid->size = temp->size = l->size;
    mid->array = malloc(sizeof(int) * mid->size);
    temp->array = malloc(sizeof(int) * temp->size);
    for (int i = 0; i < temp->size; i++){
        temp->array[i] = l->array[i];
        scanf("%d", &mid->array[i]);
    }
    int r = is_insert(temp, mid);
    if (r){
        printf("Insertion Sort\n");
        int a = temp->array[r + 1], j;
        for (j = r + 1; j > 0 && temp->array[j - 1] > a; j--)
            temp->array[j] = temp->array[j - 1];
        temp->array[j] = a;
        for (int i = 0; i < l->size - 1; i++)
            printf("%d ", temp->array[i]);
        printf("%d", temp->array[l->size - 1]);
    }
    else {
        printf("Merge Sort\n");
        int lenth = merge_lenth(l, mid);
        int *Tmp = malloc(sizeof(int) * l->size);
        merge_pass(mid->array, Tmp, mid->size, lenth);
        for (int i = 0; i < l->size - 1; i++)
            printf("%d ", mid->array[i]);
        printf("%d", mid->array[l->size - 1]);
    }
}