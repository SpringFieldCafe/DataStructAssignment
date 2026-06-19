#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1000
#define INF 0x3f3f3f3f

typedef struct TNode *PtrToTNode;
struct TNode {
    char Data;
    PtrToTNode Left;
    PtrToTNode Right;
};
typedef PtrToTNode BinTree;
typedef PtrToTNode Position;

typedef struct SNode *PtrToSNode;
struct SNode {
    Position *Data;
    int Top;
    int Capacity;
};
typedef PtrToSNode Stack;

typedef struct QNode *PtrToQNode;
struct QNode {
    Position *Data;
    int Front;
    int Rear;
    int Capacity;
};
typedef PtrToQNode Queue;

Stack CreateStack(int MaxSize) {
    Stack S;
    S = (Stack)malloc(sizeof(struct SNode));
    S->Data = (Position *)malloc(sizeof(Position) * MaxSize);
    S->Top = -1;
    S->Capacity = MaxSize;
    return S;
}

int IsFullStack(Stack S) {
    return S->Top == S->Capacity - 1;
}

int IsEmptyStack(Stack S) {
    return S->Top == -1;
}

void Push(Stack S, Position X) {
    if (!IsFullStack(S)) {
        S->Data[++S->Top] = X;
    }
}

void Pop(Stack S) {
    if (!IsEmptyStack(S)) {
        S->Top--;
    }
}

Position GetTop(Stack S) {
    if (IsEmptyStack(S)) {
        return NULL;
    }
    return S->Data[S->Top];
}

Queue CreateQueue(int MaxSize) {
    Queue Q;
    Q = (Queue)malloc(sizeof(struct QNode));
    Q->Data = (Position *)malloc(sizeof(Position) * MaxSize);
    Q->Front = 0;
    Q->Rear = 0;
    Q->Capacity = MaxSize;
    return Q;
}

int IsEmptyQueue(Queue Q) {
    return Q->Front == Q->Rear;
}

int IsFullQueue(Queue Q) {
    return (Q->Rear + 1) % Q->Capacity == Q->Front;
}

void AddQ(Queue Q, Position X) {
    if (!IsFullQueue(Q)) {
        Q->Rear = (Q->Rear + 1) % Q->Capacity;
        Q->Data[Q->Rear] = X;
    }
}

Position DeleteQ(Queue Q) {
    if (IsEmptyQueue(Q)) {
        return NULL;
    }
    Q->Front = (Q->Front + 1) % Q->Capacity;
    return Q->Data[Q->Front];
}

BinTree CreateNode(char X) {
    BinTree T;
    T = (BinTree)malloc(sizeof(struct TNode));
    T->Data = X;
    T->Left = NULL;
    T->Right = NULL;
    return T;
}

BinTree CreateBinTree(char str[]) {
    Stack S;
    BinTree T, P;
    int i, flag;

    S = CreateStack(MAXN);
    T = NULL;
    P = NULL;
    flag = 0;

    for (i = 0; str[i] != '\0'; i++) {
        if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9')) {
            P = CreateNode(str[i]);
            if (T == NULL) {
                T = P;
            } else {
                if (flag == 1) {
                    GetTop(S)->Left = P;
                } else if (flag == 2) {
                    GetTop(S)->Right = P;
                }
            }
        } else if (str[i] == '(') {
            Push(S, P);
            flag = 1;
        } else if (str[i] == ',') {
            flag = 2;
        } else if (str[i] == ')') {
            Pop(S);
        }
    }

    return T;
}

void PreOrderTraversal(BinTree BT) {
    if (BT) {
        printf("%c ", BT->Data);
        PreOrderTraversal(BT->Left);
        PreOrderTraversal(BT->Right);
    }
}

void InOrderTraversal(BinTree BT) {
    if (BT) {
        InOrderTraversal(BT->Left);
        printf("%c ", BT->Data);
        InOrderTraversal(BT->Right);
    }
}

void PostOrderTraversal(BinTree BT) {
    if (BT) {
        PostOrderTraversal(BT->Left);
        PostOrderTraversal(BT->Right);
        printf("%c ", BT->Data);
    }
}

void LevelOrderTraversal(BinTree BT) {
    Queue Q;
    Position T;

    if (BT == NULL) {
        return;
    }

    Q = CreateQueue(MAXN);
    AddQ(Q, BT);

    while (!IsEmptyQueue(Q)) {
        T = DeleteQ(Q);
        printf("%c ", T->Data);
        if (T->Left) {
            AddQ(Q, T->Left);
        }
        if (T->Right) {
            AddQ(Q, T->Right);
        }
    }
}

int GetLeafCount(BinTree BT) {
    if (BT == NULL) {
        return 0;
    }
    if (BT->Left == NULL && BT->Right == NULL) {
        return 1;
    }
    return GetLeafCount(BT->Left) + GetLeafCount(BT->Right);
}

int GetDepth(BinTree BT) {
    int L, R;

    if (BT == NULL) {
        return 0;
    }

    L = GetDepth(BT->Left);
    R = GetDepth(BT->Right);

    return L > R ? L + 1 : R + 1;
}

void FreeTree(BinTree BT) {
    if (BT) {
        FreeTree(BT->Left);
        FreeTree(BT->Right);
        free(BT);
    }
}

int main() {
    char str[MAXN];
    BinTree BT;

    scanf("%s", str);

    BT = CreateBinTree(str);

    printf("PreOrder: ");
    PreOrderTraversal(BT);
    printf("\n");

    printf("InOrder: ");
    InOrderTraversal(BT);
    printf("\n");

    printf("PostOrder: ");
    PostOrderTraversal(BT);
    printf("\n");

    printf("LevelOrder: ");
    LevelOrderTraversal(BT);
    printf("\n");

    printf("LeafCount: %d\n", GetLeafCount(BT));
    printf("Depth: %d\n", GetDepth(BT));

    FreeTree(BT);

    return 0;
}