#include <stdio.h>
#include <stdlib.h>

#define MaxVertexNum 100
#define INFINITY 65535
#define Vertex int;
#define WeightType int;
#define DataType char;

/*边的定义*/
typedef struct ENode *PtrToENode;
struct ENode
{
    Vertex v1, v2;     //有向边
    WeightType weight; //权重
};
typedef PtrToENode Edge;

/*图节点的定义*/
typedef struct GNode *PtrToGNode;
struct GNode
{
    int Nv;
    int Ne;
    WeightType G[MaxVertexNum][MaxVertexNum];
    DataType Data[MaxVertexNum];
};
typedef PtrToGNode MGraph;

MGraph CreateGragh(int VertexNum)
{ /*初始化一个有VertexNum个顶点但没有边的图*/
    int v, w;
    MGraph Graph;

    Graph = (MGraph)malloc(sizeof(struct GNode));
    Graph->Nv = VertexNum;
    Graph->Ne = 0;

    for (v = 0; v < Graph->Nv; v++)
    {
        for (w = 0; w < Graph->Nv; w++)
        {
            Graph->G[v][w] = INFINITY;
        }
    }
    return Graph;
}

void InsertEdge(MGraph Graph, Edge E)
{
    Graph->G[E->v1][E->v2] = E->weight;
    /*如果是无向图，增加反向语句*/
    Graph->G[E->v2][E->v1] = E->weight;
}

MGraph BuildGraph(void)
{
    MGraph Graph;
    Edge E;
    int Nv, v, i;

    scanf("%d", &Nv);
    Graph = CreateGragh(Nv);

    scanf("%d", &Graph->Ne);
    if(Graph->Ne != 0)
    {
        E = (Edge)molloc(sizeof(struct ENode));
        for(i=0;i<Graph->Ne;i++)
        {
            scanf("%d %d %d",&E->v1, &E->v2, &E->weight);
            InsertEdge(Graph, E);
        }
    }
    for(v=0;v<Graph->Nv;v++)
    {
        scanf(" %c",&Graph->Data[v]);
    }
    return Graph;
}
