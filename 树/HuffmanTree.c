#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MINDATA -10001
#define ERROR NULL
//哈夫曼树结点
typedef struct TreeNode *HuffmanTree;
struct TreeNode{
	int Weight;
	HuffmanTree Left, Right;
};
 
//最小堆
typedef struct HNode *Heap;
typedef Heap MaxHeap;
typedef Heap MinHeap;
typedef TreeNode ElementType;	//堆中每个结点都是哈夫曼树结点的类型
struct HNode {
	ElementType *Data;
	int Size;
	int Capacity;
};
 
MinHeap CreateHeap( int MaxSize ) {
	MinHeap H = (MinHeap)malloc(sizeof(struct HNode));
	//因为0位置是哨兵，所以MaxSize+1
	H->Data = (ElementType *)malloc((MaxSize+1) * sizeof(ElementType));
	H->Size = 0;
	H->Capacity = MaxSize;
	H->Data[0].Weight = MINDATA;
	H->Data[0].Left = H->Data[0].Right = NULL;
	return H;
}
 
bool IsFull( MinHeap H ){
	return (H->Size == H->Capacity);
}
 
bool Insert( MinHeap H, HuffmanTree T ) {
	//将元素X插入堆，其中H->Data[0]已经定义为哨兵
	int i;
	if( IsFull(H) ){
		printf("最小堆已满");
		return false;
	}
	i = ++H->Size; //i指向插入后堆中最后一个元素的位置
	for( ; H->Data[i / 2].Weight > T->Weight; i /= 2)
		H->Data[i] = H->Data[i / 2];
	H->Data[i] = *T;
	return true;
}
 
bool IsEmpty( MinHeap H ) {
	return (H->Size == 0);
}
 
HuffmanTree DeleteMin( MinHeap H ) {
	//从最小堆H中取出键值最小的元素，并删除一个结点；
	int Parent, Child;
	ElementType X;
	HuffmanTree MinItem = (HuffmanTree)malloc(sizeof(struct TreeNode));
	if( IsEmpty(H) ){
		printf("最小堆已空");
		return ERROR;
	}
	*MinItem = H->Data[1]; //取出根节点存放最小值
	//用最小堆最后的一个元素从根结点开始向上过滤下层结点
	X = H->Data[H->Size--];
	for( Parent = 1; 2 * Parent <= H->Size; Parent = Child){
		//Child指向左右子结点的较小者
		Child = 2 * Parent;
		if( Child != H->Size && H->Data[Child].Weight > H->Data[Child + 1].Weight )
			Child++;
 
		if( X.Weight <= H->Data[Child].Weight ) break;	//找到了合适位置，要 >=
		else  //下滤
			H->Data[Parent] = H->Data[Child];
	}
	H->Data[Parent] = X;
	return MinItem;
}
 
 
HuffmanTree CreateHuffmanNode(int weight){
	HuffmanTree T = (HuffmanTree)malloc(sizeof(struct TreeNode));
	T->Weight = weight;
	T->Left = T->Right = NULL;
	return T;
}
HuffmanTree Huffman( MinHeap H ){
	//假设权值已经在H中，且已是最小堆形式
	int i;
	HuffmanTree T;
	for(i = 1; i < H->Capacity; i++) {  //是Capacity,不是Size；Size会变(错误原因）
		//printf("size:%d\n", H->Capacity);
		T = (HuffmanTree)malloc( sizeof(struct TreeNode) );
		T->Left = DeleteMin( H );
		T->Right = DeleteMin( H );
		T->Weight = T->Left->Weight + T->Right->Weight;
		//printf("l %d r %d\n", T->Left->Weight, T->Right->Weight);
		Insert( H, T );
		//printf("%d .\n", T->Weight);
	}
	T = DeleteMin( H );   //右边是个结点，左右孩子为空，不是一棵树（错误原因）
	//printf("%d .\n", T->Weight);
	return T;
}
 
int WPL( HuffmanTree T, int Depth ) {
	if( !T->Left && !T->Right )
		return ( Depth * T->Weight );
	else 
		return ( WPL(T->Left, Depth + 1) + WPL(T->Right, Depth + 1) );
}
 
