#include<iostream>
using namespace std;

int countone(unsigned int n)
{
	int count = 0;
	while (n > 0)
	{
		count++;
		n &= n - 1; //去掉最右边的1
		//比如    xxx1000 是n ，n-1必定为xxx0111
		//n与n-1取位与运算，能够消掉最右边的1，并且不需要遍历所有位
		

		//复杂度正比与1的位数

	}
	return count;
}

int main()
{
	cout << countone(8) << endl;

	return 0;
}

