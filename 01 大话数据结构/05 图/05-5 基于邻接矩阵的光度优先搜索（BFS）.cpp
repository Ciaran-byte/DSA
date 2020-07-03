#include<iostream>
#include<queue>
#include<deque>

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
bool visited[MaxVex];
void BFSTraverse(MGraph m)
{
	for (int i = 0; i < m.numVertexes; i++)
	{
		visited[i] = 0;
	}

	queue<int, deque<int>> q;
	for (int i = 0; i < m.numVertexes; i++)
	{
		if (!visited[i])
		{
			visited[i] = true;
			q.push(i);
			cout << m.vexs[i] << endl;
			while (!q.empty())
			{
				int j = q.front();
				q.pop();
				for (int k = 0; k < m.numVertexes; k++)
				{
					if (m.arc[k][j] == 1 && visited[k] == false)
					{
						visited[k] = true;
						cout << m.vexs[k] << endl;
						q.push(k);
					}
				}
			}
		}
		
	}

}
int main()
{

	MGraph m;
	CreateGraph(&m);
	BFSTraverse(m);

	return 0;
}


