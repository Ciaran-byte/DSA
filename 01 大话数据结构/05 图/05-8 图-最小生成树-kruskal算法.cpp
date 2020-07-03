#include<iostream>
using namespace std;
//--------------------------------�ڽӾ���ṹ------------------------------------------------

typedef int VertexType; //�������
typedef int EdgeType;  //������
const int MaxVex = 100;  //��󶥵���
const int Infinity = 65535; //��ʾ����

typedef struct
{
	VertexType vexs[MaxVex];//���嶥��
	EdgeType arc[MaxVex][MaxVex]; //�����(��)
	int numVertexes, numEdges; //��ǰ�������ͱ���
}MGraph;



//--------------------------------�ڽӾ���ṹ�������-----------------------------------------


//--------------------------------------�����ڽӾ�������ͼ�Ĵ���---------------------------------

void CreateGraph(MGraph* g)
{
	//���������Ϣ
	cout << "�����붥�����ͱ���" << endl;
	cout << "����:" << ends;

	cin >> g->numVertexes;
	cout << "����:" << ends;
	cin >> g->numEdges;

	//���붥����Ϣ
	cout << "�����붥����Ϣ:" << endl;
	for (int i = 0; i < g->numVertexes; i++)
	{
		cin >> g->vexs[i];
	}

	//����Ϣ�ĳ�ʼ��
	for (int i = 0; i < g->numVertexes; i++)
	{
		for (int j = 0; j < g->numEdges; j++)
		{
			if (i == j)
			{
				g->arc[i][j] = 0;
			}
			else
			{
				g->arc[i][j] = Infinity;
			}
		}
	}

	//�����ڽӾ���
	for (int i = 0; i < g->numEdges; i++)
	{
		cout << "�������(vi,vj)��Ӧ���±�i��j��Ȩw" << endl;
		int row, col, w;
		cin >> row >> col >> w;
		g->arc[row][col] = w;
		g->arc[col][row] = g->arc[row][col]; //��Ϊ����ͼ�������ǶԳƾ���

	}







}

//--------------------------------------�����ڽӾ�������ͼ�Ĵ�������-------------------------------

//-----------------------------------------�����ڽӾ��κ�prim�㷨����С������------------------------

//01 ����߼�����

typedef struct Edge
{
	int begin;
	int end;
	int weight;
}Edge;


//����Edge����������ߴ���λ��
void Swap(Edge* e, int i, int j)
{

	int swap=e[i].begin;
	e[i].begin = e[j].begin;
	e[j].begin = swap;

	swap = e[i].end;
	e[i].end = e[j].end;
	e[j].end = swap;

	swap = e[i].weight;
	e[i].weight = e[j].weight;
	e[j].weight = swap;
	
}

//�߼�����
void sort(Edge* e,MGraph m)
{
	for (int i = 0; i < m.numEdges; i++)
	{
		for (int j = i + 1; j < m.numEdges; j++)
		{
			if (e[i].weight >e[j].weight)
			{
				Swap(e, i, j);
			}
		}
	}
}

int find(int* parent, int f) //��������һ����·�ı߽��
{

	while (parent[f] !=-1)
	{
		f = parent[f];
	}
	return f;
}
void MiniSpanTree_Kruskal(MGraph g)
{
	//�����߼�
	Edge edge[MaxVex];
	int k = 0;
	for (int i = 0; i < g.numVertexes; i++)
	{
		for (int j = i + 1; j < g.numVertexes; j++)
		{
			if (g.arc[i][j] < Infinity)
			{
				edge[k].weight = g.arc[i][j];
				edge[k].begin = i;
				edge[k].end = j;
				k++;
			}
		}
	}
	//�Ա߼���С��������
	sort(edge, g);

	//��ʼ�����鼯
	int parent[MaxVex];
	for (int i = 0; i < g.numVertexes; i++)
	{
		parent[i] = -1;
	}

	//��ʼ������С������
	for (int i = 0; i < g.numEdges; i++)
	{
		int n = find(parent, edge[i].begin); //�����߶����˵�ĸ��ڵ㣬������˵���ڵ���ͬ��˵����ɻ�
		int m = find(parent, edge[i].end);

		if (n != m)
		{
			parent[n] = m;  //�������û�л����ϲ����ϣ�һ����Ϊ����һ���ĸ��ڵ�
			cout << edge[i].begin << "-" << edge[i].end << " " << edge[i].weight << endl;
		}
	}
}

//---------------------------------------�����ڽӾ��κ�prim�㷨����С����������---------------------
int main()
{

	MGraph m;
	CreateGraph(&m);
	MiniSpanTree_Kruskal(m);
	return 0;
}
