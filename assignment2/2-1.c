#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 1000
#define INF 0x3f3f3f3f
typedef char ElementType;
typedef struct LNode *PtrToLNode;
struct LNode
{
    ElementType Data;
    PtrToLNode Next;
};
typedef PtrToLNode Position;
typedef PtrToLNode List;

List MakeEmpty()
{
    List L;
    L = (List)malloc(sizeof(struct LNode));
    L->Next = NULL;
    return L;
}

Position NewNode(ElementType X)
{
    Position P;
    P = (Position)malloc(sizeof(struct LNode));
    P->Data = X;
    P->Next = NULL;
    return P;
}

void Attach(Position P, Position *Rear)
{
    (*Rear)->Next = P;
    *Rear = P;
}

List CreateList(char S[])
{
    List L;
    Position Rear, P;
    int i;
    L = MakeEmpty();
    Rear = L;
    for (i = 0; S[i]; i++)
    {
        P = NewNode(S[i]);
        Attach(P, &Rear);
    }
    return L;
}

int IsDigit(ElementType X)
{
    return X >= '0' && X <= '9';
}

int IsLower(ElementType X)
{
    return X >= 'a' && X <= 'z';
}

int IsUpper(ElementType X)
{
    return X >= 'A' && X <= 'Z';
}

void SplitList(List L, List L1, List L2, List L3)
{
    Position P, T, R1, R2, R3;
    R1 = L1;
    R2 = L2;
    R3 = L3;
    P = L->Next;
    L->Next = NULL;
    while (P)
    {
        T = P->Next;
        P->Next = NULL;
        if (IsDigit(P->Data))
            Attach(P, &R1);
        else if (IsLower(P->Data))
            Attach(P, &R2);
        else if (IsUpper(P->Data))
            Attach(P, &R3);
        else
            free(P);
        P = T;
    }
}

void PrintList(List L, char Name[])
{
    Position P;
    printf("%s:", Name);
    for (P = L->Next; P; P = P->Next)
        printf(" %c", P->Data);
    printf("\n");
}

void FreeList(List L)
{
    Position P, T;
    P = L;
    while (P)
    {
        T = P->Next;
        free(P);
        P = T;
    }
}

int main()
{
    char S[MAXN];
    List L, L1, L2, L3;
    scanf("%s", S);
    L = CreateList(S);
    L1 = MakeEmpty();
    L2 = MakeEmpty();
    L3 = MakeEmpty();
    printf("Before split\n");
    PrintList(L, "L");
    SplitList(L, L1, L2, L3);
    printf("After split\n");
    PrintList(L1, "L1");
    PrintList(L2, "L2");
    PrintList(L3, "L3");
    FreeList(L);
    FreeList(L1);
    FreeList(L2);
    FreeList(L3);
    return 0;
}