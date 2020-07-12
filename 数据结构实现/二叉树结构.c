#include <stdio.h>
#include <stdlib.h>

typedef struct TNode *Position;
typedef Position BinTree;
/*树节点的定义*/
struct TNode
{
    int Data;
    BinTree Left;
    BinTree Right;
};

/**
 * Name：先序遍历
 * 1.先访问根节点
 * 2.遍历左子树
 * 3.遍历右子树
*/
void PreOrderTraversal(BinTree BT)
{
    if (BT)
    {
        printf("%d", BT->Data);
        PreOrderTraversal(BT->Left);
        PreOrderTraversal(BT->Right);
    }
}

/**
 * Name：中序遍历
 * 1.遍历左子树
 * 2.访问根节点
 * 3.遍历右子树
*/
void InOrderTraversal(BinTree BT)
{
    if (BT)
    {
        InOrderTraversal(BT->Left);
        printf("%d", BT->Data);
        InOrderTraversal(BT->Right);
    }
}

/**
 * Name：后序遍历
 * 1.遍历左子树
 * 2.遍历右子树
 * 3.访问根节点
*/
void PostOrderTraversal(BinTree BT)
{
    if (BT)
    {
        InOrderTraversal(BT->Left);
        InOrderTraversal(BT->Right);
        printf("%d", BT->Data);
    }
}
