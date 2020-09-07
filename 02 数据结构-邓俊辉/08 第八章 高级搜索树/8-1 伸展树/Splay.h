#pragma once
#include "BST.h"
#include<iostream>
using namespace std;


template<typename NodePosi>
inline void attachAsLChild(NodePosi p, NodePosi lc) //构建左孩子关系
{
	p->lchild = lc;
	if (lc)lc->parent = p;
}

template<typename NodePosi>
inline void attachAsRChild(NodePosi p, NodePosi rc)//构建右孩子关系
{
	p->rchild = rc;
	if (rc)rc->parent = p;
}


template<typename T>
class Splay :public BST<T>  //伸展树
{
protected:
	BinNodePosi(T) splay(BinNodePosi(T) v); //将节点v延伸至跟
public:
	virtual BinNodePosi(T)& search(const T& e); //查找
	virtual BinNodePosi(T) insert(const T& e); //插入
	virtual bool remove(const T& e); //删除
};


template<typename T>
BinNodePosi(T)Splay<T>::splay(BinNodePosi(T)v) //把结点v经过两次旋转调整变动到根节点
{

	if (!v)return nullptr;
	BinNodePosi(T) p;
	BinNodePosi(T)g;
	while ((p = v->parent) && (g = p->parent))
	{
		BinNodePosi(T) gg = g->parent;
		if (v->isLchild())
		{
			if (p->isLchild()) //左左 
			{
				attachAsLChild<BinNodePosi(T)>(g, p->rchild);
				attachAsLChild<BinNodePosi(T)>(p, v->rchild);
				attachAsRChild<BinNodePosi(T)>(p, g);
				attachAsRChild<BinNodePosi(T)>(v, p);
			}
			else //右左
			{
				attachAsLChild<BinNodePosi(T)>(p, v->rchild);
				attachAsRChild<BinNodePosi(T)>(g, v->lchild);
				attachAsLChild<BinNodePosi(T)>(v, g);
				attachAsRChild<BinNodePosi(T)>(v, p);


			}
		}
		else
		{
			if (p->isRchild()) //右右
			{
				attachAsRChild<BinNodePosi(T)>(g, p->rchild);
				attachAsRChild<BinNodePosi(T)>(p, v->rchild);
				attachAsLChild<BinNodePosi(T)>(p, g);
				attachAsLChild<BinNodePosi(T)>(v, p);
			}
			else //左右
			{
				attachAsRChild<BinNodePosi(T)>(p, v->rchild);
				attachAsLChild<BinNodePosi(T)>(g, v->lchild);
				attachAsRChild<BinNodePosi(T)>(v, g);
				attachAsLChild<BinNodePosi(T)>(v, p);
			}
		}

		if (!gg)v->parent = nullptr;//如果gg是空，v的父节点是空
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
BinNodePosi(T)& Splay<T>::search(const T& e)//查找
{
	BinNodePosi(T) p = this->searchIn(this->root(), e, this->_hot=nullptr);
	//如果找到了，p是那个结点，如果没找到，p是null，_hot是最接近的那个
	this->_root=splay(p ? p : this->_hot);
	return this->_root;
}


template<typename T>
BinNodePosi(T) Splay<T>::insert(const T& e)//插入
{
	if (!this->_root) { this->_size++;return this->_root = new BinNode<T>(e); }
	if (e == search(e)->data) { return this->_root; }//说明已经存在，不需要插入了
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
	
	if (!this->root()||(e != search(e)->data)) { return false; }//结点不存在，没法删除
	
	BinNodePosi(T)w = this->_root;

	if (!this->_root->hasLchild()) //如果没有左子树
	{
		
		this->_root = this->_root->rchild;
		if (this->_root)this->_root->parent = nullptr;
	}
	else if (!this->_root->hasRchild())//如果没有右子树
	{
		
		this->_root = this->_root->lchild;
		if (this->_root)this->_root->parent = nullptr;
	}
	else //如果左右子树都有
	{
		
		BinNodePosi(T) lTree = this->_root->lchild;
		lTree->parent = nullptr;
		this->_root->lchild = nullptr; //暂时切掉左子树
		this->_root=this->_root->rchild; //更新根节点
		this->_root->parent = nullptr;
		search(w->data);//把右子树最小的移动到根节点,该根节点左子树一定为空
		this->_root->lchild = lTree;
		lTree->parent = this->_root;

	}
	delete w;
	this->_size--;
	if (this->_root)this->updateHeight(this->_root);
	
	return true;
}