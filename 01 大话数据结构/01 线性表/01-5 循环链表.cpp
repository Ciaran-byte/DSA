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

//--------------------------------------循环链表的创建-----------------------------------------
Status ListCreate(LinkList* lst)
{
	cout << "请输入链表的值，0结束" << endl; //带头结点的循环链表
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

}//--------------------------------------循环链表的创建结束-----------------------------------------


//----------------------遍历------------------------------------------
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
//----------------------遍历结束------------------------------------------

//----------------------插入值-----------------------------------------

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
	} //找到要操作的位置的前一个
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
//----------------------插入值结束-----------------------------------------

//----------------------删除值-----------------------------------------
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

//----------------------删除值结束-----------------------------------------
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

