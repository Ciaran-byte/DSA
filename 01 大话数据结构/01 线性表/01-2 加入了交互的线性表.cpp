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
	cout << "����һ�����Ա�" << endl;
	cout << "[0]��������" << endl;
	cout << "[1]ɾ������" << endl;
	cout << "[2]��ѯ����" << endl;
	int n;
	while (cin >> n)
	{
		if(n==0)
		{
			int i;
			cout << "���ڼ���λ�ò�������ѽ?" << endl;
			cin >> i;
			cout << "���缸ѽ?" << endl;
			int data;
			cin >> data;
			if (ListInsert(&L, i, data))
			{
				cout << "����ɹ���" << endl;
			}
			else
			{
				cout << "����ʧ�ܣ�" << endl;
			}
		}
		if (n == 1)
		{
			int i;
			cout << "���ڼ���λ��ɾ������ѽ?" << endl;
			cin >> i;
			
			
			if (ListDelete(&L, i))
			{
				cout << "ɾ���ɹ���" << endl;
			}
			else
			{
				cout << "ɾ��ʧ�ܣ�" << endl;
			}
		}
		if (n == 2)
		{
			int i;
			cout << "��ѯ�ڼ�������ѽ?" << endl;
			int data;
			cin >> i;
			if (GetElem(L,i,&data))
			{
				cout <<data << endl;
				cout << "��ѯ�ɹ�" << endl;
			}
			else
			{
				cout << "��ѯʧ�ܣ�" << endl;
			}
		}
		cout << "����һ�����Ա�" << endl;
		cout << "[0]��������" << endl;
		cout << "[1]ɾ������" << endl;
		cout << "[2]��ѯ����" << endl;
	}

	return 0;
}

