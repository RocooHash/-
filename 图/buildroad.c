/**
 * name:08-图7 公路村村通
*/

#include <stdio.h>
#include <stdlib.h>
#define Infinity 65535
#define MaxNum 1005

int Nv, Ne, Graph[MaxNum][MaxNum];
int dist[MaxNum], Parent[MaxNum];

int FindMinDist()
{
    int MinV, i;
    int MinDist = Infinity;

    for (i = 1; i <= Nv; i++)
    {
        if (dist[i] != 0 && dist[i] < MinDist)
        {
            MinDist = dist[i];
            MinV = i;
        }
    }

    if (MinDist < Infinity)
    {
        return MinV;
    }
    else
    {
        return -1;
    }
}

int prim()
{
    int lengthSum = 0, a, b;
    int i, count = 0;

    /*初始化*/
    for (i = 1; i <= Nv; i++)
    {
        dist[i] = Graph[1][i];
        Parent[i] = 1;
    }

    dist[1] = 0;
    count++;
    Parent[1] = -1;

    while (1)
    {
        a = FindMinDist();
        if (a == -1)
        {
            break;
        }
        lengthSum += dist[a];
        dist[a] = 0;
        count++;

        for (i = 1; i <= Nv; i++)
        {
            if (dist[i] != 0 && Graph[a][i] != Infinity)
            {
                dist[i] = Graph[a][i];
                Parent[i] = a;
            }
        }
    }
    if (count < Nv)
    {
        return -1;
    }
    return lengthSum;
}

int main(void)
{
    int i, j, a, b, length;
    scanf("%d %d", &Nv, &Ne);
    for (i = 1; i <= Nv; i++)
    {
        for (j = 1; j <= Nv; j++)
        {
            Graph[i][j] = Infinity;
        }
    }
    for (i = 1; i <= Ne; i++)
    {
        scanf("%d %d %d", &a, &b, &length);
        Graph[a][b] = Graph[b][a] = length;
    }

    int result = prim(1);
    printf("%d", result);
}