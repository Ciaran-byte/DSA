#pragma once
#include "BST.h"
#include "BinTree.h"




template<typename T>
class AVL :public BST<T>
{
protected:
	bool Balanced(BinNodePosi(T) x);//�ж����Ƿ�ƽ��
	int BalFac(BinNodePosi(T)x); //ƽ������
	bool AvlBalanced(BinNodePosi(T) x); //AVL���Ƿ�ƽ��
	BinNodePosi(T) tallerChind(BinNodePosi(T) x); //����x���������
	
	
public:
	virtual BinNodePosi(T) insert(const T& e);
	virtual bool remove(const T& e);
};


template<typename T>
bool AVL<T>::Balanced(BinNodePosi(T) x) //�ж�������Ƿ�ƽ��
{
	return Stature(x->lchild) == Stature(x->rchild);
}

template<typename T>
int AVL<T>::BalFac(BinNodePosi(T)x) //ƽ������
{
	return Stature(x->lchild) - Stature(x->rchild);
}

template<typename T>
bool AVL<T>::AvlBalanced(BinNodePosi(T) x) //�ж�AVL���Ƿ���ƽ���
{
	return (BalFac(x) > -2 && BalFac(x) < 2);
}

template<typename T>
BinNodePosi(T) AVL<T>::tallerChind(BinNodePosi(T)x) //���ߵ�����
{
	return Stature(x->lchild) > Stature(x->rchild) ? x->lchild : //������
		Stature(x->lchild) < Stature(x->rchild) ? x->rchild : //������
		x->isLchild() ? x->lchild : x->rchild;  //����������ȸߣ������븸��ͬ�����һ������

}

template<typename T>
BinNodePosi(T) AVL<T>::insert(const T& e)
{

	BinNodePosi(T)& x = BST<T>::search(e);
	
	if (x)return x;//���Ŀ������ڣ�ֱ�ӷ���
	//���Ŀ���㲻���ڣ�x��Ҫ�����λ�ã�_hot���丸�ڵ�
	x = new BinNode<T>(e, this->_hot); this->_size++; //����x�൱�� _hot->child = .....
	

	BinNodePosi(T) xx = x;
	
	for (BinNodePosi(T) g = this->_hot; g; g = g->parent)
	{
		//���ڲ��������˵��ֻ��Ҫ�ҵ���͵Ĳ�ƽ�⸸�ڵ��������ɣ����ڵ�ĸ߶Ȳ��䣬���Ͻ��ض���ƽ����
		if (!AvlBalanced(g)) //������ڵ�g��ƽ��
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
bool AVL<T>::remove(const T& e) //ƽ���������ɾ������
{
	BinNodePosi(T)& x = this->search(e);
	if (!x)return false; //�����ڽ�㣬�޷�ɾ��
	removeAt(x, this->_hot); //ɾ��x��㣬���ұ����丸�ڵ�_hot;
	this->_size--;
	for (BinNodePosi(T)g = this->_hot; g; g = g->parent)
	{
		if (!AvlBalanced(g)) //������ƽ���㣬�����������н�㶼��ƽ��
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