//迪杰特斯拉算法主要步骤为
//(1)初始化：在距离表记录表Distance中初始结点v0和图中其余结点的距离，在路径Path表标记每一个结点的前驱都是v0
//(2)选择:从搜索到的全部路径中找到最短的那条边，不可能有任何一条路径比这个还短了，所以找到的点v1
//就是v0和这个点的最短路径。标记v1为已经找到最短路径的点。在Distance中记录二者最短距离，Path表记录v1的前驱就是v0
//(3)更新：新找到的这个点继续与没有找到的点进行路径搜索，如果新加入的点与其他未加入的点距离小于原来点与未加入点之间
//的距离，那么在Distance表中更新最短距离，并且在Path表中，记录这些更短的边的前驱是v1。
//每次循环必定会找到一条最短路径，有一个点以及被初始化选择了，所以n-1次循环之后，必定能够初始点与全部结点的最短距离和路径



#include<iostream>
using namespace std;
//--------------------------------邻接矩阵结构------------------------------------------------

typedef int VertexType; //结点类型
typedef int EdgeType;  //边类型
const int MaxVex = 10;  //最大顶点数
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

//Path数组用来记录最短路径的，Path[i]=j表示，在到i的最短路径中，前驱结点是j
//ShortPathTable表示v0到i的最短距离是ShortPathTable[i]

void ShortestPath_Dijkstra(MGraph g, int v0 ,int* Path, int* Distance)
{
	int final[MaxVex];//用来判断谁以及被决定了，final[i]为1的时候，说明结点1以及被选择了


	//初始化
	for (int i = 0; i < g.numVertexes; i++)
	{
		final[i] = 0;
		Path[i] = v0;
		Distance[i] = g.arc[v0][i];
	}

	//从第一个结点开始搜索，就要把第一个结点的东西赋值
	final[v0] = 1;
	Path[v0] = -1;
	

	int k = v0;

	for (int i = 1; i < g.numVertexes; i++)//每次循环必定找到一个点的最短路径，第一个点以及选择了，
		//因此只需要n-1个循环就能找到全部点的最短路径
	{
		int min = Infinity;

		//寻找v0到其余各点的最短距离
		for (int j = 0; j < g.numVertexes; j++)
		{
			if (!final[j] && Distance[j] < min)
			{
				min = Distance[i];
				k = j;
			}
		}

		//找到的最小的那个，会被选中,就找到一个与v0满足最短距离的点

		final[k] = 1;


		//每次加入一个新点，都会沿着这条路继续搜索，查看v0沿着这个点，与其余各个点的距离是多少
		//如果比当前小，就更新Path和ShortPathTable数组
		for (int j = 0; j < g.numVertexes; j++)
		{
			if (!final[j] && min + g.arc[k][j] < Distance[j])
			{
				Distance[j] = min + g.arc[k][j];
				Path[j] = k;
			}
		}
	}

	


}
//--------------------------------------基于邻接矩形无向图的创建结束-------------------------------
int main()
{

	MGraph m;
	CreateGraph(&m);
	int path[MaxVex];
	int distance[MaxVex];

	ShortestPath_Dijkstra(m, 0, path, distance);

	int v;
	cout << "查询0到哪个结点的最短路径？" << endl;
	while (cin >> v)
	{
		cout <<"最短距离"<< distance[v] << endl;
		cout << "路径为" << ends;
		cout << v << ends;
		while (path[v] != -1)
		{
			
			v = path[v];
			cout << v << ends;
		}
		cout << endl;

	}
	return 0;
}


