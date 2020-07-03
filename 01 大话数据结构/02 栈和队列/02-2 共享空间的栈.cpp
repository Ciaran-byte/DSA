#include<iostream>
using namespace std;
//ʹ������ջ����־λ���ɡ�
//����ʹ�ò�ͬ��ջ�ף����ǹ���һ��ջ��
//������һ���������ӣ�����һ�����ݻ���ٵ���������
//---------------------------------------ջ�ṹ�Ķ���----------------------------------------
typedef int ElemType;
const int MaxSize = 200;
typedef struct
{
	ElemType data[MaxSize];
	int top1 = -1; //ջ1��־λΪ-1��ʱ��˵��ջ1�ǿ�ջ
	int top2 = MaxSize; //ջ2��־ΪMaxSize��ʱ��˵��ջ2�ǿ�ջ
}Stack;

typedef int Status;
const int Error = 0;
const int OK = 1;
//--------------------------------------ջ�ṹ�������------------------------------------------
//--------------------------------------��ջ����------------------------------------------

Status push(Stack* s, ElemType data, int StackNum)
{
	if (s->top1 + 1 == s->top2) //ջ����
	{
		return Error;
	}
	if (StackNum == 1)
	{
		s->top1++;
		s->data[s->top1] = data;
		
	}
	else if (StackNum == 2)
	{
		s->top2--;
		s->data[s->top2] = data;
	}
	return OK;
}

//--------------------------------------��ջ��������------------------------------------------
//-----------------------------------------��ջ����----------------------------------------------

Status pop(Stack* s, int StackNum,int*data)
{
	if (StackNum == 1)
	{
		if (s->top1 == -1)//ջ1�ǿյ�
		{
			return Error;
		}
		*data = s->data[s->top1];
		s->top1--;
	}
	else if (StackNum == 2)
	{
		if (s->top2 == MaxSize) //ջ2�ǿյ�
		{
			return Error;
		}
		*data = s->data[s->top2];
		s->top2++;
	}
	return OK;
}

//---------------------------------------��ջ��������-----------------------------------------

int main()
{

	return 0;

}


