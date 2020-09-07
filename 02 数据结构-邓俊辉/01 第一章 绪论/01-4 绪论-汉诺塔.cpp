#include<iostream>
using namespace std;


//关键思路就是想象上面n-1个圆盘是一个整体，先把上面的放到B，然后最底下的从A放到C，然后把B的放到C
void hanoi(int n,char A,char B,char C)
{
	if (n == 1)
	{
		cout << A << "-" << C << endl;
	}
	else
	{
		hanoi(n - 1, A, C, B);
		cout << A << "-" << C << endl;
		hanoi(n - 1, B, A, C);
	}
}
int main()
{
	hanoi(15, 'A', 'B', 'C');

	return 0;
}

