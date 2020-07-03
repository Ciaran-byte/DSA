#include<iostream>
using namespace std;

//---------------------------------------类型定义-------------------------------------------
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
//---------------------------------------类型定义结束-------------------------------------------


//---------------------------------------建表-------------------------------------------
Status ListCreate(LinkList* lst)
{
	cout << "输入建表的数据，输入0结束" << endl;
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
//---------------------------------------建表结束-------------------------------------------

//---------------------------------------遍历-------------------------------------------
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

//---------------------------------------插入-------------------------------------------
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
	} //找到要操作的位置
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
//---------------------------------------删除-------------------------------------------
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
	} //找到要操作的位置

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
		cout << "往哪里插入?" << endl;
		int i;
		cin >> i;
		cout << "插入几?" << endl;
		int data;
		cin >> data;
		if (ListInsert(&lst, i, data))
		{
			cout << "插入成功！" << endl;
		}
		else
		{
			cout << "插入失败！" << endl;
		}
		ListShow(lst);

		cout << "往哪里删除?" << endl;
		int j;
		cin >> j;

		if (ListDelete(&lst, j))
		{
			cout << "删除成功！" << endl;
		}
		else
		{
			cout << "删除失败！" << endl;
		}
		ListShow(lst);
	}

	return 0;
}


