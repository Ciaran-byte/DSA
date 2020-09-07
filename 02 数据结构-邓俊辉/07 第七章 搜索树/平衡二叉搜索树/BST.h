#pragma once
#include"BinTree.h"
#include<iostream>
template<typename T>
class BST:public BinTree<T> //���������������ṹ
{
protected:
	BinNodePosi(T) _hot; //���н��ĸ��׽��
	
	BinNodePosi(T)& searchIn(BinNodePosi(T)& v, const T& e, BinNodePosi(T)& hot);//���ҵĹ��ߺ���
	BinNodePosi(T) connect34 //�������ع�
	(
		BinNodePosi(T) a, BinNodePosi(T) b, BinNodePosi(T) c,
		BinNodePosi(T) T0, BinNodePosi(T) T1, BinNodePosi(T) T2, BinNodePosi(T) T3
	);
BinNodePosi(T) rotateAt(BinNodePosi(T)x); //�Զ��������˳����е���
	
public:
	virtual BinNodePosi(T)& search(const T& e); //����
	virtual BinNodePosi(T) insert(const T& e);//����
	virtual bool remove(const T& e);//ɾ��
	
};

//��Ա����
template<typename T>
BinNodePosi(T)& BST<T>::searchIn(BinNodePosi(T)& v, const T& e, BinNodePosi(T)& hot) //�ݹ����
{
	if (!v || v->data == e)return v;
	hot = v;
	return searchIn((v->data > e ? v->lchild : v->rchild), e, hot);
}
template<typename T>
BinNodePosi(T)& BST<T>::search(const T& e) //�������ⲿ�Ĳ��Һ���
{
	
	return searchIn(this->root(), e, _hot=nullptr);
}

template<typename T>
BinNodePosi(T) BST<T>::insert(const T& e) //������
{
	BinNodePosi(T)& x = search(e);
	if (x)return x; //������ڣ�ֱ�ӷ���
	x = new BinNode<T>(e,_hot); //�������
	this->_size++; //�������ģ+1
	this->updateHeightAbove(x); //�������н�������
	
	return x;
}


template<typename T>
BinNodePosi(T) removeAt(BinNodePosi(T)&x,BinNodePosi(T)& hot)
{
	//x��Ҫ��ɾ���Ľ�㣬hot��x�ĸ��ڵ�
	BinNodePosi(T) w = x; //w����Ҫ��ɾ�����ĵ�ַ
	BinNodePosi(T) succ = nullptr; //�����̽��
	if (!x->hasLchild()) //���û��������
	{
		x = x->rchild; //hot->child=x->rchild,��Ϊ������
		succ = x;//���ڻָ����׽���ϵ��

	}
	else if (!x->hasRchild())//���û��������
	{
		x = x->lchild;
		succ = x;
	}
	else //������ҷ�֧���У����ҵ��ý���̽����н�����Ȼ��ɾ�������ˣ�Ȼ���Ϊ����֧���
	{
		//�������������
		w = w->succ();
		T temp = w->data;
		w->data = x->data;
		x->data = temp;

		//����w����Ҫ��ɾ���Ľ����
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

//-------------------------------------------�������ع�---------------------------------------------------
template<typename T>  //����BST��ĺ������������ع�
BinNodePosi(T) BST<T>::connect34(
	BinNodePosi(T) a, BinNodePosi(T) b, BinNodePosi(T) c,
	BinNodePosi(T) T0, BinNodePosi(T) T1, BinNodePosi(T) T2, BinNodePosi(T) T3
)
{
	//��ν�����ع������ǰ������������˳�������������Ȼ�󷵻������ĸ��ڵ�
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
BinNodePosi(T)BST<T>::rotateAt(BinNodePosi(T) v) //ʹ���������ع�����ƽ�����,v�������Ͳ�ƽ���������ӽ��
{
	
	BinNodePosi(T)p = v->parent; //��Ͳ�ƽ�������ӽڵ�
	BinNodePosi(T)g = p->parent; //��Ͳ�ƽ�����ĸ��ڵ�
	if (p->isLchild()) //zig
	{
		if (v->isLchild()) //zig-zig ����
		{
			p->parent = g->parent; //���ص��¸��ڵ���p����Ҫ����һ���丸�ڵ�
			return connect34(v, p, g, v->lchild, v->rchild, p->rchild, g->rchild);
		}
		else //zig-zag; ��-��
		{
			v->parent = g->parent;
			return connect34(p, v, g, p->lchild, v->lchild, v->rchild, g->rchild);
		}
	}
	else //zag ��
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