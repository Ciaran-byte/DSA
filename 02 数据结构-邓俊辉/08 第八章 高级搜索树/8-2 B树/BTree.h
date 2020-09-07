#pragma once
#include "BTNode.h"
#include "release.h"
//



template<typename T>
class BTree
{

protected:
	int _size; //关键码总数
	int _order; //B树的阶次。阶次表示每个结点最多的子孩子结点个数
	BTNodePosi(T) _root; //根节点
	BTNodePosi(T) _hot; //寻找结点的父亲结点
	void solveOverflow(BTNodePosi(T) v); //处理上溢操作
	void solveUnderflow(BTNodePosi(T) v);//处理下溢操作
	
public:
	BTree(int order = 3) :_order(order), _size(0)
	{
		_root = new BTNode<T>();
		
	}
	~BTree()
	{
		if (_root)release(_root);
	}
	int order()const { return _order; }//阶次
	int size()const { return _size; }//规模
	BTNodePosi(T)& root() { return _root; }//根节点
	bool empty()const { return !_root; }//是否为空
	BTNodePosi(T) search(const T& e); //查找操作
	bool insert(const T& e); //插入操作
	bool remove(const T& e); //删除操作
};

template<typename T>
BTNodePosi(T) BTree<T>::search(const T& e) //查找
{
	BTNodePosi(T) v = _root;
	_hot = nullptr;
	while (v)
	{
		int r = v->key.binSearchD(e);
		if (r >= 0 && e == v->key[r])
		{
			return v;
		}
		
			_hot = v;
			v = v->child[r + 1];
		
	}
	return nullptr;

}

template<typename T>
bool BTree<T>::insert(const T& e) //B树的插入操作
{

	BTNodePosi(T)v = search(e);
	
	if (v)return false; //如果存在结点，返回false
	
	int r = _hot->key.binSearchD(e); //找到应该插入结点的位置
	
	_hot->key.insert(e, r+1);
	_hot->child.insert(nullptr, r + 2);
	_size++;
	solveOverflow(_hot);
	return true;
}

template<typename T>
void BTree<T>::solveOverflow(BTNodePosi(T) v)
{
	
		if (v->child.size()<=_order)return; //如果结点的child不到m，就返回，不发生overflow
		int s = _order / 2; //s的位置就是要被取出来插入到上一级结点的结点
		BTNodePosi(T) u = new BTNode<T>(); //新创建的结点自带一个child
		for (int i = 0; i < _order - s - 1; i++) //把结点右侧child全都分裂进入新结点中
		{
			u->child.insert(v->child.remove(s + 1), i);
			u->key.insert(v->key.remove(s + 1),i);
			
		}
		u->child[_order - s - 1] = v->child.remove(s + 1);  //转入最后一个child
		if (u->child[0]) //如果u的孩子结点不是空
		{
			for (int i = 0; i < _order - s; i++)
			u->child[i]->parent = u;
		}
		
		BTNodePosi(T) p = v->parent;
		if (!p) { p= new BTNode<T>(); _root = p; p->child[0] = v; v->parent = p; }
		int r = p->key.binSearchD(v->key[0])+1;  //构建新结点，并且把v中最后一个结点提升到p中去
		p->key.insert( v->key.remove(s),r);
		p->child.insert(u,r+1); //插入u
		u->parent = p;
		solveOverflow(p); //继续检查新插入结点的p是否需要上溢操作

	


}

