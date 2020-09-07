#pragma once
#include "Queue_list.h"
#include "stack_list.h"
#include<iostream>
typedef enum {UNDISCOVERED,DISCOVERED,VISITED} VStatus; //顶点状态
typedef enum {UNDETERMINED,TREE,CROSS,FORWARD,BACKWARD}EType; //边的状态

//辅助函数--求最小值
int min(int lhs, int rhs)
{
	return lhs > rhs ? rhs : lhs;
}

template<typename Tv,typename Te> //结点类型和边类型
class Graph
{
private:
	void reset() //边和结点的信息全部复位
	{
		for (int i = 0; i < n; i++)
		{
			status(i) = UNDISCOVERED;
			dTime(i) = fTime(i) = -1;
			parent(i) = -1;
			priority(i) = INT_MAX;  //初始化结点信息
			for (int j = 0; j < n; j++)
			{
				if (exist(i, j))
				{
					type(i, j) = UNDETERMINED;//初始化边信息
				}
			}
		}
	}
	void BFS(int,int&); //广度优先搜索算法，从某一个结点开始遍历；
	void DFS(int, int&); //深度优先搜索算法，从某一个结点开始遍历
	bool TSort1(int v, int& clock, stack<Tv>* s); //基于DFS的拓扑排序
	bool TSort2(int v, stack<Tv>* s); //删除不必要元素的基于DFS的拓扑排序
	void BCC(int v, int& clock, stack<int>& S); 
	template<typename PU>
	void PFS(int v, PU prioUpdater); //优先级遍历，PU是函数对象类型，用于设定优先级更新规则
	
public:

	//-------------------------------------------顶点操作-------------------------------------------

	int n; //顶点数量
	virtual Tv& vertex(int) = 0; //返回结点数据
	virtual int inDegree(int) = 0; //入度
	virtual int outDegree(int) = 0; //出度
	virtual int insert(const Tv&) = 0; //插入顶点，返回编号
	virtual Tv remove(int) = 0; // 删除某个结点，返回数据
	virtual VStatus& status(int) = 0; //查询某个结点的状态
	virtual int& dTime(int) = 0;  //时间标签
	virtual int& fTime(int) = 0; 
	virtual int& parent(int) = 0; //父节点
	virtual int& priority(int) = 0; //结点的优先级
	virtual int firstNbr(int) = 0; //顶点v的首个向量顶点
	virtual int nextNbr(int, int) = 0; //顶点v相对于顶点j的下一个邻接结点
	virtual int& hca(int v) { return fTime(v); }//最高联通祖先
	//-------------------------------------------边操作-------------------------------------------

	int e; //边总数
	virtual bool exist(int i, int j) = 0;//判断某两个顶点之间的边是否存在
	virtual Te& edge(int i, int j) = 0; //边数据
	virtual int& weight(int i, int j) = 0; //边权重
	virtual void insert(const Te&, int, int, int)=0; //在u和v之间插入权值为w的边e
	virtual void insertD(const Te&, int, int, int) = 0; //在u和v之间插入权值为w的无向边
	virtual Te remove(int, int) = 0; //在两个结点之间插入一条边
	virtual EType& type(int, int) = 0; //边的类型

	//--------------------------------------------图算法-------------------------------------


	void bfs(int); //bfs遍历算法，能够遍历所有的连通域
	void dfs(int); //dfs遍历算法，能够遍历所有的连通域
	template<typename PU>
	void pfs(int,PU); //pfs遍历算法，能够根据自定义优先级规则进行遍历
	void activity(int& d, int& f) //dfs中找到时间到访问结束的时间周期称为活跃时间，活跃时间相互包含的结点具有亲属关系
	{
		d = dTime();//开始被访问时间
		f = fTime();//访问结束时间
	}
	stack<Tv>* tsort1(int v); //拓扑排序，如果返回空栈，说明没有办法进行拓扑排序，版本1是基于DFS的拓扑排序
	stack<Tv>* tsort2(int v); //拓扑排序，如果返回空栈，说明没有办法进行拓扑排序，版本2是删除不必要元素的基于DFS的拓扑排序
	queue<Tv>* tsort3(); //从入度角度进行的拓扑排序
	void bcc(int); //连通域分解，能够筛选出关键结点
	void prim(int); //prim算法，构建最小生成树
	void dijkstra(int); //prim算法，构建最小生成树
};

