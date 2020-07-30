/**
 * name:06-图2 Saving James Bond - Easy Version
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
struct vertex
{
	int x;
	int y;
};
typedef struct vertex * Vertex;
struct edgenode
{
	int edge;
	struct edgenode * Next;
};
typedef struct edgenode * Edge;
struct gnode
{
	Vertex data;
	Edge firstedge;
};
struct graph//邻接表存储图
{
	int Nv;
	int Ne;
	struct gnode * Gnode;
};
typedef struct graph * Graph;

Graph Creategraph(int N);
double distance(int x1, int y1, int x2, int y2);//计算两点之间的距离
void DFS(Graph G, int i, int D);//深度优先搜索

int * Visited;
int yes = 0;//yes==1表示可以上岸，yes==0表示不能上岸


int main()
{
	int i;
	int N, D;
	scanf("%d %d", &N, &D);
	Visited = (int *)malloc(N * sizeof(int));
	for (i = 0; i < N; i++)
	{
		Visited[i] = 0;
	}
	Graph G;
	G = Creategraph(N);
	for (i = 0; i < N; i++)
	{
		scanf("%d %d", &G->Gnode[i].data->x, &G->Gnode[i].data->y);
	}
	double d;
	int j;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			d = distance(G->Gnode[i].data->x, G->Gnode[i].data->y, G->Gnode[j].data->x, G->Gnode[j].data->y);
			if (d > 0 && d <= D)//将所有能从G->Gnode[i]跳到的结点都连接成链表
			{
				Edge Newnode;
				Newnode = (Edge)malloc(sizeof(struct edgenode));
				Newnode->edge = j;
				Newnode->Next = G->Gnode[i].firstedge;
				G->Gnode[i].firstedge = Newnode;
			}
		}
	}
	//图的遍历
	Edge p;
	for (i = 0; i < N; i++)
	{
		if (distance(G->Gnode[i].data->x, G->Gnode[i].data->y, 0, 0) > D + 15) { continue; }//寻找能从小岛跳到的出发点
		if (Visited[i] == 0)
		{
			DFS(G, i, D);
			if (yes == 1) { break; }
		}
	}
	if (yes == 0) { printf("No"); }
	else { printf("Yes"); }
	return 0;
}

Graph Creategraph(int N)
{
	Graph G;
	G = (Graph)malloc(sizeof(struct graph));
	G->Nv = N;
	G->Gnode = (struct gnode *)malloc(N * sizeof(struct gnode));
	G->Ne = 0;
	int i;
	for (i = 0; i < N; i++)
	{
		G->Gnode[i].firstedge = NULL;
		G->Gnode[i].data = (Vertex)malloc(sizeof(struct vertex));
	}
	return G;
}

double distance(int x1, int y1, int x2, int y2)
{
	double d;
	d = sqrt((x1 - x2)*(x1 - x2) + (y1 - y2) * (y1 - y2));
	return d;
}

void DFS(Graph G, int i, int D)//深度优先搜索
{
	Visited[i] = 1;
	if (G->Gnode[i].data->x + D >= 50 || G->Gnode[i].data->x - D <= -50 || G->Gnode[i].data->y + D >= 50 || G->Gnode[i].data->y - D <= -50)//可以从出发点直接上岸
	{
		yes = 1;
	}
	else
	{
		Edge p;
		p = G->Gnode[i].firstedge;
		while (p != NULL)
		{
			if (Visited[p->edge] == 0)
			{
				Visited[p->edge] = 1;
				if (G->Gnode[p->edge].data->x + D >= 50 || G->Gnode[p->edge].data->x - D <= -50 || G->Gnode[p->edge].data->y + D >= 50 || G->Gnode[p->edge].data->y - D <= -50)//中间某点可以上岸
				{
					yes = 1;
				}
				else
				{
					DFS(G, p->edge, D);
				}
			}
			p = p->Next;
		}
	}
}

