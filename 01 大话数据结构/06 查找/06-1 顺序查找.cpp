#include<iostream>
using namespace std;
//01 顺序查找

int Sequential_Search(int* a, int n, int Key)
{
	int i;
	for (int i = 1; i <= n; i++)
	{
		if (a[i] == Key)
		{
			return i;
		}
	}
	return 0;
}

//02 改进的顺序查找
int Sequential_Search2(int* a, int n, int Key)
{
	a[0] = Key;
	int i = n;
	while (a[i] != Key)
	{
		i--;
	}
	return i;
}
int main()
{
	int a[10];
	for (int i = 0; i < 10; i++)
	{
		a[i] = i;
	}

	cout << Sequential_Search(a, 9, 5) << endl;

	cout << Sequential_Search2(a, 9, 6) << endl;




	return 0;
}

