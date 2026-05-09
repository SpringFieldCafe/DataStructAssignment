#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int r;
    int c;
} Point;

typedef struct {
    Point *data;
    int front;
    int rear;
    int capacity;
} Queue;

void initQueue(Queue *q, int capacity) {
    q->data = (Point *)malloc(sizeof(Point) * capacity);
    q->front = 0;
    q->rear = 0;
    q->capacity = capacity;
}

int isEmpty(Queue *q) {
    return q->front == q->rear;
}

int enqueue(Queue *q, Point p) {
    if (q->rear >= q->capacity) {
        return 0;
    }
    q->data[q->rear++] = p;
    return 1;
}

Point dequeue(Queue *q) {
    return q->data[q->front++];
}

void freeQueue(Queue *q) {
    free(q->data);
}

int **createIntMatrix(int rows, int cols) {
    int **a = (int **)malloc(sizeof(int *) * rows);
    for (int i = 0; i < rows; i++) {
        a[i] = (int *)malloc(sizeof(int) * cols);
    }
    return a;
}

void freeIntMatrix(int **a, int rows) {
    for (int i = 0; i < rows; i++) {
        free(a[i]);
    }
    free(a);
}

int inArea(int r, int c, int rows, int cols) {
    return r >= 0 && r < rows && c >= 0 && c < cols;
}

int bfs(int **maze, int rows, int cols, Point start, Point end,
        int **visited, int **preR, int **preC) {
    Queue q;
    initQueue(&q, rows * cols);

    int dr[4] = {1, 0, -1, 0};
    int dc[4] = {0, 1, 0, -1};

    enqueue(&q, start);
    visited[start.r][start.c] = 1;

    while (!isEmpty(&q)) {
        Point cur = dequeue(&q);

        if (cur.r == end.r && cur.c == end.c) {
            freeQueue(&q);
            return 1;
        }

        for (int i = 0; i < 4; i++) {
            int nr = cur.r + dr[i];
            int nc = cur.c + dc[i];

            if (inArea(nr, nc, rows, cols)
                && maze[nr][nc] == 0
                && visited[nr][nc] == 0) {

                visited[nr][nc] = 1;

                preR[nr][nc] = cur.r;
                preC[nr][nc] = cur.c;

                Point next;
                next.r = nr;
                next.c = nc;
                enqueue(&q, next);
            }
        }
    }

    freeQueue(&q);
    return 0;
}

void printPath(int **maze, int rows, int cols, Point start, Point end,
               int **preR, int **preC) {
    Point *path = (Point *)malloc(sizeof(Point) * rows * cols);
    int pathLen = 0;

    Point cur = end;

    while (!(cur.r == start.r && cur.c == start.c)) {
        path[pathLen++] = cur;

        Point prev;
        prev.r = preR[cur.r][cur.c];
        prev.c = preC[cur.r][cur.c];

        cur = prev;
    }

    path[pathLen++] = start;

    int **pathFlag = createIntMatrix(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            pathFlag[i][j] = 0;
        }
    }

    printf("\n路径坐标如下：\n");

    for (int i = pathLen - 1; i >= 0; i--) {
        printf("(%d, %d)", path[i].r, path[i].c);

        pathFlag[path[i].r][path[i].c] = 1;

        if (i != 0) {
            printf(" -> ");
        }
    }

    printf("\n\n路径长度：%d 个结点，%d 步\n", pathLen, pathLen - 1);

    printf("\n迷宫路径显示如下：\n");
    printf("S 表示起点，E 表示终点，* 表示路径，# 表示墙，. 表示可走但未经过\n\n");

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i == start.r && j == start.c) {
                printf("S ");
            } else if (i == end.r && j == end.c) {
                printf("E ");
            } else if (maze[i][j] == 1) {
                printf("# ");
            } else if (pathFlag[i][j] == 1) {
                printf("* ");
            } else {
                printf(". ");
            }
        }
        printf("\n");
    }

    free(path);
    freeIntMatrix(pathFlag, rows);
}

int main() {
    int rows, cols;

    printf("请输入迷宫的行数和列数：\n");
    scanf("%d %d", &rows, &cols);

    Point start, end;

    printf("请输入起点坐标和终点坐标，格式为：start_r start_c end_r end_c\n");
    scanf("%d %d %d %d", &start.r, &start.c, &end.r, &end.c);

    int **maze = createIntMatrix(rows, cols);
    int **visited = createIntMatrix(rows, cols);
    int **preR = createIntMatrix(rows, cols);
    int **preC = createIntMatrix(rows, cols);

    printf("请输入迷宫数据，0 表示通路，1 表示墙：\n");

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &maze[i][j]);
            visited[i][j] = 0;
            preR[i][j] = -1;
            preC[i][j] = -1;
        }
    }

    if (!inArea(start.r, start.c, rows, cols) ||
        !inArea(end.r, end.c, rows, cols)) {
        printf("起点或终点坐标越界！\n");

        freeIntMatrix(maze, rows);
        freeIntMatrix(visited, rows);
        freeIntMatrix(preR, rows);
        freeIntMatrix(preC, rows);

        return 0;
    }

    if (maze[start.r][start.c] == 1 || maze[end.r][end.c] == 1) {
        printf("起点或终点不能是墙！\n");

        freeIntMatrix(maze, rows);
        freeIntMatrix(visited, rows);
        freeIntMatrix(preR, rows);
        freeIntMatrix(preC, rows);

        return 0;
    }

    int found = bfs(maze, rows, cols, start, end, visited, preR, preC);

    if (found) {
        printf("\n成功找到一条从起点到终点的路径！\n");
        printPath(maze, rows, cols, start, end, preR, preC);
    } else {
        printf("\n没有找到从起点到终点的路径！\n");
    }

    freeIntMatrix(maze, rows);
    freeIntMatrix(visited, rows);
    freeIntMatrix(preR, rows);
    freeIntMatrix(preC, rows);

    return 0;
}