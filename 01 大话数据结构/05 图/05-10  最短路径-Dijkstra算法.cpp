//�Ͻ���˹���㷨��Ҫ����Ϊ
//(1)��ʼ�����ھ�����¼��Distance�г�ʼ���v0��ͼ��������ľ��룬��·��Path����ÿһ������ǰ������v0
//(2)ѡ��:����������ȫ��·�����ҵ���̵������ߣ����������κ�һ��·������������ˣ������ҵ��ĵ�v1
//����v0�����������·�������v1Ϊ�Ѿ��ҵ����·���ĵ㡣��Distance�м�¼������̾��룬Path���¼v1��ǰ������v0
//(3)���£����ҵ�������������û���ҵ��ĵ����·������������¼���ĵ�������δ����ĵ����С��ԭ������δ�����֮��
//�ľ��룬��ô��Distance���и�����̾��룬������Path���У���¼��Щ���̵ıߵ�ǰ����v1��
//ÿ��ѭ���ض����ҵ�һ�����·������һ�����Լ�����ʼ��ѡ���ˣ�����n-1��ѭ��֮�󣬱ض��ܹ���ʼ����ȫ��������̾����·��



#include<iostream>
using namespace std;
//--------------------------------�ڽӾ���ṹ------------------------------------------------

typedef int VertexType; //�������
typedef int EdgeType;  //������
const int MaxVex = 10;  //��󶥵���
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

//Path����������¼���·���ģ�Path[i]=j��ʾ���ڵ�i�����·���У�ǰ�������j
//ShortPathTable��ʾv0��i����̾�����ShortPathTable[i]

void ShortestPath_Dijkstra(MGraph g, int v0 ,int* Path, int* Distance)
{
	int final[MaxVex];//�����ж�˭�Լ��������ˣ�final[i]Ϊ1��ʱ��˵�����1�Լ���ѡ����


	//��ʼ��
	for (int i = 0; i < g.numVertexes; i++)
	{
		final[i] = 0;
		Path[i] = v0;
		Distance[i] = g.arc[v0][i];
	}

	//�ӵ�һ����㿪ʼ��������Ҫ�ѵ�һ�����Ķ�����ֵ
	final[v0] = 1;
	Path[v0] = -1;
	

	int k = v0;

	for (int i = 1; i < g.numVertexes; i++)//ÿ��ѭ���ض��ҵ�һ��������·������һ�����Լ�ѡ���ˣ�
		//���ֻ��Ҫn-1��ѭ�������ҵ�ȫ��������·��
	{
		int min = Infinity;

		//Ѱ��v0������������̾���
		for (int j = 0; j < g.numVertexes; j++)
		{
			if (!final[j] && Distance[j] < min)
			{
				min = Distance[i];
				k = j;
			}
		}

		//�ҵ�����С���Ǹ����ᱻѡ��,���ҵ�һ����v0������̾���ĵ�

		final[k] = 1;


		//ÿ�μ���һ���µ㣬������������·�����������鿴v0��������㣬�����������ľ����Ƕ���
		//����ȵ�ǰС���͸���Path��ShortPathTable����
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
//--------------------------------------�����ڽӾ�������ͼ�Ĵ�������-------------------------------
int main()
{

	MGraph m;
	CreateGraph(&m);
	int path[MaxVex];
	int distance[MaxVex];

	ShortestPath_Dijkstra(m, 0, path, distance);

	int v;
	cout << "��ѯ0���ĸ��������·����" << endl;
	while (cin >> v)
	{
		cout <<"��̾���"<< distance[v] << endl;
		cout << "·��Ϊ" << ends;
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


