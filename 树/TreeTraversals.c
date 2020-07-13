/**
 * 由前序和中序推出后序
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Maxsize 30
int pre[Maxsize], in[Maxsize], post[Maxsize], temp[Maxsize];

void solve(int preL, int inL, int postL, int n);

int main()
{
    int i, j, pop = -1, outpop = -1, inpop = -1, N, data;
    char a[5];
    scanf("%d", &N);
    getchar();
    if (N)
    {
        for (i = 0; i < 2 * N; i++)
        {
            scanf("%s", a);
            if (strlen(a) == 4)
            {
                scanf("%d", &data);
                getchar();
                pre[++pop] = data;
                temp[++outpop] = data;
                
            }
            else
            {
                getchar();
                data = temp[outpop--];
                in[++inpop] = data;
            }
        }
    }

    solve(0, 0, 0, N);
    for (i = 0; i < N - 1; i++)
    {
        printf("%d ", post[i]);
    }
    printf("%d", post[i]);
}

void solve(int preL, int inL, int postL, int n)
{
    int root, i, L, R;
    if (n == 0)
        return;
    if (n == 1)
    {
        post[postL] = pre[preL];
        return;
    }
    //根结点数据为pre数组第一个元素的数据
    root = pre[preL];
    //post数组最后一个元素应为根节点的数据
    post[postL + n - 1] = root;
    //在in数组找到与根节点数据相同的元素下标
    for (i = 0; i < n; i++)
        if (in[inL + i] == root)
            break;
    L = i;
    R = n - L - 1;

    solve(preL + 1, inL, postL, L);
    solve(preL + L + 1, inL + L + 1, postL + L, R);
}