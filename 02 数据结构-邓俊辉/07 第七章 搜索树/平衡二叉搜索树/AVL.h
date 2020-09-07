#pragma once
#include "BST.h"
#include "BinTree.h"




template<typename T>
class AVL :public BST<T>
{
protected:
	bool Balanced(BinNodePosi(T) x);//判断树是否平衡
	int BalFac(BinNodePosi(T)x); //平衡因子
	bool AvlBalanced(BinNodePosi(T) x); //AVL树是否平衡
	BinNodePosi(T) tallerChind(BinNodePosi(T) x); //返回x的最高子树
	
	
public:
	virtual BinNodePosi(T) insert(const T& e);
	virtual bool remove(const T& e);
};


template<typename T>
bool AVL<T>::Balanced(BinNodePosi(T) x) //判断树结点是否平衡
{
	return Stature(x->lchild) == Stature(x->rchild);
}

template<typename T>
int AVL<T>::BalFac(BinNodePosi(T)x) //平衡因子
{
	return Stature(x->lchild) - Stature(x->rchild);
}

template<typename T>
bool AVL<T>::AvlBalanced(BinNodePosi(T) x) //判断AVL树是否是平衡的
{
	return (BalFac(x) > -2 && BalFac(x) < 2);
}

template<typename T>
BinNodePosi(T) AVL<T>::tallerChind(BinNodePosi(T)x) //更高的子树
{
	return Stature(x->lchild) > Stature(x->rchild) ? x->lchild : //左树高
		Stature(x->lchild) < Stature(x->rchild) ? x->rchild : //右树高
		x->isLchild() ? x->lchild : x->rchild;  //如果两子树等高，返回与父树同向的那一课子树

}

template<typename T>
BinNodePosi(T) AVL<T>::insert(const T& e)
{

	BinNodePosi(T)& x = BST<T>::search(e);
	
	if (x)return x;//如果目标结点存在，直接返回
	//如果目标结点不存在，x是要插入的位置，_hot是其父节点
	x = new BinNode<T>(e, this->_hot); this->_size++; //引用x相当于 _hot->child = .....
	

	BinNodePosi(T) xx = x;
	
	for (BinNodePosi(T) g = this->_hot; g; g = g->parent)
	{
		//对于插入操作来说，只需要找到最低的不平衡父节点修正即可，父节点的高度不变，以上结点必定都平衡了
		if (!AvlBalanced(g)) //如果父节点g不平衡
		{
			
			
			if (g->parent == nullptr)
			{
				this->root() = BST<T>::rotateAt(tallerChind(tallerChind(g)));
			}
			else if (g->isRchild())
			{
			
				BinNodePosi(T) P = g->parent;
				P->rchild = BST<T>::rotateAt(tallerChind(tallerChind(g)));			
			}
			else
			{

				BinNodePosi(T) P = g->parent;
				P->lchild = BST<T>::rotateAt(tallerChind(tallerChind(g)));
			}
			
			
			
			break;
		}
		else
		{
			
			this->updateHeight(g);
			
		}
			
			
		
	}
	return xx;
}


template<typename T>
bool AVL<T>::remove(const T& e) //平衡二叉树的删除操作
{
	BinNodePosi(T)& x = this->search(e);
	if (!x)return false; //不存在结点，无法删除
	removeAt(x, this->_hot); //删除x结点，并且保存其父节点_hot;
	this->_size--;
	for (BinNodePosi(T)g = this->_hot; g; g = g->parent)
	{
		if (!AvlBalanced(g)) //遇到不平衡结点，可能上面所有结点都不平衡
		{
			if(g->parent == nullptr)
			{
				this->root() = BST<T>::rotateAt(tallerChind(tallerChind(g)));
				g = this->root();
			}
			else if (g->isRchild())
			{

			BinNodePosi(T) P = g->parent;
				P->rchild = BST<T>::rotateAt(tallerChind(tallerChind(g)));
				g = P->rchild;
			}
			else
			{

			BinNodePosi(T) P = g->parent;
			P->lchild = BST<T>::rotateAt(tallerChind(tallerChind(g)));
			g = P->lchild;
			}
		}
		this->updateHeight(g);
		
	}
	return true;
}