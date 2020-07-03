#include<iostream>
using namespace std;

//-------------------------------------栈的定义---------------------------------------------
typedef int Status;
const int Error = 0;
const int OK = 1;

typedef int ElemType;

typedef struct
{
	ElemType data;
	StackNode* next=NULL;

}StackNode;


typedef struct
{
	StackNode* top=NULL;
	int count = 0;
}LinkStack;
//-------------------------------------栈的定义结束---------------------------------------------

//------------------------------------入栈操作---------------------------------------------

Status push(LinkStack* s, int data)
{
	StackNode* p = (StackNode*)malloc(sizeof(StackNode));

	p->data = data;
	p->next = s->top;
	s->top = p;
	s->count++;
	return OK;

}

//------------------------------------入栈操作结束------------------------------------------


//--------------------------------------------出栈操作---------------------------------------

Status pop(LinkStack* s, int* data)
{
	if (s->top == NULL)
	{
		return Error;
	}

	*data = s->top->data;
	StackNode* p = s->top;
	s->top = p->next;
	free(p);
	s->count--;
	return OK;
}

//--------------------------------------------出栈操作结束---------------------------------------



int main()
{

	return 0;
}


