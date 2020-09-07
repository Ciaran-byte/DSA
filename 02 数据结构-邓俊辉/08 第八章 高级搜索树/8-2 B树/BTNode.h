

#pragma once
#include "vector.h"
#define BTNodePosi(T) BTNode<T>*  //B���Ľ��

template<typename T>
struct BTNode //B�����
{
	BTNodePosi(T) parent; //���ڵ�
	vector<T> key; //�ؼ���
	vector<BTNodePosi(T)> child; //�ӽڵ�����ã������ܱȹؼ��볤�ȴ�1

	BTNode() { parent = nullptr; child.insert(NULL,0); }
	BTNode( T e, BTNodePosi(T) lchild = nullptr, BTNodePosi(T) rchild = nullptr)
	{
		parent = nullptr;
		key.insert(e,0);
		child.insert(lchild,0); child.insert(rchild,1);
		if (lchild)lchild->parent = this; if (rchild)rchild->parent = this;

	}
};

