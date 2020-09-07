#pragma once
#include "BST.h"
#include<iostream>
template<typename T>
inline bool IsBlack(BinNodePosi(T) p) { return (!p) || (p->color == RB_BLACK); }

template<typename T>
inline bool IsRed(BinNodePosi(T) p) { return !IsBlack(p); } //判断结点颜色

template<typename T>
inline bool BlackUpdateHeight(BinNodePosi(T)p) //是否需要更新结点高度
{
	return (Stature(p->lchild) == Stature(p->rchild)) && (p->height == (IsRed(p) ? Stature(p->lchild) : Stature(p->lchild) + 1));
}

template<typename T>
class RedBlack :public BST<T>
{
protected:
	void sovlveDoubleRed(BinNodePosi(T) x);//双红修正
	void solveDoubleBlack(BinNodePosi(T)x); //双黑修正
	virtual int updateHeight(BinNodePosi(T) x); //更新结点的黑高度

public:
	virtual BinNodePosi(T) insert(const T& e); //插入操作
	virtual bool remove(const T& e); //删除操作
	//search沿用二叉搜索树的接口
	
};



//----------------------------------功能函数----------------------------
template<typename T>
int RedBlack<T>::updateHeight(BinNodePosi(T)x)//高度修正
{
	
	x->height = this->max(Stature(x->lchild), Stature(x->rchild)); //孩子高度一般相等，除非双黑
	return IsBlack(x) ? x->height++ : x->height;

}

template<typename T>
BinNodePosi(T) RedBlack<T>::insert(const T& e) //插入操作
{
	BinNodePosi(T)& x = this->search(e);
	
	if (x)return x;
	x = new BinNode<T>(e, this->_hot, nullptr, nullptr, -1); //高度为-1的红结点
	
	this->_size++;
	sovlveDoubleRed(x); //双红修正
	
	return x ? x : this->_hot->parent; //这句话不是非常懂
}

template<typename T>
void RedBlack<T>::sovlveDoubleRed(BinNodePosi(T)x)
{
	
	if (x->isRoot()) //如果是根节点
	{
		x->color = RB_BLACK;
		x->height++;
		return;
	}
	
	if(x->parent->color==RB_BLACK) //黑结点直接返回
	{
		return;
	}

	BinNodePosi(T) p = x->parent;
	BinNodePosi(T) g = p->parent; //如果父节点为红，一定有祖父结点
	BinNodePosi(T) u = x->uncle(); //叔叔结点
	if (IsBlack(u)) //如果叔叔结点是黑色的
	{
	
		//叔叔结点为黑，会发生三加四重构，函数内部会更新结点信息，所以，不必额外更新黑高度
		if (p->isLchild() == x->isLchild()) //如果是父子结点同向
		{
			p->color = RB_BLACK;

		}
		else //如果父子节点异向
		{
			x->color = RB_BLACK;
		}
		
		g->color = RB_RED;//祖父结点一定会被染色为红色
		BinNodePosi(T) gg = g->parent;
	

		if (g->isRoot())
		{
			
			this->root() = this->rotateAt(x);
			
			
		}
		else if (g->isLchild())
		{
			BinNodePosi(T) P= this->rotateAt(x);
			gg->lchild = P;
		}
		else
		{
			BinNodePosi(T) P = this->rotateAt(x);
			gg->rchild = P;
		}

	}
	else
	{
		
		p->color = RB_BLACK;
		u->color = RB_BLACK;
		this->updateHeight(p); this->updateHeight(u);
		if (!g->isRoot())g->color = RB_RED;
		sovlveDoubleRed(g);

	}

}

