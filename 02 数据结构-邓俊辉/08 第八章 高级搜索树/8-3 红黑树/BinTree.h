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

	//------------------------------------------------结构域-------------------------------------
	BinNodePosi(T) _root; //根节点
	int _size;  //树的规模，也就是包括自己以下全部结点数量
	//-------------------------------------------结构域定义结束--------------------------------------

	//--------------------------------------工具函数---------------------------------------
	virtual int updateHeight(BinNodePosi(T) x); //更新结点x的高度
	void updateHeightAbove(BinNodePosi(T) x); //更新全部结点的高度
	T max(const T& lhs, const T& rhs) { return lhs >= rhs ? lhs : rhs; }
	bool isRoot(BinNodePosi(T) x)const; //判断结点是否为根节点
	bool isLChild(BinNodePosi(T) x) const;  //判断结点是否为左子结点
	bool isRChild(BinNodePosi(T) x) const; //判断结点是否为右子节点
	BinNodePosi(T)& FromParentTo(BinNodePosi(T)& x); //来自父节点的引用
	
	//----------------------------------工具函数定义结束----------------------------------


public :
	//------------------------------------构造和控制函数------------------------------
	BinTree():_size(0),_root(nullptr){}
	~BinTree() { if (_size > 0)remove(_root); }
	//---------------------------------构造和控制函数结束--------------------------------

	//-------------------------------------功能函数---------------------------------
	BinNodePosi(T)& root() { return _root; }
	int size()const { return _size; }
	bool empty() const { return !_root; }
	BinNodePosi(T) insertAsRoot(const T& e); //插入根节点
	BinNodePosi(T) insertAsLC(BinNodePosi(T) x,const T& e); //为某个结点插入左孩子
	BinNodePosi(T) insertAsRC(BinNodePosi(T) x,const T& e); //为某个结点插入右孩子
	BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T>*& S); //将S树插入x结点作为其左孩子
	BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T>*& S); //将S树插入x结点作为其右孩子
	int removeAt(BinNodePosi(T) x); //删除某个结点及其所有子节点。返回删除结点数量
	int remove(BinNodePosi(T) x);//删除某个结点及其所有子节点，并且更新所有结点的高度，返回删除结点数量
	BinTree<T>* secede(BinNodePosi(T) x); //把某个结点及其以下部分作为单独的树返回
	template<typename VST> 
	void traversePre_R(BinNodePosi(T)x, VST& visit); //前序遍历-递归版本
	template<typename VST>
	void traverseIn_R(BinNodePosi(T)x, VST& visit); //中序遍历-递归版本
	template<typename VST>
	void traversePost_R(BinNodePosi(T)x, VST& visit); //后续遍历-递归版本
	template<typename VST>
	void traversePre_I1(BinNodePosi(T)x, VST& visit); //前序遍历--迭代版本1
	template<typename VST>
	void traversePre_I2(BinNodePosi(T)x, VST& visit); //前序遍历--迭代版本2
	template<typename VST>
	void visitAlongLeftBrach(BinNodePosi(T)x, stack<BinNodePosi(T)>& S); //前序遍历-迭代版本2辅助函数
	template<typename VST>
	void traverseIn_I1(BinNodePosi(T)x, VST& visit); //中序遍历--迭代版本1
	
	void goAlongLeftBranch(BinNodePosi(T)x, stack<BinNodePosi(T)>& S); //中序遍历-迭代版本1辅助函数
	template<typename VST>
	void traverseIn_I2(BinNodePosi(T) x, VST& visit); //中序遍历-迭代版本2
	template<typename VST>
	void traverseIn_I3(BinNodePosi(T)x, VST& visit); //中序遍历-迭代版本3
	template<typename VST>
	void traversePost_I(BinNodePosi(T)x, VST& visit); //后序遍历--迭代版本
	
	void gotoHLVFL(stack < BinNodePosi(T)> & S); //后序遍历--迭代版本辅助函数，寻找最高左侧可见叶节点
	template<typename VST>
	void travLevel(VST& visit); //层序遍历--迭代版本
	
	//------------------------------------功能函数结束----------------------------------


};

//-----------------------------------------工具函数------------------------------------------
template<typename T>
int BinTree<T>::updateHeight(BinNodePosi(T)x) //更新结点高度
{
	
	return x->height=1 + max(Stature(x->lchild), Stature(x->rchild));
}

template<typename T>
void BinTree<T>::updateHeightAbove(BinNodePosi(T) x) //顺着子结点更新全部结点的高度
{
	
	while (x) {  updateHeight(x); x = x->parent; }
	
}

