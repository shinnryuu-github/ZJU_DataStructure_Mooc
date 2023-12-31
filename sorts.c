#include <stdio.h>
#include <stdlib.h>

typedef struct _list{
    int size, *array;
} *list;

int compare(const void *a, const void *b){
    const int *x = a, *y = b;
    return *x - *y;
}

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

void swap(int *a, int *b){
    int temp = *b;
    *b = *a;
    *a = temp;
}

void bubble_sort(list l){
    for (int i = l->size - 1; i >= 0; i--){
        int flag = 0;
        for (int j = 0; j < i; j++){
            if (l->array[j] > l->array[j + 1]){
                swap(&l->array[j], &l->array[j + 1]);
                flag = 1;
            }
        }
        if (!flag)
            break;
    }
}

void insertion_sort(list l){
    for (int i = 1; i < l->size; i++){
        int temp = l->array[i], j;
        for (j = i; j > 0 && l->array[j - 1] > temp; j--){
            l->array[j] = l->array[j - 1];
        }
        l->array[j] = temp;
    }
}

void InsertSort(int A[], int N){
    for (int i = 1; i < N; i++){
        int temp = A[i], j;
        for (j = i; j > 0 && A[j - 1] > temp; j--){
            A[j] = A[j - 1];
        }
        A[j] = temp;
    }
}

void selection_sort(list l){
    for (int i = 0; i < l->size; i++){
        int min = l->array[i], index = i;
        for (int j = i; j < l->size; j++){
            if (l->array[j] < min){
                index = j;
                min = l->array[j];
            }
        }
        swap(&l->array[i], &l->array[index]);
    }
}

void shell_sort(list l){
    int magic[] = {929, 505, 209, 109, 41, 19, 5, 1, 0}, dist, i;
    for (i = 0; i < 9; i++){
        if (magic[i] < l->size){
            dist = magic[i];
            break;
        }
    }
    for (dist = magic[i]; dist > 0; dist = magic[++i])
        for (int j = dist; j < l->size; j += dist){
            int temp = l->array[j], k;
            for (k = j; k > 0 && l->array[k - dist] > temp; k -= dist){
                l->array[k] = l->array[k - dist];
            }
            l->array[k] = temp;
        }
}

void percdown(list l, int p, int n){
    int temp = l->array[p], parent, child;
    for (parent = p; (parent * 2 + 1) < n; parent = child){
        child = parent * 2 + 1;
        if ((child != n - 1) && (l->array[child] < l->array[child + 1]))
            child++;
        if (temp >= l->array[child])
            break;
        else
            l->array[parent] = l->array[child];
    }
    l->array[parent] = temp;
}

void heap_sort(list l){
    for (int i = (l->size - 1) / 2; i >= 0; i--)
        percdown(l, i, l->size);
    for (int i = l->size - 1; i > 0; i--){
        swap(&l->array[0], &l->array[i]);
        percdown(l, 0, i); 
    }
}

void merge(int A[], int TmpA[], int L, int R, int REnd){
    int Lend = R - 1, num = REnd - L + 1, ptr = L;
    while (L <= Lend && R <= REnd){
        if (A[L] >= A[R])
            TmpA[ptr++] = A[R++];
        else
            TmpA[ptr++] = A[L++];
    }
    while (L <= Lend)
        TmpA[ptr++] = A[L++];
    while (R <= REnd)
        TmpA[ptr++] = A[R++];
    for (int i = 0; i < num; i++, REnd--)
        A[REnd] = TmpA[REnd];
}

void Msort(int A[], int TmpA[], int L, int REnd){
    if (L < REnd){
        int mid = (L + REnd) / 2;
        Msort(A, TmpA, L, mid);
        Msort(A, TmpA, mid + 1, REnd);
        merge(A, TmpA, L, mid + 1, REnd);
    }
}

void merge_sort(list L){
    int *TmpA = malloc(sizeof(int) * L->size);
    if (TmpA == NULL)
        printf("空间不足");
    else
        Msort(L->array, TmpA, 0, L->size - 1);
}

void merge_pass(int A[], int TmpA[], int N, int lenth){
    int i;
    for (i = 0; i <= N - 2 * lenth; i += 2 * lenth)
        merge(A, TmpA, i, i + lenth, i + 2 * lenth - 1);    
    if (i + lenth < N)
        merge(A, TmpA, i, i + lenth, N - 1);
    else{
        for (int j = i; j < N; j++){
            TmpA[j] = A[j];
        }
    }
}

void merge_sort2(list l){
    int *TmpA = malloc(sizeof(int) * l->size);
    if (!TmpA)
        printf("空间不足");
    else{
        int lenth = 1;
        while (lenth < l->size){
            merge_pass(l->array, TmpA, l->size, lenth);
            lenth *= 2;
            merge_pass(TmpA, l->array, l->size, lenth);
            lenth *= 2;
        }       
    }
}

int median3(int A[], int L, int R){
    int mid = (L + R) / 2;
    if (A[L] > A[mid])
        swap(&A[L], &A[mid]);
    if (A[L] > A[R])
        swap(&A[L], &A[R]);
    if (A[mid] > A[R])
        swap(&A[mid], &A[R]);
    swap(&A[L], &A[R - 1]);
    return A[R - 1];
}

void Qsort(int A[], int L, int R){
    if (R - L > 20){
        int pivot = median3(A, L, R);
        int low = L, high = R - 1;
        while (low < high){
            while (A[++low] < pivot);
            while (A[++high] < pivot);
            if (low < high)
                swap(&A[low], &A[high]);
            else
                break;
        }
        swap(&A[low], &A[R - 1]);
        Qsort(A, L, low - 1);
        Qsort(A, low + 1, R);
    }
    else {
        InsertSort(A + L, R - L + 1);
    }
}

int pivot_pos(int A[], int L, int R){
    int pivot = A[L];
    while (L < R){
        while (L < R && A[R] > pivot)
            R--;
        A[L] = A[R];
        while (L < R && A[L] < pivot)
            L++;
        A[R] = A[L];
    }
    A[L] = pivot;
    return L;
}

void Qsort2(int A[], int L, int R){
    if (L < R){
        int pivotp = pivot_pos(A, L, R);
        Qsort2(A, L, pivotp - 1);
        Qsort2(A, pivotp + 1, R);
    }
}

int main(){
    list l = build_list();
    Qsort2(l->array, 0, l->size - 1);
    for (int i = 0; i < l->size - 1; i++)
        printf("%d ", l->array[i]);
    printf("%d", l->array[l->size - 1]);
}