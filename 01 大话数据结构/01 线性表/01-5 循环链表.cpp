#include<iostream>
using namespace std;

typedef int ElemType;
typedef int Status;
const int OK = 1;
const int Error = 0;

typedef struct Node
{
	ElemType data;
	Node* next;

}Node; 

typedef Node* LinkList;

//--------------------------------------ѭ������Ĵ���-----------------------------------------
Status ListCreate(LinkList* lst)
{
	cout << "�����������ֵ��0����" << endl; //��ͷ����ѭ������
	int num;

	Node* test = *lst;

	while (cin >> num)
	{
		if (num == 0)
		{
			break;
		}
		else
		{
			if (*lst == NULL)
			{
				*lst = (Node*)malloc(sizeof(Node));
				Node* q = (Node*)malloc(sizeof(Node));
				if (!(*lst)||!q)return Error;
				
				q->data = num;
				(*lst)->next = q;
				q->next = *lst;
			}
			
			else
			{
				Node* p = *lst;
				while (p->next != *lst)
				{
					p = p->next;
				}
				Node* q = (Node*)malloc(sizeof(Node));
				if (!q)return Error;
				q->data = num;
				q->next = *lst;
				p->next = q;

			}
		}
	}

}//--------------------------------------ѭ������Ĵ�������-----------------------------------------


//----------------------����------------------------------------------
void ListShow(LinkList lst)
{
	Node* p = lst->next;
	while (p->next != lst)
	{
		cout << p->data << ends;
		p = p->next;
	}
	cout << p->data << ends;
	cout << endl;
}
//----------------------��������------------------------------------------

//----------------------����ֵ-----------------------------------------

Status ListInsert(LinkList* lst, int i, ElemType data)
{
	int ret = 0;
	Node* p = *lst;
	int j = 1;
	while ((p!=(*lst)||ret==0) &&j<i)
	{
		p = p->next;
		j++;
		ret = 1;
	}
	if ((p ==(*lst)&&ret!=0)|| i < 1)
	{
		return Error;
	} //�ҵ�Ҫ������λ�õ�ǰһ��
	else
	{
		Node* q = (LinkList)malloc(sizeof(Node));
		if (!q)return Error;
		q->data = data;
		q->next = p->next;
		p->next = q;

	}
	return OK;

}
//----------------------����ֵ����-----------------------------------------

//----------------------ɾ��ֵ-----------------------------------------
Status ListDelete(LinkList* lst, int i)
{
	
	Node* p = *lst;
	int j = 1;
	while (p->next != (*lst) && j < i)
	{
		p = p->next;
		j++;
		
	}
	if (p->next == (*lst)  || i < 1)
	{
		return Error;
	}
	else
	{
		Node* q = p->next;
		p->next = q->next;
		free(q);

	}
	return OK;


}

//----------------------ɾ��ֵ����-----------------------------------------
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

