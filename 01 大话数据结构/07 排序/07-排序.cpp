#include<iostream>
using namespace std;

//--------------------------------------------------线性表定义-----------------------------------------
const int MaxSize = 10;

typedef struct SqList
{
	int data[MaxSize+1];//
	int length;

}SqList;

void swap(SqList* l, int i, int j)
{
	int temp;
	temp = l->data[i];
	l->data[i] = l->data[j];
	l->data[j] = temp;

}
//--------------------------------------------------线性表定义结束--------------------------------------------

//---------------------------------------------------01 冒泡排序----------------------------------------------
void BubbleSort0(SqList* l)
{
	for (int i = 1; i < l->length; i++)
	{
		for (int j = i + 1; j < l->length; j++)
		{
			if (l->data[i] > l->data[j])
			{
				swap(l, i, j);
			}
		}
	}
}

void BubbleSort1(SqList* l)
{
	for (int i = 1; i < l->length; i++)//n个数字，只需要比较n-1趟就好
	{
		for (int j = 1; j < l->length- i; j++)
		{
			if (l->data[j] > l->data[j + 1])
			{
				swap(l, j, j + 1);
			}
		}
	}
}


void BubbleSort2(SqList* l) //优化，如果冒泡排序某一趟没发生交换，说明以及排序结束了，所以多了一个flag标记
{
	bool flag = true;
	for (int i = 1; i < l->length&&flag; i++)//n个数字，只需要比较n-1趟就好
	{
		 flag = false;
		for (int j = 1; j < l->length  - i; j++)
		{
			if (l->data[j] > l->data[j + 1])
			{
				
				swap(l, j, j + 1);
				flag = true;
			}
		}
	}
}


//---------------------------------------------------01 冒泡排序结束----------------------------------------------
//---------------------------------------------------02 直接选择排序----------------------------------------------

void SlectSort(SqList* l)
{
	for (int i = 0; i < l->length - 1; i++) //寻找下标从i到length-1的数列中的最小的那个，交换
	{
		int min = i;
		for (int j = i + 1; j < l->length; j++)
		{
			if (l->data[min] > l->data[j])
			{
				min = j;
			}
		}
		if (min != i)
		{
			swap(l, min, i);
		}
	}
}
//---------------------------------------------------02 直接选择排序结束----------------------------------------------

//---------------------------------------------------03 直接插入排序----------------------------------------------

void InsertSort1(SqList* l) //从小往大排序
{
	for (int i = 2; i < l->length; i++) //从头开始往后比较，如果有逆序的，就插入到前面排序完成的位置
	{
		if (l->data[i] < l->data[i - 1]) //如果逆序
		{
			l->data[0] = l->data[i];  //保存逆序元素
			int j = i - 1;
			for (; l->data[0] < l->data[j]; j--)  //从逆序元素的前一个开始往前跟逆序元素比较，如果逆序元素比这个元素小，再往前找，一直找到它要插入的位置
			{
				l->data[j + 1] = l->data[j]; 
			}
			l->data[j + 1] = l->data[0]; //如果找到插入元素的位置了，就把元素从0位置找过来
		}
	}
}

//---------------------------------------------------03 直接插入排序结束----------------------------------------------
//---------------------------------------------------04 折半插入排序结束----------------------------------------------

void InsertSort2(SqList* l) //从小往大排序
{
	for (int i = 2; i < l->length; i++) //从头开始往后比较，如果有逆序的，就插入到前面排序完成的位置
	{
		if (l->data[i] < l->data[i - 1]) //如果逆序
		{
			l->data[0] = l->data[i];  //保存逆序元素
			int low = 1;
			int high = i - 1;
			int mid;

			
			while (low <= high)
			{
				 mid = (low + high) / 2;
				if (l->data[mid] > l->data[0])
				{
					high = mid - 1;
					
				}
				else
				{
					low = mid + 1;
				}
		
			}

			//high+1位置就是插入点
			for (int m = i-1;m>high;m--)
			{
				l->data[m + 1] = l->data[m];
			}
			l->data[high] = l->data[0];


		}
	}
}
//---------------------------------------------------04 折半插入排序结束----------------------------------------------
//---------------------------------------------------05 希尔排序--------------------------------------------------
void ShellSort(SqList* l)
{
	int increment = l->length;
	do
	{
		increment = increment / 3 + 1;
		for (int i = increment + 1; i < l->length; i++)
		{
			if (l->data[i] < l->data[i - increment])
			{
				l->data[0] = l->data[i];

				int j;
				for (j = i - increment; j > 0 && l->data[j] > l->data[0]; j -= increment)
				{
					l->data[j + increment] = l->data[j];
				}
				l->data[j + increment] = l->data[0];
			}
		}
	} 
	while (increment > 1);
}

//---------------------------------------------------05 希尔排序结束----------------------------------------------

//---------------------------------------------------06 快速排序----------------------------------------------

