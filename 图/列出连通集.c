#include <stdio.h>
#include <stdlib.h>

typedef struct qNode
{
    int a[10];
    int start;
    int end;
} * Queue;

int a[10][10];
int count[10];
void createMap(int n, int e);
void DFS(int n);
void dfsProcess(int i, int n);
void addQueue(Queue q, int x);
int isEmpty(Queue q);
int deleteQueue(Queue q);
void BFS(int n);
void bfsProcess(Queue q, int i, int n);

int main(void)
{
    int n, e;
    scanf("%d %d", &n, &e);
    createMap(n, e);
    DFS(n);
    BFS(n);
    return 0;
}

void createMap(int n, int e)
{
    int i, j;
    int v, w;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            a[i][j] = 0;
        }
    }

    while (e--)
    {
        scanf("%d %d", &v, &w);
        a[v][w] = 1;
        a[w][v] = 1;
    }
}

void DFS(int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        count[i] = 0;
    }

    for (i = 0; i < n; i++)
    {
        if (count[i] == 1)
        {
            continue;
        }
        count[i] = 1;
        printf("{ %d ", i);
        dfsProcess(i, n);
        printf("}\n");
    }
}

void dfsProcess(int i, int n)
{
    int j;
    for (j = 0; j < n; j++)
    {
        if (count[j] == 1 || j == i)
            continue;
        else if (a[j][i] == 1)
        {
            printf("%d ", j);
            count[j] = 1;
            dfsProcess(j, n);
        }
    }
}

void addQueue(Queue q, int x)
{
    if (q->end <= 9)
    {
        q->a[++q->end] = x;
    }
}

int deleteQueue(Queue q)
{
    int num;
    if (!isEmpty(q))
    {
        num = q->a[q->start];
        q->a[q->start++] = -1;
        return num;
    }
    else return 0;
}

int isEmpty(Queue q)
{
    int i;
    for(i=0;i<10;i++)
    {
        if(q->a[i] != -1)
        return 0;
    }
    return 1;
}

void BFS(int n)
{
    Queue q = (Queue)malloc(sizeof(struct qNode));
    q->start = 0;
    q->end = -1;

    int i;
    for (i = 0; i < 10; i++)
    {
        count[i] = 0;
        q->a[i] = -1;
    }
    i = 0;
    while (i < n)
    {
        if (count[i] == 1)
        {
            i++;
            continue;
        }
        printf("{ ");
        bfsProcess(q, i, n);
        printf("}\n");
        i++;
    }
}

void bfsProcess(Queue q, int i, int n)
{
    int num;

    printf("%d ", i);
    count[i] = 1;
    addQueue(q, i);
    
    int j;
    while (!isEmpty(q))
    {
        num = deleteQueue(q);
        for (j = 0; j < n; j++)
        {
            if(a[j][num] == 1 && count[j] == 0)
            {
                printf("%d ",j);
                count[j] = 1;
                addQueue(q, j);
            }
        }
    }
}