#include<iostream>
using namespace std;


const int MaxSize = 20;
typedef int ElemType ;
typedef struct
{
	ElemType data[MaxSize];
	int length = 0;
}SqList;

typedef int Status;
const int OK = 1;
const int Error = 0;

Status GetElem(SqList L, int i, ElemType* e)
{
	if (i<1||i > L.length)
	{
		return Error;
	}
	*e = L.data[i - 1];
	return OK;
}

Status ListInsert(SqList* L, int i, ElemType e)
{
	if (L->length == MaxSize)
	{
		return Error;
	}
	if (i<1 || i>L->length + 1)
	{
		return Error;
	}
	for (int j = L->length;j>=i;j--)
	{
		L->data[j] = L->data[j - 1];
	}
	L->data[i - 1] = e;
	L->length++;
	return OK;
}

Status ListDelete(SqList* L, int i)
{
	if (L->length == 0)
	{
		return Error;
	}
	if (i<1 || i>L->length)
	{
		return Error;
	}
	for (int j = i; j < L->length; j++)
	{
		L->data[j - 1] = L->data[j];
	}
	L->length--;
	return OK;
}
int main()
{
	SqList L;
	cout << "这是一个线性表" << endl;
	cout << "[0]插入数据" << endl;
	cout << "[1]删除数据" << endl;
	cout << "[2]查询数据" << endl;
	int n;
	while (cin >> n)
	{
		if(n==0)
		{
			int i;
			cout << "往第几个位置插入数据呀?" << endl;
			cin >> i;
			cout << "插如几呀?" << endl;
			int data;
			cin >> data;
			if (ListInsert(&L, i, data))
			{
				cout << "插入成功！" << endl;
			}
			else
			{
				cout << "插入失败！" << endl;
			}
		}
		if (n == 1)
		{
			int i;
			cout << "往第几个位置删除数据呀?" << endl;
			cin >> i;
			
			
			if (ListDelete(&L, i))
			{
				cout << "删除成功！" << endl;
			}
			else
			{
				cout << "删除失败！" << endl;
			}
		}
		if (n == 2)
		{
			int i;
			cout << "查询第几个数字呀?" << endl;
			int data;
			cin >> i;
			if (GetElem(L,i,&data))
			{
				cout <<data << endl;
				cout << "查询成功" << endl;
			}
			else
			{
				cout << "查询失败！" << endl;
			}
		}
		cout << "这是一个线性表" << endl;
		cout << "[0]插入数据" << endl;
		cout << "[1]删除数据" << endl;
		cout << "[2]查询数据" << endl;
	}

	return 0;
}

