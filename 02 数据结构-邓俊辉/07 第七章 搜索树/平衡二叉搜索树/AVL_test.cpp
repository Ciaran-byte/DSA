#include<iostream>
#include "AVL.h"
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
	out ot;
	AVL<int> tree;
	
	for (int i = 0; i < 10; i++)
	{
		tree.insert(i);
	}
	
	
	
	tree.traverseIn_R(tree.root(), ot);
	cout << endl;
	for (int i = 0; i < 5; i++)
	{
		tree.remove(i);
	}
	tree.traverseIn_R(tree.root(), ot);

	return 0;
}


