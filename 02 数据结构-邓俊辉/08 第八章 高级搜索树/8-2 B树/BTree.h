#pragma once
#include "BTNode.h"
#include "release.h"
//



template<typename T>
class BTree
{

protected:
	int _size; //�ؼ�������
	int _order; //B���Ľ״Ρ��״α�ʾÿ����������Ӻ��ӽ�����
	BTNodePosi(T) _root; //���ڵ�
	BTNodePosi(T) _hot; //Ѱ�ҽ��ĸ��׽��
	void solveOverflow(BTNodePosi(T) v); //�����������
	void solveUnderflow(BTNodePosi(T) v);//�����������
	
public:
	BTree(int order = 3) :_order(order), _size(0)
	{
		_root = new BTNode<T>();
		
	}
	~BTree()
	{
		if (_root)release(_root);
	}
	int order()const { return _order; }//�״�
	int size()const { return _size; }//��ģ
	BTNodePosi(T)& root() { return _root; }//���ڵ�
	bool empty()const { return !_root; }//�Ƿ�Ϊ��
	BTNodePosi(T) search(const T& e); //���Ҳ���
	bool insert(const T& e); //�������
	bool remove(const T& e); //ɾ������
};

template<typename T>
BTNodePosi(T) BTree<T>::search(const T& e) //����
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
bool BTree<T>::insert(const T& e) //B���Ĳ������
{

	BTNodePosi(T)v = search(e);
	
	if (v)return false; //������ڽ�㣬����false
	
	int r = _hot->key.binSearchD(e); //�ҵ�Ӧ�ò������λ��
	
	_hot->key.insert(e, r+1);
	_hot->child.insert(nullptr, r + 2);
	_size++;
	solveOverflow(_hot);
	return true;
}

template<typename T>
void BTree<T>::solveOverflow(BTNodePosi(T) v)
{
	
		if (v->child.size()<=_order)return; //�������child����m���ͷ��أ�������overflow
		int s = _order / 2; //s��λ�þ���Ҫ��ȡ�������뵽��һ�����Ľ��
		BTNodePosi(T) u = new BTNode<T>(); //�´����Ľ���Դ�һ��child
		for (int i = 0; i < _order - s - 1; i++) //�ѽ���Ҳ�childȫ�����ѽ����½����
		{
			u->child.insert(v->child.remove(s + 1), i);
			u->key.insert(v->key.remove(s + 1),i);
			
		}
		u->child[_order - s - 1] = v->child.remove(s + 1);  //ת�����һ��child
		if (u->child[0]) //���u�ĺ��ӽ�㲻�ǿ�
		{
			for (int i = 0; i < _order - s; i++)
			u->child[i]->parent = u;
		}
		
		BTNodePosi(T) p = v->parent;
		if (!p) { p= new BTNode<T>(); _root = p; p->child[0] = v; v->parent = p; }
		int r = p->key.binSearchD(v->key[0])+1;  //�����½�㣬���Ұ�v�����һ�����������p��ȥ
		p->key.insert( v->key.remove(s),r);
		p->child.insert(u,r+1); //����u
		u->parent = p;
		solveOverflow(p); //��������²������p�Ƿ���Ҫ�������

	


}

template<typename T>
bool BTree<T>::remove(const T& e)
{
	
	BTNodePosi(T) v = search(e);
	
	

	if (v==nullptr)return false;
	
	
	

	int r = v->key.binSearchD(e); //�ҵ��ؼ���e���ڵ���
	
	
	if (v->child[0]) //����ҵ���v����Ҷ�ڵ�
	{
		BTNodePosi(T) u = v->child[r+1]; //��̽������ұ��ڽӽ��������ĺ���
		while (u->child[0])u = u->child[0]; //u����v�ĺ�̽��
		
		v->key[r] = u->key[0]; //��v���u��Ȼ���vָ��u������ɾ��v����Ҷ�ڵ���
		v = u;
		r = 0;
	}
	v->key.remove(r);
	v->child.remove(r + 1); //��Ϊv��Ҷ�ڵ㣬child���ǿգ�ɾ����һ�����У�������Ϊ���׶���
	_size--;
	
	solveUnderflow(v); //�����Ҫ����child̫���ˣ�����Ҫ�ϲ���
	
	return true;
}
template<typename T>
void BTree<T>::solveUnderflow(BTNodePosi(T) v)//�����������
{
	
	if ( (_order+1) / 2<= v->child.size())return; //����������ȡ����������������Ϊm/2

	BTNodePosi(T) p = v->parent;

	if (!p) //����Ѿ�����������һ�����
	{
		if (!v->key.size() && v->child[0]) //����ؼ�����ˣ����ǻ���һ�����ӽ��
		{
			_root = v->child[0];
			_root->parent = nullptr;  //��v���ӽ����Ϊ���ڵ㣬ɾ�����v

			v->child[0] = nullptr;
			release(v);
		}
		return;
	}
	
	int r = 0;
	while (p->child[r] != v)r++; //�ж�v�ǵڼ������ӽ��
	
	
	//01�����ֵܽ���
	if (r > 0) //������ǵ�һ�����ӣ�����ֵܽ��϶�����
	{
		BTNodePosi(T) ls = p->child[r - 1];
		if (ls->child.size() > (_order + 1) / 2) //������ֵ�ȥ��һ������Ժ��������m/2�ǾͰ�һ���������ֵ�
		{
			v->key.insert(p->key[r-1], 0); //p��һ������v
			p->key[r - 1] = ls->key.remove(ls->key.size() - 1); //���ֵܰѽ���Ľ���p
			v->child.insert(ls->child.remove(ls->child.size() - 1), 0);
			if (v->child[0])v->child[0]->parent = v;
			return;
		}
	}

	//02 �����ֵܽ���
	if (r < p->child.size() - 1) //˵���������ұ߽�㣬���������ֵܽ���
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

	//03 �����ֵܺϲ�����Ϊ���ֵܲ��ܽ��㡣 

	if (r > 0)
	{
		BTNodePosi(T) ls = p->child[r - 1];//���ֵ�
		ls->key.insert(p->key.remove(r - 1), ls->key.size());
		p->child.remove(r); //��Ӧ�úϲ��Ľ���ƶ���������
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
	//04 �����ֵܺϲ�
	else
	{
		BTNodePosi(T) rs = p->child[r+1];//���ֵ�
		rs->key.insert(p->key.remove(r),0);
		p->child.remove(r); //��Ӧ�úϲ��Ľ���ƶ���������
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

