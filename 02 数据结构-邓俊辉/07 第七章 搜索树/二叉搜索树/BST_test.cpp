#include<iostream>
#include "BST.h"
using namespace std;
struct out
{
	void operator()(int i)
	{
		cout << i << endl;
	}
};
int main()
{
	BST<int> tree;
	tree.insert(10);
	tree.insert(4);
	tree.insert(5);
	tree.insert(3);
	tree.insert(1);
	tree.insert(2);
	tree.insert(7);
	tree.insert(8);
	tree.insert(6);
	out ot;
	cout << endl;
	//tree.traverseIn_I3<out>(tree.root(), ot);
	cout << endl;
	tree.remove(4);
	tree.traverseIn_I1<out>(tree.root(), ot);
	//cout << (tree.root()->rchild)->succ()->isRchild() << endl;
	
	
	return 0;
}

