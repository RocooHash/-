/**
 * name:11-散列3 QQ帐户的申请与登陆 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MaxNum 2 * 10000

typedef struct Node *Cell;
struct Node
{
    char str[13];
    char key[17];
    Cell next;
};
typedef Cell Head;

typedef struct TblNode *HashTable;
struct TblNode
{
    int TableSize;
    Head head;
};

int NextPrime(int N)
{
    int i, p = (N % 2) ? N + 2 : N + 1;
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

HashTable createHashTable(int N)
{
    HashTable H;
    H = (HashTable)malloc(sizeof(struct TblNode));
    H->TableSize = NextPrime(N);
    H->head = (Head)malloc(sizeof(struct Node) * H->TableSize);

    int i;
    for (i = 0; i < H->TableSize; i++)
    {
        H->head[i].str[0] = '\0';
        H->head[i].key[0] = '\0';
        H->head[i].next = NULL;
    }
    return H;
}

int Hash(int key, int TableSize)
{
    return key % TableSize;
}

Cell Find(HashTable H, char s[])
{
    Cell position;
    int index = Hash(atoi(s), H->TableSize);
    position = H->head[index].next;
    while (position && strcmp(position->str, s))
    {
        position = position->next;
    }
    return position;
}

void login(HashTable H, char account[], char pass[])
{
    Cell position = Find(H, account);
    if (position == NULL)
    {
        printf("ERROR: Not Exist\n");
    }
    else
    {
        if (!strcmp(position->key, pass))
        {
            printf("Login: OK\n");
        }
        else
        {
            printf("ERROR: Wrong PW\n");
        }
    }
}

void newAccount(HashTable H, char account[], char pass[])
{
    Cell postion = Find(H, account);
    if(postion)
    {
        printf("ERROR: Exist\n");
    }
    else
    {
        Cell new = (Cell)malloc(sizeof(struct Node));
        int index = Hash(atoi(account), H->TableSize);
        strcpy(new->str, account);
        strcpy(new->key, pass);
        new->next = H->head[index].next;
        H->head[index].next = new;
        printf("New: OK\n");
    }
    
}

int main(void)
{
    int N;
    char op, account[11], pass[17];
    HashTable H;

    scanf("%d", &N);
    getchar();
    H = createHashTable(N);
    while (N--)
    {
        scanf("%c %s %s", &op, account, pass);
        switch (op)
        {
        case 'L':
            login(H, account, pass);
            break;

        case 'N':
            newAccount(H, account, pass);
            break;
        }
        getchar();
    }
}
