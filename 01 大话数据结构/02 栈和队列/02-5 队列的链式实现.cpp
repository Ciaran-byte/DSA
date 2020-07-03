#include<iostream>
using namespace std;

//----------------------------------��ʽ���еĶ���--------------------------------
typedef int ElemType;

typedef int Status;
const int OK = 0;
const int Error = 1;


typedef struct
{
	ElemType data;
	Node* next;
}Node;
typedef struct
{
	Node* rear, *front;
}Queue;


//----------------------------------��ʽ���еĶ������--------------------------------

Status InitQueue(Queue* q)
{
	
	Node* p = (Node*)malloc(sizeof(Node));
	if (!p )
	{
		return Error;
	}
	p->next = NULL;
	q->rear = q->front = p;
}

//----------------------------------���--------------------------------

Status EnQuene(Queue* q, int data)
{
	
	
		Node* p = (Node*)malloc(sizeof(Node));
		if (!p)
		{
			return Error;
		}
		p->data = data;
		p->next = NULL;

		q->rear->next = p;
		q->rear = p;
	
	return OK;
}
//----------------------------------��ӽ���--------------------------------

//----------------------------------����--------------------------------
Status DeQuene(Queue* q, int* data)
{
	if (q->front == q->rear)//�ն�
	{
		return Error;
	}

	*data = *q->front->next->data;
	Node* p = *q->front->next;
	*q->front->next = p->next;

	if (p == q->rear)
	{
		q->rear = q->front;
	}
	free(p);
	return OK;
}

//----------------------------------���ӽ���--------------------------------
int main()
{

	return 0;
}

