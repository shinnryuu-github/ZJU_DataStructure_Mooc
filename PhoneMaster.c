#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAXNUM 100001
#define lenth 11

typedef struct _node{
    int times;
    struct _node *next;
    char num[lenth + 1];
} *node;

typedef struct _hnode{
    node first;
} *hnode;

typedef struct _hashtbl{
    int size;
    hnode *tbl;
} *hashtbl;

int is_prime(int x){
    for (int i = 2; i <= sqrt(x); i++){
        if (!x % i)
            return 0;
    }
    return 1;
}

int next_prime(int x){
    for (int i = 0;; i++){
        if (is_prime(x + i))
            return x + i;
    }
}

hashtbl build_hash(int N){
    int size = next_prime(N);
    hashtbl h = malloc(sizeof(struct _hashtbl));
    h->size = size;
    h->tbl = malloc(sizeof(struct _hnode) * size);
    for (int i = 0; i < size; i++){
        h->tbl[i] = malloc(sizeof(struct _hnode));
        h->tbl[i]->first = NULL;
    }
    return h;
}

int hash(char *s, hashtbl h){
    return atoi(s + 6) % h->size;
}

node find(hashtbl h, char *s){
    int pos = hash(s, h);
    node p = h->tbl[pos]->first;
    while (p && strcmp(s, p->num)){
        p = p->next;
    }
    return p;
}

void insert(hashtbl h, char *s){
    int pos = hash(s, h);
    node f = find(h, s);
    if (!f){
        node tmp = malloc(sizeof(struct _node));
        tmp->times = 1;
        tmp->next = NULL;
        strcpy(tmp->num, s);
        if (!h->tbl[pos]->first)
            h->tbl[pos]->first = tmp;
        else {
            tmp->next = h->tbl[pos]->first;
            h->tbl[pos]->first = tmp;
        }
    }
    else {
        f->times++;
    }
}

void output(hashtbl h){
    int max = 0, num = 0;
    char master[lenth + 1] = "/0";
    for (int i = 0; i < h->size; i++){
        node tmp = h->tbl[i]->first;
        while (tmp){
            if (tmp->times > max){
                max = tmp->times;
                num = 1;
                strcpy(master, tmp->num);
            }
            else if (tmp->times == max){
                num++;
                if (strcmp(master, tmp->num) > 0){
                    strcpy(master, tmp->num);
                } 
            }
            tmp = tmp->next;
        }
    }
    printf("%s %d", master, max);
    if (num > 1)
        printf(" %d", num);
}

void destory_hash(hashtbl h){
    for (int i = 0; i < h->size; i++){
        node tmp = h->tbl[i]->first;    
        while (tmp){
            node p = tmp;
            tmp = tmp->next;
            free(p);
        }
        free(h->tbl[i]);
    }
    free(h);
}

int main(){
    int N;
    scanf("%d", &N);
    hashtbl h = build_hash(2 * N);
    for (int i = 0; i < N; i++){
        char num1[lenth + 1], num2[lenth + 1];
        scanf("%s %s", &num1, &num2);
        insert(h, num1);
        insert(h, num2);
    }
    output(h);
}