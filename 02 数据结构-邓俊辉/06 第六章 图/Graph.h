#pragma once
#include "Queue_list.h"
#include "stack_list.h"
#include<iostream>
typedef enum {UNDISCOVERED,DISCOVERED,VISITED} VStatus; //����״̬
typedef enum {UNDETERMINED,TREE,CROSS,FORWARD,BACKWARD}EType; //�ߵ�״̬

//��������--����Сֵ
int min(int lhs, int rhs)
{
	return lhs > rhs ? rhs : lhs;
}

template<typename Tv,typename Te> //������ͺͱ�����
class Graph
{
private:
	void reset() //�ߺͽ�����Ϣȫ����λ
	{
		for (int i = 0; i < n; i++)
		{
			status(i) = UNDISCOVERED;
			dTime(i) = fTime(i) = -1;
			parent(i) = -1;
			priority(i) = INT_MAX;  //��ʼ�������Ϣ
			for (int j = 0; j < n; j++)
			{
				if (exist(i, j))
				{
					type(i, j) = UNDETERMINED;//��ʼ������Ϣ
				}
			}
		}
	}
	void BFS(int,int&); //������������㷨����ĳһ����㿪ʼ������
	void DFS(int, int&); //������������㷨����ĳһ����㿪ʼ����
	bool TSort1(int v, int& clock, stack<Tv>* s); //����DFS����������
	bool TSort2(int v, stack<Tv>* s); //ɾ������ҪԪ�صĻ���DFS����������
	void BCC(int v, int& clock, stack<int>& S); 
	template<typename PU>
	void PFS(int v, PU prioUpdater); //���ȼ�������PU�Ǻ����������ͣ������趨���ȼ����¹���
	
public:

	//-------------------------------------------�������-------------------------------------------

	int n; //��������
	virtual Tv& vertex(int) = 0; //���ؽ������
	virtual int inDegree(int) = 0; //���
	virtual int outDegree(int) = 0; //����
	virtual int insert(const Tv&) = 0; //���붥�㣬���ر��
	virtual Tv remove(int) = 0; // ɾ��ĳ����㣬��������
	virtual VStatus& status(int) = 0; //��ѯĳ������״̬
	virtual int& dTime(int) = 0;  //ʱ���ǩ
	virtual int& fTime(int) = 0; 
	virtual int& parent(int) = 0; //���ڵ�
	virtual int& priority(int) = 0; //�������ȼ�
	virtual int firstNbr(int) = 0; //����v���׸���������
	virtual int nextNbr(int, int) = 0; //����v����ڶ���j����һ���ڽӽ��
	virtual int& hca(int v) { return fTime(v); }//�����ͨ����
	//-------------------------------------------�߲���-------------------------------------------

	int e; //������
	virtual bool exist(int i, int j) = 0;//�ж�ĳ��������֮��ı��Ƿ����
	virtual Te& edge(int i, int j) = 0; //������
	virtual int& weight(int i, int j) = 0; //��Ȩ��
	virtual void insert(const Te&, int, int, int)=0; //��u��v֮�����ȨֵΪw�ı�e
	virtual void insertD(const Te&, int, int, int) = 0; //��u��v֮�����ȨֵΪw�������
	virtual Te remove(int, int) = 0; //���������֮�����һ����
	virtual EType& type(int, int) = 0; //�ߵ�����

	//--------------------------------------------ͼ�㷨-------------------------------------


	void bfs(int); //bfs�����㷨���ܹ��������е���ͨ��
	void dfs(int); //dfs�����㷨���ܹ��������е���ͨ��
	template<typename PU>
	void pfs(int,PU); //pfs�����㷨���ܹ������Զ������ȼ�������б���
	void activity(int& d, int& f) //dfs���ҵ�ʱ�䵽���ʽ�����ʱ�����ڳ�Ϊ��Ծʱ�䣬��Ծʱ���໥�����Ľ�����������ϵ
	{
		d = dTime();//��ʼ������ʱ��
		f = fTime();//���ʽ���ʱ��
	}
	stack<Tv>* tsort1(int v); //��������������ؿ�ջ��˵��û�а취�����������򣬰汾1�ǻ���DFS����������
	stack<Tv>* tsort2(int v); //��������������ؿ�ջ��˵��û�а취�����������򣬰汾2��ɾ������ҪԪ�صĻ���DFS����������
	queue<Tv>* tsort3(); //����ȽǶȽ��е���������
	void bcc(int); //��ͨ��ֽ⣬�ܹ�ɸѡ���ؼ����
	void prim(int); //prim�㷨��������С������
	void dijkstra(int); //prim�㷨��������С������
};

