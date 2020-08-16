/**
 * name:11-散列2 Hashing
 * 易错点：上下限的确定，最小值为1， 最大设为宽限的2倍
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MaxNum 20000

typedef struct Node Cell;
struct Node
{
    int data;
};

typedef struct tblNode *HashTable;
struct tblNode
{
    int TableSize;
    Cell *cell;
};

int NextPrime(int N)
{
    if (N == 2 || N == 1)
    {
        return 2;
    }
    int i, p = (N % 2) ? N : N + 1;
    while (p <= MaxNum)
    {
        for (i = sqrt(p); i > 2; i--)
        {
            if (!(p % i))
                break;
        }
        if (i == 2)
            break;
        else
            p += 2;
    }
    return p;
}

HashTable createTable(int N)
{
    HashTable H;
    H = (HashTable)malloc(sizeof(struct tblNode));
    H->TableSize = NextPrime(N);
    H->cell = (Cell *)malloc(sizeof(Cell) * H->TableSize);
    int i;
    for (i = 0; i < H->TableSize; i++)
    {
        H->cell[i].data = -1;
    }
    return H;
}

int Hash(int key, int T)
{
    return key % T;
}

int Find(HashTable H, int key)
{
    int currentPos, NewPos;
    int Cum = 0;

    NewPos = currentPos = Hash(key, H->TableSize);
    while (H->cell[NewPos].data != -1 && H->cell[NewPos].data != key && Cum < H->TableSize / 2)
    {
        Cum++;
        NewPos = (currentPos + (Cum) * (Cum)) % H->TableSize;
    }
    if (H->cell[NewPos].data == -1)
    {
        return NewPos;
    }
    else
    {
        return -1;
    }
}

void insert(HashTable H, int N)
{
    int data, position;
    for (N; N > 1; N--)
    {
        scanf("%d", &data);
        position = Find(H, data);
        if (position == -1)
        {
            printf("- ");
        }
        else
        {
            H->cell[position].data = data;
            printf("%d ", position);
        }
    }
    scanf("%d", &data);
    position = Find(H, data);
    if (position == -1)
    {
        printf("-");
    }
    else
    {
        H->cell[position].data = data;
        printf("%d", position);
    }
}

int main(void)
{
    int N, M;
    scanf("%d%d", &M, &N);
    HashTable H = createTable(M);
    insert(H, N);
    return 0;
}