#include<iostream>
using namespace std;

//----------------------------------------------����������Ľṹ-----------------------------------------
typedef struct TreeNode
{
	int data;
	TreeNode* lchild, *rchild;
}TreeNode;

typedef TreeNode* Tree;

const int OK = 1;
const int Error = 0;
typedef int Status;
//----------------------------------------------����������Ľṹ����-----------------------------------------

//-------------------------------------------------����������-----------------------------------------------

Status ResearchTree(Tree t,int Key,Tree parent,Tree* result)
{
	//t�����������ṹ
	//parent���ڱ��淵�ص�result���ĸ��ڵ�,��ʼΪNULL
	//result���ڱ��淵�ؽ��

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

//----------------------------------------------���������ҽ���------------------------------------------


//----------------------------------------------�������Ĳ���----------------------------------------

Status InsertTree(Tree* t,int Key)
{
	Tree p;
	//������ڵ�����û�����Ԫ�ز��ܲ���
	if (ResearchTree(*t, Key, NULL, &p) == Error) 
	{


		//��ʼ�����
		TreeNode* s = (Tree)malloc(sizeof(TreeNode));
		if (!s)
		{
			return Error;
		}
		s->data = Key;
		s->lchild = NULL;
		s->rchild = NULL;

		//�����û�н�㣬�Ͱ��½��Ľ�㵱�������
		if (!(*t))
		{
			*t = s;
		}

		//���ң�û�����Ԫ�ص�ʱ��pָ�뱣�����Ҫ����Ľ��

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
	else //�����Ԫ�ؾ��ǲ���ʧ��
	{
		return Error;
	}

}

//------------------------------------------------�������������--------------------------------------

//------------------------------------------------�������������-------------------------------------

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


//------------------------------------------------�����������������-------------------------------------

//------------------------------------------------��������ɾ��-------------------------------------------

Status DeleteNode(Tree* p) //ɾ��һ�����
{
	TreeNode* q, * s;
	if ((*p)->lchild == NULL) //����Ϊ�գ��ѽ��ɾ�ˣ��ұ߽��Ź���
	{
		q = *p;

		*p = (*p)->rchild;
		free(q);
		
	}
	else if((*p)->rchild == NULL) //����Ϊ�գ��ѽ��ɾ�ˣ���߽��Ź���
	{
		q = *p;

		*p = (*p)->lchild;
		free(q);
	}
	else  //Ҫ�����ҽ�㶼��Ϊ�գ�Ҫ��ǰ�����ߺ�̽��������λ��
	{
		q = *p;
		s = q->lchild;
		while (s->rchild)
		{
			q = s;
			s = s->rchild;
		}

		(*p)->data = s->data;




		//��Ҫɾ���Ľ������ݱ���ҵ������ǰ����㣬ͬʱɾ��ǰ�����
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

Status DeleteTree(Tree* p, int Key) //ɾ��ĳ��Ԫ�صĽ��
{
	if (!(*p)) //�������ͷ��㱾��Ϊ�գ�û��ɾ����Ҫ��ֱ���˳�
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

//------------------------------------------------��������ɾ������--------------------------------------
int main()
{
	int a[10] = { 62,88,58,47,35,73,51,99,37,93 };
	Tree t = NULL;

	for (int i = 0; i < 10; i++)
	{
		InsertTree(&t, a[i]);
	}
	InOrderTraverse(t); //���������ʵ���ǴӴ�С����
	cout << endl;
	DeleteTree(&t, 37);
	InOrderTraverse(t);
	return 0;
}

