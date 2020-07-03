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

void MiniSpanTree_Prim(MGraph g)
{
	//01 创建需要的变量
	int adjvex[MaxVex]; //用来保存当前已经连接好的树与其余没有连接好的结点间构成最短距离的结点对
	int lowcost[MaxVex];  //用来储存当前已经连接好的树与其他没有连接好的结点间的最短距离

	adjvex[0] = 0; //表示从结点0开始进行搜索
	lowcost[0] = 0;  //lowcost储存的距离分为三种
					//(1)Inf,表示目前adjvex中的相应结点对没有连接关系
	                  //(2)普通数字，lowcost[j]表示adjvex[j]和j之间的距离
					//（3）表示两个结点已经连接上了，j和adjvex[j]两个结点都属于生成树了

	//02 初始化，从结点0开始，先计算结点0和其余各个点之间的距离
	for (int i = 1; i < g.numVertexes; i++)
	{
		adjvex[i] = 0; //构成边集 i和adjvex[i]是一条边的两个结点
	}
	for (int i = 1; i < g.numVertexes; i++) //距离数组初始为结点0和其余各个结点的距离
	{
		lowcost[i] = g.arc[0][i];
	}

	//03 
	int k=0;
	for (int i = 1; i < g.numVertexes; i++)//这个外循环的意义在于，防止图不是联通图，有多个子图，会有多个最小生成树
	{
		int min = Infinity;

		//03-1 搜索结点
		for (int j = 1; j < g.numVertexes; j++)
		{
			if (lowcost[j] != 0 && lowcost[j] < min) //搜索树和外部结点之间的最短距离，并记录那个结点
			{
				min = lowcost[j];
				k = j; //保存距离最小的位置
			}
		}

		//03-2 输出边
		cout << adjvex[k] << "-" << k << endl;
		lowcost[k] = 0; //表示k和adjvex[k]两个结点成功连接

		//03-3 更新边集和距离集合


		//刚刚结点k与生成树完成了连接，搜索结点k与其余各个未连接的结点之间的距离，如果k和j连接的线段比现在存的
		//j和adjvex[j]之间的距离lowcost[j]要短，那么就让adjvex[j]=结点k，并将lowcost[j]更新为k和j之间的距离
		for (int j = 1; j < g.numVertexes; j++)
		{
			if (lowcost[j] != 0 && g.arc[k][j] < lowcost[j])
			{
				adjvex[j] = k;
				lowcost[j] = g.arc[k][j];
				
			}
		}


	}


}

//---------------------------------------基于邻接矩形和prim算法的最小生成树结束---------------------
int main()
{

	MGraph m;
	CreateGraph(&m);
	MiniSpanTree_Prim(m);
	return 0;
}


