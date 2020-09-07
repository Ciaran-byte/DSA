#include "BinTree.h"
#include<iostream>
#include<ctime>
using namespace std;

template<typename T>
class seeOut
{
public:
	void operator()(const T& elem) { cout << elem << endl; }
};
int main()
{
	//01 根节点创建
	cout << "创建根结点" << endl;
	BinTree<int> S;
	S.insertAsRoot(0);
	cout<<S.root()->data<<endl;
	//02 子节点创建
	cout << endl;
	cout << "创建子节点" << endl;
	S.insertAsLC(S.root(), 2);
	S.insertAsRC(S.root(), 5);
	cout << S.root()->lchild->data << endl;
	cout << S.root()->rchild->data << endl;

	//03 删除结点
	cout << endl;
	cout << "删除结点" << endl;
	S.remove(S.root()->lchild);
	cout << !(S.root()->lchild) << endl;

	//04 延伸树
	cout << endl;
	cout << "延伸树" << endl;
	BinTree<int> Q;
	Q.insertAsRoot(7);
	Q.insertAsLC(S.root(), 71);
	Q.insertAsRC(S.root(), 56);
	BinTree<int>* Pointer = &Q;
	S.attachAsLC(S.root(), Pointer);
	cout << S.root()->lchild->data << endl;

	//05 递归遍历
	cout << endl;
	cout << "递归遍历：" << endl;
	seeOut<int> c;
	cout << "前" << endl;
	S.traversePre_R<seeOut<int>>(S.root(), c);
	cout << "中" << endl;
	S.traverseIn_I1<seeOut<int>>(S.root(), c);
	cout << "后" << endl;
	S.traversePost_R<seeOut<int>>(S.root(), c);

	//06 迭代遍历
	
	return 0;
}

