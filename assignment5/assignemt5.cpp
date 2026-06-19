#include <stdio.h>
#include <stdlib.h>

#define MaxVertex 10

typedef int ver;
typedef int edge;

typedef struct AdjVNode *PtrToAdjVNode;
typedef struct VNode *PtrToVNode;
typedef struct GNode *PtrToGNode;

typedef PtrToGNode LGraph;

/* 边表结点 */
struct AdjVNode {
    char d;                  /* 邻接点数据 */
    PtrToAdjVNode next;      /* 指向下一条边 */
};

/* 顶点结点 */
struct VNode {
    PtrToAdjVNode FirstEdge; /* 指向第一条边 */
    char d;                  /* 顶点数据 */
};

/* 邻接表 */
typedef struct VNode AdjList[MaxVertex];

/* 图结构 */
struct GNode {
    ver Nv;                  /* 顶点数 */
    edge Ne;                 /* 边数 */
    AdjList G;               /* 邻接表 */
};

LGraph create(int v, int e) {
    int i;

    LGraph G = (LGraph)malloc(sizeof(struct GNode));

    G->Nv = v;
    G->Ne = e;

    for (i = 0; i < G->Nv; i++) {
        G->G[i].d = 'A' + i;
        G->G[i].FirstEdge = NULL;
    }

    return G;
}

void addEdge(LGraph g, char a, char b) {
    PtrToAdjVNode v;
    PtrToAdjVNode p;

    v = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    v->d = b;
    v->next = NULL;

    if (g->G[a - 'A'].FirstEdge == NULL) {
        g->G[a - 'A'].FirstEdge = v;
    } else {
        p = g->G[a - 'A'].FirstEdge;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = v;
    }
}

void insert(LGraph g) {
    char a, b;

    scanf(" %c %c", &a, &b);

    addEdge(g, a, b);
    addEdge(g, b, a);
}

void show(LGraph g) {
    int i;
    PtrToAdjVNode p;

    printf("邻接表为：\n");

    for (i = 0; i < g->Nv; i++) {
        printf("%c: ", g->G[i].d);

        p = g->G[i].FirstEdge;
        while (p != NULL) {
            printf("%c ", p->d);
            p = p->next;
        }

        printf("\n");
    }
}