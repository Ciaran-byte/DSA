#pragma once
#include "vector.h"
#include "Graph.h"


template<typename Tv>
struct Vertex //结点数据类型
{
	Tv data; //结点数据
	int inDegree; //结点入度
	int outDegree; //结点出度
	VStatus status; //结点状态
	int dTime, fTime; //时间标签
	int parent; int priority; //定义父节点和结点的优先级
	
	//构造函数
	Vertex(const Tv& data = (Tv)0):
		data(data),inDegree(0),outDegree(0),status(UNDISCOVERED),
		dTime(-1),fTime(-1),parent(-1),priority(INT_MAX){}
};

template<typename Te>
struct Edge //边数据类型
{
	Te data; int weight; //边的数据和权重
	EType type;
	//构造函数
	Edge(const Te& data,int weight):data(data),weight(weight),type(UNDETERMINED){}
};

template<typename Tv,typename Te>
class GraphMatrix :public Graph<Tv,Te>
{
private:
	vector<Vertex<Tv>> V; //顶点集合
	vector<vector<Edge<Te>*>> E; //边集
public:
	GraphMatrix() { this->n = 0; this->e = 0; }
	~GraphMatrix()
	{
		for (int j = 0; j < this->n; j++)
		{
			for (int k = 0; k < this->n; k++)
			{
				delete E[j][k];
			}
		}
	}

	//顶点静态操作
	virtual Tv& vertex(int i) { return V[i].data; } //数据
	virtual int inDegree(int i) { return V[i].inDegree;}//入度
	virtual int outDegree(int i) { return V[i].outDegree; }//出度
	virtual VStatus& status(int i) { return V[i].status; }//结点状态
	virtual int& dTime(int i) { return V[i].dTime; }//结点时间标签
	virtual int& fTime(int i) { return V[i].fTime; }//结点的时间标签
	virtual int& parent(int i) { return V[i].parent; }//父节点
	virtual int& priority(int i) { return V[i].priority; }//优先级
	virtual int firstNbr(int i) { return nextNbr(i, this->n); }//第一个结点
	virtual int nextNbr(int i, int j) //相对于顶点j的下一个邻结点
	{
		while ((j > -1) && !exist(i, --j));return j;
	}


	//顶点动态操作
	virtual int insert(const Tv& vertex) //插入一个值为vertex的结点，并且返回索引
	{
		for (int i = 0; i < this->n; i++)E[i].insert(nullptr); this->n++; //本来的每一行都插入一个空指针
		E.insert(vector<Edge<Te>*>(this->n,this->n,nullptr)); //并且插入一行容量为n，规模为n的空指针
		return V.insert(Vertex<Tv>(vertex)); //往结点表插入一个新的结点，并且返回插入的位置下标
	}
	virtual Tv remove(int i) //删除第i个结点，并且返回第i个结点储存的数据
	{
		int vData = V[i].data;
		for (int j= 0; j < this->n; j++) 
		{
			if (exist(i, j))
			{
				delete E[i][j];//删除以i为起点的边
				E[i][j] = nullptr;
				V[j].inDegree--;
			}
		}
		E.remove(i); this->n--; V.remove(i);//删除第i行，结点数-1，删掉结点i
		for (int j = 0; j < this->n; j++) //删除以i为终点的边
		{
			if (Edge<Te>* e = E[j].remove(i)) 
			{
				delete e;
				V[j].outDegree--;
			}
		}
		
		return vData;
	}
	//边静态操作
	virtual bool exist(int i, int j)//判断某条边是否存在
	{ return (i >= 0) && (i < this->n) && (j >= 0) && (j < this->n) && E[i][j] != nullptr; }
	virtual Te& edge(int i, int j) { return E[i][j]->data; }//边的数据
	virtual int& weight(int i, int j) { return E[i][j]->weight; }//边的权值
	virtual EType& type(int i, int j) { return E[i][j]->type; }//边的类型
	
	//边动态操作
	virtual void insert(const Te& edge, int w, int i, int j) //插入权值为w的边e(i,j)
	{
		if (exist(i, j))return; //如果边已经存在了，就返回
		 
		E[i][j] = new Edge<Te>(edge, w);//创建新的边
		this->e++;//边数+1
		V[i].outDegree++;
		V[j].inDegree++;
		

	}
	virtual void insertD(const Te& edge, int w, int i, int j) //插入权值为w的无向边e(i,j)
	{
		if (exist(i, j)||exist(j,i))return; //如果边已经存在了，就返回

		E[i][j] = new Edge<Te>(edge, w);//创建新的边
		E[j][i] = new Edge<Te>(edge, w);//创建新的边
		this->e++;//边数+1
		


	}
	virtual Te remove(int i, int j)//删除i和j之间的边
	{
		Te eData = edge(i, j);
		delete E[i][j];
		E[i][j] = nullptr;
		this->e--;
		V[i].outDegree--;
		V[j].inDegree--;
		return eData;
	}

	//图算法
};