template<typename Tv, typename Te>
void Graph<Tv,Te>::BFS(int v,int& clock)
{

	queue<int> q; //������ȱ���
	status(v) = DISCOVERED; //��ջԪ�ض���Ϊ�����ֵ�
	q.enqueue(v); //��ջ

	while (!q.empty())
	{
		int v = q.dequeue(); //��ջ
		dTime(v) = ++clock;
		for (int u = firstNbr(v); u != -1; u = nextNbr(v, u)) //v�����ڽ��ȫ����ջ
		{
			if (status(u) == UNDISCOVERED)//������uû�����ֹ���������ջ
			{
				std::cout << "���" << u << std::endl;
				q.enqueue(u);
				status(u) = DISCOVERED;
				type(v, u) = TREE; //���������û�����ֹ�����vu��������һ����
				parent(u) = v;
			}
			else
			{
				type(v, u) = CROSS;//�����㱻���ֹ�����vu�������ظ��ı�
			}
		}

		status(v) = VISITED; //�����������

	}

}

template<typename Tv, typename Te>
void Graph<Tv, Te>::bfs(int s)//����ͨ��bfs�㷨
{
	reset();
	
	int v = s;
	int clock = 0;
	do
	{
		if (status(v) == UNDISCOVERED)
		{
			std::cout << "���ڵ�" << v << std::endl;
			BFS(v, clock);

		}
	} while (s != (v = ++v % n)); //�ܴ�ÿ����㿪ʼ����һ��
}

