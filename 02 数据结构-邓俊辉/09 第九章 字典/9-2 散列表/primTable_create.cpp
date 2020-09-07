#include "Bitmap.h"
#include <iostream>
using namespace std;

int min(int a, int b) { return a < b ? a : b; }

void Eratosthenes(int n, char* file) //��file��д�뺬��n�������ı�0��1����������
{
	Bitmap B(n);
	B.set(0);
	B.set(1);
	for (int i = 2; i < n; i++)
	{
		if (!B.test(i))//��i�����������������i*i��ʼ���䱶��ȫ�����Ǻ��������Ϊ1
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