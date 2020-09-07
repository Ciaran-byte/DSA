#pragma once
#include "BinNode.h"
#include "stack_vector.h"
#include "Queue_list.h"
#include <iostream>

template<typename T>
class OT
{
public:
	void operator()(const T& e) { std::cout << e << std::endl; }
};

template<typename T>
class BinTree
{
	
protected:

	//------------------------------------------------�ṹ��-------------------------------------
	BinNodePosi(T) _root; //���ڵ�
	int _size;  //���Ĺ�ģ��Ҳ���ǰ����Լ�����ȫ���������
	//-------------------------------------------�ṹ�������--------------------------------------

	//--------------------------------------���ߺ���---------------------------------------
	virtual int updateHeight(BinNodePosi(T) x); //���½��x�ĸ߶�
	void updateHeightAbove(BinNodePosi(T) x); //����ȫ�����ĸ߶�
	T max(const T& lhs, const T& rhs) { return lhs >= rhs ? lhs : rhs; }
	bool isRoot(BinNodePosi(T) x)const; //�жϽ���Ƿ�Ϊ���ڵ�
	bool isLChild(BinNodePosi(T) x) const;  //�жϽ���Ƿ�Ϊ���ӽ��
	bool isRChild(BinNodePosi(T) x) const; //�жϽ���Ƿ�Ϊ���ӽڵ�
	BinNodePosi(T)& FromParentTo(BinNodePosi(T)& x); //���Ը��ڵ������
	
	//----------------------------------���ߺ����������----------------------------------


public :
	//------------------------------------����Ϳ��ƺ���------------------------------
	BinTree():_size(0),_root(nullptr){}
	~BinTree() { if (_size > 0)remove(_root); }
	//---------------------------------����Ϳ��ƺ�������--------------------------------

	//-------------------------------------���ܺ���---------------------------------
	BinNodePosi(T)& root() { return _root; }
	int size()const { return _size; }
	bool empty() const { return !_root; }
	BinNodePosi(T) insertAsRoot(const T& e); //������ڵ�
	BinNodePosi(T) insertAsLC(BinNodePosi(T) x,const T& e); //Ϊĳ������������
	BinNodePosi(T) insertAsRC(BinNodePosi(T) x,const T& e); //Ϊĳ���������Һ���
	BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T>*& S); //��S������x�����Ϊ������
	BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T>*& S); //��S������x�����Ϊ���Һ���
	int removeAt(BinNodePosi(T) x); //ɾ��ĳ����㼰�������ӽڵ㡣����ɾ���������
	int remove(BinNodePosi(T) x);//ɾ��ĳ����㼰�������ӽڵ㣬���Ҹ������н��ĸ߶ȣ�����ɾ���������
	BinTree<T>* secede(BinNodePosi(T) x); //��ĳ����㼰�����²�����Ϊ������������
	template<typename VST> 
	void traversePre_R(BinNodePosi(T)x, VST& visit); //ǰ�����-�ݹ�汾
	template<typename VST>
	void traverseIn_R(BinNodePosi(T)x, VST& visit); //�������-�ݹ�汾
	template<typename VST>
	void traversePost_R(BinNodePosi(T)x, VST& visit); //��������-�ݹ�汾
	template<typename VST>
	void traversePre_I1(BinNodePosi(T)x, VST& visit); //ǰ�����--�����汾1
	template<typename VST>
	void traversePre_I2(BinNodePosi(T)x, VST& visit); //ǰ�����--�����汾2
	template<typename VST>
	void visitAlongLeftBrach(BinNodePosi(T)x, stack<BinNodePosi(T)>& S); //ǰ�����-�����汾2��������
	template<typename VST>
	void traverseIn_I1(BinNodePosi(T)x, VST& visit); //�������--�����汾1
	
	void goAlongLeftBranch(BinNodePosi(T)x, stack<BinNodePosi(T)>& S); //�������-�����汾1��������
	template<typename VST>
	void traverseIn_I2(BinNodePosi(T) x, VST& visit); //�������-�����汾2
	template<typename VST>
	void traverseIn_I3(BinNodePosi(T)x, VST& visit); //�������-�����汾3
	template<typename VST>
	void traversePost_I(BinNodePosi(T)x, VST& visit); //�������--�����汾
	
	void gotoHLVFL(stack < BinNodePosi(T)> & S); //�������--�����汾����������Ѱ��������ɼ�Ҷ�ڵ�
	template<typename VST>
	void travLevel(VST& visit); //�������--�����汾
	
	//------------------------------------���ܺ�������----------------------------------


};

//-----------------------------------------���ߺ���------------------------------------------
template<typename T>
int BinTree<T>::updateHeight(BinNodePosi(T)x) //���½��߶�
{
	
	return x->height=1 + max(Stature(x->lchild), Stature(x->rchild));
}

template<typename T>
void BinTree<T>::updateHeightAbove(BinNodePosi(T) x) //˳���ӽ�����ȫ�����ĸ߶�
{
	
	while (x) {  updateHeight(x); x = x->parent; }
	
}

