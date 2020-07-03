#include<iostream>
using namespace std;

//-------------------------------------------邻接表的结构定义------------------------------------

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

//--------------------------------------------邻接表结构定义结束----------------------------------

//-------------------------------------------基于邻接表的无向图创建-----------------------------

void CreateGraph(Graph* g)
{
	cout << "请输入顶点数和边数" << endl;
	cout << "顶点数" << ends;
	cin >> g->numVexes;
	cout << "边数" << ends;
	cin >> g->numEdges;

	cout << "请输入顶点信息" << endl;
	for (int i = 0; i < g->numVexes; i++)
	{
		cin >> (g->vexs)[i].data;
		(g->vexs)[i].firstEdge = NULL;


	}

	for (int k = 0; k < g->numEdges; k++)
	{
		cout << "请输入边(vi,vj)的顶点序号i，j以及权值w:" << endl;
		int i, j, weight;
		cin >> i >> j >> weight;


		//头插法建立邻接表
		EdgeNode* e = (EdgeNode*)malloc(sizeof(EdgeNode));  //先创建一个结点，说明结点号和权值
		if (!e)
		{
			exit(0);
		}
		e->adjvex = j;
		e->weight = weight;
		e->next = g->vexs[i].firstEdge;// 结点指向结点表的第一邻结点
		g->vexs[i].firstEdge = e;  //第一邻结点指向当前结点

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

//-------------------------------------------基于邻接表的无向图创建结束--------------------------------
bool visited[MaxVex];

//递归搜索
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
//递归遍历
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

