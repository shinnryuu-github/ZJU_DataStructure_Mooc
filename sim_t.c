#include <stdio.h>
#include <stdlib.h>

#define Maxsize 10

typedef struct _node
{
    char ch;
    int left, right;
}node;

int creat_tree(node T[], int N){
    int conected[N];
    for (int i = 0; i < N; i++) conected[i] = 0;
    for (int i = 0; i < N; i++)
    {
        char a, b, c;
        scanf(" %c %c %c", &a, &b, &c);
        T[i].ch = a;
        if (b == '-'){
            T[i].left = -1;
        }
        else{
            T[i].left = b - '0';
            conected[b - '0'] = 1;
        }
        if (c == '-'){
            T[i].right = -1;
        }
        else{
            T[i].right = c - '0';
            conected[c - '0'] = 1;
        }
    }
    for (int i = 0; i < N; i++){
        if (conected[i] == 0){
            return i;
        }
    }
    return -1;
}

int is_sim(node T1[], int root1, node T2[], int root2){
    if (root1 == -1 && root2 == -1){
        return 1;
    }
    else if ((root1 == -1 && root2 != -1) || (root1 != -1 && root2 == -1)){
        return 0;
    }
    else if (T1[root1].ch != T2[root2].ch){
        return 0;
    }
    else if (is_sim(T1, T1[root1].left, T2, T2[root2].left)){
        return is_sim(T1, T1[root1].right, T2, T2[root2].right);
    }
    else if (!is_sim(T1, T1[root1].left, T2, T2[root2].left)){
        if (is_sim(T1, T1[root1].left, T2, T2[root2].right)){
            return is_sim(T1, T1[root1].right, T2, T2[root2].left);
        }
        else {
            return 0;
        }
    }
}

int main()
{
    int N1, N2;
    scanf("%d", &N1);
    node T1[N1];
    int root1 = creat_tree(T1, N1);
    scanf("%d", &N2);
    node T2[N2];
    int root2 = creat_tree(T2, N2);
    int b = is_sim(T1, root1, T2, root2);
    if (b){
        printf("Yes");
    }
    else {
        printf("No");
    }
}