template<typename T>
bool BinTree<T>::isRoot(BinNodePosi(T) x)const //是否为根节点
{
	return !(x->parent);
}

template<typename T>
bool BinTree<T>::isLChild(BinNodePosi(T) x) const //判断是否为左孩子结点
{

	return !isRoot(x) && (x == x->parent->lchild);
}

template<typename T>
bool BinTree<T>::isRChild(BinNodePosi(T) x) const
{
	return !isRoot(x) && (x == x->parent->rchild);
}

template<typename T>
BinNodePosi(T)& BinTree<T>::FromParentTo(BinNodePosi(T) &x) //返回来自父节点的引用
{
	return isRoot(x) ? _root : isLChild(x) ? x->parent->lchild : x->parent->rchild;
}
//--------------------------------------功能函数----------------------------------------
template<typename T>
BinNodePosi(T) BinTree<T>::insertAsRoot(const T& e) //插入根节点
{
	_size = 1;
	return _root = new BinNode<T>(e);
	
}

template<typename T>
BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x,const T& e) //插入左孩子结点
{
	_size++;
	x->insertAsLC(e);
	updateHeightAbove(x);
	return x->lchild;
}

template<typename T>
BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, const T& e)//插入右孩子结点
{
	_size++;
	x->insertAsRC(e);
	updateHeightAbove(x);
	return x->rchild;
}

template<typename T>
BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x, BinTree<T>* &S) //接入一颗树作为左孩子
{
	//如果不是空树
	if (x->lchild = S->_root) x->lchild->parent = x;
	_size += S->_size; //更新树的规模
	updateHeightAbove(x); //更新当前结点以上的树高度

	//清空原树
	S->_root = nullptr;
	S->_size = 0;
	S = nullptr;

	return x;

}

template<typename T>
BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x, BinTree<T>*& S) //接入一颗树作为左孩子
{
	//如果不是空树
	if (x->rchild = S->_root) x->rchild->parent = x;
	_size += S->_size; //更新树的规模
	updateHeightAbove(x); //更新当前结点以上的树高度

	//清空原树
	S->_root = nullptr;
	S->_size = 0;
	S = nullptr;

	return x;

}

template<typename T>
int BinTree<T>::removeAt(BinNodePosi(T) x) //删除结点及其以下的结点，并返回删除结点的数量
{
	if (!x) return 0;
	int n = 1+removeAt(x->lchild) + removeAt(x->rchild);
	delete x;
	return n;
}

template<typename T>
int BinTree<T>::remove(BinNodePosi(T) x) //删除结点及其以下的结点，更新高度，返回删除结点的数量
{
	
	//切断结点与父节点的联系
	FromParentTo(x) = nullptr;
	
	//更新父节点以上的结点的高度
	updateHeightAbove(x->parent);
	
	//删除结点及其以下的结点，并返回删除个数
	int n = removeAt(x); 

	//更新结点数量
	_size -= n;
	
	//返回删除结点数
	return n;
}

template<typename T>
BinTree<T>* BinTree<T>::secede(BinNodePosi(T) x) //截取子树
{
	//删除结点与父节点之间的连续
	FromParentTo(x) = nullptr;

	//更新父节点及其以上的高度
	updateHeightAbove(x->parent);
	
	//更新父树的节点数
	int size = x->size();
	this->_size -= size;

	//子树独立
	
	BinTree<T>* tree = new BinTree<T>();
	tree->_root = x;
	x->parent = nullptr;
	tree->_size = size;
	return tree;



}


template<typename T> template<typename VST>
void BinTree<T>::traversePre_R(BinNodePosi(T)x, VST& visit) //前序遍历--递归版
{
	if (!x)return;//递归基
	visit(x->data); //data->lchlid->rchild
	traversePre_R(x->lchild, visit);
	traversePre_R(x->rchild, visit);
}
template<typename T> template<typename VST>
void BinTree<T>::traversePost_R(BinNodePosi(T)x, VST& visit) //后序遍历--递归版
{
	if (!x)return;//递归基
	
	traversePost_R(x->lchild, visit);//lchild->rchild->data
	traversePost_R(x->rchild, visit);
	visit(x->data);
}
template<typename T> template<typename VST>
void BinTree<T>::traverseIn_R(BinNodePosi(T)x, VST& visit) //中序遍历--递归版
{
	if (!x)return;//递归基

	traverseIn_R(x->lchild, visit);//lchild->data->rchild
	visit(x->data);
	traverseIn_R(x->rchild, visit);
	
}