template<typename Tv, typename Te>
void Graph<Tv,Te>::BFS(int v,int& clock)
{

	queue<int> q; //广度优先遍历
	status(v) = DISCOVERED; //入栈元素定义为被发现的
	q.enqueue(v); //入栈

	while (!q.empty())
	{
		int v = q.dequeue(); //出栈
		dTime(v) = ++clock;
		for (int u = firstNbr(v); u != -1; u = nextNbr(v, u)) //v的相邻结点全部入栈
		{
			if (status(u) == UNDISCOVERED)//如果结点u没被发现过，可以入栈
			{
				std::cout << "结点" << u << std::endl;
				q.enqueue(u);
				status(u) = DISCOVERED;
				type(v, u) = TREE; //如果这个结点没被发现过，边vu就是树的一部分
				parent(u) = v;
			}
			else
			{
				type(v, u) = CROSS;//如果结点被发现过，边vu就属于重复的边
			}
		}

		status(v) = VISITED; //结点访问完毕了

	}

}

template<typename Tv, typename Te>
void Graph<Tv, Te>::bfs(int s)//多连通域bfs算法
{
	reset();
	
	int v = s;
	int clock = 0;
	do
	{
		if (status(v) == UNDISCOVERED)
		{
			std::cout << "根节点" << v << std::endl;
			BFS(v, clock);

		}
	} while (s != (v = ++v % n)); //能从每个结点开始遍历一次
}

template<typename Tv, typename Te>
void Graph<Tv, Te>::DFS(int v, int& clock)
{
	
	dTime(v) = ++clock; //dTime标志着结点b被发现的时间
	status(v) = DISCOVERED;
	for (int u = firstNbr(v); u > -1; u = nextNbr(v, u))
	{
		
		if (status(u) == UNDISCOVERED)
		{
			std::cout << "结点" << u << std::endl;
			type(v, u) = TREE;
			parent(u) = v;
			DFS(u, clock);
		}
		else if (status(u) == DISCOVERED)
		{
			type(v, u) = BACKWARD;
		}
		else
		{
			
			type(v, u) = dTime(v) < dTime(u) ? FORWARD : CROSS;
		}
		
	}
	status(v) = VISITED;
	
	fTime(v) = ++clock;

}

template<typename Tv, typename Te>
void Graph<Tv, Te>::dfs(int s) //能够访问全部联通集的深度优先搜索算法
{
	reset();
	int clock = 0;
	int v = s;
	do
	{
		if (status(v) == UNDISCOVERED)
		{
			std::cout << "根节点" << v << std::endl;
			DFS(v, clock);
		}
	} while (s != (v = ++v % n));
}
template<typename Tv, typename Te>
template<typename PU>
void Graph<Tv, Te>::PFS(int v, PU prioUpdater) //对单个结点进行优先级遍历
{
	status(v) = VISITED;
	priority(v) = 0;
	while (1) //搜索v的邻结点
	{
		for (int w = firstNbr(v); w > -1; w = nextNbr(v, w))
			prioUpdater(this,v,w);
		for (int shortest = INT_MAX, w = 0; w < this->n; w++) //数字小，优先级高，找到优先级最高的那个，作为下一个遍历点
			if (status(w) == UNDISCOVERED)
				if (shortest > priority(w))
				{
					shortest = priority(w);
					v = w; //寻找下一个遍历点
				}
		if (status(v) == VISITED)break; //说明所有点都遍历完了

		status(v) = VISITED;
		type(parent(v), v) = TREE;
		std::cout << "边" << parent(v) << "-" << v << std::endl;

	}
}
template<typename Tv, typename Te>
template<typename PU>
void Graph<Tv, Te>::pfs(int s, PU prioUpdater) //对整个图进行遍历
{
	reset();
	int v = s;
	do
	{
		if (status(v) == UNDISCOVERED)
		{
			PFS(v, prioUpdater);
		}
	} while (s != ((v = ++v) % n));
	
}

