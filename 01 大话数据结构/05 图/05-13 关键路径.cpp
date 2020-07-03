//(1)�ؼ�·���㷨���ĸ���Ҫ�Ķ���
// etv ������翪ʼʱ��
// ltv ���������ʱ��
// ete �����翪ʼʱ��
// lte ������ʼʱ��
//(2)�˽⼸����Ҫ˼��
// -������翪ʼʱ��=max(ǰһ���������翪ʼʱ��+·����Ȩֵ) ��Ϊֻ��ǰ�����ȫ����ɲ��ܿ�ʼ��һ�����͵õ����������
// -�������ʼʱ�� = min(��һ����������ʼʱ��-·����Ȩֵ) ��Ϊ�����������밴����ɣ����������ǰһ��·���ȿ�ʼ�����������
// - �����翪ʼʱ��= �������翪ʼʱ��
// - ��������ʱ�� = �ҽ������ʼʱ��-Ȩֵ
// ���ߵ����翪ʼʱ��=�ߵ�����ʼʱ��ʱ��˵�����������û�����ɶȣ��ǹؼ�·��

//(3�����˼·
// ����ÿ������etv����ǰ������
// ����ÿ������ltv���Ӻ���ǰ��
// ����ete��lte��etv��ltv�Ĺ�ϵ������ߵ����硢����ʼʱ��
// �ж�һ��·����ete�Ƿ���lte��ȣ���Ⱦ��ǹؼ�·��



#include<iostream>
#include<stack>
#include<vector>
using namespace std;

//-----------------------------Ԥ�ȶ������---------------------------------------------------
const int MaxVex = 20;
const int OK = 1;
const int Error = 0;
const int Infinity = 65535;
typedef int Status;

int* etv; //ÿ���������翪ʼʱ��
int* ltv;//ÿ����������ʼʱ��
stack<int> stack2; //���������������н��
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
void CreateAGraph(MGraph m, AGraph* a)
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


//�ڹؼ�·���㷨�У������������Ҫ�ж��Ƿ��л����⣬��Ҫ��ɵ�������Ǳ����������У��������ÿ���������翪ʼʱ��
Status TopologicalSort(AGraph* a)  
{
	
	int count = 0;//01 ��¼���������

	//02 ��ʼ��etv���飬����ÿ����������翪ʼʱ�䶼��0
	
	etv = (int*)malloc(sizeof(int) * a->numVertexs);
	if (!etv)
	{
		exit(-1);
	}
	for (int i = 0; i < a->numVertexs; i++)
	{
		etv[i] = 0;
		
		
	}
	

	//03 ����һ��ջ����������Ϊ0�ĵ㣬ѹ��ջ��,��Ϊ���Ϊ0�Ľ�����ܹ���ʼ�Ľ��

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
		//04 ���Ϊ0��Ԫ�س�ջ�����Ұ���֮�����Ľ�����-1
		int top = nodeList.top();
		//cout << top << endl;
		nodeList.pop();
		count++;
		stack2.push(top); //stack2���ڼ�¼��������

		//�������ĩ�˽�����-1
		EdgeNode* e = a->vexs[top].first;
		

		while (e)
		{

			int k = e->adjvex; //������-1�Ժ�Ľ����ȳ�Ϊ0�ˣ��ͼ�����ջ
			if (!(--a->vexs[k].in))
			{
				nodeList.push(k);
			}
		
			

			//���ǰ���������翪ʼʱ��+·��ʱ�����һ���������翪ʼʱ�仹Ҫ������Ƚ�����Ǹ�
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

//-----------------------------------���������㷨�жϱ����Ƿ��л�����---------------------------------------


//-----------------------------------------�ؼ�·���㷨--------------------------------------------------------

void CriticalPath(AGraph* a)
{
	
	if (TopologicalSort(a) == 0) //���ͼ�л�����������AOEͼ��ֱ���˳�����
	{
		
		exit(-1);
	}
	else //���ͼû�л������������Ĺؼ�·��
	{
		
		
		//01 ��ʼ��ltv���飬����ÿ�����������ʼʱ�䶼�����һ���������翪ʼʱ��

		int top = stack2.top(); //����ط����һ��Ԫ��û�г�ջ
	
		ltv = (int*)malloc(sizeof(int) * a->numVertexs);
		if (!ltv)
		{
			exit(-1);
		}
	
		for (int i = 0; i < a->numVertexs; i++)
		{
			ltv[i]=etv[top];
		}
		
		//02 ��ÿ����������ʼʱ��,����ltv��
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

		//03 ��ÿ��·���Ļ���翪ʼʱ��ete�ͻ����ʼʱ��lte,���ete��lte��ȣ�����ǹؼ�·��

		for (int i = 0; i < a->numVertexs; i++)
		{
			EdgeNode* e = a->vexs[i].first;
			while (e)
			{
				int k = e->adjvex;
				int ete = etv[i]; //��ǰ·���Ļ���翪ʼʱ�䣬������һ�������¼����翪ʼʱ��
				int lte = ltv[k] - e->weight; //��ǰ·���Ļ����ʼʱ�䣬������һ�������¼�������ʼʱ��-weight
				if (ete == lte)
				{
					cout << a->vexs[i].data << "-" << a->vexs[k].data << endl;
				}
				e = e->next;

			}
		}
		
	}
}

//-----------------------------------------�ؼ�·���㷨����--------------------------------------------------------
int main()
{
	MGraph m;
	AGraph a;
	CreateMGraph(&m);
	CreateAGraph(m, &a);
	CriticalPath(&a);
	return 0;
}

