#include<iostream>
using namespace std;
//---------------------------------------ջ�ṹ�Ķ���----------------------------------------
typedef int ElemType;
const int MaxSize = 200;
typedef struct
{
	ElemType data[MaxSize];
	int top=-1;
}Stack;

typedef int Status;
const int Error = 0;
const int OK = 1;
//--------------------------------------ջ�ṹ�������------------------------------------------



//---------------------------------------��ջ����-----------------------------------------------
Status push(Stack* s, int data)
{
	if (s->top == MaxSize - 1)//ջ��
	{
		return Error;
	}
		s->top++;
		s->data[s->top] = data;
		
		return OK;
	

}


//---------------------------------------��ջ����-----------------------------------------------

//---------------------------------------��ջ����-----------------------------------------------

Status pop(Stack* s,int *data)
{
	if (s->top == -1)//��ջ������ɾ��
	{
		return Error;
	}
	else
	{
		*data = s->data[s->top];
		s->top--;

	}
}
//---------------------------------------��ջ��������-----------------------------------------
int main()
{

	return 0;

}

