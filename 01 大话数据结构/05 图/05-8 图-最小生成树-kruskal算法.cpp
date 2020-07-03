#include<iostream>
using namespace std;
//--------------------------------邻接矩阵结构------------------------------------------------

typedef int VertexType; //结点类型
typedef int EdgeType;  //边类型
const int MaxVex = 100;  //最大顶点数
const int Infinity = 65535; //表示无穷

typedef struct
{
	VertexType vexs[MaxVex];//定义顶点
	EdgeType arc[MaxVex][MaxVex]; //定义边(弧)
	int numVertexes, numEdges; //当前定义数和边数
}MGraph;



//--------------------------------邻接矩阵结构定义结束-----------------------------------------


//--------------------------------------基于邻接矩形无向图的创建---------------------------------

void CreateGraph(MGraph* g)
{
	//输入个数信息
	cout << "请输入顶点数和边数" << endl;
	cout << "顶点:" << ends;

	cin >> g->numVertexes;
	cout << "边数:" << ends;
	cin >> g->numEdges;

	//输入顶点信息
	cout << "请输入顶点信息:" << endl;
	for (int i = 0; i < g->numVertexes; i++)
	{
		cin >> g->vexs[i];
	}

	//边信息的初始化
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

	//建立邻接矩形
	for (int i = 0; i < g->numEdges; i++)
	{
		cout << "请输入边(vi,vj)对应的下标i，j和权w" << endl;
		int row, col, w;
		cin >> row >> col >> w;
		g->arc[row][col] = w;
		g->arc[col][row] = g->arc[row][col]; //因为无向图，所以是对称矩阵

	}







}

//--------------------------------------基于邻接矩形无向图的创建结束-------------------------------

//-----------------------------------------基于邻接矩形和prim算法的最小生成树------------------------

//01 定义边集数组

typedef struct Edge
{
	int begin;
	int end;
	int weight;
}Edge;


//交换Edge数组的两条边储存位置
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

//边集排序
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

int find(int* parent, int f) //用来查找一条回路的边界点
{

	while (parent[f] !=-1)
	{
		f = parent[f];
	}
	return f;
}
void MiniSpanTree_Kruskal(MGraph g)
{
	//创建边集
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
	//对边集按小到大排序
	sort(edge, g);

	//初始化并查集
	int parent[MaxVex];
	for (int i = 0; i < g.numVertexes; i++)
	{
		parent[i] = -1;
	}

	//开始进行最小生成树
	for (int i = 0; i < g.numEdges; i++)
	{
		int n = find(parent, edge[i].begin); //查找线段两端点的根节点，如果两端点根节点相同，说明会成环
		int m = find(parent, edge[i].end);

		if (n != m)
		{
			parent[n] = m;  //如果二者没有环，合并集合，一个作为另外一个的根节点
			cout << edge[i].begin << "-" << edge[i].end << " " << edge[i].weight << endl;
		}
	}
}

//---------------------------------------基于邻接矩形和prim算法的最小生成树结束---------------------
int main()
{

	MGraph m;
	CreateGraph(&m);
	MiniSpanTree_Kruskal(m);
	return 0;
}
