#include "Bitmap.h"
#include <iostream>
using namespace std;

int min(int a, int b) { return a < b ? a : b; }

void Eratosthenes(int n, char* file) //往file中写入含有n个素数的表，0和1都不是素数
{
	Bitmap B(n);
	B.set(0);
	B.set(1);
	for (int i = 2; i < n; i++)
	{
		if (!B.test(i))//第i个数字是素数，则从i*i开始，其倍数全部都是合数，标记为1
		{
			for (int j = min(i, 46340) * min(i, 46340); j < n; j += i)
			{
				B.set(j);
			}
		}

	}
	B.dump(file);
}
int main()
{
	char s[10] = "prim1.txt";
	Eratosthenes(1048576,s);


	return 0;
}