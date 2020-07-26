#include <stdio.h>
#include <stdlib.h>
#define MINDATA -10001
#define false 0
#define true 1

/*哈夫曼树结构*/
typedef struct TreeNode *HuffmanTree;
struct TreeNode
{
    int Weight;
    HuffmanTree Left, Right;
};

/*最小堆结构*/
typedef struct TreeNode *ElementType;
typedef struct HNode *Heap;
struct HNode
{
    ElementType *Data;
    int size;
    int Capacity;
};
typedef Heap MinHeap;

MinHeap CreateHeap(int Size)
{
    MinHeap H = (MinHeap)malloc(sizeof(struct HNode));
    H->Data = (ElementType *)malloc(sizeof(ElementType) * (Size + 1));
    H->size = 0;
    H->Capacity = Size;
    H->Data[0]->Weight = MINDATA;
    H->Data[0]->Left = H->Data[0]->Right = NULL;

    return H;
}

int isFull(MinHeap H)
{
    return (H->size == H->Capacity);
}

int insert(MinHeap H, ElementType x)
{
    int i;

    if (isFull(H))
    {
        print("MinHeap is Full");
        return false;
    }
    i = ++H->size;
    for (; H->Data[i / 2]->Weight > x->Weight; i = i / 2)
    {
        H->Data[i] = H->Data[i / 2];
    }
    H->Data[i] = x;
    return true;
}

int IsEmpty(MinHeap H)
{
    return H->size == 0;
}

ElementType deleteMin(MinHeap H)
{
    int Parent, Child;

    if (IsEmpty(H))
    {
        printf("MinHeap is Empty");
        return NULL;
    }

    ElementType MinItem = H->Data[1];
    ElementType x = H->Data[H->size--];
    for (Parent = 1; Parent*2< )
}