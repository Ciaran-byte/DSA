#include<iostream>
#include<stack>
using namespace std;

//-----------------------------Ԥ�ȶ������---------------------------------------------------
const int MaxVex = 20;
const int OK = 1;
const int Error = 0;
const int Infinity = 65535;
typedef int Status;
//-----------------------------Ԥ�ȶ����������---------------------------------------------------


//----------------------------�����ڽӾ���Ľṹ----------------------------------------------------

typedef struct MGraph
{
	int vexs[MaxVex];
	int arc[MaxVex][MaxVex];
	int numVertexs;
	int numEdges;
}MGraph;

//-----------------------------�����ڽӾ���ṹ����-------------------------------------------------


//------------------------------�����ڽӾ�����--------------------------------------------------

void CreateMGraph(MGraph* g)
{
	//01 ���������Ϣ
	cout << "������������" << endl;
	int vexs;
	cin >> vexs;
	g->numVertexs = vexs;

	cout << "������ߵ�����" << endl;
	int edges;
	cin >> edges;
	g->numEdges = edges;

	cout << "����������Ϣ" << endl;
	for (int i = 0; i < g->numVertexs; i++)
	{
		cin >> g->vexs[i];
	}

	//02 �ڽӾ����ʼ��
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


	cout << "������ߺ�Ȩֵ��ע������������ͼ" << endl;
	for (int i = 0; i < g->numEdges; i++)
	{
		int x, y, w;
		cin >> x >> y >> w;
		g->arc[x][y] = w;
		
	}

}
//-------------------------------�����ڽӾ���������--------------------------------------------



//----------------------------------�����ڽӱ���������-------------------------------------------

typedef struct EdgeNode //�߽��
{
	int adjvex;
	int weight;
	EdgeNode* next;
}EdgeNode;

typedef struct VertexNode //ͷ���
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

//-----------------------------------�����ڽӱ��������ͽ���-------------------------------------


//------------------------------------ʹ���ڽӾ��󴴽��ڽӱ�------------------------------
void CreateAGraph(MGraph m,AGraph* a)
{
	
	
	//01 �ڽӱ��ʼ�������Ͷ�����
	a->numEdges = m.numEdges;
	a->numVertexs = m.numVertexs;
	

	//02 ��ʼ����������
	for (int i = 0; i < a->numVertexs; i++)
	{
		a->vexs[i].data = m.vexs[i];
		a->vexs[i].in = 0;
		a->vexs[i].first = NULL;
	}

	//03 ������ṹ
	
	for (int i = 0; i < m.numVertexs; i++)
	{
		for (int j = 0; j < m.numVertexs; j++)
		{
			
			if (m.arc[i][j] != 0 && m.arc[i][j] < Infinity)
			{
				
				//���i-j֮�������ߣ�����һ���߽�㣬���iָ����j�����j�����+1
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
//------------------------------------ʹ���ڽӾ��󴴽��ڽӱ����------------------------------


//-----------------------------------���������㷨�жϱ����Ƿ��л�---------------------------------------

Status TopologicalSort(AGraph* a)
{
	int count = 0;//��¼���������
	
	//����һ��ջ����������Ϊ0�ĵ㣬ѹ��ջ��
	
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
		//���Ϊ0��Ԫ�س�ջ
		int top = nodeList.top();
		cout << top << endl;
		nodeList.pop();
		count++;

		//�������ĩ�˽�����-1
		EdgeNode* e=a->vexs[top].first;
		
		
		while (e)
		{
			
			int k = e->adjvex; //������-1�Ժ�Ľ����ȳ�Ϊ0�ˣ��ͼ�����ջ
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
		cout << "�л�" << endl;
	}
	else
	{
		cout << "�޻�" << endl;
	}
	return 0;
}

