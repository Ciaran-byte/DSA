#include<iostream>
using namespace std;

int countone(unsigned int n)
{
	int count = 0;
	while (n > 0)
	{
		count++;
		n &= n - 1; //ȥ�����ұߵ�1
		//����    xxx1000 ��n ��n-1�ض�Ϊxxx0111
		//n��n-1ȡλ�����㣬�ܹ��������ұߵ�1�����Ҳ���Ҫ��������λ
		

		//���Ӷ�������1��λ��

	}
	return count;
}

int main()
{
	cout << countone(8) << endl;

	return 0;
}

