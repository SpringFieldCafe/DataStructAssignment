#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXSIZE 10000

typedef struct BiTNode {
    char data;
    struct BiTNode *lchild;
    struct BiTNode *rchild;
} BiTNode, *BiTree;

/* 顺序循环队列，用于层次遍历 */
typedef struct {
    BiTree data[MAXSIZE];
    int front;
    int rear;
} SeqQueue;

/* 初始化队列 */
void InitQueue(SeqQueue *Q) {
    Q->front = 0;
    Q->rear = 0;
}

/* 判断队列是否为空 */
int QueueEmpty(SeqQueue *Q) {
    return Q->front == Q->rear;
}

/* 入队 */
int EnQueue(SeqQueue *Q, BiTree x) {
    if ((Q->rear + 1) % MAXSIZE == Q->front) {
        return 0;
    }

    Q->data[Q->rear] = x;
    Q->rear = (Q->rear + 1) % MAXSIZE;
    return 1;
}

/* 出队 */
BiTree DeQueue(SeqQueue *Q) {
    BiTree x;

    if (QueueEmpty(Q)) {
        return NULL;
    }

    x = Q->data[Q->front];
    Q->front = (Q->front + 1) % MAXSIZE;
    return x;
}

/* 跳过空格 */
void SkipSpace(const char **p) {
    while (**p != '\0' && isspace((unsigned char)**p)) {
        (*p)++;
    }
}

/* 判断是否为结点字符 */
int IsNodeChar(char ch) {
    return isalnum((unsigned char)ch);
}

/*
    根据括号表示法创建二叉树

    例如：
    A(B(D(,G),),C(E,F))
*/
BiTree CreateTree(const char **p) {
    BiTree root;

    SkipSpace(p);

    if (**p == '\0' || **p == ')' || **p == ',') {
        return NULL;
    }

    if (!IsNodeChar(**p)) {
        return NULL;
    }

    root = (BiTree)malloc(sizeof(BiTNode));
    if (root == NULL) {
        printf("内存分配失败！\n");
        exit(1);
    }

    root->data = **p;
    root->lchild = NULL;
    root->rchild = NULL;

    (*p)++;

    SkipSpace(p);

    if (**p == '(') {
        (*p)++;

        SkipSpace(p);

        if (**p != ',' && **p != ')') {
            root->lchild = CreateTree(p);
        }

        SkipSpace(p);

        if (**p == ',') {
            (*p)++;

            SkipSpace(p);

            if (**p != ')') {
                root->rchild = CreateTree(p);
            }
        }

        SkipSpace(p);

        if (**p == ')') {
            (*p)++;
        }
    }

    return root;
}

/* 先序遍历：根 左 右 */
void PreOrder(BiTree T) {
    if (T == NULL) {
        return;
    }

    printf("%c ", T->data);
    PreOrder(T->lchild);
    PreOrder(T->rchild);
}

/* 中序遍历：左 根 右 */
void InOrder(BiTree T) {
    if (T == NULL) {
        return;
    }

    InOrder(T->lchild);
    printf("%c ", T->data);
    InOrder(T->rchild);
}

/* 后序遍历：左 右 根 */
void PostOrder(BiTree T) {
    if (T == NULL) {
        return;
    }

    PostOrder(T->lchild);
    PostOrder(T->rchild);
    printf("%c ", T->data);
}

/* 层次遍历 */
void LevelOrder(BiTree T) {
    SeqQueue Q;
    BiTree p;

    if (T == NULL) {
        return;
    }

    InitQueue(&Q);
    EnQueue(&Q, T);

    while (!QueueEmpty(&Q)) {
        p = DeQueue(&Q);

        printf("%c ", p->data);

        if (p->lchild != NULL) {
            EnQueue(&Q, p->lchild);
        }

        if (p->rchild != NULL) {
            EnQueue(&Q, p->rchild);
        }
    }
}

/* 统计叶子结点个数 */
int CountLeaf(BiTree T) {
    if (T == NULL) {
        return 0;
    }

    if (T->lchild == NULL && T->rchild == NULL) {
        return 1;
    }

    return CountLeaf(T->lchild) + CountLeaf(T->rchild);
}

/* 求二叉树深度 */
int TreeDepth(BiTree T) {
    int leftDepth;
    int rightDepth;

    if (T == NULL) {
        return 0;
    }

    leftDepth = TreeDepth(T->lchild);
    rightDepth = TreeDepth(T->rchild);

    return leftDepth > rightDepth ? leftDepth + 1 : rightDepth + 1;
}

/* 释放二叉树 */
void DestroyTree(BiTree T) {
    if (T == NULL) {
        return;
    }

    DestroyTree(T->lchild);
    DestroyTree(T->rchild);
    free(T);
}

int main() {
    char str[MAXSIZE];
    const char *p;
    BiTree T;

    printf("请输入二叉树的括号表示法字符串：\n");
    fgets(str, MAXSIZE, stdin);

    str[strcspn(str, "\n")] = '\0';

    p = str;
    T = CreateTree(&p);

    printf("\n先序遍历结果：");
    PreOrder(T);

    printf("\n中序遍历结果：");
    InOrder(T);

    printf("\n后序遍历结果：");
    PostOrder(T);

    printf("\n层次遍历结果：");
    LevelOrder(T);

    printf("\n叶子结点个数：%d", CountLeaf(T));
    printf("\n二叉树深度：%d\n", TreeDepth(T));

    DestroyTree(T);

    return 0;
}