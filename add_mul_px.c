#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
    int a, r;
    struct _node *next;
}node;

typedef node *px;

px input(){
    int N;
    scanf("%d", &N);
    px p = (px)malloc(sizeof(node));
    p->next = NULL;
    px rear = p;
    for (int i = 0; i < N; i++){
        px in = (px)malloc(sizeof(node));
        scanf("%d %d", &(in->a), &(in->r));
        in->next = NULL;
        rear->next = in;
        rear = in;
    }
    return p;
}

void print_px(px p){
    px rear = p;
    if (!rear->next){
        printf("0 0");
        return;
    }
    rear = rear->next;
    while (rear->next){
        printf("%d %d ", rear->a, rear->r);
        rear = rear->next;
    }
    printf("%d %d", rear->a, rear->r);
}

void attach(int a, int r, px *rp){
    px p = (px)malloc(sizeof(node));
    p->a = a;
    p->r = r;
    p->next = NULL;
    (*rp)->next = p;
    (*rp) = p;
}

px add(px p1, px p2){
    px r1 = p1, r2 = p2, pa = (px)malloc(sizeof(node));
    r1 = r1->next;
    r2 = r2->next;
    pa->next = NULL;
    px ra = pa;
    while (r1&&r2){
        if (r1->r < r2->r){
            attach(r2->a, r2->r, &ra);
            r2 = r2->next;
        }
        else if (r1->r > r2->r){
            attach(r1->a, r1->r, &ra);
            r1 = r1->next;
        }
        else{
            int a = r1->a + r2->a;
            if (a == 0){
                r1 = r1->next;
                r2 = r2->next;
            }
            else{
                attach(a, r1->r, &ra);
                r1 = r1->next;
                r2 = r2->next;
            }
        }
    }
    for (; r1; r1 = r1->next){
        attach(r1->a, r1->r, &ra);
    }
    for (; r2; r2 = r2->next){
        attach(r2->a, r2->r, &ra);
    }
    return pa;
}

px mul1(px p1, px p2){
    px pm = (px)malloc(sizeof(node)), pa = (px)malloc(sizeof(node)), r1 = p1;
    pm->next = NULL;
    r1 = r1->next;
    while(r1){
        px r2 = p2->next, ra = pa;
        while(r2){
            if (r1->a * r2->a){
                attach(r1->a * r2->a, r1->r + r2->r, &ra);
            }
            r2 = r2->next;
        }
        r1 = r1->next;
        pm = add(pm, pa);
    }
    return pm;
}

int main(){
    px p1, p2, pa, pm;
    p1 = input();
    p2 = input();
    pa = add(p1, p2);
    pm = mul1(p1, p2);
    print_px(pm);
    printf("\n");
    print_px(pa);
}