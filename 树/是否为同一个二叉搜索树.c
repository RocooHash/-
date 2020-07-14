/**
 * url:https://pintia.cn/problem-sets/1268384564738605056/problems/1276814005115539456
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode *Tree;
struct TreeNode
{
    int v;
    Tree Left, Right;
    int flag;
};

Tree MakeTree(int N);
Tree Insert(Tree T, int V);
int check(Tree T, int V);
int judge(Tree T, int N);
void resetTree(Tree T);
void freeTree(Tree T);

int main()
{
    int i, N, M;
    scanf("%d", &N);
    while (N)
    {
        scanf("%d", &M);
        Tree T = MakeTree(N);
        for (i = 0; i < M; i++)
        {
            if (judge(T, N))
                printf("Yes\n");
            else
                printf("No\n");
            resetTree(T);
        }
        freeTree(T);
        scanf("%d", &N);
    }

    return 0;
}

Tree MakeTree(int N)
{
    Tree T = NULL;
    int i, data;
    for (i = 0; i < N; i++)
    {
        scanf("%d", &data);
        T = Insert(T, data);
    }
    return T;
}

Tree Insert(Tree T, int V)
{
    if (!T)
    {
        T = (Tree)malloc(sizeof(struct TreeNode));
        T->v = V;
        T->Left = T->Right = NULL;
        T->flag = 0;
    }
    else
    {
        if (V < T->v)
            T->Left = Insert(T->Left, V);
        else if (V > T->v)
            T->Right = Insert(T->Right, V);
    }
    return T;
}

int check(Tree T, int V)
{
    if (T->flag)
    {
        if (V < T->v)
            return check(T->Left, V);
        else if (V > T->v)
            return check(T->Right, V);
        else
            return 0;
    }
    else
    {
        if (V == T->v)
        {
            T->flag == 1;
            return 1;
        }
        else
            return 0;
    }
}

int judge(Tree T, int N)
{
    int i, V, result = 0;

    scanf("%d", &V);
    if (V != T->v)
        result = 1;
    else
        T->flag = 1;
    for (i = 1; i < N; i++)
    {
        scanf("%d", &V);
        if ((!result) && (!check(T, V)))
            result = 1;
    }
    if (result)
        return 0;
    else
        return 1;
}

void resetTree(Tree T)
{
    if (T->Left)
        resetTree(T->Left);
    if (T->Right)
        resetTree(T->Right);
    T->flag = 0;
}

void freeTree(Tree T)
{
    if (T->Left)
        freeTree(T->Left);
    if (T->Right)
        freeTree(T->Right);
    free(T);
}