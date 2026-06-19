#include <stdio.h>
#include <stdlib.h>
#define INF 0x3f3f3f3f
typedef struct MazeNode *PtrToMazeNode;
struct MazeNode
{
    int X;
    int Y;
    int Dir;
};
typedef PtrToMazeNode Position;
 
typedef struct SNode *PtrToSNode;
struct SNode
{
    struct MazeNode *Data;
    int Top;
    int Capacity;
};
typedef PtrToSNode Stack;
 
Stack CreateStack(int MaxSize)
{
    Stack S;
    S = (Stack)malloc(sizeof(struct SNode));
    S->Data = (struct MazeNode *)malloc(sizeof(struct MazeNode) * MaxSize);
    S->Top = -1;
    S->Capacity = MaxSize;
    return S;
}
 
int IsFull(Stack S)
{
    return S->Top == S->Capacity - 1;
}
 
int IsEmpty(Stack S)
{
    return S->Top == -1;
}
 
void Push(Stack S, struct MazeNode X)
{
    if (!IsFull(S))
        S->Data[++S->Top] = X;
}
 
void Pop(Stack S)
{
    if (!IsEmpty(S))
        S->Top--;
}
 
Position GetTop(Stack S)
{
    if (IsEmpty(S))
        return NULL;
    return &S->Data[S->Top];
}
 
int **CreateMatrix(int Row, int Col)
{
    int **A, i;
    A = (int **)malloc(sizeof(int *) * Row);
    for (i = 0; i < Row; i++)
        A[i] = (int *)malloc(sizeof(int) * Col);
    return A;
}
 
void FreeMatrix(int **A, int Row)
{
    int i;
    for (i = 0; i < Row; i++)
        free(A[i]);
    free(A);
}
 
int Check(int X, int Y, int Row, int Col, int **Maze, int **Visited)
{
    if (X < 0 || X >= Row || Y < 0 || Y >= Col)
        return 0;
    if (Maze[X][Y] != 0 || Visited[X][Y])
        return 0;
    return 1;
}
 
void PrintPath(Stack S)
{
    int i;
    printf("Path length: %d\n", S->Top + 1);
    for (i = 0; i <= S->Top; i++)
        printf("(%d,%d)%c", S->Data[i].X, S->Data[i].Y, i == S->Top ? '\n' : ' ');
}
 
int SearchPath(int **Maze, int Row, int Col, int Sx, int Sy, int Tx, int Ty)
{
    int **Visited, D, Nx, Ny;
    int Dx[4] = {0, 1, 0, -1};
    int Dy[4] = {1, 0, -1, 0};
    Stack S;
    Position P;
    struct MazeNode Start, Next;
    Visited = CreateMatrix(Row, Col);
    for (Nx = 0; Nx < Row; Nx++)
        for (Ny = 0; Ny < Col; Ny++)
            Visited[Nx][Ny] = 0;
    if (Sx < 0 || Sx >= Row || Sy < 0 || Sy >= Col || Tx < 0 || Tx >= Row || Ty < 0 || Ty >= Col)
    {
        FreeMatrix(Visited, Row);
        return 0;
    }
    if (Maze[Sx][Sy] != 0 || Maze[Tx][Ty] != 0)
    {
        FreeMatrix(Visited, Row);
        return 0;
    }
    S = CreateStack(Row * Col + 5);
    Start.X = Sx;
    Start.Y = Sy;
    Start.Dir = 0;
    Push(S, Start);
    Visited[Sx][Sy] = 1;
    while (!IsEmpty(S))
    {
        P = GetTop(S);
        if (P->X == Tx && P->Y == Ty)
        {
            PrintPath(S);
            FreeMatrix(Visited, Row);
            free(S->Data);
            free(S);
            return 1;
        }
        if (P->Dir < 4)
        {
            D = P->Dir;
            P->Dir++;
            Nx = P->X + Dx[D];
            Ny = P->Y + Dy[D];
            if (Check(Nx, Ny, Row, Col, Maze, Visited))
            {
                Next.X = Nx;
                Next.Y = Ny;
                Next.Dir = 0;
                Push(S, Next);
                Visited[Nx][Ny] = 1;
            }
        }
        else
        {
            Pop(S);
        }
    }
    FreeMatrix(Visited, Row);
    free(S->Data);
    free(S);
    return 0;
}
 
int main()
{
    int Row, Col, Sx, Sy, Tx, Ty, i, j;
    int **Maze;
    scanf("%d%d", &Row, &Col);
    Maze = CreateMatrix(Row, Col);
    for (i = 0; i < Row; i++)
        for (j = 0; j < Col; j++)
            scanf("%d", &Maze[i][j]);
    scanf("%d%d%d%d", &Sx, &Sy, &Tx, &Ty);
    if (!SearchPath(Maze, Row, Col, Sx, Sy, Tx, Ty))
        printf("No path\n");
    FreeMatrix(Maze, Row);
    return 0;
}