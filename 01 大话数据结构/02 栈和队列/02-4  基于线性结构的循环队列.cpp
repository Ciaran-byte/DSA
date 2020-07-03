#include<iostream>
using namespace std;
//------------------------------------------------���нṹ����----------------------------------
typedef int Status;
const int Error = 0;
const int OK = 1;

const int MaxSize = 20;
typedef int ElemType;
typedef struct
{
	ElemType data[MaxSize];
	int front ;
	int rear ;
}Queue;

//------------------------------------------------���нṹ�������----------------------------------


//------------------------------------------------���г�ʼ��----------------------------------
Status QueueInit(Queue* q)
{
	q->front = 0;
	q->rear = 0;
	return OK;
}

//------------------------------------------------���г�ʼ������----------------------------------



//------------------------------------------------����г���----------------------------------
Status QueueLength(Queue* q, int* len)
{
	*len = (q->rear - q->front + MaxSize) % MaxSize;
	return OK;
}

//------------------------------------------------����г��Ƚ���----------------------------------



//------------------------------------------------���----------------------------------

Status QueueInsert(Queue* q, ElemType data)
{
	if (((q->rear + 1) % MaxSize) == q->front) //man��
	{
		return Error;
	}
	
		q->data[q->rear] = data;
		q->rear = (q->rear + 1) % MaxSize;
	return OK;
}

//------------------------------------------------��ӽ���----------------------------------

//------------------------------------------------����----------------------------------

Status QueueDelete(Queue* q,int*data)
{
	if (q->rear == q->front)//�ն�
	{
		return Error;
	}
	*data = q->data[q->front];
	q->front = (q->front + 1) % MaxSize;
	return OK;
}
//------------------------------------------------���ӽ���----------------------------------
int main()
{


	return 0;
}

