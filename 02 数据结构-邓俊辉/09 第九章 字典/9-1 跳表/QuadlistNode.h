#pragma once
#include "Entry.h"

#define QlistNodePosi(T) QuadlistNode<T>*

template<typename T>
class QuadlistNode  //��������
{
public:
	T entry;
	QlistNodePosi(T) pred;//ǰ�����
	QlistNodePosi(T) succ; //��̽��
	QlistNodePosi(T) above; //���ڽ��
	QlistNodePosi(T) below; //���ڽ��
	


	//�����½�㣬�Ե�ǰ���Ϊǰ�����Խ��bΪ����
	QuadlistNode(T e = T(), QlistNodePosi(T)p = nullptr, QlistNodePosi(T) s = nullptr,
		QlistNodePosi(T) a = nullptr, QlistNodePosi(T) b = nullptr) :entry(e), pred(p), succ(s), above(a), below(b) {}//���캯��


	
	QlistNodePosi(T) insertAsSuccAbove(const T& e, QlistNodePosi(T) b = nullptr); //�ڸý��֮��b���֮�ϲ�����


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