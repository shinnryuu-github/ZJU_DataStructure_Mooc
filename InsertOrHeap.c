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

int is_same(int A[], int B[], int N){
    for (int i = 0; i < N; i++){
        if (A[i] != B[i])
            return 0;
    }
    return 1;
}

void percdown(int A[], int N, int p){
    int parent, child, temp = A[p];
    for (parent = p; 2 * parent + 1 < N; parent = child){
        child = 2 * parent + 1;
        if (child + 1 < N && A[child] < A[child + 1])
            child++;
        if (temp > A[child])
            break;
        A[parent] = A[child];
    }
    A[parent] = temp;
}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int haep_times(list l, list mid){
    for (int i = (l->size - 1) / 2; i >= 0; i--)
        percdown(l->array, l->size, i);
    for (int i = l->size - 1; i > 0; i--){
        swap(&l->array[0], &l->array[i]);
        percdown(l->array, i, 0);
        if (is_same(l->array, mid->array, l->size))
            return i - 1;
    }
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
        printf("Heap Sort\n");
        int n = haep_times(l, mid);
        swap(&mid->array[0], &mid->array[n]);
        percdown(mid->array, n, 0);
        for (int i = 0; i < l->size - 1; i++)
            printf("%d ", mid->array[i]);
        printf("%d", mid->array[l->size - 1]);
    }
}