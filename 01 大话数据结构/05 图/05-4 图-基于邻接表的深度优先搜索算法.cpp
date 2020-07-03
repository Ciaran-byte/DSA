#include<iostream>
using namespace std;

//-------------------------------------------�ڽӱ�Ľṹ����------------------------------------

typedef int VertexType;
typedef int EdgeType;
const int MaxVex = 1000;

typedef struct EdgeNode
{
	int adjvex;
	EdgeType weight;
	EdgeNode* next;
}EgetNode;

typedef struct VertexNode
{
	VertexType data;
	EdgeNode* firstEdge;
}VertexNode;

typedef struct Graph
{
	VertexNode vexs[MaxVex];
	int numVexes, numEdges;

}Graph;

//--------------------------------------------�ڽӱ�ṹ�������----------------------------------

//-------------------------------------------�����ڽӱ������ͼ����-----------------------------

void CreateGraph(Graph* g)
{
	cout << "�����붥�����ͱ���" << endl;
	cout << "������" << ends;
	cin >> g->numVexes;
	cout << "����" << ends;
	cin >> g->numEdges;

	cout << "�����붥����Ϣ" << endl;
	for (int i = 0; i < g->numVexes; i++)
	{
		cin >> (g->vexs)[i].data;
		(g->vexs)[i].firstEdge = NULL;


	}

	for (int k = 0; k < g->numEdges; k++)
	{
		cout << "�������(vi,vj)�Ķ������i��j�Լ�Ȩֵw:" << endl;
		int i, j, weight;
		cin >> i >> j >> weight;


		//ͷ�巨�����ڽӱ�
		EdgeNode* e = (EdgeNode*)malloc(sizeof(EdgeNode));  //�ȴ���һ����㣬˵�����ź�Ȩֵ
		if (!e)
		{
			exit(0);
		}
		e->adjvex = j;
		e->weight = weight;
		e->next = g->vexs[i].firstEdge;// ���ָ�����ĵ�һ�ڽ��
		g->vexs[i].firstEdge = e;  //��һ�ڽ��ָ��ǰ���

		//  firstedge  ->p;
		// e->next = p;
		// firstedge -> e;



		e = (EdgeNode*)malloc(sizeof(EdgeNode));
		if (!e)
		{
			exit(0);
		}
		e->adjvex = i;
		e->weight = weight;
		e->next = g->vexs[j].firstEdge;
		g->vexs[j].firstEdge = e;




	}
}

//-------------------------------------------�����ڽӱ������ͼ��������--------------------------------
bool visited[MaxVex];

//�ݹ�����
void DFS(Graph g, int i)
{
	

	visited[i] = true;
	cout << g.vexs[i].data << endl;
	
	EdgeNode* p = g.vexs[i].firstEdge;

	while (p)
	{
		if (!visited[p->adjvex])
		{
			DFS(g, p->adjvex);
			

		}
		p = p->next;
	}

}
//�ݹ����
void DFSTraverse(Graph g)
{
	for (int i = 0; i < g.numVexes; i++)
	{
		visited[i] = false;
	}
	for (int i = 0; i < g.numVexes; i++)
	{
		if (!visited[i])
			DFS(g, i);
	}
}
int main()
{
	Graph g;
	CreateGraph(&g);
	DFSTraverse(g);
	
	return 0;
}

