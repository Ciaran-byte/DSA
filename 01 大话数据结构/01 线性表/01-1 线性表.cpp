#include<iostream>
using namespace std;

const int MaxSize = 20;
//--------------------------------------定义基本链表的结构--------------------------------
typedef int ElemType;  
typedef struct
{
	ElemType data[MaxSize] = { 0 };
	int length=0;
}SqList;
//--------------------------------------定义基本链表的结构结束--------------------------------

//--------------------------------------获取元素操作---------------------------------------

const int Error = 0;
const int OK = 1;
typedef int status;

status GetElem(SqList L, int i, ElemType* e)
{
	if (i<1 || i>L.length)
	{
		return Error;
	}
	*e = (L.data)[i - 1];
	return OK;
}

//--------------------------------------获取元素操作结束---------------------------------------



//--------------------------------------插入操作---------------------------------------
status ListInsert(SqList* L, int i, ElemType e)
{
	if (L->length == MaxSize) //表满了
	{
		return Error;
	}
	if (i<1 || i>L->length + 1) //插入位置不合理
	{
		return Error;
	}

	if (i <= L->length)
	{
		for (int j = L->length-1;j>=i-1;j--)
		{
			L->data[j + 1] = L->data[j];
		}
		
	}
	L->data[i-1] = e;
	L->length++;
	return OK;
}


//--------------------------------------插入操作结束---------------------------------------

//--------------------------------------删除操作-------------------------------------------
status ListIDelete(SqList* L, int i)
{
	if (L->length == 0) //表空了
	{
		return Error;
	}
	if (i<1 || i>L->length ) //删除位置不合理
	{
		return Error;
	}

	for (int j = i; j < L->length; j++)
	{
		L->data[i - 1] = L->data[i];
	}
	L->length--;
	return OK;
}

//--------------------------------------删除操作结束-------------------------------------------
int main()
{
	//线性表定义
	SqList l;

	//插入值
	ListInsert(&l, 1, 5);
	int m;

	//读取值
	GetElem(l, 1, &m);
	cout << m << endl;

	//删除值
	ListIDelete(&l, 1);
	
	return 0;
}