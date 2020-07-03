#include<iostream>
#include<ctime>
using namespace std;


//--------------------------------------���嵥����-----------------------------------------------
typedef int ElemType;
typedef struct Node
{
	ElemType data;
	Node* next=NULL;
}Node;
//--------------------------------------���嵥�������-----------------------------------------------
//---------------------------------------������Ҫ�ķ���ֵ--------------------------

typedef int Status;
const int OK = 1;
const int Error = 0;

//---------------------------------------������Ҫ�ķ���ֵ����--------------------------



//---------------------------------------�����ѯ����-------------------------------

Status GetElem(Node n, int i, ElemType* e)
{
	int j = 1;
	//n��ͷ���
	Node* p = n.next;

	
	while (p && j < i)
	{
		p = p->next;
		j++;
	}
	if (!p || i < 1)
	{
		return Error;
	}
	*e = p->data;
	return OK;

}

//---------------------------------------�����ѯ��������-------------------------------


//---------------------------------------����������-------------------------------
Status ListInsert(Node *L, int i, ElemType e)
{
	int j = 1;
	Node *q = L;
	while (q&&j<i)
	{
		q = q->next;
		j++;
	}

	if (!q || i < 1)
	{
		return Error;
	}
	Node* p = (Node*)malloc(sizeof(Node));
	if (p == NULL)
	{
		return Error;
	}
	else
	{
		p->data = e;
		p->next = q->next;
		q->next = p;
	}
	

	return OK;



}
//---------------------------------------��������������-------------------------------


//---------------------------------------����ɾ������-------------------------------
//�Լ���д��
Status ListDelete1(Node* L, int i)
{
	int j = 1;
	Node* p = L->next;
	Node* q = L;
	while (p && j < i)
	{
		q = p;
		p = p->next;
		j++;
	}
	if (!p || i < 1)
	{
		return Error;
	}
	q->next = p->next;
	free(p);
	return OK;
}

//���ϵ�д��
Status ListDelete(Node* L, int i)
{
	int j = 1;
	Node* p = L;
	
	while (p->next && j < i)
	{
		
		p = p->next;
		j++;
	}
	if (!p->next || i < 1)
	{
		return Error;
	}
	Node* q = p->next;
	p->next = q->next;
	free(q);
	return OK;
}

//---------------------------------------����ɾ����������-------------------------------


//---------------------------------------����������������-------------------------------
void ListCreateHead(Node* L, int i)//ͷ�巨����
{
	srand(time(0));
	
	
	L = (Node*)malloc(sizeof(Node));
	if (L == NULL)
	{
		cerr << "�����ڴ�ʧ�ܣ�" << endl;
		return;
	}
	else
	{
		L->next = NULL;
		for (int j = 0; j < i; j++)
		{
			Node* p = (Node*)malloc(sizeof(Node));
			if (p == NULL)
			{
				cerr << "�����ڴ�ʧ�ܣ�" << endl;
				return;
			}
			else
			{
				int num = rand() % 100;
				p->data = num;
				p->next = NULL;
				L->next = p;
			}
			

		}
	}
	

}
void ListCreateHeap(Node* L, int i)//β�巨����
{
	srand(time(0));
	Node* p = L;
	if (p == NULL)
	{
		cerr << "�����ڴ�ʧ�ܣ�" << endl;
		return;
	}
	else
	{
		for (int j = 0; j < i; j++)
		{
			Node* q = (Node*)malloc(sizeof(Node));
			if (q == NULL)
			{
				cerr << "�����ڴ�ʧ�ܣ�" << endl;
				return;
			}
			else
			{
				int num = rand() % 100;
				q->data = num;
				q->next = NULL;
				p->next = q;
				p = p->next;
			}
			
		}
	}
	

}
//---------------------------------------������������������-------------------------------

//---------------------------------------����������ɾ������-------------------------------
void ListClear(Node* L)
{
	Node* q = L->next;
	while (q)
	{
		Node* p = q->next;
		free(q);
		q = p;

	}
	L->next = NULL;


}
//---------------------------------------��������ɾ����������-------------------------------
int main()
{
	Node p;
	ListCreateHeap(&p, 10);
	for (int i = 0; i < 10; i++)
	{
		int m;
		GetElem(p, i + 1, &m);
		cout << m << endl;
	}
	ListClear(&p);

	return 0;
}