template<typename T>
bool BinTree<T>::isRoot(BinNodePosi(T) x)const //�Ƿ�Ϊ���ڵ�
{
	return !(x->parent);
}

template<typename T>
bool BinTree<T>::isLChild(BinNodePosi(T) x) const //�ж��Ƿ�Ϊ���ӽ��
{

	return !isRoot(x) && (x == x->parent->lchild);
}

template<typename T>
bool BinTree<T>::isRChild(BinNodePosi(T) x) const
{
	return !isRoot(x) && (x == x->parent->rchild);
}

template<typename T>
BinNodePosi(T)& BinTree<T>::FromParentTo(BinNodePosi(T) &x) //�������Ը��ڵ������
{
	return isRoot(x) ? _root : isLChild(x) ? x->parent->lchild : x->parent->rchild;
}
//--------------------------------------���ܺ���----------------------------------------
template<typename T>
BinNodePosi(T) BinTree<T>::insertAsRoot(const T& e) //������ڵ�
{
	_size = 1;
	return _root = new BinNode<T>(e);
	
}

template<typename T>
BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x,const T& e) //�������ӽ��
{
	_size++;
	x->insertAsLC(e);
	updateHeightAbove(x);
	return x->lchild;
}

template<typename T>
BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, const T& e)//�����Һ��ӽ��
{
	_size++;
	x->insertAsRC(e);
	updateHeightAbove(x);
	return x->rchild;
}

template<typename T>
BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x, BinTree<T>* &S) //����һ������Ϊ����
{
	//������ǿ���
	if (x->lchild = S->_root) x->lchild->parent = x;
	_size += S->_size; //�������Ĺ�ģ
	updateHeightAbove(x); //���µ�ǰ������ϵ����߶�

	//���ԭ��
	S->_root = nullptr;
	S->_size = 0;
	S = nullptr;

	return x;

}

template<typename T>
BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x, BinTree<T>*& S) //����һ������Ϊ����
{
	//������ǿ���
	if (x->rchild = S->_root) x->rchild->parent = x;
	_size += S->_size; //�������Ĺ�ģ
	updateHeightAbove(x); //���µ�ǰ������ϵ����߶�

	//���ԭ��
	S->_root = nullptr;
	S->_size = 0;
	S = nullptr;

	return x;

}

template<typename T>
int BinTree<T>::removeAt(BinNodePosi(T) x) //ɾ����㼰�����µĽ�㣬������ɾ����������
{
	if (!x) return 0;
	int n = 1+removeAt(x->lchild) + removeAt(x->rchild);
	delete x;
	return n;
}

template<typename T>
int BinTree<T>::remove(BinNodePosi(T) x) //ɾ����㼰�����µĽ�㣬���¸߶ȣ�����ɾ����������
{
	
	//�жϽ���븸�ڵ����ϵ
	FromParentTo(x) = nullptr;
	
	//���¸��ڵ����ϵĽ��ĸ߶�
	updateHeightAbove(x->parent);
	
	//ɾ����㼰�����µĽ�㣬������ɾ������
	int n = removeAt(x); 

	//���½������
	_size -= n;
	
	//����ɾ�������
	return n;
}

template<typename T>
BinTree<T>* BinTree<T>::secede(BinNodePosi(T) x) //��ȡ����
{
	//ɾ������븸�ڵ�֮�������
	FromParentTo(x) = nullptr;

	//���¸��ڵ㼰�����ϵĸ߶�
	updateHeightAbove(x->parent);
	
	//���¸����Ľڵ���
	int size = x->size();
	this->_size -= size;

	//��������
	
	BinTree<T>* tree = new BinTree<T>();
	tree->_root = x;
	x->parent = nullptr;
	tree->_size = size;
	return tree;



}


template<typename T> template<typename VST>
void BinTree<T>::traversePre_R(BinNodePosi(T)x, VST& visit) //ǰ�����--�ݹ��
{
	if (!x)return;//�ݹ��
	visit(x->data); //data->lchlid->rchild
	traversePre_R(x->lchild, visit);
	traversePre_R(x->rchild, visit);
}
template<typename T> template<typename VST>
void BinTree<T>::traversePost_R(BinNodePosi(T)x, VST& visit) //�������--�ݹ��
{
	if (!x)return;//�ݹ��
	
	traversePost_R(x->lchild, visit);//lchild->rchild->data
	traversePost_R(x->rchild, visit);
	visit(x->data);
}
template<typename T> template<typename VST>
void BinTree<T>::traverseIn_R(BinNodePosi(T)x, VST& visit) //�������--�ݹ��
{
	if (!x)return;//�ݹ��

	traverseIn_R(x->lchild, visit);//lchild->data->rchild
	visit(x->data);
	traverseIn_R(x->rchild, visit);
	
}

