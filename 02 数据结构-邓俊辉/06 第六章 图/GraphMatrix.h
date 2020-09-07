#pragma once
#include "vector.h"
#include "Graph.h"


template<typename Tv>
struct Vertex //�����������
{
	Tv data; //�������
	int inDegree; //������
	int outDegree; //������
	VStatus status; //���״̬
	int dTime, fTime; //ʱ���ǩ
	int parent; int priority; //���常�ڵ�ͽ������ȼ�
	
	//���캯��
	Vertex(const Tv& data = (Tv)0):
		data(data),inDegree(0),outDegree(0),status(UNDISCOVERED),
		dTime(-1),fTime(-1),parent(-1),priority(INT_MAX){}
};

template<typename Te>
struct Edge //����������
{
	Te data; int weight; //�ߵ����ݺ�Ȩ��
	EType type;
	//���캯��
	Edge(const Te& data,int weight):data(data),weight(weight),type(UNDETERMINED){}
};

template<typename Tv,typename Te>
class GraphMatrix :public Graph<Tv,Te>
{
private:
	vector<Vertex<Tv>> V; //���㼯��
	vector<vector<Edge<Te>*>> E; //�߼�
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

	//���㾲̬����
	virtual Tv& vertex(int i) { return V[i].data; } //����
	virtual int inDegree(int i) { return V[i].inDegree;}//���
	virtual int outDegree(int i) { return V[i].outDegree; }//����
	virtual VStatus& status(int i) { return V[i].status; }//���״̬
	virtual int& dTime(int i) { return V[i].dTime; }//���ʱ���ǩ
	virtual int& fTime(int i) { return V[i].fTime; }//����ʱ���ǩ
	virtual int& parent(int i) { return V[i].parent; }//���ڵ�
	virtual int& priority(int i) { return V[i].priority; }//���ȼ�
	virtual int firstNbr(int i) { return nextNbr(i, this->n); }//��һ�����
	virtual int nextNbr(int i, int j) //����ڶ���j����һ���ڽ��
	{
		while ((j > -1) && !exist(i, --j));return j;
	}


	//���㶯̬����
	virtual int insert(const Tv& vertex) //����һ��ֵΪvertex�Ľ�㣬���ҷ�������
	{
		for (int i = 0; i < this->n; i++)E[i].insert(nullptr); this->n++; //������ÿһ�ж�����һ����ָ��
		E.insert(vector<Edge<Te>*>(this->n,this->n,nullptr)); //���Ҳ���һ������Ϊn����ģΪn�Ŀ�ָ��
		return V.insert(Vertex<Tv>(vertex)); //���������һ���µĽ�㣬���ҷ��ز����λ���±�
	}
	virtual Tv remove(int i) //ɾ����i����㣬���ҷ��ص�i����㴢�������
	{
		int vData = V[i].data;
		for (int j= 0; j < this->n; j++) 
		{
			if (exist(i, j))
			{
				delete E[i][j];//ɾ����iΪ���ı�
				E[i][j] = nullptr;
				V[j].inDegree--;
			}
		}
		E.remove(i); this->n--; V.remove(i);//ɾ����i�У������-1��ɾ�����i
		for (int j = 0; j < this->n; j++) //ɾ����iΪ�յ�ı�
		{
			if (Edge<Te>* e = E[j].remove(i)) 
			{
				delete e;
				V[j].outDegree--;
			}
		}
		
		return vData;
	}
	//�߾�̬����
	virtual bool exist(int i, int j)//�ж�ĳ�����Ƿ����
	{ return (i >= 0) && (i < this->n) && (j >= 0) && (j < this->n) && E[i][j] != nullptr; }
	virtual Te& edge(int i, int j) { return E[i][j]->data; }//�ߵ�����
	virtual int& weight(int i, int j) { return E[i][j]->weight; }//�ߵ�Ȩֵ
	virtual EType& type(int i, int j) { return E[i][j]->type; }//�ߵ�����
	
	//�߶�̬����
	virtual void insert(const Te& edge, int w, int i, int j) //����ȨֵΪw�ı�e(i,j)
	{
		if (exist(i, j))return; //������Ѿ������ˣ��ͷ���
		 
		E[i][j] = new Edge<Te>(edge, w);//�����µı�
		this->e++;//����+1
		V[i].outDegree++;
		V[j].inDegree++;
		

	}
	virtual void insertD(const Te& edge, int w, int i, int j) //����ȨֵΪw�������e(i,j)
	{
		if (exist(i, j)||exist(j,i))return; //������Ѿ������ˣ��ͷ���

		E[i][j] = new Edge<Te>(edge, w);//�����µı�
		E[j][i] = new Edge<Te>(edge, w);//�����µı�
		this->e++;//����+1
		


	}
	virtual Te remove(int i, int j)//ɾ��i��j֮��ı�
	{
		Te eData = edge(i, j);
		delete E[i][j];
		E[i][j] = nullptr;
		this->e--;
		V[i].outDegree--;
		V[j].inDegree--;
		return eData;
	}

	//ͼ�㷨
};

