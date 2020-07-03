#include<iostream>
#include<ctime>
using namespace std;


//--------------------------------------定义单链表-----------------------------------------------
typedef int ElemType;
typedef struct Node
{
	ElemType data;
	Node* next=NULL;
}Node;
//--------------------------------------定义单链表结束-----------------------------------------------
//---------------------------------------定义需要的返回值--------------------------

typedef int Status;
const int OK = 1;
const int Error = 0;

//---------------------------------------定义需要的返回值结束--------------------------



//---------------------------------------定义查询操作-------------------------------

Status GetElem(Node n, int i, ElemType* e)
{
	int j = 1;
	//n是头结点
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

//---------------------------------------定义查询操作结束-------------------------------


//---------------------------------------定义插入操作-------------------------------
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
//---------------------------------------定义插入操作结束-------------------------------


//---------------------------------------定义删除操作-------------------------------
//自己的写法
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

//书上的写法
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

//---------------------------------------定义删除操作结束-------------------------------


//---------------------------------------定义整个表创建操作-------------------------------
void ListCreateHead(Node* L, int i)//头插法建表
{
	srand(time(0));
	
	
	L = (Node*)malloc(sizeof(Node));
	if (L == NULL)
	{
		cerr << "分配内存失败！" << endl;
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
				cerr << "分配内存失败！" << endl;
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
void ListCreateHeap(Node* L, int i)//尾插法建表
{
	srand(time(0));
	Node* p = L;
	if (p == NULL)
	{
		cerr << "分配内存失败！" << endl;
		return;
	}
	else
	{
		for (int j = 0; j < i; j++)
		{
			Node* q = (Node*)malloc(sizeof(Node));
			if (q == NULL)
			{
				cerr << "分配内存失败！" << endl;
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
//---------------------------------------定义整表创建操作结束-------------------------------

//---------------------------------------定义整个表删除操作-------------------------------
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
//---------------------------------------定义整表删除操作结束-------------------------------
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

