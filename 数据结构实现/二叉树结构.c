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


// void LevelorderTraversal ( BinTree BT )
// { 
//     // Queue Q; 
//     BinTree T;
 
//     if ( !BT ) return; /* 若是空树则直接返回 */
     
//     Q = CreatQueue(); /* 创建空队列Q */
//     AddQ( Q, BT );
//     while ( !IsEmpty(Q) ) {
//         T = DeleteQ( Q );
//         printf("%d ", T->Data); /* 访问取出队列的结点 */
//         if ( T->Left )   AddQ( Q, T->Left );
//         if ( T->Right )  AddQ( Q, T->Right );
//     }
// }