//(1)关键路径算法有四个重要的东西
// etv 结点最早开始时间
// ltv 结点最晚卡死时间
// ete 边最早开始时间
// lte 边最晚开始时间
//(2)了解几个重要思想
// -结点最早开始时间=max(前一个结点的最早开始时间+路径的权值) 因为只有前驱结点全部完成才能开始下一步，就得等最慢的完成
// -结点最晚开始时间 = min(后一个结点的最晚开始时间-路径的权值) 因为后驱结点如果想按期完成，必须是最长的前一条路径先开始才能完成任务，
// - 边最早开始时间= 左结点最早开始时间
// - 边最晚卡死时间 = 右结点最晚开始时间-权值
// 当边的最早开始时间=边的最晚开始时间时，说明做这个事情没有自由度，是关键路径

//(3）求解思路
// 先求每个结点的etv，从前往后求
// 再求每个结点的ltv，从后往前求
// 利用ete、lte与etv、ltv的关系，求出边的最早、最晚开始时间
// 判断一条路径的ete是否与lte相等，相等就是关键路径



#include<iostream>
#include<stack>
#include<vector>
using namespace std;

//-----------------------------预先定义变量---------------------------------------------------
const int MaxVex = 20;
const int OK = 1;
const int Error = 0;
const int Infinity = 65535;
typedef int Status;

int* etv; //每个结点的最早开始时间
int* ltv;//每个结点的最晚开始时间
stack<int> stack2; //用来保存拓扑序列结果
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
void CreateAGraph(MGraph m, AGraph* a)
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


//在关键路径算法中，拓扑排序除了要判断是否有环以外，还要完成的事情就是保存拓扑序列，并且求出每个结点的最早开始时间
Status TopologicalSort(AGraph* a)  
{
	
	int count = 0;//01 记录输出顶点数

	//02 初始化etv数组，假设每个事情的最早开始时间都是0
	
	etv = (int*)malloc(sizeof(int) * a->numVertexs);
	if (!etv)
	{
		exit(-1);
	}
	for (int i = 0; i < a->numVertexs; i++)
	{
		etv[i] = 0;
		
		
	}
	

	//03 创建一个栈，如果有入度为0的点，压入栈中,因为入度为0的结点是能够开始的结点

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
		//04 入度为0的元素出栈，并且把与之相连的结点入度-1
		int top = nodeList.top();
		//cout << top << endl;
		nodeList.pop();
		count++;
		stack2.push(top); //stack2用于记录拓扑数组

		//这个结点的末端结点入度-1
		EdgeNode* e = a->vexs[top].first;
		

		while (e)
		{

			int k = e->adjvex; //如果入度-1以后的结点入度成为0了，就继续入栈
			if (!(--a->vexs[k].in))
			{
				nodeList.push(k);
			}
		
			

			//如果前驱结点的最早开始时间+路径时间比下一个结点的最早开始时间还要晚，保存比较晚的那个
			if (etv[top] + e->weight > etv[k])
			{
				etv[k] = etv[top] + e->weight;
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

//-----------------------------------拓扑排序算法判断表中是否有环结束---------------------------------------


//-----------------------------------------关键路径算法--------------------------------------------------------

void CriticalPath(AGraph* a)
{
	
	if (TopologicalSort(a) == 0) //如果图有环，不可能是AOE图，直接退出程序
	{
		
		exit(-1);
	}
	else //如果图没有环，再来找他的关键路径
	{
		
		
		//01 初始化ltv数组，假设每个事情的最晚开始时间都是最后一个结点的最早开始时间

		int top = stack2.top(); //这个地方最后一个元素没有出栈
	
		ltv = (int*)malloc(sizeof(int) * a->numVertexs);
		if (!ltv)
		{
			exit(-1);
		}
	
		for (int i = 0; i < a->numVertexs; i++)
		{
			ltv[i]=etv[top];
		}
		
		//02 求每个结点的最晚开始时间,创建ltv表
		while (!stack2.empty())
		{
			top = stack2.top();
			stack2.pop();
			EdgeNode* e = a->vexs[top].first;
			

			while (e)
			{
				int k = e->adjvex;
				if (ltv[top] > ltv[k] - e->weight)
				{
					ltv[top] = ltv[k] - e->weight;
				}
				e = e->next;
			}
		}

		//03 求每个路径的活动最早开始时间ete和活动最晚开始时间lte,如果ete与lte相等，这就是关键路径

		for (int i = 0; i < a->numVertexs; i++)
		{
			EdgeNode* e = a->vexs[i].first;
			while (e)
			{
				int k = e->adjvex;
				int ete = etv[i]; //当前路径的活动最早开始时间，等于上一个结点的事件最早开始时间
				int lte = ltv[k] - e->weight; //当前路径的活动最晚开始时间，等于下一个结点的事件的最晚开始时间-weight
				if (ete == lte)
				{
					cout << a->vexs[i].data << "-" << a->vexs[k].data << endl;
				}
				e = e->next;

			}
		}
		
	}
}

//-----------------------------------------关键路径算法结束--------------------------------------------------------
int main()
{
	MGraph m;
	AGraph a;
	CreateMGraph(&m);
	CreateAGraph(m, &a);
	CriticalPath(&a);
	return 0;
}

