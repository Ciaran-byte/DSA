#include<iostream>
using namespace std;
//使用两个栈顶标志位即可。
//二者使用不同的栈底，但是公用一个栈顶
//适用于一个数据增加，另外一个数据会减少的数据类型
//---------------------------------------栈结构的定义----------------------------------------
typedef int ElemType;
const int MaxSize = 200;
typedef struct
{
	ElemType data[MaxSize];
	int top1 = -1; //栈1标志位为-1的时候说明栈1是空栈
	int top2 = MaxSize; //栈2标志为MaxSize的时候说明栈2是空栈
}Stack;

typedef int Status;
const int Error = 0;
const int OK = 1;
//--------------------------------------栈结构定义结束------------------------------------------
//--------------------------------------入栈操作------------------------------------------

Status push(Stack* s, ElemType data, int StackNum)
{
	if (s->top1 + 1 == s->top2) //栈满了
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

//--------------------------------------入栈操作结束------------------------------------------
//-----------------------------------------出栈操作----------------------------------------------

Status pop(Stack* s, int StackNum,int*data)
{
	if (StackNum == 1)
	{
		if (s->top1 == -1)//栈1是空的
		{
			return Error;
		}
		*data = s->data[s->top1];
		s->top1--;
	}
	else if (StackNum == 2)
	{
		if (s->top2 == MaxSize) //栈2是空的
		{
			return Error;
		}
		*data = s->data[s->top2];
		s->top2++;
	}
	return OK;
}

//---------------------------------------出栈操作结束-----------------------------------------

int main()
{

	return 0;

}


