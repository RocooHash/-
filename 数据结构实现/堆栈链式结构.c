#include <stdio.h>
#include <stdlib.h>

#define true 1;
#define false 0;

typedef struct SNode *PtrToSNode;
struct SNode {
    int Data;
    PtrToSNode Next;
};
typedef PtrToSNode Stack;
 
Stack CreateStack( ) 
{ /* 构建一个堆栈的头结点，返回该结点指针 */
    Stack S;
 
    S = (Stack)malloc(sizeof(struct SNode));
    S->Next = NULL;
    return S;
}
 
int IsEmpty ( Stack S )
{ /* 判断堆栈S是否为空，若是返回true；否则返回false */
    return ( S->Next == NULL );
}
 
int Push( Stack S, int X )
{ /* 将元素X压入堆栈S */
    PtrToSNode TmpCell;
 
    TmpCell = (PtrToSNode)malloc(sizeof(struct SNode));
    TmpCell->Data = X;
    TmpCell->Next = S->Next;
    S->Next = TmpCell;
    return true;
}
 
int Pop( Stack S )  
{ /* 删除并返回堆栈S的栈顶元素 */
    PtrToSNode FirstCell;
    int TopElem;
 
    if( IsEmpty(S) ) {
        printf("堆栈空"); 
        return false;
    }
    else {
        FirstCell = S->Next; 
        TopElem = FirstCell->Data;
        S->Next = FirstCell->Next;
        free(FirstCell);
        return TopElem;
    }
}