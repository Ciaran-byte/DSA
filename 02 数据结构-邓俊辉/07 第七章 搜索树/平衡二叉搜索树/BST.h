#pragma once
#include"BinTree.h"
#include<iostream>
template<typename T>
class BST:public BinTree<T> //二叉搜索树基本结构
{
protected:
	BinNodePosi(T) _hot; //命中结点的父亲结点
	
	BinNodePosi(T)& searchIn(BinNodePosi(T)& v, const T& e, BinNodePosi(T)& hot);//查找的工具函数
	BinNodePosi(T) connect34 //三加四重构
	(
		BinNodePosi(T) a, BinNodePosi(T) b, BinNodePosi(T) c,
		BinNodePosi(T) T0, BinNodePosi(T) T1, BinNodePosi(T) T2, BinNodePosi(T) T3
	);
BinNodePosi(T) rotateAt(BinNodePosi(T)x); //对二叉树结点顺序进行调整
	
public:
	virtual BinNodePosi(T)& search(const T& e); //查找
	virtual BinNodePosi(T) insert(const T& e);//插入
	virtual bool remove(const T& e);//删除
	
};

//成员函数
template<typename T>
BinNodePosi(T)& BST<T>::searchIn(BinNodePosi(T)& v, const T& e, BinNodePosi(T)& hot) //递归查找
{
	if (!v || v->data == e)return v;
	hot = v;
	return searchIn((v->data > e ? v->lchild : v->rchild), e, hot);
}
template<typename T>
BinNodePosi(T)& BST<T>::search(const T& e) //表现在外部的查找函数
{
	
	return searchIn(this->root(), e, _hot=nullptr);
}

template<typename T>
BinNodePosi(T) BST<T>::insert(const T& e) //插入结点
{
	BinNodePosi(T)& x = search(e);
	if (x)return x; //如果存在，直接返回
	x = new BinNode<T>(e,_hot); //创建结点
	this->_size++; //插入结点规模+1
	this->updateHeightAbove(x); //更新所有结点的树高
	
	return x;
}


template<typename T>
BinNodePosi(T) removeAt(BinNodePosi(T)&x,BinNodePosi(T)& hot)
{
	//x是要被删除的结点，hot是x的父节点
	BinNodePosi(T) w = x; //w保存要被删除结点的地址
	BinNodePosi(T) succ = nullptr; //保存后继结点
	if (!x->hasLchild()) //如果没有左子树
	{
		x = x->rchild; //hot->child=x->rchild,因为是引用
		succ = x;//用于恢复父亲结点关系的

	}
	else if (!x->hasRchild())//如果没有右子树
	{
		x = x->lchild;
		succ = x;
	}
	else //如果左右分支都有，就找到该结点后继结点进行交换，然后删除就行了，然后变为单分支情况
	{
		//交换结点数据域
		w = w->succ();
		T temp = w->data;
		w->data = x->data;
		x->data = temp;

		//现在w就是要被删除的结点了
		BinNodePosi(T) u = w->parent;
		((u == x) ? u->rchild : u->lchild)=w->rchild ;
		succ = w->rchild;

	}

	hot = w->parent;
	if (succ)succ->parent = hot;
	delete w;
	return succ;
}

template<typename T>
bool BST<T>::remove(const T& e)
{
	BinNodePosi(T)& x = search(e);
	if (!x)return false;
	removeAt(x, _hot);
	this->_size--;
	this->updateHeightAbove(_hot);

	return true;

}

//-------------------------------------------三加四重构---------------------------------------------------
template<typename T>  //来自BST类的函数，三加四重构
BinNodePosi(T) BST<T>::connect34(
	BinNodePosi(T) a, BinNodePosi(T) b, BinNodePosi(T) c,
	BinNodePosi(T) T0, BinNodePosi(T) T1, BinNodePosi(T) T2, BinNodePosi(T) T3
)
{
	//所谓三加重构，就是按照中序遍历的顺序，重造这棵树，然后返回新树的根节点
	a->lchild = T0; if (T0) T0->parent = a;
	a->rchild = T1; if (T1) T1->parent = a; this->updateHeight(a);
	c->lchild = T2; if (T2) T2->parent = c;
	c->rchild = T3; if (T3) T3->parent = c; this->updateHeight(c);
	b->lchild = a; a->parent = b;
	b->rchild = c; c->parent = b;
	this->updateHeight(b);
	return b;

}

template<typename T>
BinNodePosi(T)BST<T>::rotateAt(BinNodePosi(T) v) //使用三加四重构进行平衡操作,v结点是最低不平衡树的孙子结点
{
	
	BinNodePosi(T)p = v->parent; //最低不平衡树的子节点
	BinNodePosi(T)g = p->parent; //最低不平衡树的根节点
	if (p->isLchild()) //zig
	{
		if (v->isLchild()) //zig-zig 左左
		{
			p->parent = g->parent; //返回的新根节点是p，需要更改一下其父节点
			return connect34(v, p, g, v->lchild, v->rchild, p->rchild, g->rchild);
		}
		else //zig-zag; 左-右
		{
			v->parent = g->parent;
			return connect34(p, v, g, p->lchild, v->lchild, v->rchild, g->rchild);
		}
	}
	else //zag 右
	{
		if (v->isRchild())//zag-zag;
		{
			p->parent = g->parent;
			return connect34(g, p, v, g->lchild, p->lchild, v->lchild, v->rchild);
		}
		else //zag-zig
		{
			v->parent = g->parent;
			return connect34(g, v, p, g->lchild, v->lchild, v->rchild, p->rchild);
		}
	}
}