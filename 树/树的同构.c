/**
 * https://pintia.cn/problem-sets/1268384564738605056/problems/1274008636207132672
*/
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10


typedef struct TNode
{
    char data;
    int left;
    int right;
} TNode;

int createBinTree(TNode T[]);
int Isomorphic(int T1, int T2);

TNode t1[MAXSIZE], t2[MAXSIZE];

int main(void)
{
    int T1, T2;
    int result;
    T1 = createBinTree(t1);
    T2 = createBinTree(t2);

    result = Isomorphic(T1, T2);
    if (result)
    {
        printf("Yes");
    }
    else
    {
        printf("No");
    }

    return 0;
}

int Isomorphic(int T1, int T2)
{
    if ((T1 == -1) && (T2 == -1))
    {
        return 1;
    }
    if (((T1 == -1) && (T2 != -1)) || (T1 != -1) && (T2 == -1))
    {
        return 0;
    }
    if (t1[T1].data != t2[T2].data)
    {
        return 0;
    }
    if ((t1[T1].left == -1) && (t2[T2].left == -1))
    {
        return Isomorphic(t1[T1].right, t2[T2].right);
    }
    if (((t1[T1].left != -1) && (t2[T2].left != -1)) && ((t1[t1[T1].left].data == t2[t2[T2].left].data)))
    {
        return (Isomorphic(t1[T1].left, t2[T2].left) && Isomorphic(t1[T1].right, t2[T2].right));
    }
    else
    {
        return (Isomorphic(t1[T1].left, t2[T2].right) && Isomorphic(t1[T1].right, t2[T2].left));
    }
}

int createBinTree(TNode T[])
{
    int i, N, Root = -1, check[MAXSIZE];
    char left, right;

    scanf("%d", &N);
    getchar();
    if (N)
    {
        for (i = 0; i < N; i++)
        {
            check[i] = 0;
        }
        for (i = 0; i < N; i++)
        {
            scanf("%c %c %c\n", &T[i].data, &left, &right);
            if (left != '-')
            {
                T[i].left = left - '0';
                check[T[i].left] = 1;
            }
            else
            {
                T[i].left = -1;
            }
            if (right != '-')
            {
                T[i].right = right - '0';
                check[T[i].right] = 1;
            }
            else
            {
                T[i].right = -1;
            }
        }
        for (i = 0; i < N; i++)
        {
            if (check[i] == 0)
            {
                Root = i;
                break;
            }
        }
    }
    return Root;
}
