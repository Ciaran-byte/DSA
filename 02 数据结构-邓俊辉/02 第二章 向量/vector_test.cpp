#include<iostream>
#include<algorithm>
#include "vector.h"
using namespace std;

int main()
{
	//01  构造vector
	int a[5] = { 0,1,2,3,4 };
	vector<int> v(a,5);
	cout << "当前元素为" << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << v[i] << endl;
	}
	cout << endl;
	//02 置乱
	v.unsort();
	cout << "置乱后元素为" << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << v[i] << endl;
	}
	cout << endl;

	//03 静态查找(无序查找)
	cout << "元素2的下标为" << endl;
	cout << v.find(2) << endl;

	//04 插入操作
	cout << endl;
	cout << "将元素8插入到下标为5的位置，并打印" << endl;
	v.insert(8, 5);
	cout << v[5] << endl;
	//05 删除操作
	cout << "删除操作" << endl;
	v.remove(5);
	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << endl;
	}
	
	//06 有序向量去重
	cout << endl;
	cout << "有序向量去重" << endl;
	int b[5] = { 0,1,2,2,2 };
	vector<int> v2(b, 5);
	v2.unique();
	for (int i = 0; i < v2.size(); i++)
	{
		cout << v2[i] << endl;
	}
	
	//07 查找
	cout << endl;
	cout << "二分查找版本A" << endl;
	int s1[10] = { 0,2,3,4,5,6,7,8,11,14 };
	vector<int> v3(s1, 10);
	cout<<v3.binSearchA(9, 0, v3.size())<<endl;
	cout << endl;
	cout << "二分查找版本B" << endl;
	cout << v3.binSearchB(8, 0, v3.size()) << endl;

	cout << endl;
	cout << "二分查找版本C" << endl;
	cout << v3.binSearchC(8, 0, v3.size()) << endl;

	cout << endl;
	cout << "斐波那契查找" << endl;
	cout << v3.fibSearch(8, 0, v3.size()) << endl;

	cout << endl;
	cout << "插值查找" << endl;
	cout << v3.insertSearch(8, 0, v3.size()) << endl;

	cout << endl;
	cout << "查找" << endl;
	cout << v3.search(9) << endl;


	//08 排序
	cout << "冒泡排序" << endl;
	int s2[10] = { 1,6,4,2,7,9,0,3,5,6 };
	vector<int> v4(s2, 10);
	v4.bubbleSortB(0, v4.size());
	for (int i = 0; i < v4.size(); i++)
	{
		cout << v4[i] << endl;
	}

	cout << "归并排序" << endl;
	vector<int> v5(s2, 10);
	v5.mergeSort(0, v5.size());
	for (int i = 0; i < v5.size(); i++)
	{
		cout << v5[i] << endl;
	}
	
	cout << "选择排序" << endl;
	vector<int> v6(s2, 10);
	
	v6.selectSort(0, v6.size());
	for (int i = 0; i < v6.size(); i++)
	{
		cout << v6[i] << endl;
	}

	cout << "插入排序" << endl;
	vector<int> v7(s2, 10);

	v7.insertSort(0, v7.size());
	for (int i = 0; i < v7.size(); i++)
	{
		cout << v7[i] << endl;
	}
	return 0;
}