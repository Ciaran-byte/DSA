#include<iostream>
using namespace std;


//�ؼ�˼·������������n-1��Բ����һ�����壬�Ȱ�����ķŵ�B��Ȼ������µĴ�A�ŵ�C��Ȼ���B�ķŵ�C
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

