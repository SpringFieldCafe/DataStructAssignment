#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MaxVertexNum 30
#define MaxSize 30
#define INF 0x3f3f3f3f
typedef int Vertex;
typedef int WeightType;
typedef char DataType;
typedef struct AdjVNode *PtrAdjVNode;
struct AdjVNode
{
    Vertex AdjV;
    WeightType Weight;
    PtrAdjVNode Next;
};
 
struct VNode
{
    PtrAdjVNode FirstEdge;
    DataType Data;
};
typedef struct VNode AdjList[MaxVertexNum];
 
typedef struct GNode *PtrGNode;
struct GNode
{
    int Nv;
    int Ne;
    AdjList G;
};
typedef PtrGNode LGraph;
 
typedef struct ENode *PtrENode;
struct ENode
{
    Vertex V1, V2;
    WeightType Weight;
};
typedef PtrENode Edge;
 
typedef struct QNode *PtrQNode;
struct QNode
{
    Vertex *Data;
    int Front;
    int Rear;
    int Capacity;
};
typedef PtrQNode Queue;
 
bool Visited[MaxVertexNum];
 
LGraph CreateGraph(int VertexNum)
{
    LGraph Graph;
    Vertex V;
    Graph = (LGraph)malloc(sizeof(struct GNode));
    Graph->Nv = VertexNum;
    Graph->Ne = 0;
    for (V = 0; V < Graph->Nv; V++)
    {
        Graph->G[V].FirstEdge = NULL;
        Graph->G[V].Data = 'A' + V;
    }
    return Graph;
}
 
void InsertOneEdge(LGraph Graph, Vertex V1, Vertex V2, WeightType Weight)
{
    PtrAdjVNode NewNode, P, Pre;
    NewNode = (PtrAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = V2;
    NewNode->Weight = Weight;
    NewNode->Next = NULL;
    P = Graph->G[V1].FirstEdge;
    Pre = NULL;
    while (P && P->AdjV < V2)
    {
        Pre = P;
        P = P->Next;
    }
    if (!Pre)
    {
        NewNode->Next = Graph->G[V1].FirstEdge;
        Graph->G[V1].FirstEdge = NewNode;
    }
    else
    {
        NewNode->Next = Pre->Next;
        Pre->Next = NewNode;
    }
}
 
void InsertEdge(LGraph Graph, Edge E)
{
    InsertOneEdge(Graph, E->V1, E->V2, E->Weight);
    InsertOneEdge(Graph, E->V2, E->V1, E->Weight);
}
 
LGraph BuildDemoGraph()
{
    int Edges[16][2] = {
        {0, 1}, {0, 2}, {0, 3}, {1, 2},
        {1, 4}, {1, 5}, {2, 3}, {2, 5},
        {2, 6}, {3, 6}, {3, 7}, {4, 5},
        {4, 6}, {5, 6}, {5, 7}, {6, 7}
    };
    int i;
    Edge E;
    LGraph Graph;
    Graph = CreateGraph(8);
    Graph->Ne = 16;
    E = (Edge)malloc(sizeof(struct ENode));
    E->Weight = 1;
    for (i = 0; i < Graph->Ne; i++)
    {
        E->V1 = Edges[i][0];
        E->V2 = Edges[i][1];
        InsertEdge(Graph, E);
    }
    free(E);
    return Graph;
}
 
void DisplayGraph(LGraph Graph)
{
    Vertex V;
    PtrAdjVNode W;
    printf("Adjacency list\n");
    for (V = 0; V < Graph->Nv; V++)
    {
        printf("%c:", Graph->G[V].Data);
        for (W = Graph->G[V].FirstEdge; W; W = W->Next)
            printf(" %c", Graph->G[W->AdjV].Data);
        printf("\n");
    }
}
 
void InitVisited(LGraph Graph)
{
    Vertex V;
    for (V = 0; V < Graph->Nv; V++)
        Visited[V] = false;
}
 
void Visit(LGraph Graph, Vertex V)
{
    printf(" %c", Graph->G[V].Data);
}
 
void DFS(LGraph Graph, Vertex V)
{
    PtrAdjVNode W;
    Visit(Graph, V);
    Visited[V] = true;
    for (W = Graph->G[V].FirstEdge; W; W = W->Next)
        if (!Visited[W->AdjV])
            DFS(Graph, W->AdjV);
}
 
void DFSGraph(LGraph Graph)
{
    Vertex V;
    InitVisited(Graph);
    printf("DFS:");
    for (V = 0; V < Graph->Nv; V++)
        if (!Visited[V])
            DFS(Graph, V);
    printf("\n");
}
 
Queue CreateQueue(int Capacity)
{
    Queue Q;
    Q = (Queue)malloc(sizeof(struct QNode));
    Q->Data = (Vertex *)malloc(sizeof(Vertex) * Capacity);
    Q->Front = Q->Rear = 0;
    Q->Capacity = Capacity;
    return Q;
}
 
int IsEmpty(Queue Q)
{
    return Q->Front == Q->Rear;
}
 
void AddQ(Queue Q, Vertex X)
{
    if ((Q->Rear + 1) % Q->Capacity != Q->Front)
    {
        Q->Rear = (Q->Rear + 1) % Q->Capacity;
        Q->Data[Q->Rear] = X;
    }
}
 
Vertex DeleteQ(Queue Q)
{
    Q->Front = (Q->Front + 1) % Q->Capacity;
    return Q->Data[Q->Front];
}
 
void BFS(LGraph Graph, Vertex S)
{
    Queue Q;
    Vertex V;
    PtrAdjVNode W;
    Q = CreateQueue(MaxSize);
    Visit(Graph, S);
    Visited[S] = true;
    AddQ(Q, S);
    while (!IsEmpty(Q))
    {
        V = DeleteQ(Q);
        for (W = Graph->G[V].FirstEdge; W; W = W->Next)
        {
            if (!Visited[W->AdjV])
            {
                Visit(Graph, W->AdjV);
                Visited[W->AdjV] = true;
                AddQ(Q, W->AdjV);
            }
        }
    }
    free(Q->Data);
    free(Q);
}
 
void BFSGraph(LGraph Graph)
{
    Vertex V;
    InitVisited(Graph);
    printf("BFS:");
    for (V = 0; V < Graph->Nv; V++)
        if (!Visited[V])
            BFS(Graph, V);
    printf("\n");
}
 
void FreeGraph(LGraph Graph)
{
    Vertex V;
    PtrAdjVNode P, T;
    for (V = 0; V < Graph->Nv; V++)
    {
        P = Graph->G[V].FirstEdge;
        while (P)
        {
            T = P->Next;
            free(P);
            P = T;
        }
    }
    free(Graph);
}
 
int main()
{
    LGraph Graph;
    Graph = BuildDemoGraph();
    DisplayGraph(Graph);
    DFSGraph(Graph);
    BFSGraph(Graph);
    FreeGraph(Graph);
    return 0;
}