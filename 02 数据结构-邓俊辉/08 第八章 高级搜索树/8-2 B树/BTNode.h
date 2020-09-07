

#pragma once
#include "vector.h"
#define BTNodePosi(T) BTNode<T>*  //B树的结点

template<typename T>
struct BTNode //B树结点
{
	BTNodePosi(T) parent; //父节点
	vector<T> key; //关键码
	vector<BTNodePosi(T)> child; //子节点的引用，长度总比关键码长度大1

	BTNode() { parent = nullptr; child.insert(NULL,0); }
	BTNode( T e, BTNodePosi(T) lchild = nullptr, BTNodePosi(T) rchild = nullptr)
	{
		parent = nullptr;
		key.insert(e,0);
		child.insert(lchild,0); child.insert(rchild,1);
		if (lchild)lchild->parent = this; if (rchild)rchild->parent = this;

	}
};

