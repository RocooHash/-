#include <stdio.h>
#include <stdlib.h>

void Bubble_Sort(int a[], int n)
{
    int i, j, temp;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n - 1 - i; j++)
        {
            if (a[j] > a[j + 1])
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

/*插入排序*/
void Insert_Sort(int a[], int n)
{
    int i, j, temp;
    for (i = 1; i < n; i++)
    {
        temp = a[i];
        for (j = i; j > 0 && a[j - 1] > temp; j--)
        {
            a[j] = a[j - 1];
        }
        a[j] = temp;
    }
}

/*希尔排序*/
void Shell_Sort(int a[], int N)
{
    int i, j, D, temp;
    for (D = N / 2; D > 0; D /= 2)
    {
        /*以D为步长的序列*/
        for (i = D; i < N; i++)
        {
            temp = a[i];
            for (j = i; j >= D && a[j - D] > temp; j -= D)
            {
                a[j] = a[j - D];
            }
            a[j] = temp;
        }
    }
}

/*选择排序*/
void Selection_Sort(int a[], int N)
{
    int i, j, temp, min;
    for (i = 0; i < N; i++)
    {
        min = i;
        for (j = i; j < N; j++)
        { /*找最小值*/
            if (a[j] < a[min])
            {
                min = j;
            }
        }
        temp = a[i];
        a[i] = a[min];
        a[min] = temp;
    }
}

/**
 * name: 堆排序
 * 详见 堆结构.c
*/

/* 归并排序 - 递归实现 */

/* L = 左边起始位置, R = 右边起始位置, RightEnd = 右边终点位置*/
void Merge(int A[], int TmpA[], int L, int R, int RightEnd)
{ /* 将有序的A[L]~A[R-1]和A[R]~A[RightEnd]归并成一个有序序列 */
    int LeftEnd, NumElements, Tmp;
    int i;

    LeftEnd = R - 1; /* 左边终点位置 */
    Tmp = L;         /* 有序序列的起始位置 */
    NumElements = RightEnd - L + 1;

    while (L <= LeftEnd && R <= RightEnd)
    {
        if (A[L] <= A[R])
            TmpA[Tmp++] = A[L++]; /* 将左边元素复制到TmpA */
        else
            TmpA[Tmp++] = A[R++]; /* 将右边元素复制到TmpA */
    }

    while (L <= LeftEnd)
        TmpA[Tmp++] = A[L++]; /* 直接复制左边剩下的 */
    while (R <= RightEnd)
        TmpA[Tmp++] = A[R++]; /* 直接复制右边剩下的 */

    for (i = 0; i < NumElements; i++, RightEnd--)
        A[RightEnd] = TmpA[RightEnd]; /* 将有序的TmpA[]复制回A[] */
}

void MSort(int A[], int TmpA[], int L, int RightEnd)
{ /* 核心递归排序函数 */
    int Center;

    if (L < RightEnd)
    {
        Center = (L + RightEnd) / 2;
        MSort(A, TmpA, L, Center);               /* 递归解决左边 */
        MSort(A, TmpA, Center + 1, RightEnd);    /* 递归解决右边 */
        Merge(A, TmpA, L, Center + 1, RightEnd); /* 合并两段有序序列 */
    }
}

void MergeSort(int A[], int N)
{ /* 归并排序 */
    int *TmpA;
    TmpA = (int *)malloc(N * sizeof(int));

    if (TmpA != NULL)
    {
        MSort(A, TmpA, 0, N - 1);
        free(TmpA);
    }
    else
        printf("空间不足");
}

int main()
{
    int N;
    scanf("%d", &N);
    int a[N], i;
    for(i =0 ;i<N;i++)
    {
        scanf("%d", &a[i]);
    }
    MergeSort(a, N);
    for (i = 0; i < N-1; i++)
    {
        printf("%d ", a[i]);
    }
    printf("%d",a[i]);
}

/* 归并排序 - 循环实现 */
/* 这里Merge函数在递归版本中给出 */

/* length = 当前有序子列的长度*/
void Merge_pass(int A[], int TmpA[], int N, int length)
{ /* 两两归并相邻有序子列 */
    int i, j;

    for (i = 0; i <= N - 2 * length; i += 2 * length)
        Merge(A, TmpA, i, i + length, i + 2 * length - 1);
    if (i + length < N) /* 归并最后2个子列*/
        Merge(A, TmpA, i, i + length, N - 1);
    else /* 最后只剩1个子列*/
        for (j = i; j < N; j++)
            TmpA[j] = A[j];
}

void Merge_Sort(int A[], int N)
{
    int length;
    int *TmpA;

    length = 1; /* 初始化子序列长度*/
    TmpA = malloc(N * sizeof(int));
    if (TmpA != NULL)
    {
        while (length < N)
        {
            Merge_pass(A, TmpA, N, length);
            length *= 2;
            Merge_pass(TmpA, A, N, length);
            length *= 2;
        }
        free(TmpA);
    }
    else
        printf("空间不足");
}