#include "GraphMatrix.h"
#include<iostream>
#include<ctime>
using namespace std;
int main()
{
	//01图的创建
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
				cout << i << "和" << j << "之间有路径" << endl;
			}

		}
		if (edge == gM.e)break;
	}
	cout << "共计有" << edge << "条路径" << endl;

	//02图的遍历
	cout << endl;
	cout << "图的遍历" << endl;
	cout << endl;
	gM.bfs(1);

	//03 拓扑排序

	//----------建图------
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

	//----------拓扑排序1------
	cout << "拓扑排序1" << endl;
	stack<char>* s = gV.tsort1(1);
	if (s->empty())
	{
		cout << "无法拓扑排序!" << endl;
	}
	else
	{
		while (!s->empty())
		{
			cout << s->pop() << endl;
		}
		
	}
	delete s;

	//----------拓扑排序2------
	cout << endl;
	cout << "拓扑排序2" << endl;
	stack<char>* p = gV.tsort2(1);
	if (p->empty())
	{
		cout << "无法拓扑排序!" << endl;
	}
	else
	{
		while (!p->empty())
		{
			cout << p->pop() << endl;
		}

	}
	delete p;
	////----------拓扑排序3------
	//cout << endl;
	//cout << "拓扑排序3" << endl; //三版本拓扑排序会删除结点
	//queue<char>* qu = gV.tsort3();
	//if (qu->empty())
	//{
	//	cout << "无法拓扑排序!" << endl;
	//}
	//else
	//{
	//	while (!qu->empty())
	//	{
	//		cout << qu->dequeue()<< endl;
	//	}
	//}
	//delete qu;

	//03 寻找关节点
	cout << endl;
	cout << "寻找关节点" << endl;
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

//04 最小生成树
	cout << endl;
	cout << "最小生成树" << endl;
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


	cout << "第二个最小生成树函数" << endl;
	primPU<char, char> pu;
	shortest.pfs(0, pu);

	//05 迪杰特斯拉算法
	cout << endl;
	cout << "迪杰特斯拉算法1" << endl;
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
	cout << "最短路径为" << endl;
	while(!order.empty())
	{
		cout << order.pop() << endl;
	}

	cout << endl;
	cout << "迪杰特斯拉算法2" << endl;
	shortest.dijkstra(0);
	point = p2;
	while (shortest.parent(point) != p1)
	{
		order.push(point);
		point = shortest.parent(point);
	}
	order.push(point);
	order.push(p1);
	cout << "最短路径为" << endl;
	while (!order.empty())
	{
		cout << order.pop() << endl;
	}
		return 0;
}

