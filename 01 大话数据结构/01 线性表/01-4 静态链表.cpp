#include<iostream>
using namespace std;

//---------------------------------------定义常量-----------------------------------------
const int MaxSize = 1000;
using ElemType = int;
using Status = int;
const int OK = 1;
const int Error = 0;

//---------------------------------------定义常量结束-----------------------------------------


//---------------------------------------定义静态链表数据类型-----------------------------------------
typedef struct
{
	ElemType data;
	int cur;
}Component,StaticLinkList[MaxSize];


//---------------------------------------定义静态链表数据类型结束---------------------------------------

//---------------------------------------初始化静态链表--------------------------------------
Status InitList(StaticLinkList space)
{
	for (int i = 0; i < MaxSize - 1; i++)
	{
		space[i].cur = i + 1;
		
	}
	space[MaxSize - 1].cur = 0;
	return OK;
}
//---------------------------------------初始化静态链表结束--------------------------------------


//---------------------------------------自定义malloc--------------------------------------
int Malloc_SSL(StaticLinkList space)
{
	int i = space[0].cur;//第一个备用链表位置，如果cur为0的话，说明表满了
	
	if (space[0].cur)
	{
		space[0].cur = space[i].cur; //备用链表位置后移

	}
	if (space[0].cur == MaxSize - 1) //如果下一个指向MaxSize-1了，说明表满了
	{
		space[0].cur = 0;
	}
	return i;
}
//---------------------------------------自定义malloc结束--------------------------------------

//---------------------------------------获取静态链表长度--------------------------------------
int LinkLength(StaticLinkList space)
{
	int i = space[MaxSize - 1].cur;
	int j = 0;
	while (i)
	{
		
		i = space[i].cur;
		j++;
		
	}
	return j;

}

//---------------------------------------获取静态链表长度结束----------------------------------
//-----------------------------------------------插入静态链表---------------------------
Status ListInsert(StaticLinkList space, int i, ElemType data)
{
	if (i<1 || i>LinkLength(space)+1) //如果插入位置有问题
	{
		return Error;
	}

	int num = Malloc_SSL(space); //如果num为0说明表满了
	if (num == 0)
	{
		return Error;
	}
	
	else //如果表没有满
	{
		if (LinkLength(space) == 0&&i==1) //如果表为空
		{
		
			
			space[num].data = data;
			space[num].cur = 0;
			space[0].cur = num + 1;
			space[MaxSize - 1].cur = num;

			return OK;
		
		}
		else //如果表木空
		{
			if (i == LinkLength(space) + 1)//如果原来不是空表，但是往最后一个位置插入值
			{
				
				space[num].data = data;
				space[num].cur = 0;
				space[0].cur = num + 1;
				int k = space[MaxSize - 1].cur;
				for (int j = 0; j < LinkLength(space) - 1; j++)
				{
					k = space[k].cur;
				}
				space[k].cur = num;
				return OK;
			}
			else if (i == 1)//如果不是空表，但是想插入到第一个
			{
				
				space[num].data = data;
				space[num].cur = space[MaxSize - 1].cur;
				space[MaxSize - 1].cur = num;
				return OK;
			}
			else //如果不是空表也不插入到最后一个
			{
				space[num].data = data;



				int k = space[MaxSize - 1].cur;
				for (int j = 0; j < i - 1; j++)
				{
					k = space[k].cur;
				}
				space[num].cur = space[k].cur;
				space[k].cur = num;

				return OK;
			}
		}
		
	}
	return Error;
	

}

//-------------------------------------------------插入静态链表结束--------------------------------

//-------------------------------------------------自定义free--------------------------------------
void Free_SSL(StaticLinkList space,int k)
{
	space[k].cur = space[0].cur;
	space[0].cur = k;
}
//-------------------------------------------------自定义free结束--------------------------------------

//------------------------------------------------删除静态链表某个元素
Status ListDelete(StaticLinkList space, int i)
{
	if (i<1 || i>LinkLength(space))
	{
		return Error;
	}

	int k = MaxSize - 1;
	for (int j = 0; j < i - 1; j++)
	{
		k = space[k].cur;
	}
	int nxt = space[k].cur;

	space[k].cur = space[nxt].cur;
	Free_SSL(space, nxt);
	return OK;
}

Status GetElem(StaticLinkList space, int i,int *data)
{
	if (i<1 || i>LinkLength(space))
	{
		return Error;
	}
	int k = space[MaxSize - 1].cur;
	for (int j = 0; j < i-1; j++)
	{
		k = space[k].cur;
	}
	*data = space[k].data;
	return OK;
}
int main()
{
	int i;
	StaticLinkList space;
	InitList(space);
	
	cout << "欢迎进入静态链表的世界！" << endl;
	cout << "1 插入数据" << endl;
	cout << "2 查询数据" << endl;
	cout << "3 删除数据" << endl;
	int select;
	while (cin >> select)
	{
		switch (select)
		{
		case(1):
			{
			cout << "往哪里插入?" << endl;
			int i;
			cin >> i;
			cout << "插入几?" << endl;
			int data;
			cin >> data;
			if (ListInsert(space, i, data))
			{
				cout << "插入成功！" << endl;
			}
			else
			{
				cout << "插入失败！" << endl;
			}
				break;
			}
		case(2):
		{
			cout << "查询第几个?" << endl;
			int i;
			cin >> i;
			int data;
			if (GetElem(space,i, &data))
			{
				cout << "查询成功！" << endl;
				cout << data << endl;
			}
			else
			{
				cout << "查询失败！" << endl;
			}
			break;
		}
		case(3):
		{
			cout << "删除第几个?" << endl;
			int i;
			cin >> i;
			
			if (ListDelete(space, i))
			{
				cout << "删除成功！" << endl;
			}
			else
			{
				cout << "删除失败！" << endl;
			}
			break;
		}

		
		}
		for (int n = 1; n <= LinkLength(space); n++)
		{
			int data;
			GetElem(space, n, &data);
			cout << data;
			if (n != LinkLength(space))
			{
				cout << ends;

			}
			else
			{
				cout << endl;
			}


		}
		cout << "继续！" << endl;
		char m;
		cin >> m;
		if(m=='n'||m=='N')
		{
		break;
		}
		else
		{
			system("cls");
			cout << "欢迎进入静态链表的世界！" << endl;
			cout << "1 插入数据" << endl;
			cout << "2 查询数据" << endl;
			cout << "3 删除数据" << endl;
		}
		
		
		
	}
	return 0;
}

