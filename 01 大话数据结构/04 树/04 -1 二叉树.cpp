#include<iostream>
using namespace std;


//------------------------------------�������ṹ����-----------------------------
typedef int ElemType;

typedef struct Node
{
	ElemType data;
	Node* lchid, * rchild;
}Node;

typedef Node* Tree;

//----------------------------------------�������ṹ�������--------------------------------

//----------------------------------------�����㷨-----------------------------------------

//01 ǰ�����

void preOrderTraverse(Tree t)
{
	if (t == NULL)
	{
		return;
	}
	cout << t->data << endl;
	preOrderTraverse(t->lchid);
	preOrderTraverse(t->rchild);
}
//02 �������

void inOrderTraverse(Tree t)
{
	if (t == NULL)
	{
		return;
	}

	inOrderTraverse(t->lchid);

	cout << t->data << endl;
	
	inOrderTraverse(t->rchild);
}

//03 �������
void postOrderTraverse(Tree t)
{
	if (t == NULL)
	{
		return;
	}

	postOrderTraverse(t->lchid);
	postOrderTraverse(t->rchild);
	cout << t->data << endl;

	
}
//------------------------------------------�����㷨����-----------------------------------------


//-------------------------------------ʹ��ǰ������ķ�������������--------------------------------
void createTree(Tree* t)
{
	int data;
	
	cin >> data;
	if (data == -1)
	{
		*t = NULL;
	}
	else
	{
		*t = (Tree)malloc(sizeof(Node));
		if (!*t)
		{
			exit(0);
		}
		else
		{
			(*t)->data = data;
			createTree(&(*t)->lchid);
			createTree(&(*t)->rchild);
		}
	}

	
}
//-------------------------------------ʹ��ǰ������ķ�����������������--------------------------------
int main()
{
	Tree t;
	createTree(&t);
	cout << endl;
	postOrderTraverse(t);
	return 0;
}