template<typename T>
bool BTree<T>::remove(const T& e)
{
	
	BTNodePosi(T) v = search(e);
	
	

	if (v==nullptr)return false;
	
	
	

	int r = v->key.binSearchD(e); //找到关键码e所在的秩
	
	
	if (v->child[0]) //如果找到的v不是叶节点
	{
		BTNodePosi(T) u = v->child[r+1]; //后继结点就是右边邻接结点的最左侧的孩子
		while (u->child[0])u = u->child[0]; //u就是v的后继结点
		
		v->key[r] = u->key[0]; //把v变成u，然后把v指向u，现在删除v就是叶节点了
		v = u;
		r = 0;
	}
	v->key.remove(r);
	v->child.remove(r + 1); //因为v是叶节点，child都是空，删除哪一个都行，这里是为了易读性
	_size--;
	
	solveUnderflow(v); //如果需要结点的child太少了，就需要合并了
	
	return true;
}
template<typename T>
void BTree<T>::solveUnderflow(BTNodePosi(T) v)//处理下溢操作
{
	
	if ( (_order+1) / 2<= v->child.size())return; //这里是向上取整，孩子数量最少为m/2

	BTNodePosi(T) p = v->parent;

	if (!p) //如果已经到了最上面一个结点
	{
		if (!v->key.size() && v->child[0]) //如果关键码空了，但是还有一个孩子结点
		{
			_root = v->child[0];
			_root->parent = nullptr;  //把v孩子结点作为根节点，删除结点v

			v->child[0] = nullptr;
			release(v);
		}
		return;
	}
	
	int r = 0;
	while (p->child[r] != v)r++; //判断v是第几个孩子结点
	
	
	//01向左兄弟借结点
	if (r > 0) //如果不是第一个孩子，左边兄弟结点肯定存在
	{
		BTNodePosi(T) ls = p->child[r - 1];
		if (ls->child.size() > (_order + 1) / 2) //如果左兄弟去掉一个结点以后还满足大于m/2那就把一个结点给右兄弟
		{
			v->key.insert(p->key[r-1], 0); //p把一个结点给v
			p->key[r - 1] = ls->key.remove(ls->key.size() - 1); //左兄弟把借出的结点给p
			v->child.insert(ls->child.remove(ls->child.size() - 1), 0);
			if (v->child[0])v->child[0]->parent = v;
			return;
		}
	}

	//02 向右兄弟借结点
	if (r < p->child.size() - 1) //说明不是最右边结点，可以向右兄弟借结点
	{
		BTNodePosi(T) rs = p->child[r + 1];
		if (rs->child.size() > (_order + 1) / 2)
		{
			v->key.insert(p->key[r], v->key.size());
			p->key[r] = rs->key.remove(0);
			v->child.insert(rs->child.remove(0), v->child.size());
			if (v->child[v->child.size() - 1])
			{
				v->child[v->child.size() - 1]->parent = v;
			}
			return;
		}
		

	}

	//03 向左兄弟合并，因为左兄弟不能借结点。 

	if (r > 0)
	{
		BTNodePosi(T) ls = p->child[r - 1];//左兄弟
		ls->key.insert(p->key.remove(r - 1), ls->key.size());
		p->child.remove(r); //把应该合并的结点移动到下面来
		ls->child.insert(v->child.remove(0), ls->child.size());
		if (ls->child[ls->child.size() - 1])
		{
			ls->child[ls->child.size() - 1]->parent = ls;
		}
		while (!v->key.empty())
		{
			ls->key.insert(v->key.remove(0), ls->key.size());
			ls->child.insert(v->child.remove(0), ls->child.size());
			
			if (ls->child[ls->child.size() - 1])ls->child[ls->child.size() - 1]->parent = ls;
		}
		release(v);
	}
	//04 与右兄弟合并
	else
	{
		BTNodePosi(T) rs = p->child[r+1];//右兄弟
		rs->key.insert(p->key.remove(r),0);
		p->child.remove(r); //把应该合并的结点移动到下面来
		rs->child.insert(v->child.remove(v->child.size()-1),0);
		if (rs->child[0])
		{
			rs->child[0]->parent = rs;
		}
		while (!v->key.empty())
		{
			rs->key.insert(v->key.remove(v->key.size() - 1), 0);
			rs->child.insert(v->child.remove(v->child.size() - 1), 0);
			
			if(rs->child[0])rs->child[0]->parent = rs;
		}
		release(v);
	}

	solveUnderflow(p);
	return;
}

