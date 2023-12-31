#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

void PreorderTraversal( BinTree BT ){
    if (!BT){
        return;
    }
    printf("%d ", BT->Data);
    PreorderTraversal(BT->Left);
    PreorderTraversal(BT->Right);
} /* 先序遍历，由裁判实现，细节不表 */
void InorderTraversal( BinTree BT ){
    if (!BT){
        return;
    }
    InorderTraversal(BT->Left);
    printf("%d ", BT->Data);
    InorderTraversal(BT->Right);
}  /* 中序遍历，由裁判实现，细节不表 */

Position Find( BinTree BST, ElementType X ){
    if (!BST){
        return NULL;
    }
    if (X < BST->Data){
        return Find(BST->Left, X);
    }
    else if (X > BST->Data){
        return Find(BST->Right, X);
    }
    else{

        return BST;
    }
}
Position FindMin( BinTree BST ){
    BinTree ptr = BST;
    while (ptr && ptr->Left){
        ptr = ptr->Left;
    }
    return ptr;
}
Position FindMax( BinTree BST ){
    BinTree ptr = BST;
    while (ptr->Right && ptr){
        ptr = ptr->Right;
    }
    return ptr;
}
BinTree Insert( BinTree BST, ElementType X ){
    if (!BST){
        BST = malloc(sizeof(struct TNode));
        BST->Data = X;
        BST->Left = BST->Right = NULL;
    }
    else {
        if (X < BST->Data){
            BST->Left = Insert(BST->Left, X);
        }
        else if (X > BST->Data){
            BST->Right = Insert(BST->Right, X);
        }
    }
    return BST;
}
BinTree Delete( BinTree BST, ElementType X ){
    Position temp;
    if (!BST) {
        printf("Not Found\n");
        return BST;
    }
    else {
        if (X < BST->Data){
            BST->Left = Delete(BST->Left, X);
        }
        else if (X > BST->Data){
            BST->Right = Delete(BST->Right, X);
        }
        else {
            if (BST->Left && BST->Right){
                temp = FindMax(BST->Left);
                BST->Data = temp->Data;
                BST->Left = Delete(BST->Left, temp->Data);
            }
            else {
                temp = BST;
                if (!BST->Left){
                    BST = BST->Right;
                }
                else {
                    BST = BST->Left;
                }
                free(temp);
            }
        }
    }
    return BST;
}

int main()
{
    BinTree BST, MinP, MaxP, Tmp;
    ElementType X;
    int N, i;

    BST = NULL;
    scanf("%d", &N);
    for ( i=0; i<N; i++ ) {
        scanf("%d", &X);
        BST = Insert(BST, X);
    }
    printf("Preorder:"); PreorderTraversal(BST); printf("\n");
    MinP = FindMin(BST);
    MaxP = FindMax(BST);
    scanf("%d", &N);
    for( i=0; i<N; i++ ) {
        scanf("%d", &X);
        Tmp = Find(BST, X);
        if (Tmp == NULL) printf("%d is not found\n", X);
        else {
            printf("%d is found\n", Tmp->Data);
            if (Tmp==MinP) printf("%d is the smallest key\n", Tmp->Data);
            if (Tmp==MaxP) printf("%d is the largest key\n", Tmp->Data);
        }
    }
    scanf("%d", &N);
    for( i=0; i<N; i++ ) {
        scanf("%d", &X);
        BST = Delete(BST, X);
    }
    printf("Inorder:"); InorderTraversal(BST); printf("\n");

    return 0;
}
/* 你的代码将被嵌在这里 */