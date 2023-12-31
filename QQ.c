#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct _node{
    struct _node *next;
    char account[11], password[17];
} *node;

typedef struct _hash{
    int size;
    node *tbl;
} *hash;

int is_prime(int x){
    for (int i = 2; i <= sqrt(x); i++){
        if (x % i == 0)
            return 0;
    }
    return 1;
}

int next_prime(int x){
    for (int i = 0;;i++){
        if (is_prime(x + i))
            return x + i;
    }
}

hash build_hash(int N){
    hash h = malloc(sizeof(struct _hash));
    h->size = next_prime(N);
    h->tbl = malloc(sizeof(node) * h->size);
    for (int i = 0; i < h->size; i++)
        h->tbl[i] = NULL;
    return h;
}

int hash_pos(hash h, char *account){
    return atoi(account + 3) % h->size;
}

node find(hash h, char *account){
    int pos = hash_pos(h, account);
    node p = h->tbl[pos];
    while (p && strcmp(account, p->account)){
        p = p->next;
    }
    return p;
}

int login(hash h, char *account, char *password){
    int pos = hash_pos(h, account);
    node p = h->tbl[pos];
    while (p && strcmp(account, p->account)){
        p = p->next;
    }
    if (!p){
        return 0;
    }
    else {
        if (strcmp(password, p->password))
            return 0;
        else
            return 1;
    }
}

int insert(hash h, char *account, char *password){
    node p = find(h, account);
    int pos = hash_pos(h, account);
    if (!p){
        node new = malloc(sizeof(struct _node));
        strcpy(new->account, account);
        strcpy(new->password, password);
        if (!h->tbl[pos]){
            new->next = NULL;
            h->tbl[pos] = new;
        }
        else {
            new->next = h->tbl[pos];
            h->tbl[pos] = new;
        }
        return 1;
    }
    else
        return 0;
}

int main(){
    int N;
    scanf("%d", &N);
    hash h = build_hash(N);
    for (int i = 0; i < N; i++){
        char o, account[11], password[17];
        scanf(" %c %s %s", &o, &account, &password);
        if (o == 'L'){
            if (!find(h, account))
                printf("ERROR: Not Exist\n");
            else if (!login(h, account, password))
                printf("ERROR: Wrong PW\n");
            else
                printf("Login: OK\n");
        }
        else if (o == 'N'){
            if (find(h, account))
                printf("ERROR: Exist\n");
            else {
                printf("New: OK\n");
                insert(h, account, password);
            }
        }
    }
}