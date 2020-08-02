/**
 * name:07-图4 哈利·波特的考试
*/

#include <stdio.h>
#include <stdlib.h>
#define MaxVertexNum 100
#define INFINITY 65535

typedef struct ENode *PtrToENode;
struct ENode
{
    int v1, v2;
    int weight;
};
typedef PtrToENode Edge;

typedef struct GNode *PtrToGNode;
struct GNode
{
    int Nv;
    int Ne;
    int G[MaxVertexNum][MaxVertexNum];
};
typedef PtrToGNode MGraph;

MGraph createGraph(int Nv)
{
    MGraph G;
    int i, j;

    G = (MGraph)malloc(sizeof(struct GNode));
    G->Nv = Nv;
    G->Ne = 0;

    for (i = 0; i < Nv; i++)
    {
        for (j = 0; j < Nv; j++)
        {
            G->G[i][j] = INFINITY;
        }
    }

    return G;
}

void InsertEdge(MGraph Graph, Edge E)
{
    Graph->G[E->v1][E->v2] = E->weight;
    Graph->G[E->v2][E->v1] = E->weight;
}

MGraph BuildGraph(void)
{
    MGraph G;
    Edge E;
    int Nv, Ne, i;

    scanf("%d", &Nv);
    G = createGraph(Nv);

    scanf("%d", &Ne);
    E = (Edge)malloc(sizeof(struct ENode));
    for (i = 0; i < Ne; i++)
    {  
        scanf("%d %d %d", &E->v1, &E->v2, &E->weight);
        E->v1--;
        E->v2--;
        InsertEdge(G, E);
    }
    return G;
}

void Floyd(MGraph G, int D[][MaxVertexNum])
{
    int i, j, k;
    for(i = 0;i<G->Nv;i++)
    {
        for(j=0;j<G->Nv;j++)
        {
            D[i][j] = G->G[i][j];
        }
    }

    for(k=0;k<G->Nv;k++)
    {
        for(i=0;i<G->Nv;i++)
        {
            for(j=0;j<G->Nv;j++)
            {
                if(D[i][k] + D[k][j] < D[i][j])
                {
                    D[i][j] = D[i][k] + D[k][j];
                }
            }
        }
    }
}

int findMaxDist(int D[][MaxVertexNum], int i, int N)
{
    int MaxDist;
    int j;

    MaxDist = 0;
    for (j=0;j<N;j++)
    {
        if(i!=j && D[i][j] > MaxDist)
        {
            MaxDist = D[i][j];
        }
    }

    return MaxDist;
}


void FindAnimal(MGraph G)
{
    int D[MaxVertexNum][MaxVertexNum], MaxDist, MinDist;
    int Animal, i;

    Floyd(G , D);

    MinDist = INFINITY;
    for(i=0;i<G->Nv;i++)
    {
        MaxDist = findMaxDist(D, i ,G->Nv);
        if(MaxDist == INFINITY)
        {
            printf("0\n");
            return;
        }
        if (MinDist > MaxDist)
        {
            MinDist = MaxDist;
            Animal = i +1;
        }
    }
    printf("%d %d", Animal, MinDist);
}

int main(void)
{
    MGraph G = BuildGraph();
    FindAnimal(G);
    return 0;
}