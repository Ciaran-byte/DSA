#include<iostream>
#include<stack>
using namespace std;

//-----------------------------预先定义变量---------------------------------------------------
const int MaxVex = 20;
const int OK = 1;
const int Error = 0;
const int Infinity = 65535;
typedef int Status;
//-----------------------------预先定义变量结束---------------------------------------------------


//----------------------------定义邻接矩阵的结构----------------------------------------------------

typedef struct MGraph
{
	int vexs[MaxVex];
	int arc[MaxVex][MaxVex];
	int numVertexs;
	int numEdges;
}MGraph;

//-----------------------------定义邻接矩阵结构结束-------------------------------------------------


//------------------------------创建邻接矩阵函数--------------------------------------------------

void CreateMGraph(MGraph* g)
{
	//01 输入基本信息
	cout << "请输入结点数量" << endl;
	int vexs;
	cin >> vexs;
	g->numVertexs = vexs;

	cout << "请输入边的数量" << endl;
	int edges;
	cin >> edges;
	g->numEdges = edges;

	cout << "请输入结点信息" << endl;
	for (int i = 0; i < g->numVertexs; i++)
	{
		cin >> g->vexs[i];
	}

	//02 邻接矩阵初始化
	for (int i = 0; i < g->numVertexs; i++)
	{
		for (int j = 0; j < g->numVertexs; j++)
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


	cout << "请输入边和权值，注意这里是有向图" << endl;
	for (int i = 0; i < g->numEdges; i++)
	{
		int x, y, w;
		cin >> x >> y >> w;
		g->arc[x][y] = w;
		
	}

}
//-------------------------------创建邻接矩阵函数结束--------------------------------------------



//----------------------------------创建邻接表数据类型-------------------------------------------

typedef struct EdgeNode //边结点
{
	int adjvex;
	int weight;
	EdgeNode* next;
}EdgeNode;

typedef struct VertexNode //头结点
{
	int in;
	int data;
	EdgeNode* first;

}VertexNode;

typedef struct AGraph
{
	VertexNode vexs[MaxVex];
	int numVertexs;
	int numEdges;
};

//-----------------------------------创建邻接表数据类型结束-------------------------------------


//------------------------------------使用邻接矩阵创建邻接表------------------------------
void CreateAGraph(MGraph m,AGraph* a)
{
	
	
	//01 邻接表初始化边数和顶点数
	a->numEdges = m.numEdges;
	a->numVertexs = m.numVertexs;
	

	//02 初始化顶点数据
	for (int i = 0; i < a->numVertexs; i++)
	{
		a->vexs[i].data = m.vexs[i];
		a->vexs[i].in = 0;
		a->vexs[i].first = NULL;
	}

	//03 构建表结构
	
	for (int i = 0; i < m.numVertexs; i++)
	{
		for (int j = 0; j < m.numVertexs; j++)
		{
			
			if (m.arc[i][j] != 0 && m.arc[i][j] < Infinity)
			{
				
				//如果i-j之间有连线，创建一个边结点，结点i指向结点j，结点j的入度+1
				EdgeNode* e = (EdgeNode*)malloc(sizeof(EdgeNode));
				if (!e)
				{
					exit(0);
				}
				
				e->adjvex = j;
				e->weight = m.arc[i][j];
				e->next = a->vexs[i].first;

				a->vexs[i].first = e;
				a->vexs[j].in++;

			}
		}
	}
	
	
}
//------------------------------------使用邻接矩阵创建邻接表结束------------------------------


//-----------------------------------拓扑排序算法判断表中是否有环---------------------------------------

Status TopologicalSort(AGraph* a)
{
	int count = 0;//记录输出顶点数
	
	//创建一个栈，如果有入度为0的点，压入栈中
	
	stack<int> nodeList;
	
	for (int i = 0; i < a->numVertexs; i++)
	{
		if (a->vexs[i].in == 0)
		{
			nodeList.push(i);
		
		}
	}

	while (!nodeList.empty())
	{
		//入度为0的元素出栈
		int top = nodeList.top();
		cout << top << endl;
		nodeList.pop();
		count++;

		//这个结点的末端结点入度-1
		EdgeNode* e=a->vexs[top].first;
		
		
		while (e)
		{
			
			int k = e->adjvex; //如果入度-1以后的结点入度成为0了，就继续入栈
			if (!(--a->vexs[k].in))
			{
				nodeList.push(k); 
			}
			e = e->next;
		}

	}

	if (count < a->numVertexs)
	{
		return Error;
	}
	else
	{
		return OK;
	}
}
int main()
{
	MGraph m;
	AGraph a;
	CreateMGraph(&m);
	CreateAGraph(m, &a);
	if (TopologicalSort(&a) == 0)
	{
		cout << "有环" << endl;
	}
	else
	{
		cout << "无环" << endl;
	}
	return 0;
}

