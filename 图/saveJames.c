/**
 * name:07-图5 Saving James Bond - Hard Version 
 * method:Dijkstra
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define infinity 65535
#define radius 7.5

typedef struct
{
    int x;
    int y;
} Node;

Node G[102];
int N, D;

void Initialize(int dist[], int path[])
{
    int i = 0;
    for (i = 0; i < N; i++)
    {
        scanf("%d %d", &G[i].x, &G[i].y);
        if (G[i].x >= 50 || G[i].x <= -50)
        {
            G[i].x = infinity;
        }
        if (G[i].y >= 50 || G[i].y <= -50)
        {
            G[i].y = infinity;
        }
        dist[i] = infinity;
        path[i] = -1;
    }
}

int FirstJump(int i)
{
    double distance = radius + D;
    double dis = pow(G[i].x, 2) + pow(G[i].y, 2);
    if (dis <= pow(distance, 2) && dis > pow(radius, 2))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int isSafe(int k)
{
    int x = G[k].x;
    int y = G[k].y;
    if ((x - D <= -50) || (x + D >= 50) || (y - D <= -50) || (y + D >= 50))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int isAround(int k, int i)
{
    if (k == i)
        return 0;
    double dist = pow(G[k].x - G[i].x, 2) + pow(G[k].y - G[i].y, 2);
    if (dist <= pow(D, 2))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int source(int a, int b, int path[])
{
    while (path[a] != -1)
    {
        a = path[a];
    }
    while (path[a] != -1)
    {
        a = path[a];
    }
    double disA = pow(G[a].x, 2) + pow(G[a].y, 2);
    double disB = pow(G[b].x, 2) + pow(G[b].y, 2);

    if (disB <= disA)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int shortestPath(int k, int dist[], int path[])
{
    dist[k] = 1;
    path[k] = -1;
    int answer = -1;
    if (isSafe(k))
    {
        answer = k;
    }
    else
    {
        int Q[N], head = 0, rear = 0;
        Q[rear++] = k;
        while (head != rear)
        {
            int temp = Q[head++];
            int i = 0 ;
            for(i=0;i<N;i++)
            {
                if(isAround(temp, i) )
                {  
                     
                    if(dist[i] > dist[temp] +1)
                    {
                        dist[i] = dist[temp] + 1;
                        path[i] = temp;
                        Q[rear++] = i;
                        if(isSafe(i))
                        {
                            answer = i;
                            break;
                        }
                    }
                    else if (dist[i] == (dist[temp] + 1) && source(i ,temp ,path))
                    {
                        dist[i] = dist[temp] + 1;
                        path[i] = temp;
                        Q[rear++] = i;
                        if(isSafe(i))
                        {
                            answer = i;
                            break;
                        }
                    }
                }
            }
            if(answer != -1)
            {
                break;
            }
        }
    }
    return answer;
}

void Save(int dist[], int path[])
{
    int i = 0;
    int answer = -1;
    int minAnswer = -1;
    int minDist = infinity;
    double distance = radius + D;
    if (distance >= 50.0)
    {
        printf("1");
        return;
    }
    for (i = 0; i < N; i++)
    {
        if (FirstJump(i))
        {
            answer = shortestPath(i, dist, path);
            if (minDist == dist[answer])
            {
                if (source(minAnswer, answer, path))
                {
                    minAnswer = answer;
                    minDist = dist[answer];
                }
                else
                {
                    continue;
                }
            }
            else
            {
                minAnswer = answer;
                minDist = dist[answer];
            }
        }
    }

    if (minAnswer != -1)
    {
        printf("%d\n", dist[minAnswer] + 1);
        int stack[100];
        int top = 0;
        stack[top++] = minAnswer;
        while (path[minAnswer] != -1)
        {
            stack[top++] = path[minAnswer];
            minAnswer = path[minAnswer];
        }
        while (top > 0)
        {
            int i = stack[--top];
            printf("%d %d\n", G[i].x, G[i].y);
        }
    }
    else
    {
        printf("0");
    }
}

int main(void)
{
    scanf("%d %d", &N, &D);
    int dist[N];
    int path[N];
    Initialize(dist, path);
    Save(dist, path);
    return 0;
}
