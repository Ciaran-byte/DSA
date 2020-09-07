#include<iostream>
using namespace std;

void swap(int* a, int n1, int n2)
{
	int temp = a[n1];
	a[n1] = a[n2];
	a[n2] = temp;
}
void bubble_sort(int* a, int n)
{
	bool sort = false;

	for (int i = 0; i < n - 1 && !sort; i++)
	{
		sort = true;
		for (int j = 0; j < n - 1 - i; j++)
		{
			if (a[j] > a[j + 1])
			{
				sort = false;
				swap(a, j, j + 1);
			}
		}
	}

}

int main()
{
	int a[10] = { 1,3,5,7,9,2,4,6,8,10 };
	bubble_sort(a, 10);
	for (int i = 0; i < 10; i++)
	{
		cout << a[i] << endl;
	}

	return 0;
}


