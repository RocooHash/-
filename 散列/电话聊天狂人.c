/**
 * name:11-散列1 电话聊天狂人
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAXNUM 1000000

typedef struct Node Cell;
struct Node
{
    char str[12];
    Cell *next;
    int count;
};

typedef struct Table *HashTable;
struct Table
{
    int TableSize;
    Cell *cell;
};

int NextPrime(int N);
HashTable createHashTable(int N);
int Hash(int key, int P);
void insert(HashTable H, char s[]);
Cell *Find(HashTable H, char s[]);
void scanTable(HashTable H);

int main()
{
    int N;
    HashTable H;
    char str1[12], str2[12];

    scanf("%d", &N);
    getchar();
    H = createHashTable(N * 2);

    int i;
    for (i = 0; i < N; i++)
    {
        scanf("%s", str1);
        scanf("%s", str2);
        insert(H, str1);
        insert(H, str2);
    }

    scanTable(H);
    return 0;
}

int NextPrime(int N)
{
    int i, p = (N % 2) ? N + 2 : N + 1;
    while (p <= MAXNUM)
    {
        for (i = sqrt(p); i > 2; i--)
        {
            if (!(p % i))
                break;
        }
        if (i == 2)
            break;
        else
        {
            p += 2;
        }
    }
    return p;
}

HashTable createHashTable(int N)
{
    HashTable H;
    int i;

    H = (HashTable)malloc(sizeof(struct Table));
    H->TableSize = NextPrime(N);
    H->cell = (Cell *)malloc(sizeof(Cell) * H->TableSize);

    for (i = 0; i < H->TableSize; i++)
    {
        H->cell[i].str[0] = '\0';
        H->cell[i].next = NULL;
        H->cell[i].count = 0;
    }
    return H;
}

int Hash(int key, int P)
{
    return key % P;
}

void insert(HashTable H, char s[])
{
    Cell *newcell, *position;

    position = Find(H, s);
    if (!position)
    {
        newcell = (Cell *)malloc(sizeof(struct Node));
        strcpy(newcell->str, s);
        newcell->count = 1;
        int pos = Hash(atoi(s + 11 - 5), H->TableSize);
        newcell->next = H->cell[pos].next;
        H->cell[pos].next = newcell;
    }
    else
    {
        position->count++;
    }
}

Cell *Find(HashTable H, char s[])
{
    Cell *position = NULL;
    int pos = Hash(atoi(s + 11 - 5), H->TableSize);

    position = H->cell[pos].next;
    while (position && strcmp(position->str, s))
    {
        position = position->next;
    }

    return position;
}

void scanTable(HashTable H)
{
    int i, Maxcount = 0, parataxis = 0;
    char str[12] = "";
    Cell *cell;

    for (i = 0; i < H->TableSize; i++)
    {
        cell = H->cell[i].next;
        while (cell)
        {
            if (cell->count > Maxcount)
            {
                Maxcount = cell->count;
                strcpy(str, cell->str);
                parataxis = 1;
            }
            else if (cell->count == Maxcount)
            {
                parataxis++;
                if (strcmp(cell->str, str) < 0)
                {
                    strcpy(str, cell->str);
                }
            }
            cell = cell->next;
        }
    }

    printf("%s %d", str, Maxcount);
    if (parataxis > 1)
        printf(" %d", parataxis);
}