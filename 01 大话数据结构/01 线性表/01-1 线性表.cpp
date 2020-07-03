#include<iostream>
using namespace std;

const int MaxSize = 20;
//--------------------------------------�����������Ľṹ--------------------------------
typedef int ElemType;  
typedef struct
{
	ElemType data[MaxSize] = { 0 };
	int length=0;
}SqList;
//--------------------------------------�����������Ľṹ����--------------------------------

//--------------------------------------��ȡԪ�ز���---------------------------------------

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

//--------------------------------------��ȡԪ�ز�������---------------------------------------



//--------------------------------------�������---------------------------------------
status ListInsert(SqList* L, int i, ElemType e)
{
	if (L->length == MaxSize) //������
	{
		return Error;
	}
	if (i<1 || i>L->length + 1) //����λ�ò�����
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


//--------------------------------------�����������---------------------------------------

//--------------------------------------ɾ������-------------------------------------------
status ListIDelete(SqList* L, int i)
{
	if (L->length == 0) //�����
	{
		return Error;
	}
	if (i<1 || i>L->length ) //ɾ��λ�ò�����
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

//--------------------------------------ɾ����������-------------------------------------------
int main()
{
	//���Ա���
	SqList l;

	//����ֵ
	ListInsert(&l, 1, 5);
	int m;

	//��ȡֵ
	GetElem(l, 1, &m);
	cout << m << endl;

	//ɾ��ֵ
	ListIDelete(&l, 1);
	
	return 0;
}