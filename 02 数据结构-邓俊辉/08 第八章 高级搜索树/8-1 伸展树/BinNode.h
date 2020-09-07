#pragma once

#define Stature(p) ((p)?(p)->height:-1) //����ǿս�㣬�߶�Ϊ-1��ֻ�и��ڵ㣬�߶���0
#define BinNodePosi(T) BinNode<T>*
typedef enum {RB_RED,RB_BLACK} RBColor;

template<typename T>
class BinNode //�������Ľ��
{
public:
	T data;
	BinNodePosi(T) parent;	BinNodePosi(T) lchild;	BinNodePosi(T) rchild; //���ڵ�������ӽڵ�
	int height; //�߶�
	int npl; //��ʽ��
	RBColor color; //�����

	//���캯��
	BinNode():parent(nullptr),lchild(nullptr),rchild(nullptr),height(0),npl(1),color(RB_RED){}


	BinNode(T data,BinNodePosi(T) p = nullptr,BinNodePosi(T) lc = nullptr,BinNodePosi(T) rc = nullptr,
		int h = 0,int l = 1,RBColor c = RB_RED):
		data(data),parent(p),lchild(lc),rchild(rc),height(h),npl(l),color(c){}
	//�������Һ��ӽ��
	BinNodePosi(T) insertAsLC(const T& e);
	BinNodePosi(T) insertAsRC(const T& e);

	//���������
	bool operator<(const BinNode& rhs)
	{
		return this->data < rhs.data;
	}
	bool operator==(const BinNode& rhs)
	{
		return this->data == rhs.data;
	}

	//ͳ�Ƶ�ǰ��㼰����������
	int size(BinNodePosi(T) x)const;
	int size()const { size(this); }

	//���������ֱ�Ӻ��
	BinNodePosi(T) succ();
	//�жϵ�ǰ����Ƿ�Ϊ���һ��߸��ڵ�
	bool isRoot()const;
	bool isRchild()const;
	bool isLchild()const;
	bool hasLchild()const;
	bool hasRchild()const;
	
};

template<typename T>
BinNodePosi(T) BinNode<T>::insertAsLC(const T& e)
{
	return lchild = new BinNode<T>(e, this);

}
template<typename T>
BinNodePosi(T) BinNode<T>::insertAsRC(const T& e)
{
	return rchild = new BinNode<T>(e, this);

}

template<typename T>
int BinNode<T>::size(BinNodePosi(T) x)const
{
	if (!x)return 0;
	int n = size(x->lchild) + size(x->rchild) + 1;
	return n;
}
template<typename T>
bool BinNode<T>::isRoot() const //�ж��Ƿ�Ϊ���ڵ�
{
	return !(this->parent);
}
template<typename T>
bool BinNode<T>::isLchild() const //�ж��Ƿ�Ϊ���ӽڵ�
{
	return !isRoot() && (this->parent->lchild == this);
}
template<typename T>
bool BinNode<T>::isRchild() const //�ж��Ƿ�Ϊ���ӽڵ�
{
	return (!isRoot() && (this->parent->rchild == this));
}
template<typename T>
bool BinNode<T>::hasRchild() const //�ж��Ƿ������ӽڵ�
{
	return rchild!=nullptr;
}
template<typename T>
bool BinNode<T>::hasLchild()const //�ж��Ƿ������ӽ��
{
	return lchild!=nullptr;
}
template<typename T>
BinNodePosi(T)  BinNode<T>::succ() //���������ֱ�Ӻ�̽��
{
	BinNodePosi(T) x = this;
	if (rchild)//��������ӽڵ㣬ֱ�Ӻ��һ�������ӽڵ�����ߵ��Ǹ�
	{
		x = rchild;
		while (x->hasLchild())x = x->lchild;
		
	}
	else //���û�����ӽڵ㣬�����ŵ�ǰ������ϣ�����������Ѱ�Һ�̽��
	{
		while (x->isRchild())
		{
			x = x->parent;
		}//������������ұ߽��Ļ������ĸ��ڵ�һ���Լ����������ˣ�����������
		x = x->parent;
	}
	return x;
}
