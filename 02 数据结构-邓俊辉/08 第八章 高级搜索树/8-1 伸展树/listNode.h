#pragma once
#define ListNodePosi(T) ListNode<T>*  //��ģ��ı���
//list�н�����ݽṹ�Ĺ���
template<typename T>
class ListNode
{
public:
	//���ݳ�Ա
	T data;
	ListNodePosi(T) pred; //ǰ�����
	ListNodePosi(T) succ; //��̽��

	//���캯��
	ListNode(){}//Ϊ�׽���β���׼����(��ͷβĩ)
	ListNode(T e,ListNodePosi(T) p =nullptr,ListNodePosi(T) s = nullptr):data(e),pred(p),succ(s){}

	//���ܺ���
	ListNodePosi(T) insertAsPred(const T&);
	ListNodePosi(T) insertAsSucc(const T&);
	
};

template<typename T>
ListNodePosi(T) ListNode<T>::insertAsPred(const T&e) //�ڽ��ǰ����һ�����
{
	ListNodePosi(T) node = new ListNode(e, pred, this);
	pred->succ = node;
	this->pred = node;

	return node;
}

template<typename T>
ListNodePosi(T) ListNode<T>::insertAsSucc(const T& e) //�ڽ������һ�����
{
	ListNodePosi(T) node = new ListNode(e, this, succ);
	succ->pred = node;
	this->succ = node;
	
	return node;
}