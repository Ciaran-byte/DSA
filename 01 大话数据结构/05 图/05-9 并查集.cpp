#include<iostream>
using namespace std;

const int VexNum = 6;

void initialize(int* parent) //初始化parent集合，表示目前任何一个点都没有父节点(或者说根节点就是它自己)
{
	for (int i = 0; i < VexNum; i++)
	{
		parent[i] = -1;
	}
}

int find_root(int x, int* parent) //寻找一个点所属集合的根节点
{
	while (parent[x] != -1) //只要保存的值不是-1，说明这个结点不是根节点，上面还有父节点，那就继续往前搜
	{
		x = parent[x];
	}
	return x;
}


//如果两个点不属于同一个集合，就连接起来，返回1；否则返回0，说明构成了环
int union_vertex(int x, int y, int *parent) 
{
	int x_root = find_root(x, parent);
	int y_root = find_root(y, parent);
	if (x_root == y_root)
	{
		return 0;
	}
	else
	{
		parent[x_root] = y_root;
	}
}
int main()
{
	int parent[VexNum];
	initialize(parent);
	int edges[6][2] = 
	{ 
		{ 0,1 },
		{1,2},
		{1,3},
		{2,4},
		{3,4},
		{2,5} 
	}; //如图的六条边

	for (int i = 0; i < 6; i++)
	{
		int x = edges[i][0];
		int y = edges[i][1];
		if (union_vertex(x, y, parent) == 0)
		{
			cout << "有环" << endl;
			exit(0);
		}
	}
	cout << "没有环！" << endl;
	return 0;
}