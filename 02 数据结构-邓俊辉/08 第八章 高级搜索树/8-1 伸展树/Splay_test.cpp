#include<iostream>
#include "Splay.h"
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
	Splay<int> tree; //ÉìÕ¹Ê÷
	for (int i = 0; i < 15; i++)
	{
		tree.insert(i);
	}
	tree.traversePre_R(tree.root(), ot);
	
	for (int i = 0; i < 5; i++)
	{
		tree.remove(i);
	}
	

	cout << endl;
	
	tree.traverseIn_R(tree.root(), ot);
	return 0;
}

