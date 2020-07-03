#include<iostream>
using namespace std;

//------------------------------------------平衡二叉树结构----------------------------------------------

typedef struct TreeNode
{
	int data;
	TreeNode* lchild;
	TreeNode* rchild;
	int bf;
}TreeNode;

typedef TreeNode* Tree;

//------------------------------------------平衡二叉树结构定义结束----------------------------------------------

//------------------------------------------平衡二叉树旋转操作定义----------------------------------------------
void R_Rotate(Tree *p) //RR旋转
{
	Tree q = (*p)->lchild;
	(*p)->lchild = q->rchild;
	q->rchild = (*p);
	*p = q;//p指向新的根节点
}

void L_Rotate(Tree* p)//LL旋转
{
	Tree q = (*p)->rchild;

	(*p)->rchild = q->lchild;

	q->lchild = (*p);

	(*p) = q;
}

const int LH = 1; //左高
const int EN = 0;  //平衡
const int RH = -1;  //右高
//------------------------------------------平衡二叉树旋转操作定义结束----------------------------------------------


//------------------------------------------平衡二叉树失衡处理定义------------------------------------------

//处理LR失衡和LL失衡两种状况。LR失衡要做两次旋转，先左旋再右旋；LL失衡直接右旋即可
void LeftBalance(Tree* T) //T结点不平衡以后的调整。结束时T成为根节点
{
	Tree L, Lr;
	L = (*T)->lchild;

	switch (L->bf)
	{
		//LL失衡
	case LH:
	
		//简单右旋即可
		(*T)->bf = L->bf = EN;
		R_Rotate(T);
		break;
	
		
	case RH:  //LR失衡

		//首先调整根节点和根节点在左边孩子的bf值
		Lr = L->rchild;
		switch (Lr->bf)
		{
		case LH:
			L->bf = RH;
			(*T)->bf = EN;

		/*	L->bf = EN;
			(*T)->bf = RH;*/
			
			break;
		case EN:
			(*T)->bf = L->bf = EN;
			break;
		case RH:
			(*T)->bf = LH;
			L->bf = EN;

			/*(*T)->bf = EN;
			L->bf = LH;*/

		
			break;
		}

	

		//然后做双旋处理
		L_Rotate(&(*T)->lchild);
		R_Rotate(T);

		break;

	}
}
//处理RL失衡和RR失衡两种状况。RL失衡要做两次旋转，先右旋再左旋；RR失衡直接左旋即可
void RightBalance(Tree* T) //T结点不平衡以后的调整。结束时T成为根节点
{
	Tree R, Rl;
	R = (*T)->rchild;

	switch (R->bf)
	{
		//RR失衡
	case RH:

		//简单左旋即可
		(*T)->bf = R->bf = EN;
		L_Rotate(T);
		break;


	case LH:  //RL失衡

		//首先调整根节点和根节点在右边孩子的bf值
		Rl = R->lchild;
		switch (Rl->bf)
		{
		case RH:
			R->bf = LH;
			(*T)->bf = EN;


		/*	R->bf = EN;
			(*T)->bf = LH;*/
		
			break;
		case EN:
			(*T)->bf = R->bf = EN;
			break;
		case LH:
			(*T)->bf = RH;
			R->bf = EN;

		/*	(*T)->bf = EN;
			R->bf = RH;*/
			
			break;
		}



		//然后做双旋处理
		R_Rotate(&(*T)->rchild);
		L_Rotate(T);

		break;

	}
}
//------------------------------------------平衡二叉树失衡处理定义结束------------------------------------------

//taller变量用于判断树是否长高
bool InsertAVL(Tree *t,int data,bool *taller)
{
	
	//01 如果这个地方没有结点，就新建根节点
	if (!(*t))
	{
		
		*t = (Tree)malloc(sizeof(TreeNode));
		
		if (!(*t))
		{
			
			exit(-1);
		}
		
		(*t)->lchild = NULL;
		(*t)->rchild = NULL;
		
		(*t)->data = data;
		
		(*t)->bf = EN;
		
		
		(*taller) = true;
	
		
		
		
	}
	else //如果有结点，就继续搜索下一个插入位置
	{
		if ((*t)->data == data)
		{
			return false; //有这个数据了，就插入失败
		}

		else if(data<(*t)->data) //往左树继续找
		{
			if (!InsertAVL(&(*t)->lchild, data, taller)) //没插入成功就返回false
			{
				return false;
			}
			if (*taller)//如果树长高了
			{
				switch ((*t)->bf)
				{
				case RH://如果本身是个右高顶点，插入左节点会等高
					*taller = false;
					(*t)->bf = EN;
					break;
				case EN://如果本来等高插入结点以后会左高
					*taller = true;
					(*t)->bf = LH;
					break;
				case LH://如果本来就左高，需要做平衡处理了
					*taller = false;
					LeftBalance(t);
					break;
				}
				
			}

			



		}

		else  //往右树继续找
		{
			if (!InsertAVL(&(*t)->rchild, data, taller)) //没插入成功就返回false
			{
				return false;
			}
			if (*taller)//如果树长高了
			{
				switch ((*t)->bf)
				{
				case LH://如果本身是个左高顶点，插入右节点会等高
					*taller = false;
					(*t)->bf = EN;
					break;
				case EN://如果本来等高插入结点以后会右高
					*taller = true;
					(*t)->bf = RH;
					break;
				case RH://如果本来就右高，需要做平衡处理了
					*taller = false;
					RightBalance(t);
					break;
				}

			}
		}
	}

	return true; //插入成功
}
//------------------------------------------------二叉树中序遍历-------------------------------------

void InOrderTraverse(Tree t)
{
	if (t == NULL)
	{
		return;
	}
	InOrderTraverse(t->lchild);
	cout << t->data << endl;
	InOrderTraverse(t->rchild);
}


//------------------------------------------------二叉树中序遍历结束-------------------------------------
int main()
{
	int a[10] = { 62,88,58,47,35,73,51,99,37,93 };
	Tree t = NULL;
	bool taller ;
	for (int i = 0; i < 10; i++)
	{
		InsertAVL(&t, a[i], &taller);
	}
	InOrderTraverse(t); //中序遍历其实就是从大到小排列
	return 0;
}