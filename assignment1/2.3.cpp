#include<stdlib.h>
#include<stdio.h>

typedef struct List list;

struct List{
    list* next;
    int data;
};

list* Create(){
    int d;
    list* head=NULL;
    list* tail=NULL;
    while(scanf("%d",&d)==1){
        list* newNode=(list*)malloc(sizeof(list));
        if(newNode==NULL){
            printf("fail\n");
            exit(1);
        }
        newNode->data=d;
        newNode->next=NULL;
        if (head == NULL)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
    }
    return head;
}

void Read(list* l){
    while(l!=NULL){
        printf("%d ",l->data);
        l=l->next;
    }
}

void Update(list* l){
    int row,newI;
    scanf("%d %d",&row,&newI);
    while(l!=NULL){
        if(row==(l->data)){
            l->data=newI;
        }
        l=l->next;
    }
}

void Delete(list* l){
    list* n=l;
    while(n!=NULL){
        list* temp=n;
        n=n->next;
        free(temp);
    }
    printf("succes\n");
}

list* solve(list* head)
{
    if (head == NULL)
        return NULL;

    int x = head->data;
    list* pre = head;
    list* cur = head->next;

    while (cur != NULL)
    {
        if (cur->data < x)
        {
            pre->next = cur->next;
            cur->next = head;
            head = cur;
            cur = pre->next;
        }
        else
        {
            pre = cur;
            cur = cur->next;
            }
    }

    return head;
}

int main(){
    list* L=Create();
    Read(L);
    // Update(L);
    // Read(L);
    // Delete(L);
    printf("\n");
    list* l=solve(L);
    Read(l);
    return 0;
}