#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
    ElementType Data;
    PtrToNode   Next;
};
typedef PtrToNode List;

List Read(); /* 细节在此不表 */
void Print( List L ); /* 细节在此不表；空链表将输出NULL */
void attach(int data, List *rear);
List Merge( List L1, List L2 );

int main()
{
    List L1, L2, L;
    L1 = Read();
    L2 = Read();
    L = Merge(L1, L2);
    Print(L);
    printf("\n");
    Print(L1);
    printf("\n");
    Print(L2);
    return 0;
}

List Read(){
    int N;
    scanf("%d", &N);
    List p = (List)malloc(sizeof(struct Node));
    p->Next = NULL;
    List rear = p;
    for (int i = 0; i < N; i++){
        int data;
        scanf("%d", &data);
        attach(data, &rear);
    }
    return p;
}

void Print(List L){
    if (!L->Next){
        printf("NULL");
        return;
    }
    L = L->Next;
    while (L->Next){
        printf("%d ", L->Data);
        L = L->Next;
    }
    printf("%d", L->Data);
}

void attach(int data, List *rear){
    List p = (List)malloc(sizeof(struct Node));
    p->Data = data;
    p->Next = NULL;
    (*rear)->Next = p;
    (*rear) = p;
}

List Merge( List L1, List L2){
    List L = (List)malloc(sizeof(struct Node));
    L->Next = NULL;
    List rear = L, p1 = L1, p2 = L2;
    p1 = p1->Next;
    p2 = p2->Next;
    while (p1 && p2){
        if (p1->Data <= p2->Data){
            attach(p1->Data, &rear);
            p1 = p1->Next;
        }
        else{
            attach(p2->Data, &rear);
            p2 = p2->Next;
        }
    }
    for (; p1; p1 = p1->Next){
        attach(p1->Data, &rear);
    }
    for (; p2; p2 = p2->Next){
         attach(p2->Data, &rear);
    }
    L1->Next = NULL;
    L2->Next = NULL;
    return L;
}