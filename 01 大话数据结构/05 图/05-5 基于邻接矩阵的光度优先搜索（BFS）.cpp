#include<iostream>
#include<queue>
#include<deque>

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


