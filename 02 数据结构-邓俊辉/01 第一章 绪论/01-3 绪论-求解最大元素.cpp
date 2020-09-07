#include<iostream>
using namespace std;

int max(int a, int b)
{
	return a > b ? a : b;
}


//µü´ú°æ±¾
int maxI(int*a,int n)
{
	int m = a[0];
	for (int i = 1; i < n; i++)
	{
		m = max(m, a[i]);
	}
	return m;

}

int maxR(int* a, int n)
{
	if (n <2)
	{
		return a[n - 1];
	}
	else
	{
		return max(maxR(a, n - 1), a[n - 1]);

	}
	
	
}

int main()
{
	int a[10] = {100, 9,3,4,55,2,66,77,22,87};

	cout << maxI(a, 10) << endl;
	cout << maxR(a, 10) << endl;
	return 0;
}

