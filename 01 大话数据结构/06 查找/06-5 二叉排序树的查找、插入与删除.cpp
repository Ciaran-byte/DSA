#include<iostream>
using namespace std;

//----------------------------------------------定义二叉树的结构-----------------------------------------
typedef struct TreeNode
{
	int data;
	TreeNode* lchild, *rchild;
}TreeNode;

typedef TreeNode* Tree;

const int OK = 1;
const int Error = 0;
typedef int Status;
//----------------------------------------------定义二叉树的结构结束-----------------------------------------

//-------------------------------------------------二叉树查找-----------------------------------------------

Status ResearchTree(Tree t,int Key,Tree parent,Tree* result)
{
	//t用于输入树结构
	//parent用于保存返回的result结点的父节点,初始为NULL
	//result用于保存返回结点

	if (!t)
	{
		*result = parent;
		return Error;
	}
	else if (t->data == Key)
	{
		*result = t;
		return OK;
	}
	else if (Key<t->data)
	{
		return ResearchTree(t->lchild, Key, t, result);
	}
	else
	{
		return ResearchTree(t->rchild, Key, t, result);
	}
}

//----------------------------------------------二叉树查找结束------------------------------------------


//----------------------------------------------二叉树的插入----------------------------------------

Status InsertTree(Tree* t,int Key)
{
	Tree p;
	//如果现在的树里没有这个元素才能插入
	if (ResearchTree(*t, Key, NULL, &p) == Error) 
	{


		//初始化结点
		TreeNode* s = (Tree)malloc(sizeof(TreeNode));
		if (!s)
		{
			return Error;
		}
		s->data = Key;
		s->lchild = NULL;
		s->rchild = NULL;

		//如果还没有结点，就把新建的结点当跟结点了
		if (!(*t))
		{
			*t = s;
		}

		//并且，没有这个元素的时候，p指针保存的是要插入的结点

		else
		{
			if (Key > p->data)
			{
				p->rchild = s;
			}
			else
			{
				p->lchild = s;
			}
		}
		return OK;
	}
	else //有这个元素就是插入失败
	{
		return Error;
	}

}

//------------------------------------------------二叉树插入结束--------------------------------------

//------------------------------------------------二叉树中序遍历-------------------------------------

void InOrderTraverse(Tree t)
{
	if (t == NULL)
	{
		return;
	}
	InOrderTraverse(t->lchild);
	cout << t->data<<endl;
	InOrderTraverse(t->rchild);
}


//------------------------------------------------二叉树中序遍历结束-------------------------------------

//------------------------------------------------二叉树的删除-------------------------------------------

Status DeleteNode(Tree* p) //删除一个结点
{
	TreeNode* q, * s;
	if ((*p)->lchild == NULL) //左树为空，把结点删了，右边结点放过来
	{
		q = *p;

		*p = (*p)->rchild;
		free(q);
		
	}
	else if((*p)->rchild == NULL) //右树为空，把结点删了，左边结点放过来
	{
		q = *p;

		*p = (*p)->lchild;
		free(q);
	}
	else  //要是左右结点都不为空，要找前驱或者后继结点代替这个位置
	{
		q = *p;
		s = q->lchild;
		while (s->rchild)
		{
			q = s;
			s = s->rchild;
		}

		(*p)->data = s->data;




		//把要删除的结点的数据变成找到的这个前驱结点，同时删除前驱结点
		if (q != *p)
		{
			q->rchild = s->lchild;
			free(s);
		}
		else
		{
			q->lchild = s->lchild;
			free(s);
		}
		

	}
	return OK;
	
}

Status DeleteTree(Tree* p, int Key) //删除某个元素的结点
{
	if (!(*p)) //如果树的头结点本身为空，没有删除必要，直接退出
	{
		return Error;
	}

	else if ((*p)->data == Key)
	{
		DeleteNode(p);
		return OK;
	}
	else if (Key < (*p)->data)
	{
		DeleteTree(&(*p)->lchild, Key);
	}
	else
	{
		DeleteTree(&(*p)->rchild, Key);
	}
	
}

//------------------------------------------------二叉树的删除结束--------------------------------------
int main()
{
	int a[10] = { 62,88,58,47,35,73,51,99,37,93 };
	Tree t = NULL;

	for (int i = 0; i < 10; i++)
	{
		InsertTree(&t, a[i]);
	}
	InOrderTraverse(t); //中序遍历其实就是从大到小排列
	cout << endl;
	DeleteTree(&t, 37);
	InOrderTraverse(t);
	return 0;
}