template<typename Tv,typename Te>
bool Graph<Tv, Te>::TSort1(int v, int& clock, stack<Tv>* s) //基于DFS框架的拓扑排序
{
	status(v) = DISCOVERED;  //发现结点
	dTime(v) = ++clock; //发现结点的时间
	for (int u = firstNbr(v); u > -1; u = nextNbr(v, u)) //遍历邻结点
	{
		switch (status(u))
		{
		case(UNDISCOVERED): //如果邻结点没有被访问
		{
			parent(u) = v; //说明v是父节点
			type(v,u) = TREE; //u是树的一部分
			if (!TSort1(u, clock, s))return false; //如果不是有向无环图，返回false，不能做拓扑排序
			break;
		}
		case(DISCOVERED):
		{
			type(v, u) = BACKWARD;
			return false; //如果在一路上发现了后向边，说明这条支路有环，不能做拓扑排序
		}
		default:
		{
			type(v, u) = dTime(v) < dTime(u) ? FORWARD : CROSS;
			break;
		}


		}
	}
	status(v) = VISITED;
	fTime(v) = ++clock;
	s->push(vertex(v)); //如果结点的邻结点全部不能访问了，说明该回溯了，也就是出度为0的情况了，放入栈中，倒序出栈就是拓扑排序的结果
	return true;
}

template<typename Tv, typename Te>
stack<Tv>* Graph<Tv, Te>::tsort1(int v) //基于DFS框架的拓扑排序
{
	reset();//重置所有标志位
	int clock = 0; //时间标签
	stack<Tv>* s = new stack<Tv>;//最终用来返回的栈
	int m = v;
	
	do 
	{
		if (status(m) == UNDISCOVERED)
		{
			if (!TSort1(m, clock, s)) //如果不能进行拓扑排序，应该清空栈
			{
				while (!s->empty())
				{
					s->pop();
				}
				break;
			}
		}
	} while (v != (m = (++m % n)));
	return s;
}

template<typename Tv, typename Te>
bool Graph<Tv, Te>::TSort2(int v,stack<Tv>* s) //删除不必要数据的基于DFS框架的拓扑排序
{
	status(v) = DISCOVERED;  //发现结点
	for (int u = firstNbr(v); u > -1; u = nextNbr(v, u)) //遍历邻结点
	{
		switch (status(u))
		{
		case(UNDISCOVERED): //如果邻结点没有被访问
		{
			if (!TSort2(u, s))return false; //如果不是有向无环图，返回false，不能做拓扑排序
			break;
		}
		case(DISCOVERED):
		{
			return false; //如果在一路上发现了后向边，说明这条支路有环，不能做拓扑排序
		}
		default:
			break;
		}
	}
	status(v) = VISITED;
	s->push(vertex(v)); //如果结点的邻结点全部不能访问了，说明该回溯了，也就是出度为0的情况了，放入栈中，倒序出栈就是拓扑排序的结果
	return true;
}
template<typename Tv, typename Te>
stack<Tv>* Graph<Tv, Te>::tsort2(int v) //删除不必要数据的基于DFS的拓扑排序
{
	reset();//重置所有标志位
	stack<Tv>* s = new stack<Tv>;//最终用来返回的栈
	int m = v;

	do
	{
		if (status(m) == UNDISCOVERED)
		{
			if (!TSort2(m,s)) //如果不能进行拓扑排序，应该清空栈
			{
				while (!s->empty())
				{
					s->pop();
				}
				break;
			}
		}
	} while (v != (m = (++m % n)));
	return s;
}

template<typename Tv, typename Te>
queue<Tv>* Graph<Tv, Te>::tsort3() //从入度角度进行的拓扑排序，会把表删除
{
	int v; //记录结点下标的
	stack<int> s; //存储初始入度为0的结点
	for (int i = 0; i < n; i++)//入度为0的结点入栈
		if (inDegree(i) == 0)s.push(i);
	queue<Tv>* q = new queue<Tv>; //最终返回的就是这个队列
	while (!s.empty())//如果栈没空
	{
		q->enqueue(vertex(v=s.pop())); 

		for (int i = 0; i < n; i++) //如果与v相连的结点有入度为1的，就是马上要输出的
			if (exist(v, i))
				if (inDegree(i) < 2) s.push(i);
			
		remove(v); //删除结点v
			

	}
	if (q->size() < n)
	{
		delete q;
		q = nullptr;
	}
	return q;

}

template<typename Tv, typename Te>
void Graph<Tv, Te>::bcc(int v)//连通域分解，用于筛选关结点
{
	reset();
	int m = v;
	stack<int> S;
	int clock = 0;
	do
	{
		if (status(m) == UNDISCOVERED)
		{
			BCC(m, clock, S);
			S.pop();//pop弹出最后一个顶点，是当前连通域的起点。这个结点和BCC()中重新入栈的v结点，都是关节点
		}
	} while (v != (m = ++m % n));

}

