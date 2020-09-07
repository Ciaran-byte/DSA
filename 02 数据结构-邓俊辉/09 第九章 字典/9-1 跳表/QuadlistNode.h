#pragma once
#include "Entry.h"

#define QlistNodePosi(T) QuadlistNode<T>*

template<typename T>
class QuadlistNode  //四联表结点
{
public:
	T entry;
	QlistNodePosi(T) pred;//前驱结点
	QlistNodePosi(T) succ; //后继结点
	QlistNodePosi(T) above; //上邻结点
	QlistNodePosi(T) below; //下邻结点
	


	//插入新结点，以当前结点为前驱，以结点b为下邻
	QuadlistNode(T e = T(), QlistNodePosi(T)p = nullptr, QlistNodePosi(T) s = nullptr,
		QlistNodePosi(T) a = nullptr, QlistNodePosi(T) b = nullptr) :entry(e), pred(p), succ(s), above(a), below(b) {}//构造函数


	
	QlistNodePosi(T) insertAsSuccAbove(const T& e, QlistNodePosi(T) b = nullptr); //在该结点之后，b结点之上插入结点


};

template<typename T>
QlistNodePosi(T) QuadlistNode <T>::insertAsSuccAbove(const T& e, QlistNodePosi(T) b)
{
	QlistNodePosi(T) x = new QuadlistNode(e, this, succ, nullptr, b);
	succ = x;
	succ->pred = x;
	if (b)b->above = x;
	return x;
}