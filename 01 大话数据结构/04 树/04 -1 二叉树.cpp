#include<iostream>
using namespace std;


//------------------------------------二叉树结构定义-----------------------------
typedef int ElemType;

typedef struct Node
{
	ElemType data;
	Node* lchid, * rchild;
}Node;

typedef Node* Tree;

//----------------------------------------二叉树结构定义结束--------------------------------

//----------------------------------------遍历算法-----------------------------------------

//01 前序遍历

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
//02 中序遍历

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

//03 后序遍历
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
//------------------------------------------遍历算法结束-----------------------------------------


//-------------------------------------使用前序遍历的方法构建二叉树--------------------------------
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
//-------------------------------------使用前序遍历的方法构建二叉树结束--------------------------------
int main()
{
	Tree t;
	createTree(&t);
	cout << endl;
	postOrderTraverse(t);
	return 0;
}

