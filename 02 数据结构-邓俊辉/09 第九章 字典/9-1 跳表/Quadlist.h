#pragma once
#include "QuadlistNode.h"

template<typename T>
class Quadlist
{
private:
	int _size;
	QlistNodePosi(T) header; //�������ͷ�ڱ���β���ڱ�
	QlistNodePosi(T) tailer;
protected:
	void init(); //Quadlist����ʱ��ĳ�ʼ��
	int clear(); //�������н��

public:
	//���캯��
	Quadlist() { init(); } //Ĭ�Ϲ��캯��

	//��������
	~Quadlist() { clear(); delete header; delete tailer; } //ɾ�����н�㣬���ͷ���β�ڱ�

	//ֻ�����ʽӿ�
	int size()const { return _size; } //��ģ
	bool empty()const { return _size <= 0; }//�ж��Ƿ�Ϊ��
	QlistNodePosi(T) first()const { return header->succ; } //�׽ڵ�λ��
	QlistNodePosi(T) last()const { return tailer->pred; } //ĩ���λ��
	bool valid(QlistNodePosi(T)p) //�ж�pλ���Ƿ����Ϸ����ǿ��Ҳ���ͷβ���
	{
		return p && (tailer != p) && (header != p);
	}

	//��д���ʽ��
	T remove(QlistNodePosi(T) p); //ɾ���Ϸ�λ�ý�㣬���ر�ɾ��������

	QlistNodePosi(T) insertAfterabove //��e��Ϊp�ĺ�̣�b�����ڲ���
		(const T& e, QlistNodePosi(T)p, QlistNodePosi(T)b = nullptr);
	
	//����
	template<typename VST>
	void traverse(VST&); //�����������
};


template<typename T>
void Quadlist<T>::init() //�������������ʱ������������������κν��
{
	//������β�ڱ�
	header = new QuadlistNode<T>;
	tailer = new QuadlistNode<T>;
	header->succ = tailer; header->pred = nullptr;
	tailer->pred = header; tailer->succ = nullptr;

	header->above = nullptr;
	header->below = nullptr;
	tailer->above = nullptr;
	tailer->below = nullptr;

	//��ģΪ0
	_size = 0; 
}
template<typename T>
QlistNodePosi(T) Quadlist<T>::insertAfterabove //��e��Ϊp�ĺ�̣�b�����ڲ���
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