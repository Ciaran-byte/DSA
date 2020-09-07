#include<iostream>
#include "BTree.h"
using namespace std;
int main()
{
	BTree<int> tree;
	for (int i = 0; i < 10; i++)
	{
		tree.insert(i);
	}
	for (int i = 0; i < 15; i++)
	{
		tree.remove(i);
	}

	
	
}