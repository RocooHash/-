/**
 * name:05-树7 堆中的路径
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Heap *MinHeap;
struct Heap
{
    int *data;
    int size;
};

MinHeap createHeap(MinHeap mp, int N);
MinHeap insert(MinHeap mp, int X);
void findWay(MinHeap mp, int X);

int main(void)
{
    int N, M, X;
    scanf("%d %d", &N, &M);

    MinHeap mp = malloc(sizeof (MinHeap));
    mp = createHeap(mp, N);
    while (M--)
    {
        scanf("%d", &X);
        findWay(mp, X);
    }
    return 0;
}

MinHeap createHeap(MinHeap mp, int N)
{
    int i, data;
    
    mp->data =(int*) malloc((N + 1) * sizeof(int));
    mp->size = 0;
    mp->data[0] = -10005;
    for (i = 1; i <= N; i++)
    {
        scanf("%d", &data);
        mp = insert(mp, data);
    }
    return mp;
}

MinHeap insert(MinHeap mp, int X)
{
    int i;
    i = ++mp->size;
    for (; mp->data[i / 2] > X; i = i / 2)
    {
        mp->data[i] = mp->data[i / 2];
    }
    mp->data[i] = X;
    return mp;
}

void findWay(MinHeap mp, int X)
{
    for (; X > 1; X = X / 2)
    {
        printf("%d ",mp->data[X]);
    }
    printf("%d\n",mp->data[1]);
}