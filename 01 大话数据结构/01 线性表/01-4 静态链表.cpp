#include<iostream>
using namespace std;

//---------------------------------------���峣��-----------------------------------------
const int MaxSize = 1000;
using ElemType = int;
using Status = int;
const int OK = 1;
const int Error = 0;

//---------------------------------------���峣������-----------------------------------------


//---------------------------------------���徲̬������������-----------------------------------------
typedef struct
{
	ElemType data;
	int cur;
}Component,StaticLinkList[MaxSize];


//---------------------------------------���徲̬�����������ͽ���---------------------------------------

//---------------------------------------��ʼ����̬����--------------------------------------
Status InitList(StaticLinkList space)
{
	for (int i = 0; i < MaxSize - 1; i++)
	{
		space[i].cur = i + 1;
		
	}
	space[MaxSize - 1].cur = 0;
	return OK;
}
//---------------------------------------��ʼ����̬�������--------------------------------------


//---------------------------------------�Զ���malloc--------------------------------------
int Malloc_SSL(StaticLinkList space)
{
	int i = space[0].cur;//��һ����������λ�ã����curΪ0�Ļ���˵��������
	
	if (space[0].cur)
	{
		space[0].cur = space[i].cur; //��������λ�ú���

	}
	if (space[0].cur == MaxSize - 1) //�����һ��ָ��MaxSize-1�ˣ�˵��������
	{
		space[0].cur = 0;
	}
	return i;
}
//---------------------------------------�Զ���malloc����--------------------------------------

//---------------------------------------��ȡ��̬������--------------------------------------
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

//---------------------------------------��ȡ��̬�����Ƚ���----------------------------------
//-----------------------------------------------���뾲̬����---------------------------
Status ListInsert(StaticLinkList space, int i, ElemType data)
{
	if (i<1 || i>LinkLength(space)+1) //�������λ��������
	{
		return Error;
	}

	int num = Malloc_SSL(space); //���numΪ0˵��������
	if (num == 0)
	{
		return Error;
	}
	
	else //�����û����
	{
		if (LinkLength(space) == 0&&i==1) //�����Ϊ��
		{
		
			
			space[num].data = data;
			space[num].cur = 0;
			space[0].cur = num + 1;
			space[MaxSize - 1].cur = num;

			return OK;
		
		}
		else //�����ľ��
		{
			if (i == LinkLength(space) + 1)//���ԭ�����ǿձ����������һ��λ�ò���ֵ
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
			else if (i == 1)//������ǿձ���������뵽��һ��
			{
				
				space[num].data = data;
				space[num].cur = space[MaxSize - 1].cur;
				space[MaxSize - 1].cur = num;
				return OK;
			}
			else //������ǿձ�Ҳ�����뵽���һ��
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

//-------------------------------------------------���뾲̬�������--------------------------------

//-------------------------------------------------�Զ���free--------------------------------------
void Free_SSL(StaticLinkList space,int k)
{
	space[k].cur = space[0].cur;
	space[0].cur = k;
}
//-------------------------------------------------�Զ���free����--------------------------------------

//------------------------------------------------ɾ����̬����ĳ��Ԫ��
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
	
	cout << "��ӭ���뾲̬��������磡" << endl;
	cout << "1 ��������" << endl;
	cout << "2 ��ѯ����" << endl;
	cout << "3 ɾ������" << endl;
	int select;
	while (cin >> select)
	{
		switch (select)
		{
		case(1):
			{
			cout << "���������?" << endl;
			int i;
			cin >> i;
			cout << "���뼸?" << endl;
			int data;
			cin >> data;
			if (ListInsert(space, i, data))
			{
				cout << "����ɹ���" << endl;
			}
			else
			{
				cout << "����ʧ�ܣ�" << endl;
			}
				break;
			}
		case(2):
		{
			cout << "��ѯ�ڼ���?" << endl;
			int i;
			cin >> i;
			int data;
			if (GetElem(space,i, &data))
			{
				cout << "��ѯ�ɹ���" << endl;
				cout << data << endl;
			}
			else
			{
				cout << "��ѯʧ�ܣ�" << endl;
			}
			break;
		}
		case(3):
		{
			cout << "ɾ���ڼ���?" << endl;
			int i;
			cin >> i;
			
			if (ListDelete(space, i))
			{
				cout << "ɾ���ɹ���" << endl;
			}
			else
			{
				cout << "ɾ��ʧ�ܣ�" << endl;
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
		cout << "������" << endl;
		char m;
		cin >> m;
		if(m=='n'||m=='N')
		{
		break;
		}
		else
		{
			system("cls");
			cout << "��ӭ���뾲̬��������磡" << endl;
			cout << "1 ��������" << endl;
			cout << "2 ��ѯ����" << endl;
			cout << "3 ɾ������" << endl;
		}
		
		
		
	}
	return 0;
}

