#include<iostream>
using namespace std;

//---------------------------------------���Ͷ���-------------------------------------------
typedef int ElemType;
typedef int Status;
const int OK = 1;
const int Error = 0;

typedef struct Node
{
	ElemType data;
	Node* prior;
	Node* next;
}Node;
typedef Node* LinkList;
//---------------------------------------���Ͷ������-------------------------------------------


//---------------------------------------����-------------------------------------------
Status ListCreate(LinkList* lst)
{
	cout << "���뽨������ݣ�����0����" << endl;
	int data;
	while (cin >> data)
	{
		if (data == 0)
		{
			break;
		}
		else
		{
			if (*lst == NULL)
			{
				*lst = (LinkList)malloc(sizeof(Node));
				LinkList p = (LinkList)malloc(sizeof(Node));
				if (!(*lst)||!p)
				{
					return Error;
				}
				p->data = data;
				p->next = *lst;
				p->prior = *lst;
				
				(*lst)->next = p;
				(*lst)->prior = p;
			}
			else
			{
				LinkList p = (*lst);
				while (p->next != *lst)
				{
					p = p->next;
				}
				LinkList q = (LinkList)malloc(sizeof(Node));
				if (!q)
				{
					return Error;
				}
				q->data = data;
				

				q->next = p->next;
				p->next->prior = q;
				q->prior = p;
				p->next = q;

				

			}
		}
	}
	return OK;
}
//---------------------------------------�������-------------------------------------------

//---------------------------------------����-------------------------------------------
void ListShow(LinkList lst)
{
	
	LinkList p = lst->next;
	while (p != lst)
	{
		cout << p->data << ends;
		p = p->next;
	}
	cout << endl;
}

//---------------------------------------����-------------------------------------------
Status ListInsert(LinkList* lst, int i, ElemType data)
{

	Node* p = (*lst)->next;
	int j = 1;
	while (p != (*lst)&& j < i)
	{
		p = p->next;
		j++;
		
	}
	if ((p== (*lst)&&j!=i) || i < 1)
	{
		return Error;
	} //�ҵ�Ҫ������λ��
	else
	{
		Node* q = (LinkList)malloc(sizeof(Node));
		if (!q)return Error;
		
		q->data = data;
		q->next = p;
		q->prior = p->prior;
		p->prior->next = q;
		p->prior = q;


	}
	return OK;

}
//---------------------------------------ɾ��-------------------------------------------
Status ListDelete(LinkList* lst, int i)
{
	Node* p = (*lst)->next;
	int j = 1;
	while (p != (*lst) && j < i)
	{
		p = p->next;
		j++;

	}
	if ((p == (*lst) && j != i) || i < 1)
	{
		return Error;
	} //�ҵ�Ҫ������λ��

	else
	{
		p->prior->next = p->next;
		p->next->prior = p->prior;
		free(p);
	}
	return OK;

}



int main()
{
	LinkList lst = NULL;
	ListCreate(&lst);

	ListShow(lst);
	while (1)
	{
		cout << "���������?" << endl;
		int i;
		cin >> i;
		cout << "���뼸?" << endl;
		int data;
		cin >> data;
		if (ListInsert(&lst, i, data))
		{
			cout << "����ɹ���" << endl;
		}
		else
		{
			cout << "����ʧ�ܣ�" << endl;
		}
		ListShow(lst);

		cout << "������ɾ��?" << endl;
		int j;
		cin >> j;

		if (ListDelete(&lst, j))
		{
			cout << "ɾ���ɹ���" << endl;
		}
		else
		{
			cout << "ɾ��ʧ�ܣ�" << endl;
		}
		ListShow(lst);
	}

	return 0;
}


