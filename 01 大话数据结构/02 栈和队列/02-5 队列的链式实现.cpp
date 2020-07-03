#include<iostream>
using namespace std;

//----------------------------------链式队列的定义--------------------------------
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


//----------------------------------链式队列的定义结束--------------------------------

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

//----------------------------------入队--------------------------------

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
//----------------------------------入队结束--------------------------------

//----------------------------------出队--------------------------------
Status DeQuene(Queue* q, int* data)
{
	if (q->front == q->rear)//空队
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

//----------------------------------出队结束--------------------------------
int main()
{

	return 0;
}

