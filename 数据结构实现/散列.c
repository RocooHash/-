#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXTABLESIZE 100000
typedef int ElementType; /*关键词类型用整型*/
typedef int Index;       /*散列地址类型*/
typedef Index Position;  /*数据所在位置与散列地址是同一类型*/
/*散列单元状态类型，分别对应，有合法元素、空单元、有已删除元素*/
typedef enum
{
    Legitimate,
    Empty,
    Deleted
} EntrtType;

typedef struct HashEntry Cell; /*散列表单元类型*/
struct HashEntry
{
    ElementType Data;
    EntrtType Info;
};

typedef struct TblNode *HashTable; /*散列表类型*/
struct TblNode
{
    int TableSize;
    Cell *Cells;
};

int NextPrime(int N)
{ /*返回大于N且不超过MAXTABLESIZE的最小素数*/
    int i, p = (N % 2) ? N + 2 : N + 1;

    while (p <= MAXTABLESIZE)
    {
        for (i = (int)sqrt(p); i > 2; i--)
            if (!(p % i))
                break;
        if (i == 2)
            break;
        else
            p += 2;
    }
    return p;
}

HashTable CreateTable(int TableSize)
{
    HashTable H;
    int i;

    H = (HashTable)malloc(sizeof(struct TblNode));
    H->TableSize = NextPrime(TableSize);
    H->Cells = (Cell *)malloc(sizeof(Cell) * H->TableSize);

    for (i = 0; i < H->TableSize; i++)
    {
        H->Cells[i].Info = Empty;
    }
    return H;
}

/**
 * 定义： 以增量序列正整数平方（正负），且q <= [TableSize/2] 循环试探下一个存储地址
 * 
 * PS：有定理显示：如果散列表长度是某个4k+3的素数形式，平方探测法就可以探查到整个散列表空间
*/
Position Find(HashTable H, ElementType key)
{
    Position CurrentPos, NewPos;
    int CNum = 0; /*记录冲突次数*/

    NewPos = CurrentPos = Hash(key, H->TableSize);
    /*当该位置的单元非空，并且不是要找的元素时，发生冲突*/
    while (H->Cells[NewPos].Info != Empty && H->Cells[NewPos].Data != key)
    {
        if (++CNum % 2)
        {
            NewPos = CurrentPos + (CNum + 1) *(CNum + 1)/4;
             /* 增量为+[(CNum+1)/2]^2 */
            if(NewPos >= H->TableSize)
            {
                NewPos = NewPos % H->TableSize;
            }
        }
        else
        {
            NewPos = CurrentPos - CNum % 4;
             /* 增量为-(CNum/2)^2 */
            while(NewPos < 0)
            {
                NewPos += H->TableSize;
            }
        }
        
    }
    return NewPos;
}

int Insert(HashTable H, ElementType key)
{
    Position Pos = Find(H, key);

    if (H->Cells[Pos].Info != Legitimate)
    {
        H->Cells[Pos].Info = Legitimate;
        H->Cells[Pos].Data = key;
        return 1;
    }
    else
    {
        printf("键值已存在");
        return 0;
    }
    
}