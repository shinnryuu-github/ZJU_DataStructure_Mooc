#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
    int left, right;
} node;

typedef struct _qnode
{
    int data;
    struct _qnode *next;
} qnode;

typedef struct 
{
    qnode *head, *rear;
} queue;

queue *creat_q(){
    queue *q = malloc(sizeof(queue));
    q->head = NULL;
    q->rear = NULL;
    return q;
}

void enq(queue *q, int d){
    qnode *temp = malloc(sizeof(qnode));
    temp->data = d;
    if (!q->head){
        temp->next = NULL;
        q->head = q->rear = temp;
    }
    else{
        temp->next = NULL;
        q->rear->next = temp;
        q->rear = temp;
    }
}

int deq(queue *q){
    if (!q->head){
        return -1;
    }
    qnode *ptr = q->head;
    int r = q->head->data;
    q->head = q->head->next;
    if (!q->head)
        q->rear = NULL;
    free(ptr);
    return r;
}

void print(node T[], int root){
    queue *q = creat_q();
    int out[10], count = 0;
    enq(q, root);
    while (q->head && root != -1){
        int ptr = deq(q);
        if (T[ptr].left == -1 && T[ptr].right == -1){
            out[count] = ptr;
            count++;
        }
        if (T[ptr].left != -1) enq(q, T[ptr].left);
        if (T[ptr].right != -1) enq(q, T[ptr].right);
    }
    for (int i = 0; i < count - 1; i++){
        printf("%d ", out[i]);
    }
    printf("%d", out[count - 1]);
}

int main(){
    int N;
    scanf("%d", &N);
    node T[N];
    int conected[N];
    for (int i = 0; i < N; i++) conected[i] = 0;
    for (int i = 0; i < N; i++){
        char a, b;
        scanf(" %c %c", &a, &b);
        if (a == '-'){
            T[i].left = -1;
        }
        else{
            T[i].left = a - '0';
            conected[a - '0'] = 1;
        }
        if (b == '-'){
            T[i].right = -1;
        }
        else{
            T[i].right = b - '0';
            conected[b - '0'] = 1;
        }
    }
    int root = -1;
    for (int i = 0; i < N; i++){
        if (conected[i] == 0){
            root = i;
            break;
        }
    }
    print(T, root);
}