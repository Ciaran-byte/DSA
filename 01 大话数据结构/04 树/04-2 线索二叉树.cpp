#include<iostream>
using namespace std;


//--------------------------------------------------定义二叉树----------------------------------------
typedef enum{Link,Thread}PointerTag;
typedef int ElemType;
//Link表示左右树节点
//Thread表示前驱或者后驱的标志


typedef struct Node
{
	ElemType data;
	Node* lchild;
	Node* rchild;
	PointerTag LTag;
	PointerTag RTag;
}Node,*Tree;
//----------------------------------------------定义二叉树结束-----------------------------------------

//-------------------------------------------在中序遍历过程中生成线索二叉树-----------------------------
Node* pre = NULL;
void InThreading(Tree p)
{
	
	if (p)
	{
		
		InThreading(p->lchild);
		if (!p->lchild)
		{
			p->LTag = Thread; //加入前后驱标志
			p->lchild = pre;
		}
		else
		{
			p->LTag = Link; //加入左右树标志
		}

		
		if (pre && !pre->rchild)
		{
			pre->RTag = Thread;
			pre->rchild = p;
		}
		if (pre && pre->rchild)
		{
			pre->RTag = Link;

		}
		pre = p;
		InThreading(p->rchild);
	}
}
//--------------------------------在中序遍历过程中生成线索二叉树结束-----------------------------



int main()
{

	return 0;
}


