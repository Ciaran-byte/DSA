#include<iostream>
using namespace std;

int Binary_Search(int* a, int len, int Key)
{
	int low = 0;
	int high = len - 1;

	int i = 0;

	while (low <= high)
	{
		
		i++;
		cout << i << endl;
		int mid = low + ((Key - a[low]) / (a[high] - a[low])) * (high - low);
		if (Key < a[mid])
		{
			high = mid - 1;
		}
		else if (Key > a[mid])
		{
			low = mid + 1;
		}
		else
		{
			return mid;
		}

	}
	return 0;
}
int main()
{
	int a[11] = { 0,1,16,24,35,47,59,62,73,88,99 };
	int n = Binary_Search(a, 11, 16);
	cout << endl;
	cout << n << endl;


	return 0;
}

