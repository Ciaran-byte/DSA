#include<iostream>
using namespace std;
//--------------------------------�ڽӾ���ṹ------------------------------------------------

typedef int VertexType; //�������
typedef int EdgeType;  //������
const int MaxVex = 100;  //��󶥵���
const int Infinity = 65535; //��ʾ����

typedef struct
{
	VertexType vexs[MaxVex];//���嶥��
	EdgeType arc[MaxVex][MaxVex]; //�����(��)
	int numVertexes, numEdges; //��ǰ�������ͱ���
}MGraph;



//--------------------------------�ڽӾ���ṹ�������-----------------------------------------


//--------------------------------------�����ڽӾ�������ͼ�Ĵ���---------------------------------

void CreateGraph(MGraph* g)
{
	//���������Ϣ
	cout << "�����붥�����ͱ���" << endl;
	cout << "����:" << ends;

	cin >> g->numVertexes;
	cout << "����:" << ends;
	cin >> g->numEdges;

	//���붥����Ϣ
	cout << "�����붥����Ϣ:" << endl;
	for (int i = 0; i < g->numVertexes; i++)
	{
		cin >> g->vexs[i];
	}

	//����Ϣ�ĳ�ʼ��
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

	//�����ڽӾ���
	for (int i = 0; i < g->numEdges; i++)
	{
		cout << "�������(vi,vj)��Ӧ���±�i��j��Ȩw" << endl;
		int row, col, w;
		cin >> row >> col >> w;
		g->arc[row][col] = w;
		g->arc[col][row] = g->arc[row][col]; //��Ϊ����ͼ�������ǶԳƾ���

	}







}

//--------------------------------------�����ڽӾ�������ͼ�Ĵ�������-------------------------------

//-----------------------------------------�����ڽӾ��κ�prim�㷨����С������------------------------

void MiniSpanTree_Prim(MGraph g)
{
	//01 ������Ҫ�ı���
	int adjvex[MaxVex]; //�������浱ǰ�Ѿ����Ӻõ���������û�����ӺõĽ��乹����̾���Ľ���
	int lowcost[MaxVex];  //�������浱ǰ�Ѿ����Ӻõ���������û�����ӺõĽ������̾���

	adjvex[0] = 0; //��ʾ�ӽ��0��ʼ��������
	lowcost[0] = 0;  //lowcost����ľ����Ϊ����
					//(1)Inf,��ʾĿǰadjvex�е���Ӧ����û�����ӹ�ϵ
	                  //(2)��ͨ���֣�lowcost[j]��ʾadjvex[j]��j֮��ľ���
					//��3����ʾ��������Ѿ��������ˣ�j��adjvex[j]������㶼������������

	//02 ��ʼ�����ӽ��0��ʼ���ȼ�����0�����������֮��ľ���
	for (int i = 1; i < g.numVertexes; i++)
	{
		adjvex[i] = 0; //���ɱ߼� i��adjvex[i]��һ���ߵ��������
	}
	for (int i = 1; i < g.numVertexes; i++) //���������ʼΪ���0������������ľ���
	{
		lowcost[i] = g.arc[0][i];
	}

	//03 
	int k=0;
	for (int i = 1; i < g.numVertexes; i++)//�����ѭ�����������ڣ���ֹͼ������ͨͼ���ж����ͼ�����ж����С������
	{
		int min = Infinity;

		//03-1 �������
		for (int j = 1; j < g.numVertexes; j++)
		{
			if (lowcost[j] != 0 && lowcost[j] < min) //���������ⲿ���֮�����̾��룬����¼�Ǹ����
			{
				min = lowcost[j];
				k = j; //���������С��λ��
			}
		}

		//03-2 �����
		cout << adjvex[k] << "-" << k << endl;
		lowcost[k] = 0; //��ʾk��adjvex[k]�������ɹ�����

		//03-3 ���±߼��;��뼯��


		//�ոս��k����������������ӣ��������k���������δ���ӵĽ��֮��ľ��룬���k��j���ӵ��߶α����ڴ��
		//j��adjvex[j]֮��ľ���lowcost[j]Ҫ�̣���ô����adjvex[j]=���k������lowcost[j]����Ϊk��j֮��ľ���
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

//---------------------------------------�����ڽӾ��κ�prim�㷨����С����������---------------------
int main()
{

	MGraph m;
	CreateGraph(&m);
	MiniSpanTree_Prim(m);
	return 0;
}


