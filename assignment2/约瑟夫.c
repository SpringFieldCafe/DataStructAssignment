#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 1000
#define INF 0x3f3f3f3f

typedef struct JNode *PtrToJNode;
struct JNode
{
    int Data;
    PtrToJNode Next;
};
typedef PtrToJNode JList;

JList CreateJosephus(int N)
{
    JList Head, Tail, P;
    int i;
    Head = NULL;
    Tail = NULL;
    for (i = 1; i <= N; i++)
    {
        P = (JList)malloc(sizeof(struct JNode));
        P->Data = i;
        P->Next = NULL;
        if (!Head)
        {
            Head = P;
            Tail = P;
        }
        else
        {
            Tail->Next = P;
            Tail = P;
        }
    }
    if (Tail)
        Tail->Next = Head;
    return Tail;
}

void Josephus(int N, int M, int Start)
{
    JList Pre, Del;
    int Cnt, i;
    if (N <= 0 || M <= 0 || Start < 1 || Start > N)
    {
        printf("Invalid input\n");
        return;
    }
    Pre = CreateJosephus(N);
    while (Pre->Next->Data != Start)
        Pre = Pre->Next;
    Cnt = N;
    printf("Josephus order:");
    while (Cnt)
    {
        for (i = 1; i < M; i++)
            Pre = Pre->Next;
        Del = Pre->Next;
        printf(" %d", Del->Data);
        Pre->Next = Del->Next;
        free(Del);
        Cnt--;
    }
    printf("\n");
}

int main()
{
    int N, M, Start;
    scanf("%d%d%d", &N, &M, &Start);
    Josephus(N, M, Start);
    return 0;
}