template<typename Tv,typename Te>
void Graph<Tv, Te>::BCC(int v, int& clock, stack<int>& S) //连通域分解功能函数
{
	hca(v) = dTime(v) = ++clock;
	status(v) = DISCOVERED;
	S.push(v);
	
	for (int u = firstNbr(v); u > -1; u = nextNbr(v, u))
	{
		
		switch (status(u))
		{
			
		case(UNDISCOVERED):
			{
				parent(u) = v;
				type(v, u) = TREE;
				BCC(u, clock, S);//一直找到最后面
				if (hca(u) < dTime(v)) //如果u能够联通到比v还靠前的结点，说明v不是联通结点
				{
					hca(v) = min(hca(u), hca(v)); //这个地方与hca(u)而不是dTime(u)比较是因为u在v后面，把v前面的点删了可能还是可以连接到hca(u)的
				}
				else //如果u联通不到v前面，说明v是联通结点，那么v后面那些结点就都没有用了，可以出栈了
				{
					while (v != S.pop());
					S.push(v); //这个地放入栈的v，就是关节点。同时也构成了上一级树的第一个叶节点
					std::cout << S.top() << std::endl;
				}
				break;
				
			}
		case(DISCOVERED):
		{
			type(v, u) = BACKWARD;
			if (u != parent(v))hca(v) = min(hca(v), dTime(u));
			//这个地方与dTime(u)比较而不与hca(u)比较是因为，u在v前面，u能连接的最前端，不一定是双线连接的
			break;
		}
		default:
		{
			type(v, u) = dTime(v) < dTime(u) ? FORWARD : CROSS;
			break;
		}

			
		}//switch
	}//for
	status(v) = VISITED;


}

template<typename Tv, typename Te>
void Graph<Tv, Te>::prim(int v)
{
	reset(); priority(v) = 0;
	for (int i = 0; i < this->n; i++){
		status(v) = VISITED;
		if (parent(v) != -1)
		{
			type(parent(v), v) = TREE;
			std::cout << "边" << parent(v) << "-" << v << std::endl;
		}
		for (int w = firstNbr(v); w > -1; w = nextNbr(v, w))
			if (status(w) == UNDISCOVERED && priority(w) > weight(v, w))
				{priority(w) = weight(v, w); parent(w) = v;	}
		for (int shortest = INT_MAX, w = 0; w < n; w++)
			if (status(w) == UNDISCOVERED && shortest > priority(w))
				{shortest = priority(w); v = w;	}
	}
}

template<typename Tv, typename Te>
void Graph<Tv, Te>::dijkstra(int v)
{
	reset(); priority(v) = 0;
	for (int i = 0; i < this->n; i++) {
		status(v) = VISITED;
		if (parent(v) != -1)
		{
			type(parent(v), v) = TREE;
			std::cout << "边" << parent(v) << "-" << v << std::endl;
		}
		for (int w = firstNbr(v); w > -1; w = nextNbr(v, w))
			if (status(w) == UNDISCOVERED && priority(w) > weight(v, w)+priority(v))
			{
				priority(w) = weight(v, w) + priority(v); parent(w) = v;
			}
		for (int shortest = INT_MAX, w = 0; w < n; w++)
			if (status(w) == UNDISCOVERED && shortest > priority(w))
			{
				shortest = priority(w); v = w;
			}
	}
}

//-----------------------------------一个prim算法的函数对象，能够借助pfs框架实现prim算法-------------------------
template<typename Tv,typename Te>
class primPU
{
public:
		void operator() (Graph<Tv, Te>* g, int v, int w) //v是父节点，w是子节点
	{
		if (g->status(w) == UNDISCOVERED)
		{
			
			if (g->priority(w) > g->weight(v, w))
			{
				g->parent(w) = v;
				g->priority(w) = g->weight(v, w);
			}
		}
	}
};

//------------------------------一个dijkstra算法的函数对象，能够借助pfs框架实现dijkstra算法-------------------------
template<typename Tv, typename Te>
class dikstraPU
{
public:
	void operator() (Graph<Tv, Te>* g, int v, int w) //v是父节点，w是子节点
	{
		if (g->status(w) == UNDISCOVERED)
		{

			if (g->priority(w) > g->weight(v, w)+g->priority(v))
			{
				g->parent(w) = v;
				g->priority(w) = g->weight(v, w) + g->priority(v);
			}
		}
	}
};