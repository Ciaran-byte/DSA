#include<iostream>
using namespace std;
//------------------------------------------------队列结构定义----------------------------------
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

//------------------------------------------------队列结构定义结束----------------------------------


//------------------------------------------------队列初始化----------------------------------
Status QueueInit(Queue* q)
{
	q->front = 0;
	q->rear = 0;
	return OK;
}

//------------------------------------------------队列初始化结束----------------------------------



//------------------------------------------------求队列长度----------------------------------
Status QueueLength(Queue* q, int* len)
{
	*len = (q->rear - q->front + MaxSize) % MaxSize;
	return OK;
}

//------------------------------------------------求队列长度结束----------------------------------



//------------------------------------------------入队----------------------------------

Status QueueInsert(Queue* q, ElemType data)
{
	if (((q->rear + 1) % MaxSize) == q->front) //man队
	{
		return Error;
	}
	
		q->data[q->rear] = data;
		q->rear = (q->rear + 1) % MaxSize;
	return OK;
}

//------------------------------------------------入队结束----------------------------------

//------------------------------------------------出队----------------------------------

Status QueueDelete(Queue* q,int*data)
{
	if (q->rear == q->front)//空对
	{
		return Error;
	}
	*data = q->data[q->front];
	q->front = (q->front + 1) % MaxSize;
	return OK;
}
//------------------------------------------------出队结束----------------------------------
int main()
{


	return 0;
}

