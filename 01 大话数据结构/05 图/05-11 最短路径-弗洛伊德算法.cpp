//弗洛伊德算法在于，先记录直接连接的两个点的距离，依次在两个结点之间插入新结点，
//查看是否存在一个中间结点，使得经过中间结点的距离更小。

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

void ShortestPath_Floyd(MGraph m, int Path[][MaxVex], int Distance[][MaxVex])
{
	//Path表记录的是两个点之间是否存在更短的路径
	//Distance记录的是两个点之间的最短距离
	for (int i = 0; i < m.numVertexes; i++)
	{
		for (int j = 0; j < m.numVertexes; j++)
		{
			Path[i][j] = -1;
			Distance[i][j] = m.arc[i][j]; //两个点之间的直接距离
		}
	}

	for (int v = 0; v < m.numVertexes; v++)
	{
		for (int i = 0; i < m.numVertexes; i++)
		{
			for (int j= 0; j < m.numVertexes; j++)//每次增加一个点看看，是否加入一个间接点能够缩短距离
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



//--------------------------------------基于邻接矩形无向图的创建结束-------------------------------
int main()
{

	MGraph m;
	CreateGraph(&m);
	int Path[MaxVex][MaxVex];
	int Distance[MaxVex][MaxVex];

	ShortestPath_Floyd(m,Path,Distance);

	cout << "请输入两个结点，为你生成最短路径" << endl;
	
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


