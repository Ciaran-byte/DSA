#include<iostream>
using namespace std;


//--------------------------------------------------���������----------------------------------------
typedef enum{Link,Thread}PointerTag;
typedef int ElemType;
//Link��ʾ�������ڵ�
//Thread��ʾǰ�����ߺ����ı�־


typedef struct Node
{
	ElemType data;
	Node* lchild;
	Node* rchild;
	PointerTag LTag;
	PointerTag RTag;
}Node,*Tree;
//----------------------------------------------�������������-----------------------------------------

//-------------------------------------------�����������������������������-----------------------------
Node* pre = NULL;
void InThreading(Tree p)
{
	
	if (p)
	{
		
		InThreading(p->lchild);
		if (!p->lchild)
		{
			p->LTag = Thread; //����ǰ������־
			p->lchild = pre;
		}
		else
		{
			p->LTag = Link; //������������־
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
//--------------------------------���������������������������������-----------------------------



int main()
{

	return 0;
}


