#pragma once
#include "QuadlistNode.h"

template<typename T>
class Quadlist
{
private:
	int _size;
	QlistNodePosi(T) header; //四联表的头哨兵和尾部哨兵
	QlistNodePosi(T) tailer;
protected:
	void init(); //Quadlist创建时候的初始化
	int clear(); //清理所有结点

public:
	//构造函数
	Quadlist() { init(); } //默认构造函数

	//析构函数
	~Quadlist() { clear(); delete header; delete tailer; } //删除所有结点，并释放收尾哨兵

	//只读访问接口
	int size()const { return _size; } //规模
	bool empty()const { return _size <= 0; }//判断是否为空
	QlistNodePosi(T) first()const { return header->succ; } //首节点位置
	QlistNodePosi(T) last()const { return tailer->pred; } //末结点位置
	bool valid(QlistNodePosi(T)p) //判断p位置是否对外合法，非空且不是头尾结点
	{
		return p && (tailer != p) && (header != p);
	}

	//可写访问结点
	T remove(QlistNodePosi(T) p); //删除合法位置结点，返回被删除的数据

	QlistNodePosi(T) insertAfterabove //把e作为p的后继，b的上邻插入
		(const T& e, QlistNodePosi(T)p, QlistNodePosi(T)b = nullptr);
	
	//遍历
	template<typename VST>
	void traverse(VST&); //遍历各个结点
};


template<typename T>
void Quadlist<T>::init() //构造的四联表暂时与其他表独立，不含任何结点
{
	//创建收尾哨兵
	header = new QuadlistNode<T>;
	tailer = new QuadlistNode<T>;
	header->succ = tailer; header->pred = nullptr;
	tailer->pred = header; tailer->succ = nullptr;

	header->above = nullptr;
	header->below = nullptr;
	tailer->above = nullptr;
	tailer->below = nullptr;

	//规模为0
	_size = 0; 
}
template<typename T>
QlistNodePosi(T) Quadlist<T>::insertAfterabove //把e作为p的后继，b的上邻插入
(const T& e, QlistNodePosi(T)p, QlistNodePosi(T)b)
{
	_size++;
	return p->insertAsSuccAbove(e, b);
}

template<typename T>
T Quadlist<T>::remove(QlistNodePosi(T) p)
{
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	_size--;
	T e = p->entry;
	delete p; 
	
	return e;
}

template<typename T>
int Quadlist<T>::clear()
{
	int oldSize = _size;
	while (_size>0)
	{
		remove(header->succ);
	}
	return oldSize;
}