#include<iostream>
#include<vector>
using namespace std;

const int MaxSize = 100;

int  Fibonacci_Search(int* a, int len, int Key)
{
	//01 ����쳲���������
	static vector<int> Fibnocci = { 1,1 };
	while (len >Fibnocci[Fibnocci.size() - 1]) //���쳲��������в������ˣ�Ҫ��
	{
		Fibnocci.push_back(Fibnocci[Fibnocci.size() - 1] + Fibnocci[Fibnocci.size() - 2]);
	}
	
	/*auto it = Fibnocci.begin();
	for (; it != Fibnocci.end(); it++)
	{
		cout << *it << endl;
	}*/

	int k = 0;
	//02 Ѱ�����г�����쳲��������е�ʲô��Χ
	while (len > Fibnocci[k] - 1)  //����������Ϊ���ڽ���쳲�����������ô��
	{
		k++;
	}


	//03 ��Щ�ط�û��Ԫ�أ������һ��Ԫ��������ʹ���������䵽Fibnocci[k]-1�ĳ���
	for (int i = len; i < Fibnocci[k] - 1; i++) //����ΪFibnocci[k]-1�� �±��0-Fibnocci[k]-2;
	{
		a[i] = a[len - 1];
	}

	int low = 0;
	int high = Fibnocci[k] - 2;

	//04 ��ʼ쳲��������ң�ǰһ�볤Fibnocci[k-1]-1�� ��һ�볤Fibnocci[k-2]-1

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
		
			if (mid < len) //�������mid�ȳ���С��˵������
			{
				return mid;
			}
			else  //������ȴ��ڵ���len��˵�����������У��������һ������
			{
				return len-1;
			}

		}

	}
	return 0;
}

int main()
{
	int a[MaxSize] = { 0,1,16,24,35,47,59,62,73,88,99 };//����11
	cout << Fibonacci_Search(a, 11, 16) << endl;

	
}