template<typename T> template<typename VST>
void BinTree<T>::traversePre_I1(BinNodePosi(T)x, VST& visit) //前序遍历--迭代版1
{
	stack<BinNodePosi(T)> S; //临时栈
	if(x)S.push(x); //x入栈
	while (!S.empty()) //通过栈的方式模拟尾递归，可以把递归变成迭代，但是不具有对其他遍历通用的表现形式
	{
		 x = S.pop();
		visit(x->data);
		if (x->rchild) { S.push(x->rchild); } //因为先遍历左子树，所以应该左子树后进栈，先出栈
		if (x->lchild) { S.push(x->lchild); }
		
	}
}
template<typename T> template<typename VST>
void BinTree<T>::traversePre_I2(BinNodePosi(T)x, VST& visit) //前序遍历--迭代版2
{
	//迭代版本2更加具有通用的表现形式
	//因为前序遍历更像是顺序遍历左子树，然后把右子树逆序遍历这种样子
	stack<BinNodePosi(T)> S;
	
	while (true) //如果栈不是空的就继续
	{
		
		visitAlongLeftBrach(x, S); //遍历到这个结点的最左边一个结点，在这个过程中逆序保存右子树。然后从最后一个右子树再遍历
		if (S.empty())break; //如果栈空了，说明遍历完了
		x = S.pop();
	}

}
template<typename T> template<typename VST>
void BinTree<T>::visitAlongLeftBrach(BinNodePosi(T)x, stack<BinNodePosi(T)>& S) //前序遍历迭代版本2辅助函数
{
	while (x)
	{
		visit(x->data);
		S.push(x->rchild);
		x = x->lchild;
	}
}
template<typename T>
void BinTree<T>::goAlongLeftBranch(BinNodePosi(T)x, stack<BinNodePosi(T)>& S) //中序遍历-迭代版本1辅助函数
{
	//中序遍历是先沿左子树走到底，逆序保存左子树，然后再访问最末尾的左子树，如果其有右子树，加入栈中，否则上一个左子树出栈
	while (x)
	{
		S.push(x);
		x = x->lchild;
	}
}

template<typename T> template<typename VST>
void BinTree<T>::traverseIn_I1(BinNodePosi(T)x, VST& visit) //中序遍历--迭代版1
{
	stack<BinNodePosi(T)> S; //辅助栈
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
void BinTree<T>::traverseIn_I2(BinNodePosi(T)x, VST& visit) //中序遍历--迭代版2
{
	//这个版本跟迭代版本1是等效的
	stack<BinNodePosi(T)> S; //辅助栈
	while (true)
	{
		if (x)//如果x不是空节点
		{
			S.push(x);
			x = x->lchild;
		}
		else if(!S.empty())//如果x是空节点
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
void BinTree<T>::traverseIn_I3(BinNodePosi(T)x, VST& visit) //中序遍历--迭代版3
{
	bool backtrack = false; //回溯标志，当访问结点的左右子树都空的时候，回溯到上一个分叉位置
	while (true)
	{
		if (!backtrack && x->hasLchild()) //如果没有发生回溯，并且左节点不为空
		{
			x = x->lchild; //x一直到底
		}
		else //如果发生了回溯说明左树都访问过了，或者左节点为空，说明没必要访问左子树
		{
			visit(x->data); //访问当前结点
			if (x->hasRchild()) //如果右边子树不为空,应该往右树方向继续遍历
			{
				x = x->rchild;
				backtrack = false;
			}
			else //左右子树均空，该找下一个后继结点了
			{
				if (!(x = x->succ()))break; //没有后继的就是遍历完了
				backtrack = true;//回溯标志设置
			}
		}
	}
}
template<typename T> 
void BinTree<T>::gotoHLVFL(stack<BinNodePosi(T)> & S) //后序遍历--迭代版辅助函数
{
	while (BinNodePosi(T) x = S.top())
	{
		if (x->lchild) //如果有左孩子结点
		{
			if (x->rchild)//如果有右孩子结点，右孩子先入栈
			{
				S.push(x->rchild);
			}
			S.push(x->lchild);
		}
		else //如果没有左孩子结点
		{
			S.push(x->rchild); //右边结点入栈
		}
		S.pop(); //栈顶是个空栈，删去
	}
}
template<typename T> template<typename VST>
void BinTree<T>::traversePost_I(BinNodePosi(T)x, VST& visit) //后序遍历--迭代版
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
void BinTree<T>::travLevel(VST& visit)//层序遍历--迭代版本
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