template<typename Tv, typename Te>
void Graph<Tv, Te>::DFS(int v, int& clock)
{
	
	dTime(v) = ++clock; //dTime��־�Ž��b�����ֵ�ʱ��
	status(v) = DISCOVERED;
	for (int u = firstNbr(v); u > -1; u = nextNbr(v, u))
	{
		
		if (status(u) == UNDISCOVERED)
		{
			std::cout << "���" << u << std::endl;
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
void Graph<Tv, Te>::dfs(int s) //�ܹ�����ȫ����ͨ����������������㷨
{
	reset();
	int clock = 0;
	int v = s;
	do
	{
		if (status(v) == UNDISCOVERED)
		{
			std::cout << "���ڵ�" << v << std::endl;
			DFS(v, clock);
		}
	} while (s != (v = ++v % n));
}
template<typename Tv, typename Te>
template<typename PU>
void Graph<Tv, Te>::PFS(int v, PU prioUpdater) //�Ե������������ȼ�����
{
	status(v) = VISITED;
	priority(v) = 0;
	while (1) //����v���ڽ��
	{
		for (int w = firstNbr(v); w > -1; w = nextNbr(v, w))
			prioUpdater(this,v,w);
		for (int shortest = INT_MAX, w = 0; w < this->n; w++) //����С�����ȼ��ߣ��ҵ����ȼ���ߵ��Ǹ�����Ϊ��һ��������
			if (status(w) == UNDISCOVERED)
				if (shortest > priority(w))
				{
					shortest = priority(w);
					v = w; //Ѱ����һ��������
				}
		if (status(v) == VISITED)break; //˵�����е㶼��������

		status(v) = VISITED;
		type(parent(v), v) = TREE;
		std::cout << "��" << parent(v) << "-" << v << std::endl;

	}
}
template<typename Tv, typename Te>
template<typename PU>
void Graph<Tv, Te>::pfs(int s, PU prioUpdater) //������ͼ���б���
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
bool Graph<Tv, Te>::TSort1(int v, int& clock, stack<Tv>* s) //����DFS��ܵ���������
{
	status(v) = DISCOVERED;  //���ֽ��
	dTime(v) = ++clock; //���ֽ���ʱ��
	for (int u = firstNbr(v); u > -1; u = nextNbr(v, u)) //�����ڽ��
	{
		switch (status(u))
		{
		case(UNDISCOVERED): //����ڽ��û�б�����
		{
			parent(u) = v; //˵��v�Ǹ��ڵ�
			type(v,u) = TREE; //u������һ����
			if (!TSort1(u, clock, s))return false; //������������޻�ͼ������false����������������
			break;
		}
		case(DISCOVERED):
		{
			type(v, u) = BACKWARD;
			return false; //�����һ·�Ϸ����˺���ߣ�˵������֧·�л�����������������
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
	s->push(vertex(v)); //��������ڽ��ȫ�����ܷ����ˣ�˵���û����ˣ�Ҳ���ǳ���Ϊ0������ˣ�����ջ�У������ջ������������Ľ��
	return true;
}

template<typename Tv, typename Te>
stack<Tv>* Graph<Tv, Te>::tsort1(int v) //����DFS��ܵ���������
{
	reset();//�������б�־λ
	int clock = 0; //ʱ���ǩ
	stack<Tv>* s = new stack<Tv>;//�����������ص�ջ
	int m = v;
	
	do 
	{
		if (status(m) == UNDISCOVERED)
		{
			if (!TSort1(m, clock, s)) //������ܽ�����������Ӧ�����ջ
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
bool Graph<Tv, Te>::TSort2(int v,stack<Tv>* s) //ɾ������Ҫ���ݵĻ���DFS��ܵ���������
{
	status(v) = DISCOVERED;  //���ֽ��
	for (int u = firstNbr(v); u > -1; u = nextNbr(v, u)) //�����ڽ��
	{
		switch (status(u))
		{
		case(UNDISCOVERED): //����ڽ��û�б�����
		{
			if (!TSort2(u, s))return false; //������������޻�ͼ������false����������������
			break;
		}
		case(DISCOVERED):
		{
			return false; //�����һ·�Ϸ����˺���ߣ�˵������֧·�л�����������������
		}
		default:
			break;
		}
	}
	status(v) = VISITED;
	s->push(vertex(v)); //��������ڽ��ȫ�����ܷ����ˣ�˵���û����ˣ�Ҳ���ǳ���Ϊ0������ˣ�����ջ�У������ջ������������Ľ��
	return true;
}
template<typename Tv, typename Te>
stack<Tv>* Graph<Tv, Te>::tsort2(int v) //ɾ������Ҫ���ݵĻ���DFS����������
{
	reset();//�������б�־λ
	stack<Tv>* s = new stack<Tv>;//�����������ص�ջ
	int m = v;

	do
	{
		if (status(m) == UNDISCOVERED)
		{
			if (!TSort2(m,s)) //������ܽ�����������Ӧ�����ջ
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
queue<Tv>* Graph<Tv, Te>::tsort3() //����ȽǶȽ��е��������򣬻�ѱ�ɾ��
{
	int v; //��¼����±��
	stack<int> s; //�洢��ʼ���Ϊ0�Ľ��
	for (int i = 0; i < n; i++)//���Ϊ0�Ľ����ջ
		if (inDegree(i) == 0)s.push(i);
	queue<Tv>* q = new queue<Tv>; //���շ��صľ����������
	while (!s.empty())//���ջû��
	{
		q->enqueue(vertex(v=s.pop())); 

		for (int i = 0; i < n; i++) //�����v�����Ľ�������Ϊ1�ģ���������Ҫ�����
			if (exist(v, i))
				if (inDegree(i) < 2) s.push(i);
			
		remove(v); //ɾ�����v
			

	}
	if (q->size() < n)
	{
		delete q;
		q = nullptr;
	}
	return q;

}

template<typename Tv, typename Te>
void Graph<Tv, Te>::bcc(int v)//��ͨ��ֽ⣬����ɸѡ�ؽ��
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
			S.pop();//pop�������һ�����㣬�ǵ�ǰ��ͨ�����㡣�������BCC()��������ջ��v��㣬���ǹؽڵ�
		}
	} while (v != (m = ++m % n));

}

template<typename Tv,typename Te>
void Graph<Tv, Te>::BCC(int v, int& clock, stack<int>& S) //��ͨ��ֽ⹦�ܺ���
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
				BCC(u, clock, S);//һֱ�ҵ������
				if (hca(u) < dTime(v)) //���u�ܹ���ͨ����v����ǰ�Ľ�㣬˵��v������ͨ���
				{
					hca(v) = min(hca(u), hca(v)); //����ط���hca(u)������dTime(u)�Ƚ�����Ϊu��v���棬��vǰ��ĵ�ɾ�˿��ܻ��ǿ������ӵ�hca(u)��
				}
				else //���u��ͨ����vǰ�棬˵��v����ͨ��㣬��ôv������Щ���Ͷ�û�����ˣ����Գ�ջ��
				{
					while (v != S.pop());
					S.push(v); //����ط���ջ��v�����ǹؽڵ㡣ͬʱҲ��������һ�����ĵ�һ��Ҷ�ڵ�
					std::cout << S.top() << std::endl;
				}
				break;
				
			}
		case(DISCOVERED):
		{
			type(v, u) = BACKWARD;
			if (u != parent(v))hca(v) = min(hca(v), dTime(u));
			//����ط���dTime(u)�Ƚ϶�����hca(u)�Ƚ�����Ϊ��u��vǰ�棬u�����ӵ���ǰ�ˣ���һ����˫�����ӵ�
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
			std::cout << "��" << parent(v) << "-" << v << std::endl;
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
			std::cout << "��" << parent(v) << "-" << v << std::endl;
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

//-----------------------------------һ��prim�㷨�ĺ��������ܹ�����pfs���ʵ��prim�㷨-------------------------
template<typename Tv,typename Te>
class primPU
{
public:
		void operator() (Graph<Tv, Te>* g, int v, int w) //v�Ǹ��ڵ㣬w���ӽڵ�
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

//------------------------------һ��dijkstra�㷨�ĺ��������ܹ�����pfs���ʵ��dijkstra�㷨-------------------------
template<typename Tv, typename Te>
class dikstraPU
{
public:
	void operator() (Graph<Tv, Te>* g, int v, int w) //v�Ǹ��ڵ㣬w���ӽڵ�
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