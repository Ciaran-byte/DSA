#pragma once
#include "BST.h"
#include<iostream>
template<typename T>
inline bool IsBlack(BinNodePosi(T) p) { return (!p) || (p->color == RB_BLACK); }

template<typename T>
inline bool IsRed(BinNodePosi(T) p) { return !IsBlack(p); } //�жϽ����ɫ

template<typename T>
inline bool BlackUpdateHeight(BinNodePosi(T)p) //�Ƿ���Ҫ���½��߶�
{
	return (Stature(p->lchild) == Stature(p->rchild)) && (p->height == (IsRed(p) ? Stature(p->lchild) : Stature(p->lchild) + 1));
}

template<typename T>
class RedBlack :public BST<T>
{
protected:
	void sovlveDoubleRed(BinNodePosi(T) x);//˫������
	void solveDoubleBlack(BinNodePosi(T)x); //˫������
	virtual int updateHeight(BinNodePosi(T) x); //���½��ĺڸ߶�

public:
	virtual BinNodePosi(T) insert(const T& e); //�������
	virtual bool remove(const T& e); //ɾ������
	//search���ö����������Ľӿ�
	
};



//----------------------------------���ܺ���----------------------------
template<typename T>
int RedBlack<T>::updateHeight(BinNodePosi(T)x)//�߶�����
{
	
	x->height = this->max(Stature(x->lchild), Stature(x->rchild)); //���Ӹ߶�һ����ȣ�����˫��
	return IsBlack(x) ? x->height++ : x->height;

}

template<typename T>
BinNodePosi(T) RedBlack<T>::insert(const T& e) //�������
{
	BinNodePosi(T)& x = this->search(e);
	
	if (x)return x;
	x = new BinNode<T>(e, this->_hot, nullptr, nullptr, -1); //�߶�Ϊ-1�ĺ���
	
	this->_size++;
	sovlveDoubleRed(x); //˫������
	
	return x ? x : this->_hot->parent; //��仰���Ƿǳ���
}

template<typename T>
void RedBlack<T>::sovlveDoubleRed(BinNodePosi(T)x)
{
	
	if (x->isRoot()) //����Ǹ��ڵ�
	{
		x->color = RB_BLACK;
		x->height++;
		return;
	}
	
	if(x->parent->color==RB_BLACK) //�ڽ��ֱ�ӷ���
	{
		return;
	}

	BinNodePosi(T) p = x->parent;
	BinNodePosi(T) g = p->parent; //������ڵ�Ϊ�죬һ�����游���
	BinNodePosi(T) u = x->uncle(); //������
	if (IsBlack(u)) //����������Ǻ�ɫ��
	{
	
		//������Ϊ�ڣ��ᷢ���������ع��������ڲ�����½����Ϣ�����ԣ����ض�����ºڸ߶�
		if (p->isLchild() == x->isLchild()) //����Ǹ��ӽ��ͬ��
		{
			p->color = RB_BLACK;

		}
		else //������ӽڵ�����
		{
			x->color = RB_BLACK;
		}
		
		g->color = RB_RED;//�游���һ���ᱻȾɫΪ��ɫ
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
	if (!x)return false; //���û�н��x��������ɾ��������ʧ��
	BinNodePosi(T) r = removeAt(x, this->_hot); //ɾ�����x��rΪx��ֱ�Ӻ�̽�㣬_hot��¼x�ĸ��ڵ�λ��
	if (!(--this->_size)) { return true; } //��ģ-1�������ģΪ0�ˣ�˵������Ҫ�������ж���

	if (!this->_hot) //���_hotΪ�գ�˵��ɾ�����Ǹ��ڵ㣬��ôֱ�Ӻ��һ���Ǹ�Ҷ�ڵ㣬��ɫ�ģ�Ⱦ�ھ��У��ڸ߶Ȳ���
	{
		this->_root->color = RB_BLACK; //Ⱦ��
		updateHeight(this->_root); //���¸��ڵ�߶�
		return true;
	}



	//-----------------------------ɾ�����ͺ�̽��һ��һ�ڵ����-------------------------------------------
	//���ɾ���Ĳ��Ǹ��ڵ㣬����ɾ�������Ժ󣬺������Ȼƽ�⣬ֱ�ӷ��ؼ���
	if (BlackUpdateHeight(this->_hot))return true; 


	if (IsRed(r)) //��̽���Ǹ���ģ����ڵ�ض��Ǻڵģ��Ѻ�̽��Ⱦɫ������ƽ������
	{
		r->color = RB_BLACK;
		r->height++;
		return true;
	}

	//�����ɾ���ͺ�̽�㶼�Ǻ�ɫ�ģ��͵�˫�ڵ���
	solveDoubleBlack(r);
	return true;
}

template<typename T>
void RedBlack<T>::solveDoubleBlack(BinNodePosi(T) r) //˫������
{
	BinNodePosi(T) p = r ? r->parent : this -> _hot;
	if (!p)return;
	BinNodePosi(T) s = (r == p->lchild) ? p->rchild : p->lchild; //s�Ǻ�̽��r���ֵܽ��

	if (IsBlack(s)) //����ֵ��Ǻ�ɫ���
	{
		BinNodePosi(T) t = nullptr; //�ֵܽ��ĺ캢��
		if (IsRed(s->rchild))t = s->rchild;
		if (IsRed(s->lchild))t = s->lchild;
		if (t) //������s��һ���캢�ӣ�����ͨ����ת�ķ������ع������:BB-1
		{
			RBColor oldColor = p->color;
			BinNodePosi(T) gg = p->parent;  //3+4�ع�������ת����
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
		else  //����ֵܽ��û�к캢�ӣ���ζ�Ų���ͨ����ת������ɺ����ƽ�⣬��Ϊ2-4��s��㲻�����
		{
			s->color = RB_RED;
			s->height--;
			if (IsRed(p)) //������ڵ��Ǻ�ɫ��,����Ⱦ��ɫ���ֵ�Ⱦ��ɫ�������ƽ��: BB-2R
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
	else //����ֵܽ���Ǻ�ɫ��
	{
		s->color = RB_BLACK; //�ֵܺ�ɫ����ɺڵ�
		p->color = RB_RED; //���׺ڵģ���ɺ�ģ�Ȼ��ִ��һ��3+4�ع����ѽṹ����ֵܽ���Ǻ�ɫ���������
		BinNodePosi(T) t = s->isLchild() ? s->lchild : s->rchild;
		this->_hot = p;

		BinNodePosi(T) gg = p->parent;  //3+4�ع�������ת����
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
		solveDoubleBlack(r); //������ṹ�����������ĺ����˫������
	}

}