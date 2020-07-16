/*url:https://pintia.cn/problem-sets/1268384564738605056/problems/1278908289143574529*/

#include <stdio.h>
#include <stdlib.h>

int* init(int *net, int n);
int findRoot(int *net, int n);
void unionSet(int *net, int n, int m);
void insert(int *net);
void check(int* net);
void print_state(int* net, int n);

int main(void)
{
    int *net;
    int n;
    char x;

    scanf("%d", &n);
    net = init(net, n);
    
    do
    {
        getchar();
        scanf("%c", &x);
        switch (x)
        {
            
        case 'S':
        {
            print_state(net, n);
            break;
        }
        case 'I':
        {
            insert(net);
            break;
        }
        case 'C':
        {
            check(net);
            break;
        }
        }
    } while (x != 'S');
}

int* init(int *net, int n)
{
    int i;

    net = (int *)malloc((n + 1) * sizeof(int));
    for (i = 1; i <= n; i++)
    {
        net[i] = -1;
    }
    return net;
}

int findRoot(int *net, int n)
{
    if (net[n] < 0)
    {
        return n;
    }
    return net[n]
     = findRoot(net, net[n]);
}

void unionSet(int *net, int n, int m)
{
    int Root1, Root2;
    Root1 = findRoot(net, n);
    Root2 = findRoot(net, m);
    if (Root1 != Root2)
    {
        if (net[Root1] == net[Root2])
        {
            net[Root2] = Root1;
            net[Root1]--;
        }
        else if (net[Root1] < net[Root2])
        {
            net[Root2] = Root1;
        }
        else
        {
            net[Root1] = Root2;
        }
    }
}

void insert(int *net)
{
    int n, m;
    scanf("%d %d", &n, &m);

    unionSet(net, n, m);
}

void check(int* net)
{
    int n, m, Root1, Root2;
    scanf("%d %d", &n, &m);
    Root1 = findRoot(net, n);
    Root2 = findRoot(net, m);

    if(Root1 == Root2)
    {
        printf("yes\n");
    }
    else 
    {
        printf("no\n");
    }
}

void print_state(int* net, int n)
{
    int i, state = 0, result = 0;
    for(i =1;i<=n;i++)
    {
        if(net[i] == -1)
        {
            state = 1;
        }
        if(net[i] < 0)
        {
            result++;
        }
    }
    if(state == 1)
    {
        printf("There are %d components.", result);
    }
    else
    {
        printf("The network is connected.");
    }
    
}