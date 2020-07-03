#include<iostream>
#include<vector>
using namespace std;

const int MaxSize = 100;

int  Fibonacci_Search(int* a, int len, int Key)
{
	//01 生成斐波那契数列
	static vector<int> Fibnocci = { 1,1 };
	while (len >Fibnocci[Fibnocci.size() - 1]) //如果斐波那契数列不够长了，要补
	{
		Fibnocci.push_back(Fibnocci[Fibnocci.size() - 1] + Fibnocci[Fibnocci.size() - 2]);
	}
	
	/*auto it = Fibnocci.begin();
	for (; it != Fibnocci.end(); it++)
	{
		cout << *it << endl;
	}*/

	int k = 0;
	//02 寻找数列长度在斐波那契数列的什么范围
	while (len > Fibnocci[k] - 1)  //把数列扩大为最邻近的斐波那契数列那么大
	{
		k++;
	}


	//03 有些地方没有元素，用最后一个元素填满，使得数列扩充到Fibnocci[k]-1的长度
	for (int i = len; i < Fibnocci[k] - 1; i++) //长度为Fibnocci[k]-1， 下标从0-Fibnocci[k]-2;
	{
		a[i] = a[len - 1];
	}

	int low = 0;
	int high = Fibnocci[k] - 2;

	//04 开始斐波那契查找，前一半长Fibnocci[k-1]-1， 后一半长Fibnocci[k-2]-1

	while (low <= high)
	{
		
		int mid = low + Fibnocci[k - 1] - 1;
	
		if (Key < a[mid])
		{
			high = mid - 1;
			k = k - 1;
		}
		else if (Key >a[mid])
		{
			low = mid + 1;
			k = k - 2;
		}
		else
		{
		
			if (mid < len) //如果返回mid比长度小，说明就是
			{
				return mid;
			}
			else  //如果长度大于等于len，说明是扩充数列，返回最后一个即可
			{
				return len-1;
			}

		}

	}
	return 0;
}

int main()
{
	int a[MaxSize] = { 0,1,16,24,35,47,59,62,73,88,99 };//长度11
	cout << Fibonacci_Search(a, 11, 16) << endl;

	
}

