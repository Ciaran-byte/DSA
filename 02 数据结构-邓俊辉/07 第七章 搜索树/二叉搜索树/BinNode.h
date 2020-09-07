#pragma once

#define Stature(p) ((p)?(p)->height:-1) //如果是空结点，高度为-1，只有根节点，高度是0
#define BinNodePosi(T) BinNode<T>*
typedef enum {RB_RED,RB_BLACK} RBColor;

template<typename T>
class BinNode //二叉树的结点
{
public:
	T data;
	BinNodePosi(T) parent;	BinNodePosi(T) lchild;	BinNodePosi(T) rchild; //父节点和左右子节点
	int height; //高度
	int npl; //左式堆
	RBColor color; //红黑树

	//构造函数
	BinNode():parent(nullptr),lchild(nullptr),rchild(nullptr),height(0),npl(1),color(RB_RED){}


	BinNode(T data,BinNodePosi(T) p = nullptr,BinNodePosi(T) lc = nullptr,BinNodePosi(T) rc = nullptr,
		int h = 0,int l = 1,RBColor c = RB_RED):
		data(data),parent(p),lchild(lc),rchild(rc),height(h),npl(l),color(c){}
	//插入左右孩子结点
	BinNodePosi(T) insertAsLC(const T& e);
	BinNodePosi(T) insertAsRC(const T& e);

	//运算符重载
	bool operator<(const BinNode& rhs)
	{
		return this->data < rhs.data;
	}
	bool operator==(const BinNode& rhs)
	{
		return this->data == rhs.data;
	}

	//统计当前结点及其后代的数量
	int size(BinNodePosi(T) x)const;
	int size()const { size(this); }

	//中序遍历的直接后继
	BinNodePosi(T) succ();
	//判断当前结点是否为左右或者根节点
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
bool BinNode<T>::isRoot() const //判断是否为根节点
{
	return !(this->parent);
}
template<typename T>
bool BinNode<T>::isLchild() const //判断是否为左子节点
{
	return !isRoot() && (this->parent->lchild == this);
}
template<typename T>
bool BinNode<T>::isRchild() const //判断是否为右子节点
{
	return (!isRoot() && (this->parent->rchild == this));
}
template<typename T>
bool BinNode<T>::hasRchild() const //判断是否有右子节点
{
	return rchild!=nullptr;
}
template<typename T>
bool BinNode<T>::hasLchild()const //判断是否有左子结点
{
	return lchild!=nullptr;
}
template<typename T>
BinNodePosi(T)  BinNode<T>::succ() //中序遍历的直接后继结点
{
	BinNodePosi(T) x = this;
	if (rchild)//如果有右子节点，直接后继一定是右子节点最左边的那个
	{
		x = rchild;
		while (x->hasLchild())x = x->lchild;
		
	}
	else //如果没有右子节点，就沿着当前结点向上，在左子树中寻找后继结点
	{
		while (x->isRchild())
		{
			x = x->parent;
		}//如果这个结点是右边结点的话，他的父节点一定以及被遍历过了，就再往上找
		x = x->parent;
	}
	return x;
}
