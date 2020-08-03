/**
 * name:08-图8 How Long Does It Take
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Infinity 65535
#define MAXNUM 105

typedef struct TNode *Vertex;
struct TNode
{
    int v;
    int time;
    Vertex Next;
};

typedef struct
{
    Vertex FirstEdge;
} List[MAXNUM];

typedef struct LNode *LGraph;
struct LNode
{
    int Nv, Ne;
    List Graph;
};

void Insert(LGraph L, int v, Vertex E)
{
    E->Next = L->Graph[v].FirstEdge;
    L->Graph[v].FirstEdge = E;
}

LGraph buildGraph()
{
    int i, v;
    LGraph L;
    Vertex Edge;

    L = (LGraph)malloc(sizeof(struct LNode));
    scanf("%d %d", &L->Nv, &L->Ne);
    for (i = 0; i < L->Nv; i++)
    {
        L->Graph[i].FirstEdge = NULL;
    }
    for (i = 0; i < L->Ne; i++)
    {
        Edge = (Vertex)malloc(sizeof(struct TNode));
        scanf("%d %d %d", &v, &Edge->v, &Edge->time);
        Insert(L, v, Edge);
    }

    return L;
}

int TopSort(LGraph L)
{
    int InDegree[MAXNUM], cnt, time[MAXNUM];
    int i, temp;
    Vertex edge;
    int Queue[MAXNUM], rear = 0, head = 0;

    /*init InDegree*/
    for (i = 0; i < L->Nv; i++)
    {
        InDegree[i] = 0;
        time[i] = 0;
    }

    for (i = 0; i < L->Nv; i++)
    {
        for (edge = L->Graph[i].FirstEdge; edge; edge = edge->Next)
        {
            InDegree[edge->v]++;
        }
    }

    for (i = 0; i < L->Nv; i++)
    {
        if (InDegree[i] == 0)
        {
            Queue[rear++] = i;
        }
    }

    /*TopSort*/
    cnt = 0;
    while (rear != head)
    {
        temp = Queue[head++];
        cnt++;
        for (edge = L->Graph[temp].FirstEdge; edge; edge = edge->Next)
        {
            if (time[edge->v] < time[temp] + edge->time)
            {
                time[edge->v] = time[temp] + edge->time;
            }
            if (--InDegree[edge->v] == 0)
            {
                Queue[rear++] = edge->v;
            }
        }
    }

    int result = 0;
    for (i = 0; i < L->Nv; i++)
    {
        if(time[i] > result)
        {
            result = time[i];
        }
    }

    if (cnt != L->Nv)
    {
        return 0;
    }
    else
    {
        return result;
    }
}

int main(void)
{
    LGraph L;
    L = buildGraph();
    int result = TopSort(L);
    if (result == 0)
    {
        printf("Impossible");
    }
    else
    {
        printf("%d", result);
    }

    return 0;
}