template<typename T> template<typename VST>
void BinTree<T>::traversePre_I1(BinNodePosi(T)x, VST& visit) //ǰ�����--������1
{
	stack<BinNodePosi(T)> S; //��ʱջ
	if(x)S.push(x); //x��ջ
	while (!S.empty()) //ͨ��ջ�ķ�ʽģ��β�ݹ飬���԰ѵݹ��ɵ��������ǲ����ж���������ͨ�õı�����ʽ
	{
		 x = S.pop();
		visit(x->data);
		if (x->rchild) { S.push(x->rchild); } //��Ϊ�ȱ���������������Ӧ�����������ջ���ȳ�ջ
		if (x->lchild) { S.push(x->lchild); }
		
	}
}
template<typename T> template<typename VST>
void BinTree<T>::traversePre_I2(BinNodePosi(T)x, VST& visit) //ǰ�����--������2
{
	//�����汾2���Ӿ���ͨ�õı�����ʽ
	//��Ϊǰ�����������˳�������������Ȼ������������������������
	stack<BinNodePosi(T)> S;
	
	while (true) //���ջ���ǿյľͼ���
	{
		
		visitAlongLeftBrach(x, S); //������������������һ����㣬��������������򱣴���������Ȼ������һ���������ٱ���
		if (S.empty())break; //���ջ���ˣ�˵����������
		x = S.pop();
	}

}
template<typename T> template<typename VST>
void BinTree<T>::visitAlongLeftBrach(BinNodePosi(T)x, stack<BinNodePosi(T)>& S) //ǰ����������汾2��������
{
	while (x)
	{
		visit(x->data);
		S.push(x->rchild);
		x = x->lchild;
	}
}
template<typename T>
void BinTree<T>::goAlongLeftBranch(BinNodePosi(T)x, stack<BinNodePosi(T)>& S) //�������-�����汾1��������
{
	//��������������������ߵ��ף����򱣴���������Ȼ���ٷ�����ĩβ�����������������������������ջ�У�������һ����������ջ
	while (x)
	{
		S.push(x);
		x = x->lchild;
	}
}

template<typename T> template<typename VST>
void BinTree<T>::traverseIn_I1(BinNodePosi(T)x, VST& visit) //�������--������1
{
	stack<BinNodePosi(T)> S; //����ջ
	while (true)
	{
		goAlongLeftBranch(x, S);
		if (S.empty())break;
		x = S.pop();
		visit(x->data);
		x = x->rchild;
	}
}


template<typename T> template<typename VST>
void BinTree<T>::traverseIn_I2(BinNodePosi(T)x, VST& visit) //�������--������2
{
	//����汾�������汾1�ǵ�Ч��
	stack<BinNodePosi(T)> S; //����ջ
	while (true)
	{
		if (x)//���x���ǿսڵ�
		{
			S.push(x);
			x = x->lchild;
		}
		else if(!S.empty())//���x�ǿսڵ�
		{
			x = S.pop();
			visit(x->data);
			x = x->rchild;
		}
		else
		{
			break;
		}
	}
}

template<typename T> template<typename VST>
void BinTree<T>::traverseIn_I3(BinNodePosi(T)x, VST& visit) //�������--������3
{
	bool backtrack = false; //���ݱ�־�������ʽ��������������յ�ʱ�򣬻��ݵ���һ���ֲ�λ��
	while (true)
	{
		if (!backtrack && x->hasLchild()) //���û�з������ݣ�������ڵ㲻Ϊ��
		{
			x = x->lchild; //xһֱ����
		}
		else //��������˻���˵�����������ʹ��ˣ�������ڵ�Ϊ�գ�˵��û��Ҫ����������
		{
			visit(x->data); //���ʵ�ǰ���
			if (x->hasRchild()) //����ұ�������Ϊ��,Ӧ�������������������
			{
				x = x->rchild;
				backtrack = false;
			}
			else //�����������գ�������һ����̽����
			{
				if (!(x = x->succ()))break; //û�к�̵ľ��Ǳ�������
				backtrack = true;//���ݱ�־����
			}
		}
	}
}
template<typename T> 
void BinTree<T>::gotoHLVFL(stack<BinNodePosi(T)> & S) //�������--�����渨������
{
	while (BinNodePosi(T) x = S.top())
	{
		if (x->lchild) //��������ӽ��
		{
			if (x->rchild)//������Һ��ӽ�㣬�Һ�������ջ
			{
				S.push(x->rchild);
			}
			S.push(x->lchild);
		}
		else //���û�����ӽ��
		{
			S.push(x->rchild); //�ұ߽����ջ
		}
		S.pop(); //ջ���Ǹ���ջ��ɾȥ
	}
}
template<typename T> template<typename VST>
void BinTree<T>::traversePost_I(BinNodePosi(T)x, VST& visit) //�������--������
{
	stack<BinNodePosi(T)> S;
	S.push(x);
	while (!S.empty())
	{
		if (S.top() != x->parent)
		{
			this->gotoHLVFL(S);
		}
		x = S.pop();
		visit(x->data);
	}
}
template<typename T> template<typename VST>
void BinTree<T>::travLevel(VST& visit)//�������--�����汾
{
	queue<BinNodePosi(T)>Q;
	Q.enqueue(this);
	while (!Q.empty())
	{
		BinNodePosi(T) x = Q.dequeue();
		visit(x->data);
		if (x->lchild)Q.enqueue(x->lchild);
		if (x->rchild)Q.enqueue(x->rchild);
	}
}