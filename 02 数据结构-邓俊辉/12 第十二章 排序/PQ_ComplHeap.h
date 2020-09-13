
#pragma once

#include "vector.h"
#include "PQ.h"
#include "HeapComplete.h"


					
			
							  



template<typename T> 
class PQ_ComplHeap :public vector<T>,public PQ<T>
{
protected:
	//int percolateDown(int n, int i); //下滤操作
	//int percolateUp(int i); //上滤操作
	//void heapify(int n); //Floyd建堆算法
public:
	PQ_ComplHeap(){} //默认构造函数
	PQ_ComplHeap(T* A, int n) { this->copyFrom(A, 0, n); heapify(this->_elem,n); } //批量构造
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

//template<typename T>
//int  PQ_ComplHeap<T>::percolateUp(int i)
//{
//	while (ParentValid(i))//只要还有父亲结点
//	{
//		int j = Parent(i);
//		if (this->_elem[j] > this->_elem[i])break;
//		else
//		{
//			swap(this->_elem[j], this->_elem[i]);
//			i = j;
//		}
//	}
//	return i; //返回上滤最终达到的位置
//}

template<typename T>
T PQ_ComplHeap<T>::delMax()
{
	T maxElem = this->_elem[0];
	this->_elem[0] = this->_elem[--this->_size];
	percolateDown(this->_size, 0);
	return maxElem; //返回删除的元素
}

//template<typename T> 
//int PQ_ComplHeap<T>::percolateDown(int n, int i)
//{
//	int j;
//	while (i != (j = ProperParent(this->_elem, n, i)))
//	{
//		swap(this->_elem[i], this->_elem[j]);
//		i = j;
//	}
//	return i;
//}
//
//template<typename T>
//void  PQ_ComplHeap<T>::heapify(int n) //floyd法建堆
//
//{
//	for (int i = LastInternal(n); InHeap(n, i); i--)
//	{
//		percolateDown(n,i);
//	}
//}
//

