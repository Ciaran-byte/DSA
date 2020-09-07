#pragma once
#define InHeap(n,i)(((-1)<(i))&&((i)<(n))) //判断P[i]是否合法
#define Parent(i)  ((i-1)>>2) //父亲结点
#define LastInternal(n) Parent(n-1)  //最后一个内部结点，就是末结点的父节点
#define LChild(i) (1+((i)<<1)) //左孩子
#define RChild(i) ((1+(i))<<1) //右孩子
#define ParentValid(i) (i>0) //判断父节点是否存在
#define LChildValid(n,i) InHeap(n,LChild(i)); //判断是否存在左孩子
#define RChildValid(n,i) InHeap(n,RChild(i)); //判断是否存在右孩子
#define Bigger(PQ,i,j) ((PQ[i]>PQ[j])?i:j) //返回最大者的秩,相等的时候取前者
#define ProperParent(PQ,n,i)/*返回三节点最大者*/ \
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
	int percolateDown(int n, int i); //下滤操作
	int percolateUp(int i); //上滤操作
	void heapify(int n); //Floyd建堆算法
public:
	PQ_ComplHeap(){} //默认构造函数
	PQ_ComplHeap(T* A, int n) { this->copyFrom(A, 0, n); heapify(n); } //批量构造
	void insert(T); //按照优先级插入词条
	T getMax(); //读取优先级最高的词条
	T delMax(); //删除优先级最高的词条
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
	while (ParentValid(i))//只要还有父亲结点
	{
		int j = Parent(i);
		if (_elem[j] > _elem[i])break;
		else
		{
			swap(_elem[j], _elem[i]);
			i = j;
		}
	}
	return i; //返回上滤最终达到的位置
}

template<typename T>
T PQ_ComplHeap<T>::delMax()
{
	T maxElem = _elem[0];
	_elem[0] = _elem[--this->_size];
	percolateDown(this->_size, 0);
	return maxElem; //返回删除的元素
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
void PQ_ComplHeap<T>::heapify(int n) //floyd法建堆

{
	for (int i = LastInternal(n); InHeap(n, i); i--)
	{
		percolateDown(n,i);
	}
}

