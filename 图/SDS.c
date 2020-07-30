/**
 * name:06-图3 六度空间
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10005

typedef struct TNode *Vertex;
struct TNode
{
    int v;
    Vertex Next;
};

typedef struct LNode
{
    Vertex FirstEdge;
} List[MAX];

typedef struct GNode *Graph;
struct GNode
{
    int Nv, Ne;
    List Head;
};

void Insert(int v, int w);
void BFS(int s);

Graph G;
int Visit[MAX];

int main(void)
{
    int i;
    int v, w;
    G = (Graph)malloc(sizeof(struct GNode));
    scanf("%d %d", &G->Nv, &G->Ne);
    for (i = 1; i <= G->Nv; i++)
    {
        G->Head[i].FirstEdge = NULL;
    }
    for (i = 1; i <= G->Ne; i++)
    {
        scanf("%d %d",&v, &w);
        Insert(v, w);
    }
    for (i = 1; i <= G->Nv; i++)
    {
        memset(Visit, 0 ,sizeof(Visit));
        BFS(i);
    }

    return 0;
}

void Insert(int v, int w)
{
    Vertex NewNode = (Vertex)malloc(sizeof(struct TNode));
    NewNode->v = v;
    NewNode->Next = G->Head[w].FirstEdge;
    G->Head[w].FirstEdge = NewNode;

    NewNode = (Vertex)malloc(sizeof(struct TNode));
    NewNode->v = w;
    NewNode->Next = G->Head[v].FirstEdge;
    G->Head[v].FirstEdge = NewNode;
}

void BFS(int s)
{
    int Q[MAX], front = 0, rear = 0, v;
    int tail, last = s, cnt = 0, level = 0, state = s;
    Vertex p;
    double percent;
    Q[++rear] = s;
    Visit[s] = 1;
    cnt++;

    while (rear != front)
    {
        v = Q[++front];
        for (p = G->Head[v].FirstEdge; p; p = p->Next)
        {
            if (!Visit[p->v])
            {
                Q[++rear] = p->v;
                Visit[p->v] = 1;
                cnt++;
                tail = p->v;
            }
            
        }
        if (v == last)
            {
                level++;
                last = tail;
            }
        if (level == 6)
                break;
    }
    percent = ((double)cnt) / ((double)G->Nv) * 100;
    printf("%d: %.2lf%%\n", state, percent);
}
