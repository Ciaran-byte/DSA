#include "GraphMatrix.h"
#include<iostream>
#include<ctime>
using namespace std;
int main()
{
	//01ͼ�Ĵ���
	srand(time(0));
	GraphMatrix<char, char> gM;
	for (int i = 0; i < 10; i++)
	{
		gM.insert(i + 'A');
	}
	for (int i = 0; i < gM.n; i++)
	{
		for (int j = 0; j < gM.n; j++)
		{
			if (rand()%3==0)
			{
				gM.insert('E', rand() % 10 + 1, i, j);
			}
		}
	}

	int edge = 0;
	for (int i = 0; i < gM.n; i++)
	{
		
		for (int j = 0; j < gM.n; j++)
		{
			if (edge == gM.e)break;
			if (gM.exist(i, j))
			{
				edge++;
				cout << i << "��" << j << "֮����·��" << endl;
			}

		}
		if (edge == gM.e)break;
	}
	cout << "������" << edge << "��·��" << endl;

	//02ͼ�ı���
	cout << endl;
	cout << "ͼ�ı���" << endl;
	cout << endl;
	gM.bfs(1);

	//03 ��������

	//----------��ͼ------
	cout << endl;
	GraphMatrix<char, char> gV;
	for (int i = 0; i < 5; i++)
	{
		gV.insert(i + '0');
	}

	gV.insert('V',2, 3, 1);
	gV.insert('V', 2, 3, 2);
	gV.insert('V', 2, 1, 0);
	gV.insert('V', 2, 2, 0);
	gV.insert('V', 2, 0, 4);

	//----------��������1------
	cout << "��������1" << endl;
	stack<char>* s = gV.tsort1(1);
	if (s->empty())
	{
		cout << "�޷���������!" << endl;
	}
	else
	{
		while (!s->empty())
		{
			cout << s->pop() << endl;
		}
		
	}
	delete s;

	//----------��������2------
	cout << endl;
	cout << "��������2" << endl;
	stack<char>* p = gV.tsort2(1);
	if (p->empty())
	{
		cout << "�޷���������!" << endl;
	}
	else
	{
		while (!p->empty())
		{
			cout << p->pop() << endl;
		}

	}
	delete p;
	////----------��������3------
	//cout << endl;
	//cout << "��������3" << endl; //���汾���������ɾ�����
	//queue<char>* qu = gV.tsort3();
	//if (qu->empty())
	//{
	//	cout << "�޷���������!" << endl;
	//}
	//else
	//{
	//	while (!qu->empty())
	//	{
	//		cout << qu->dequeue()<< endl;
	//	}
	//}
	//delete qu;

	//03 Ѱ�ҹؽڵ�
	cout << endl;
	cout << "Ѱ�ҹؽڵ�" << endl;
	GraphMatrix<char, char> gA;
	for (int i = 0; i < 8; i++)
	{
		gA.insert(i + '0');
	}

	gA.insert('V', 2, 0, 1);
	gA.insert('V', 2, 1, 2);
	gA.insert('V', 2, 2, 3);
	gA.insert('V', 2, 3, 4);
	gA.insert('V', 2, 2, 7);
	gA.insert('V', 2, 7, 0);
	gA.insert('V', 2, 6, 3);
	gA.insert('V', 2, 4, 6);
	gA.insert('V', 2, 6, 5);

	
	gA.bcc(0);

//04 ��С������
	cout << endl;
	cout << "��С������" << endl;
	GraphMatrix<char, char> shortest;
	for (int i = 0; i < 8; i++)
	{
		shortest.insert(i + '0');
	}
	shortest.insertD('1', 6, 0, 3);
	shortest.insertD('2', 4, 0, 1);
	shortest.insertD('3', 12, 1, 2);
	shortest.insertD('4', 7, 0, 6);
	shortest.insertD('5', 9, 2, 3);
	shortest.insertD('6', 1, 2, 4);
	shortest.insertD('7', 2, 2, 5);
	shortest.insertD('8', 7, 5, 7);
	shortest.insertD('10', 10, 2, 7);
	shortest.insertD('11', 5, 4, 5);
	shortest.insertD('12', 13, 3, 4);
	shortest.insertD('13', 2, 3, 6);
	shortest.insertD('14', 11, 4, 6);
	shortest.insertD('15', 8, 4, 7);
	shortest.insertD('16', 14, 6, 7);
	shortest.prim(0);


	cout << "�ڶ�����С����������" << endl;
	primPU<char, char> pu;
	shortest.pfs(0, pu);

	//05 �Ͻ���˹���㷨
	cout << endl;
	cout << "�Ͻ���˹���㷨1" << endl;
	dikstraPU<char, char> dpu;
	shortest.pfs(0, dpu);
	int p1 = 0;
	int p2 = 4;
	stack<int> order;
	int point = p2;
	while (shortest.parent(point) != p1)
	{
		order.push(point);
		point = shortest.parent(point);
	}
	order.push(point);
	order.push(p1);
	cout << "���·��Ϊ" << endl;
	while(!order.empty())
	{
		cout << order.pop() << endl;
	}

	cout << endl;
	cout << "�Ͻ���˹���㷨2" << endl;
	shortest.dijkstra(0);
	point = p2;
	while (shortest.parent(point) != p1)
	{
		order.push(point);
		point = shortest.parent(point);
	}
	order.push(point);
	order.push(p1);
	cout << "���·��Ϊ" << endl;
	while (!order.empty())
	{
		cout << order.pop() << endl;
	}
		return 0;
}

