#include<stdio.h>
#include<stdlib.h>

typedef struct ListNode LNode, *List;

struct ListNode
{
    char data;
    LNode *next;
};

void split(List L, List *L1, List *L2, List *L3);
void split(List L, List *L1, List *L2, List *L3) {
    LNode *p, *q;
    LNode *r1, *r2, *r3;
    *L1 = (List)malloc(sizeof(LNode));
    *L2 = (List)malloc(sizeof(LNode));
    *L3 = (List)malloc(sizeof(LNode));

    (*L1)->next = NULL;
    (*L2)->next = NULL;
    (*L3)->next = NULL;

    r1 = *L1;
    r2 = *L2;
    r3 = *L3;

    p = L->next;

    while (p != NULL) {
        q = p->next;      
        p->next = NULL;   

        if (p->data >= '0' && p->data <= '9') {
            r1->next = p;
            r1 = p;
        } else if (p->data >= 'a' && p->data <= 'z') {
            r2->next = p;
            r2 = p;
        } else if (p->data >= 'A' && p->data <= 'Z') {
            r3->next = p;
            r3 = p;
        }

        p = q;
    }
    L->next = NULL;
}

int main(){
    return 0;
}