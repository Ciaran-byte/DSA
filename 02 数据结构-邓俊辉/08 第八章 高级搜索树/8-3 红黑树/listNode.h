#pragma once
#define ListNodePosi(T) ListNode<T>*  //对模板的别名
//list中结点数据结构的构建
template<typename T>
class ListNode
{
public:
	//数据成员
	T data;
	ListNodePosi(T) pred; //前驱结点
	ListNodePosi(T) succ; //后继结点

	//构造函数
	ListNode(){}//为首结点和尾结点准备的(首头尾末)
	ListNode(T e,ListNodePosi(T) p =nullptr,ListNodePosi(T) s = nullptr):data(e),pred(p),succ(s){}

	//功能函数
	ListNodePosi(T) insertAsPred(const T&);
	ListNodePosi(T) insertAsSucc(const T&);
	
};

template<typename T>
ListNodePosi(T) ListNode<T>::insertAsPred(const T&e) //在结点前插入一个结点
{
	ListNodePosi(T) node = new ListNode(e, pred, this);
	pred->succ = node;
	this->pred = node;

	return node;
}

template<typename T>
ListNodePosi(T) ListNode<T>::insertAsSucc(const T& e) //在结点后插入一个结点
{
	ListNodePosi(T) node = new ListNode(e, this, succ);
	succ->pred = node;
	this->succ = node;
	
	return node;
}