int Partition(SqList* l, int low, int high);
void QSort(SqList* l, int low, int high);
//快速排序的思路就是，随便选择一个点作为中心点，比这个点小的放置在表点左侧，大的放置在表右侧。不断缩减表的大小，
//当每个子表只有一个元素的时候，就完成了排序
void QuickSort(SqList* l) //排序函数
{
	QSort(l, 1, l->length-1);
}

void QSort(SqList* l, int low, int high) //排序函数的实现
{
	int pivot; //中点坐标
	if(low < high)
	{
		pivot = Partition(l, low, high);

		QSort(l, low, pivot - 1);
		QSort(l, pivot + 1, high);
	}
}

int Partition(SqList* l, int low, int high) //获取中间点坐标的函数
{
	l->data[0] = l->data[low];
	while (low < high)
	{
		while (low<high && l->data[high]>l->data[0])
		{
			high--;
		}
		l->data[low] = l->data[high];
		
		while (low < high && l->data[low] < l->data[0])
		{
			low++;
		}
		l->data[high] = l->data[low];
	}
	l->data[low] = l->data[0];
	return low;
}

//---------------------------------------------------06 快速排序结束----------------------------------------------

//---------------------------------------------------07 堆排序----------------------------------------------

//基于大根堆的堆调整
void HeapAdjust(SqList* l, int s, int m)
{
	int temp = l->data[s]; //如果下层有比堆顶大的元素，就换上来
	for (int j = s * 2; j <=m; j *= 2)
	{
		if (j<m&&l->data[j] < l->data[j + 1])
		{
			j++;  //如果兄弟结点更大，就用顶元素跟兄弟结点换,去两个子节点中的最大值
		}

		if (temp >= l->data[j])
		{
			break;//如果根节点比两个子节点都大，那还换个锤子
		}

		
		l->data[s] = l->data[j];
		
		s = j;
	
	}

	l->data[s] = temp;
}

//堆排序
void HeapSort(SqList* l)
{
	//从最底下的根节点开始，每个结点做一次大根堆调整，调整到堆顶的时候，就完成的大根堆的创建
	for (int i = (l->length-1) / 2; i >= 1; i--)
	{
		HeapAdjust(l, i, l->length-1);
	}

	//输出序列
	for (int i=l->length-1;i>1;i--)
	{
		swap(l, 1, i); //把最大值排到最后一个，最后一个数放到最前面，继续做大根推堆调整，找到次大值
		HeapAdjust(l, 1, i-1);
	}
}
//---------------------------------------------------07 堆排序结束----------------------------------------------

//---------------------------------------------------08 并归排序----------------------------------------------

void Merge(int arr[], int L, int M, int R) //用来把已经有规律的两半进行合并
{
	//L     M     R
	//x x x x x x x
	//left[l->M-1]
	//right[M->R]
	 int LeftSize = M - L; //左数组长度
	 int RightSize = R - M+1; //右数组长度
	 int left[MaxSize]; //保存左边的数字
	 int right[MaxSize];//保存右边的数字

	 //01 拆分
	 for (int i = L; i < L + LeftSize; i++)
	 {
		 left[i - L] = arr[i];
	 }

	 for (int i = M; i < M + RightSize; i++)
	 {
		 right[i - M] = arr[i];
	 }

	//02 归并排序
	 int i = 0;
	 int j = 0;
	 int k = L;

	 while (i < LeftSize && j < RightSize)
	 {
		 if (left[i] <= right[j])
		 {
			 arr[k] = left[i];
			 i++;
			 k++;
		 }
		 else
		 {
			 arr[k] = right[j];
			 j++;
			 k++;
		 }
	 }

	 while (i < LeftSize)
	 {
		 arr[k] = left[i];
		 i++;
		 k++;
	 }

	 while (j < RightSize)
	 {
		 arr[k] = right[j];
		 j++;
		 k++;
	 }

}

//并归排序，将所有的数组拆分成单个元素，从单个元素开始并归排序
void MergeSort (int arr[], int L, int R)
{
	if (L == R)
	{
		return;
	}
	else
	{
		int M = (L + R) / 2;
		MergeSort(arr, L, M);
		MergeSort(arr, M + 1, R);
		Merge(arr, L, M + 1, R);
	}
}

////---------------------------------------------------08 并归排序结束----------------------------------------------

int main()
{
	SqList s;
	s.length = 11;
	s.data[0] = 0;
	s.data[1] = 5;
	s.data[2] = 2;
	s.data[3] = 4;
	s.data[4] = 7;
	s.data[5] = 11;
	s.data[6] = 3;
	s.data[7] = 8;
	s.data[8] = 40;
	s.data[9] = 1;
	s.data[10] = 6;

	//InsertSort1(&s);
	//InsertSort2(&s);
	//ShellSort(&s);
	//QuickSort(&s);
	//HeapSort(&s);
	//for (int i = 1; i < s.length; i++)
	//{
	//	cout << s.data[i] << endl;
	//}
	//cout << endl;

	int arr[10] = { 1,3,7,8,3,4,9,11,2,5 };
	MergeSort(arr, 0, 9);
	for (int i = 0; i < 10; i++)
	{
		cout << arr[i] << endl;
	}
	return 0;
}




