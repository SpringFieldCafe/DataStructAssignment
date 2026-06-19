#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000
#define INF 0x3f3f3f3f

typedef int ElementType;

typedef struct LNode *PtrToLNode;
struct LNode {
    ElementType Data[MAXN];
    int Last;
};
typedef PtrToLNode List;

List CreateList() {
    List L;
    L = (List)malloc(sizeof(struct LNode));
    L->Last = 0;
    return L;
}

void PrintList(List L) {
    int i;

    for (i = 1; i <= L->Last; i++) {
        if (i > 1) {
            printf(" ");
        }
        printf("%d", L->Data[i]);
    }
    printf("\n");
}

void BinarySearch(List L, ElementType K) {
    int Left, Right, Mid, Step;

    Left = 1;
    Right = L->Last;
    Step = 1;

    printf("BinarySearch Process:\n");

    while (Left <= Right) {
        Mid = (Left + Right) / 2;
        printf("Step %d: low=%d high=%d mid=%d value=%d\n", Step, Left, Right, Mid, L->Data[Mid]);

        if (L->Data[Mid] == K) {
            printf("Find %d at position %d\n", K, Mid);
            return;
        } else if (L->Data[Mid] < K) {
            Left = Mid + 1;
        } else {
            Right = Mid - 1;
        }

        Step++;
    }

    printf("Not Found\n");
}

void Swap(ElementType *A, ElementType *B) {
    ElementType T;

    T = *A;
    *A = *B;
    *B = T;
}

int Partition(List L, int Left, int Right) {
    ElementType Pivot;

    Pivot = L->Data[Left];

    while (Left < Right) {
        while (Left < Right && L->Data[Right] >= Pivot) {
            Right--;
        }
        L->Data[Left] = L->Data[Right];

        while (Left < Right && L->Data[Left] <= Pivot) {
            Left++;
        }
        L->Data[Right] = L->Data[Left];
    }

    L->Data[Left] = Pivot;

    return Left;
}

void QuickSort(List L, int Left, int Right, int *Step) {
    int PivotPos;

    if (Left < Right) {
        PivotPos = Partition(L, Left, Right);
        printf("QuickSort Step %d: ", *Step);
        PrintList(L);
        (*Step)++;

        QuickSort(L, Left, PivotPos - 1, Step);
        QuickSort(L, PivotPos + 1, Right, Step);
    }
}

int main() {
    List SearchList, SortList;
    int n, m, i, K, Step;

    SearchList = CreateList();
    SortList = CreateList();

    scanf("%d%d", &n, &K);
    SearchList->Last = n;
    SearchList->Data[0] = INF;

    for (i = 1; i <= n; i++) {
        scanf("%d", &SearchList->Data[i]);
    }

    scanf("%d", &m);
    SortList->Last = m;
    SortList->Data[0] = INF;

    for (i = 1; i <= m; i++) {
        scanf("%d", &SortList->Data[i]);
    }

    BinarySearch(SearchList, K);

    printf("QuickSort Process:\n");
    printf("Original: ");
    PrintList(SortList);

    Step = 1;
    QuickSort(SortList, 1, SortList->Last, &Step);

    printf("Sorted: ");
    PrintList(SortList);

    free(SearchList);
    free(SortList);

    return 0;
}