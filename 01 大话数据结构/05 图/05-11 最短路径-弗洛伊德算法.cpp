//���������㷨���ڣ��ȼ�¼ֱ�����ӵ�������ľ��룬�������������֮������½�㣬
//�鿴�Ƿ����һ���м��㣬ʹ�þ����м���ľ����С��

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

void ShortestPath_Floyd(MGraph m, int Path[][MaxVex], int Distance[][MaxVex])
{
	//Path���¼����������֮���Ƿ���ڸ��̵�·��
	//Distance��¼����������֮�����̾���
	for (int i = 0; i < m.numVertexes; i++)
	{
		for (int j = 0; j < m.numVertexes; j++)
		{
			Path[i][j] = -1;
			Distance[i][j] = m.arc[i][j]; //������֮���ֱ�Ӿ���
		}
	}

	for (int v = 0; v < m.numVertexes; v++)
	{
		for (int i = 0; i < m.numVertexes; i++)
		{
			for (int j= 0; j < m.numVertexes; j++)//ÿ������һ���㿴�����Ƿ����һ����ӵ��ܹ����̾���
			{
				if (Distance[i][v] + Distance[v][j] < Distance[i][j])
				{
					Distance[i][j] = Distance[i][v] + Distance[v][j];
					Path[i][j] = v;

				}
			}
		}
	}
}



//--------------------------------------�����ڽӾ�������ͼ�Ĵ�������-------------------------------
int main()
{

	MGraph m;
	CreateGraph(&m);
	int Path[MaxVex][MaxVex];
	int Distance[MaxVex][MaxVex];

	ShortestPath_Floyd(m,Path,Distance);

	cout << "������������㣬Ϊ���������·��" << endl;
	
	int a, b;
	while (cin >> a >> b)
	{
		cout << Distance[a][b] << endl;
		while (Path[a][b] != -1)
		{
			cout << a << "-" << Path[a][b] << endl;
			a = Path[a][b];
		}
		cout << a << "-" << b << endl;

	}


	

	return 0;
}


