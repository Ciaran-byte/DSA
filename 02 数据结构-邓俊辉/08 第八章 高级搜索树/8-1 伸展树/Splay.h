#pragma once
#include "BST.h"
#include<iostream>
using namespace std;


template<typename NodePosi>
inline void attachAsLChild(NodePosi p, NodePosi lc) //�������ӹ�ϵ
{
	p->lchild = lc;
	if (lc)lc->parent = p;
}

template<typename NodePosi>
inline void attachAsRChild(NodePosi p, NodePosi rc)//�����Һ��ӹ�ϵ
{
	p->rchild = rc;
	if (rc)rc->parent = p;
}


template<typename T>
class Splay :public BST<T>  //��չ��
{
protected:
	BinNodePosi(T) splay(BinNodePosi(T) v); //���ڵ�v��������
public:
	virtual BinNodePosi(T)& search(const T& e); //����
	virtual BinNodePosi(T) insert(const T& e); //����
	virtual bool remove(const T& e); //ɾ��
};


template<typename T>
BinNodePosi(T)Splay<T>::splay(BinNodePosi(T)v) //�ѽ��v����������ת�����䶯�����ڵ�
{

	if (!v)return nullptr;
	BinNodePosi(T) p;
	BinNodePosi(T)g;
	while ((p = v->parent) && (g = p->parent))
	{
		BinNodePosi(T) gg = g->parent;
		if (v->isLchild())
		{
			if (p->isLchild()) //���� 
			{
				attachAsLChild<BinNodePosi(T)>(g, p->rchild);
				attachAsLChild<BinNodePosi(T)>(p, v->rchild);
				attachAsRChild<BinNodePosi(T)>(p, g);
				attachAsRChild<BinNodePosi(T)>(v, p);
			}
			else //����
			{
				attachAsLChild<BinNodePosi(T)>(p, v->rchild);
				attachAsRChild<BinNodePosi(T)>(g, v->lchild);
				attachAsLChild<BinNodePosi(T)>(v, g);
				attachAsRChild<BinNodePosi(T)>(v, p);


			}
		}
		else
		{
			if (p->isRchild()) //����
			{
				attachAsRChild<BinNodePosi(T)>(g, p->rchild);
				attachAsRChild<BinNodePosi(T)>(p, v->rchild);
				attachAsLChild<BinNodePosi(T)>(p, g);
				attachAsLChild<BinNodePosi(T)>(v, p);
			}
			else //����
			{
				attachAsRChild<BinNodePosi(T)>(p, v->rchild);
				attachAsLChild<BinNodePosi(T)>(g, v->lchild);
				attachAsRChild<BinNodePosi(T)>(v, g);
				attachAsLChild<BinNodePosi(T)>(v, p);
			}
		}

		if (!gg)v->parent = nullptr;//���gg�ǿգ�v�ĸ��ڵ��ǿ�
		else
		{
			(g == gg->lchild) ? attachAsLChild(gg, v) : attachAsRChild(gg, v);
		}
		this->updateHeight(g); this->updateHeight(p); this->updateHeight(v);

	}
	if (p = v->parent)
	{
		if (v->isLchild())
		{
			attachAsLChild(p, v->rchild);
			attachAsRChild(v, p);

		}
		else
		{
			attachAsRChild(p, v->lchild);
			attachAsLChild(v, p);
		}
		this->updateHeight(p);
		this->updateHeight(v);
	}
	v->parent = nullptr;
	return v;
}

template<typename T>
BinNodePosi(T)& Splay<T>::search(const T& e)//����
{
	BinNodePosi(T) p = this->searchIn(this->root(), e, this->_hot=nullptr);
	//����ҵ��ˣ�p���Ǹ���㣬���û�ҵ���p��null��_hot����ӽ����Ǹ�
	this->_root=splay(p ? p : this->_hot);
	return this->_root;
}


template<typename T>
BinNodePosi(T) Splay<T>::insert(const T& e)//����
{
	if (!this->_root) { this->_size++;return this->_root = new BinNode<T>(e); }
	if (e == search(e)->data) { return this->_root; }//˵���Ѿ����ڣ�����Ҫ������
	this->_size++;
	BinNodePosi(T) t = this->_root;
	if (this->root()->data < e)
	{
		this->_root = new BinNode<T>(e, nullptr, t, t->rchild);
		t->parent = this->_root;
		
		if (t->hasRchild()) { t->rchild->parent=this->root(); t->rchild = nullptr; }
	}
	else
	{
		this->_root = new BinNode<T>(e, nullptr, t->lchild, t);
		t->parent = this->_root;
		
		if (t->hasLchild()) { t->lchild->parent=this->root(); t->lchild = nullptr; }
	}
	this->updateHeightAbove(t);
	return this->_root;
}

template<typename T>
bool Splay<T>::remove(const T& e)
{
	
	if (!this->root()||(e != search(e)->data)) { return false; }//��㲻���ڣ�û��ɾ��
	
	BinNodePosi(T)w = this->_root;

	if (!this->_root->hasLchild()) //���û��������
	{
		
		this->_root = this->_root->rchild;
		if (this->_root)this->_root->parent = nullptr;
	}
	else if (!this->_root->hasRchild())//���û��������
	{
		
		this->_root = this->_root->lchild;
		if (this->_root)this->_root->parent = nullptr;
	}
	else //���������������
	{
		
		BinNodePosi(T) lTree = this->_root->lchild;
		lTree->parent = nullptr;
		this->_root->lchild = nullptr; //��ʱ�е�������
		this->_root=this->_root->rchild; //���¸��ڵ�
		this->_root->parent = nullptr;
		search(w->data);//����������С���ƶ������ڵ�,�ø��ڵ�������һ��Ϊ��
		this->_root->lchild = lTree;
		lTree->parent = this->_root;

	}
	delete w;
	this->_size--;
	if (this->_root)this->updateHeight(this->_root);
	
	return true;
}