MinHeap ReadData ( int n , int *f) {
	MinHeap H = CreateHeap(n);
	HuffmanTree T = (HuffmanTree)malloc( sizeof(struct TreeNode) );
	int data, i = 0;
	while ( n-- ) {
		getchar();	//第一次接收第一行的换行符，之后接收c[i]
		getchar();	//接收空格
		scanf("%d", &data);
		f[i++] = data;
		T->Weight = data;
		T->Left = T->Right = NULL;
		Insert( H, T );
	}
	free(T);
	return H;
}
 
void traverseHuffman ( HuffmanTree T ) {
	if( T ) {
	traverseHuffman( T->Left );
	printf("%d ", T->Weight);
	traverseHuffman( T->Right );
	}
}
 
void traverseHeap ( MinHeap H ) {
	for ( int i = 1; i <= H->Size; i++ ) {
		printf("%d ", H->Data[i].Weight);
	}
}
 
void DestroyTree ( HuffmanTree T ) {
	if ( T ) {
		DestroyTree( T->Left );
		DestroyTree( T->Right );
		free(T);
	}
}
 
bool Judge ( int N, int *f, int CodeLen ) {
	HuffmanTree T = (HuffmanTree)malloc(sizeof(struct TreeNode));
	HuffmanTree Tmp;
	T = CreateHuffmanNode(0);
	char code[64];
	int flag = 1, len, tmpN = N, wpl = 0, i = 0;
	while ( N-- ) {
		Tmp = T;
		getchar();
		getchar();
		scanf("%s", code);
		getchar();
		//printf("%s\n", code);
		len = strlen( code );
		wpl += len * f[i++];  //计算带权路径长度
		if ( flag && len > tmpN - 1 ) { //如果code长度大于N - 1
			flag = 0;
			//printf("1\n len : %d", len);
		}
		else if ( flag ) {
			for ( int i = 0; i < len; i++ ) {
				if ( i != len - 1 ) { //不是code的最后一位
					if ( code[i] == '1' ) {
						if ( !Tmp->Right )
							Tmp->Right = CreateHuffmanNode(0);
						else if ( Tmp->Right->Weight == 1 ) { //如果Tmp->Right已是带权节点
							flag = 0;
							//printf("2\n");
							break;
						}
						Tmp = Tmp->Right;
					}
					else {
						if ( !Tmp->Left )
							Tmp->Left = CreateHuffmanNode(0);
						else if ( Tmp->Left->Weight == 1 ) {
							flag = 0;
							//printf("3\n");
							break;
						}
						Tmp = Tmp->Left;
					}
				}
				else {
					if ( code[i] == '1' ) {
						if ( !Tmp->Right )
							Tmp->Right = CreateHuffmanNode(1);
						else { //Tmp->Right已存在，带权重复，不带权是前缀码
							flag = 0;
							//printf("4\n");
							break;
						}
						Tmp = Tmp->Right;
						if( Tmp->Right || Tmp->Left ) { //Tmp不是叶子结点
							flag = 0;
							//printf("5\n");
							break;
						}
					}
					else {
						if ( !Tmp->Left )
							Tmp->Left = CreateHuffmanNode(1);
						else {
							flag = 0;
							//printf("6\n");
							break;
						}
						Tmp = Tmp->Left;
						if( Tmp->Right || Tmp->Left ) {
							flag = 0;
							//printf("7\n");
							break;
						}
					}
				}
			}
		}
	}
	DestroyTree( T ); //释放刚建的哈夫曼树
	if ( flag && wpl == CodeLen )
		return true;
	else
		return false;
}
 
int main(){
	int N, M, CodeLen, *f;
	scanf("%d", &N);
	f = (int*)malloc( N * sizeof(int) );
	//建立堆和哈夫曼树
	MinHeap H;
	H = ReadData( N, f );
	HuffmanTree T = Huffman( H );
	CodeLen = WPL( T, 0 );
	//判断
	scanf("%d", &M);
	getchar();
	while ( M-- ) {
		if ( Judge( N, f, CodeLen ) ) {
			printf("Yes\n");
		}
		else {
			printf("No\n");
		}
	}
	//traverseHeap(H);
	//traverseHuffman(T);
	//printf("%d", CodeLen);
	system("pause");
	return 0;
}