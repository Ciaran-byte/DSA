#pragma once
#define InHeap(n,i)(((-1)<(i))&&((i)<(n))) //�ж�P[i]�Ƿ�Ϸ�
#define Parent(i)  ((i-1)>>2) //���׽��
#define LastInternal(n) Parent(n-1)  //���һ���ڲ���㣬����ĩ���ĸ��ڵ�
#define LChild(i) (1+((i)<<1)) //����
#define RChild(i) ((1+(i))<<1) //�Һ���
#define ParentValid(i) (i>0) //�жϸ��ڵ��Ƿ����
#define LChildValid(n,i) InHeap(n,LChild(i)); //�ж��Ƿ��������
#define RChildValid(n,i) InHeap(n,RChild(i)); //�ж��Ƿ�����Һ���
#define Bigger(PQ,i,j) ((PQ[i]>PQ[j])?i:j) //��������ߵ���,��ȵ�ʱ��ȡǰ��
#define ProperParent(PQ,n,i)/*�������ڵ������*/ \
					(RChildValid(n,i)?Bigger(PQ,Bigger(PQ,i,LChild(i)),RChild(i)):\
					(LChildValid(n,i)?Bigger(PQ,i,LChild(i)):i))


#include "vector.h"
#include "PQ.h"
template<typename T>
void swap(T& a, T& b)
{
	int temp = a;
	a = b;
	b = temp;
}

template<typename T> class PQ_ComplHeap :public PQ<T>, public vector<T>
{
protected:
	int percolateDown(int n, int i); //���˲���
	int percolateUp(int i); //���˲���
	void heapify(int n); //Floyd�����㷨
public:
	PQ_ComplHeap(){} //Ĭ�Ϲ��캯��
	PQ_ComplHeap(T* A, int n) { this->copyFrom(A, 0, n); heapify(n); } //��������
	void insert(T); //�������ȼ��������
	T getMax(); //��ȡ���ȼ���ߵĴ���
	T delMax(); //ɾ�����ȼ���ߵĴ���
};

template<typename T>
T PQ_ComplHeap<T>::getMax()
{
	return this->_elem[0];
}

template<typename T>
void PQ_ComplHeap<T>::insert(T e)
{
	this->insert(e);
	percolateUp(this->_size - 1);
}

template<typename T>
int PQ_ComplHeap<T>::percolateUp(int i)
{
	while (ParentValid(i))//ֻҪ���и��׽��
	{
		int j = Parent(i);
		if (_elem[j] > _elem[i])break;
		else
		{
			swap(_elem[j], _elem[i]);
			i = j;
		}
	}
	return i; //�����������մﵽ��λ��
}

template<typename T>
T PQ_ComplHeap<T>::delMax()
{
	T maxElem = _elem[0];
	_elem[0] = _elem[--this->_size];
	percolateDown(this->_size, 0);
	return maxElem; //����ɾ����Ԫ��
}

template<typename T> 
int PQ_ComplHeap<T>::percolateDown(int n, int i)
{
	int j;
	while (i != (j = ProperParent(this->_elem, n, i)))
	{
		swap(this->_elem[i], this->_elem[j]);
		i = j;
	}
	return i;
}

template<typename T>
void PQ_ComplHeap<T>::heapify(int n) //floyd������

{
	for (int i = LastInternal(n); InHeap(n, i); i--)
	{
		percolateDown(n,i);
	}
}

