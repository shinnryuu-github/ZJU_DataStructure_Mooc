#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10
#define NotFound 0
typedef int ElementType;

typedef int Position;
typedef struct LNode *List;
struct LNode {
    ElementType Data[MAXSIZE];
    Position Last; /* 保存线性表中最后一个元素的位置 */
};

List ReadInput(); /* 裁判实现，细节不表。元素从下标1开始存储 */
Position BinarySearch( List L, ElementType X );

int main()
{
    List L;
    ElementType X;
    Position P;

    L = ReadInput();
    scanf("%d", &X);
    P = BinarySearch( L, X );
    printf("%d\n", P);

    return 0;
}


List ReadInput(){
    List rt = malloc(sizeof(struct LNode));
    int lenth;
    scanf("%d", &lenth);
    for (int i = 1; i <= lenth; i++){
        scanf("%d", &rt->Data[i]);
    }
    rt->Last = lenth;
    return rt;
}

Position BinarySearch( List L, ElementType X ){
    int l = 1, r = L->Last;
    int m = (l + r) / 2;
    while (l <= r){
        if (L->Data[m] == X){
            return m;
        }
        else if (L->Data[m] < X){
            l = m + 1;
            m = (l + r) / 2;
        }
        else {
            r = m - 1;
            m = (l + r) / 2;
        }
    }
    return NotFound;
}