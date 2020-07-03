#include<iostream>
using namespace std;
//---------------------------------------栈结构的定义----------------------------------------
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
//--------------------------------------栈结构定义结束------------------------------------------



//---------------------------------------进栈操作-----------------------------------------------
Status push(Stack* s, int data)
{
	if (s->top == MaxSize - 1)//栈满
	{
		return Error;
	}
		s->top++;
		s->data[s->top] = data;
		
		return OK;
	

}


//---------------------------------------进栈结束-----------------------------------------------

//---------------------------------------出栈操作-----------------------------------------------

Status pop(Stack* s,int *data)
{
	if (s->top == -1)//空栈，不能删除
	{
		return Error;
	}
	else
	{
		*data = s->data[s->top];
		s->top--;

	}
}
//---------------------------------------出栈操作结束-----------------------------------------
int main()
{

	return 0;

}