template<typename T>
bool RedBlack<T>::remove(const T& e)
{
	BinNodePosi(T) &x = this->search(e);
	if (!x)return false; //如果没有结点x，不可能删除，返回失败
	BinNodePosi(T) r = removeAt(x, this->_hot); //删除结点x，r为x的直接后继结点，_hot记录x的父节点位置
	if (!(--this->_size)) { return true; } //规模-1，如果规模为0了，说明不需要做后续判断了

	if (!this->_hot) //如果_hot为空，说明删除的是父节点，那么直接后继一定是个叶节点，红色的，染黑就行，黑高度不变
	{
		this->_root->color = RB_BLACK; //染黑
		updateHeight(this->_root); //更新根节点高度
		return true;
	}



	//-----------------------------删除结点和后继结点一红一黑的情况-------------------------------------------
	//如果删除的不是根节点，但是删除完了以后，红黑树仍然平衡，直接返回即可
	if (BlackUpdateHeight(this->_hot))return true; 


	if (IsRed(r)) //后继结点是个红的，父节点必定是黑的，把后继结点染色，即可平衡红黑树
	{
		r->color = RB_BLACK;
		r->height++;
		return true;
	}

	//如果被删结点和后继结点都是黑色的，就得双黑调整
	solveDoubleBlack(r);
	return true;
}

template<typename T>
void RedBlack<T>::solveDoubleBlack(BinNodePosi(T) r) //双黑修正
{
	BinNodePosi(T) p = r ? r->parent : this -> _hot;
	if (!p)return;
	BinNodePosi(T) s = (r == p->lchild) ? p->rchild : p->lchild; //s是后继结点r的兄弟结点

	if (IsBlack(s)) //如果兄弟是黑色结点
	{
		BinNodePosi(T) t = nullptr; //兄弟结点的红孩子
		if (IsRed(s->rchild))t = s->rchild;
		if (IsRed(s->lchild))t = s->lchild;
		if (t) //如果结点s有一个红孩子，可以通过旋转的方法，重构红黑树:BB-1
		{
			RBColor oldColor = p->color;
			BinNodePosi(T) gg = p->parent;  //3+4重构进行旋转操作
			BinNodePosi(T) P; 
			if (p->isRoot())
			{
				P = this->rotateAt(t);
				this->root() = P;


			}
			else if (p->isLchild())
			{
				P = this->rotateAt(t);
				gg->lchild = P;
			}
			else
			{
				P = this->rotateAt(t);
				gg->rchild = P;
			}
			if (P->hasLchild()) { P->lchild->color = RB_BLACK; updateHeight(P->lchild); }
			if (P->hasRchild()) { P->rchild->color = RB_BLACK; updateHeight(P->rchild); }
			P->color = oldColor;
			updateHeight(P);

		}
		else  //如果兄弟结点没有红孩子，意味着不能通过旋转操作完成红黑树平衡，因为2-4树s结点不够借的
		{
			s->color = RB_RED;
			s->height--;
			if (IsRed(p)) //如果父节点是红色的,父亲染黑色，兄弟染红色，红黑树平衡: BB-2R
			{
				p->color = RB_BLACK;
				
			}
			else //BB-2B
			{
				p->height--;
				solveDoubleBlack(p);
			}

		}
	}
	else //如果兄弟结点是红色的
	{
		s->color = RB_BLACK; //兄弟红色，变成黑的
		p->color = RB_RED; //父亲黑的，变成红的，然后执行一次3+4重构，把结构变成兄弟结点是黑色的其他情况
		BinNodePosi(T) t = s->isLchild() ? s->lchild : s->rchild;
		this->_hot = p;

		BinNodePosi(T) gg = p->parent;  //3+4重构进行旋转操作
		BinNodePosi(T) P;
		if (p->isRoot())
		{
			P = this->rotateAt(t);
			this->root() = P;


		}
		else if (p->isLchild())
		{
			P = this->rotateAt(t);
			gg->lchild = P;
		}
		else
		{
			P = this->rotateAt(t);
			gg->rchild = P;
		}
		solveDoubleBlack(r); //调整完结构变成其他情况的红黑树双黑修正
	}

}