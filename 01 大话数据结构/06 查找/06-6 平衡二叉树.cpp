#include<iostream>
using namespace std;

//------------------------------------------ƽ��������ṹ----------------------------------------------

typedef struct TreeNode
{
	int data;
	TreeNode* lchild;
	TreeNode* rchild;
	int bf;
}TreeNode;

typedef TreeNode* Tree;

//------------------------------------------ƽ��������ṹ�������----------------------------------------------

//------------------------------------------ƽ���������ת��������----------------------------------------------
void R_Rotate(Tree *p) //RR��ת
{
	Tree q = (*p)->lchild;
	(*p)->lchild = q->rchild;
	q->rchild = (*p);
	*p = q;//pָ���µĸ��ڵ�
}

void L_Rotate(Tree* p)//LL��ת
{
	Tree q = (*p)->rchild;

	(*p)->rchild = q->lchild;

	q->lchild = (*p);

	(*p) = q;
}

const int LH = 1; //���
const int EN = 0;  //ƽ��
const int RH = -1;  //�Ҹ�
//------------------------------------------ƽ���������ת�����������----------------------------------------------


//------------------------------------------ƽ�������ʧ�⴦����------------------------------------------

//����LRʧ���LLʧ������״����LRʧ��Ҫ��������ת����������������LLʧ��ֱ����������
void LeftBalance(Tree* T) //T��㲻ƽ���Ժ�ĵ���������ʱT��Ϊ���ڵ�
{
	Tree L, Lr;
	L = (*T)->lchild;

	switch (L->bf)
	{
		//LLʧ��
	case LH:
	
		//����������
		(*T)->bf = L->bf = EN;
		R_Rotate(T);
		break;
	
		
	case RH:  //LRʧ��

		//���ȵ������ڵ�͸��ڵ�����ߺ��ӵ�bfֵ
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

	

		//Ȼ����˫������
		L_Rotate(&(*T)->lchild);
		R_Rotate(T);

		break;

	}
}
//����RLʧ���RRʧ������״����RLʧ��Ҫ��������ת����������������RRʧ��ֱ����������
void RightBalance(Tree* T) //T��㲻ƽ���Ժ�ĵ���������ʱT��Ϊ���ڵ�
{
	Tree R, Rl;
	R = (*T)->rchild;

	switch (R->bf)
	{
		//RRʧ��
	case RH:

		//����������
		(*T)->bf = R->bf = EN;
		L_Rotate(T);
		break;


	case LH:  //RLʧ��

		//���ȵ������ڵ�͸��ڵ����ұߺ��ӵ�bfֵ
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



		//Ȼ����˫������
		R_Rotate(&(*T)->rchild);
		L_Rotate(T);

		break;

	}
}
//------------------------------------------ƽ�������ʧ�⴦�������------------------------------------------

//taller���������ж����Ƿ񳤸�
bool InsertAVL(Tree *t,int data,bool *taller)
{
	
	//01 �������ط�û�н�㣬���½����ڵ�
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
	else //����н�㣬�ͼ���������һ������λ��
	{
		if ((*t)->data == data)
		{
			return false; //����������ˣ��Ͳ���ʧ��
		}

		else if(data<(*t)->data) //������������
		{
			if (!InsertAVL(&(*t)->lchild, data, taller)) //û����ɹ��ͷ���false
			{
				return false;
			}
			if (*taller)//�����������
			{
				switch ((*t)->bf)
				{
				case RH://��������Ǹ��Ҹ߶��㣬������ڵ��ȸ�
					*taller = false;
					(*t)->bf = EN;
					break;
				case EN://��������ȸ߲������Ժ�����
					*taller = true;
					(*t)->bf = LH;
					break;
				case LH://�����������ߣ���Ҫ��ƽ�⴦����
					*taller = false;
					LeftBalance(t);
					break;
				}
				
			}

			



		}

		else  //������������
		{
			if (!InsertAVL(&(*t)->rchild, data, taller)) //û����ɹ��ͷ���false
			{
				return false;
			}
			if (*taller)//�����������
			{
				switch ((*t)->bf)
				{
				case LH://��������Ǹ���߶��㣬�����ҽڵ��ȸ�
					*taller = false;
					(*t)->bf = EN;
					break;
				case EN://��������ȸ߲������Ժ���Ҹ�
					*taller = true;
					(*t)->bf = RH;
					break;
				case RH://����������Ҹߣ���Ҫ��ƽ�⴦����
					*taller = false;
					RightBalance(t);
					break;
				}

			}
		}
	}

	return true; //����ɹ�
}
//------------------------------------------------�������������-------------------------------------

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


//------------------------------------------------�����������������-------------------------------------
int main()
{
	int a[10] = { 62,88,58,47,35,73,51,99,37,93 };
	Tree t = NULL;
	bool taller ;
	for (int i = 0; i < 10; i++)
	{
		InsertAVL(&t, a[i], &taller);
	}
	InOrderTraverse(t); //���������ʵ���ǴӴ�С����
	return 0;
}