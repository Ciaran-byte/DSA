#include<iostream>
using namespace std;

const int VexNum = 6;

void initialize(int* parent) //��ʼ��parent���ϣ���ʾĿǰ�κ�һ���㶼û�и��ڵ�(����˵���ڵ�������Լ�)
{
	for (int i = 0; i < VexNum; i++)
	{
		parent[i] = -1;
	}
}

int find_root(int x, int* parent) //Ѱ��һ�����������ϵĸ��ڵ�
{
	while (parent[x] != -1) //ֻҪ�����ֵ����-1��˵�������㲻�Ǹ��ڵ㣬���滹�и��ڵ㣬�Ǿͼ�����ǰ��
	{
		x = parent[x];
	}
	return x;
}


//��������㲻����ͬһ�����ϣ�����������������1�����򷵻�0��˵�������˻�
int union_vertex(int x, int y, int *parent) 
{
	int x_root = find_root(x, parent);
	int y_root = find_root(y, parent);
	if (x_root == y_root)
	{
		return 0;
	}
	else
	{
		parent[x_root] = y_root;
	}
}
int main()
{
	int parent[VexNum];
	initialize(parent);
	int edges[6][2] = 
	{ 
		{ 0,1 },
		{1,2},
		{1,3},
		{2,4},
		{3,4},
		{2,5} 
	}; //��ͼ��������

	for (int i = 0; i < 6; i++)
	{
		int x = edges[i][0];
		int y = edges[i][1];
		if (union_vertex(x, y, parent) == 0)
		{
			cout << "�л�" << endl;
			exit(0);
		}
	}
	cout << "û�л���" << endl;
	return 0;
}