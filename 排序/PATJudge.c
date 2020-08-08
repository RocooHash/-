/**
 * name:10-排序5 PAT Judge
 * 
 * 存在问题
*/
#include <stdio.h>
#include <stdlib.h>

int judge[6] = {0};

typedef struct USER
{
    int id;
    int total;
    int point[6];
    int complete;
} userInfo;

userInfo *users;
void initUser(int n);
void solve(int n, int k, int m);
int cmpfunc(const void *a, const void *b);
int isFull(userInfo user, int k);

int main()
{
    int n, k, m, i, j, LastScore,Rank = 1;
    scanf("%d %d %d", &n, &k, &m);
    for (i = 1; i <= k; i++)
    {
        scanf("%d", &judge[i]);
    }
    initUser(n);
    solve(n, k, m);
    qsort(users, n + 1, sizeof(struct USER), cmpfunc);
    LastScore = users[0].total;
    for (i = 0; i < n; i++)
    {
        if (isFull(users[i], k))
        {
            if(users[i].total < LastScore)
            {
                Rank++;
                LastScore = users[i].total;
            }
            printf("%d %05d %d", Rank, users[i].id, users[i].total);
            for (j = 1; j <= k; j++)
            {
                if (users[i].point[j] >= 0)
                {
                    printf(" %d", users[i].point[j]);
                }
                else
                {
                    printf(" -");
                }
            }
            printf("\n");
        }
    }

    return 0;
}

void initUser(int n)
{
    users = (userInfo *)malloc(sizeof(struct USER) * (n + 1));

    int i, j;
    for (i = 1; i <= n; i++)
    {
        users[i].id = i;
        users[i].total = 0;
        users[i].complete = 0;
        for (j = 1; j <= 5; j++)
        {
            users[i].point[j] = -2;
        }
    }
    users[0].total = -1;
}

void solve(int n, int k, int m)
{
    int id, p_id, score, i, j;
    for (i = 0; i < m; i++)
    {
        scanf("%d %d %d", &id, &p_id, &score);
        if (users[id].point[p_id] < score)
        {
            if (score == -1)
            {
                users[id].point[p_id] = -1;
            }
            else
            {
                users[id].point[p_id] = score;
                if (score == judge[p_id] && users[id].point[p_id] != judge[p_id])
                {
                    users[id].complete++;
                }
            }
        }
    }

    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= k; j++)
        {
            if (users[i].point[j] < 0)
            {
                continue;
            }
            users[i].total += users[i].point[j];
        }
    }
}

int cmpfunc(const void *a, const void *b)
{
    userInfo *A = (userInfo *)a, *B = (userInfo *)b;
    if (A->total < B->total)
    {
        return 1;
    }
    if (A->total > B->total)
    {
        return -1;
    }
    if (A->total == B->total)
    {
        if (A->complete < B->complete)
        {
            return 1;
        }
        else if (A->complete > B->complete)
        {
            return -1;
        }
        else
        {
            if (A->id < B->id)
            {
                return -1;
            }
            else
            {
                return 1;
            }
        }
    }
}

int isFull(userInfo user, int k)
{
    if (user.total > 0)
    {
        return 1;
    }
    int i;
    if (user.total < 0)
    {
        return 0;
    }
    for (i = 1; i <= k; i++)
    {
        if (user.point[i] > -1)
        {
            return 1;
        }
    }
    return 0;
}