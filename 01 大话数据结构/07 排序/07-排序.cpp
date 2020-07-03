#include<iostream>
using namespace std;

//--------------------------------------------------���Ա���-----------------------------------------
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
//--------------------------------------------------���Ա������--------------------------------------------

//---------------------------------------------------01 ð������----------------------------------------------
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
	for (int i = 1; i < l->length; i++)//n�����֣�ֻ��Ҫ�Ƚ�n-1�˾ͺ�
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


void BubbleSort2(SqList* l) //�Ż������ð������ĳһ��û����������˵���Լ���������ˣ����Զ���һ��flag���
{
	bool flag = true;
	for (int i = 1; i < l->length&&flag; i++)//n�����֣�ֻ��Ҫ�Ƚ�n-1�˾ͺ�
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


//---------------------------------------------------01 ð���������----------------------------------------------
//---------------------------------------------------02 ֱ��ѡ������----------------------------------------------

void SlectSort(SqList* l)
{
	for (int i = 0; i < l->length - 1; i++) //Ѱ���±��i��length-1�������е���С���Ǹ�������
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
//---------------------------------------------------02 ֱ��ѡ���������----------------------------------------------

//---------------------------------------------------03 ֱ�Ӳ�������----------------------------------------------

void InsertSort1(SqList* l) //��С��������
{
	for (int i = 2; i < l->length; i++) //��ͷ��ʼ����Ƚϣ����������ģ��Ͳ��뵽ǰ��������ɵ�λ��
	{
		if (l->data[i] < l->data[i - 1]) //�������
		{
			l->data[0] = l->data[i];  //��������Ԫ��
			int j = i - 1;
			for (; l->data[0] < l->data[j]; j--)  //������Ԫ�ص�ǰһ����ʼ��ǰ������Ԫ�رȽϣ��������Ԫ�ر����Ԫ��С������ǰ�ң�һֱ�ҵ���Ҫ�����λ��
			{
				l->data[j + 1] = l->data[j]; 
			}
			l->data[j + 1] = l->data[0]; //����ҵ�����Ԫ�ص�λ���ˣ��Ͱ�Ԫ�ش�0λ���ҹ���
		}
	}
}

//---------------------------------------------------03 ֱ�Ӳ����������----------------------------------------------
//---------------------------------------------------04 �۰�����������----------------------------------------------

void InsertSort2(SqList* l) //��С��������
{
	for (int i = 2; i < l->length; i++) //��ͷ��ʼ����Ƚϣ����������ģ��Ͳ��뵽ǰ��������ɵ�λ��
	{
		if (l->data[i] < l->data[i - 1]) //�������
		{
			l->data[0] = l->data[i];  //��������Ԫ��
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

			//high+1λ�þ��ǲ����
			for (int m = i-1;m>high;m--)
			{
				l->data[m + 1] = l->data[m];
			}
			l->data[high] = l->data[0];


		}
	}
}
//---------------------------------------------------04 �۰�����������----------------------------------------------
//---------------------------------------------------05 ϣ������--------------------------------------------------
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

//---------------------------------------------------05 ϣ���������----------------------------------------------

//---------------------------------------------------06 ��������----------------------------------------------

int Partition(SqList* l, int low, int high);
void QSort(SqList* l, int low, int high);
//���������˼·���ǣ����ѡ��һ������Ϊ���ĵ㣬�������С�ķ����ڱ����࣬��ķ����ڱ��Ҳࡣ����������Ĵ�С��
//��ÿ���ӱ�ֻ��һ��Ԫ�ص�ʱ�򣬾����������
void QuickSort(SqList* l) //������
{
	QSort(l, 1, l->length-1);
}

void QSort(SqList* l, int low, int high) //��������ʵ��
{
	int pivot; //�е�����
	if(low < high)
	{
		pivot = Partition(l, low, high);

		QSort(l, low, pivot - 1);
		QSort(l, pivot + 1, high);
	}
}

int Partition(SqList* l, int low, int high) //��ȡ�м������ĺ���
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

//---------------------------------------------------06 �����������----------------------------------------------

//---------------------------------------------------07 ������----------------------------------------------

//���ڴ���ѵĶѵ���
void HeapAdjust(SqList* l, int s, int m)
{
	int temp = l->data[s]; //����²��бȶѶ����Ԫ�أ��ͻ�����
	for (int j = s * 2; j <=m; j *= 2)
	{
		if (j<m&&l->data[j] < l->data[j + 1])
		{
			j++;  //����ֵܽ����󣬾��ö�Ԫ�ظ��ֵܽ�㻻,ȥ�����ӽڵ��е����ֵ
		}

		if (temp >= l->data[j])
		{
			break;//������ڵ�������ӽڵ㶼���ǻ���������
		}

		
		l->data[s] = l->data[j];
		
		s = j;
	
	}

	l->data[s] = temp;
}

//������
void HeapSort(SqList* l)
{
	//������µĸ��ڵ㿪ʼ��ÿ�������һ�δ���ѵ������������Ѷ���ʱ�򣬾���ɵĴ���ѵĴ���
	for (int i = (l->length-1) / 2; i >= 1; i--)
	{
		HeapAdjust(l, i, l->length-1);
	}

	//�������
	for (int i=l->length-1;i>1;i--)
	{
		swap(l, 1, i); //�����ֵ�ŵ����һ�������һ�����ŵ���ǰ�棬����������ƶѵ������ҵ��δ�ֵ
		HeapAdjust(l, 1, i-1);
	}
}
//---------------------------------------------------07 ���������----------------------------------------------

//---------------------------------------------------08 ��������----------------------------------------------

void Merge(int arr[], int L, int M, int R) //�������Ѿ��й��ɵ�������кϲ�
{
	//L     M     R
	//x x x x x x x
	//left[l->M-1]
	//right[M->R]
	 int LeftSize = M - L; //�����鳤��
	 int RightSize = R - M+1; //�����鳤��
	 int left[MaxSize]; //������ߵ�����
	 int right[MaxSize];//�����ұߵ�����

	 //01 ���
	 for (int i = L; i < L + LeftSize; i++)
	 {
		 left[i - L] = arr[i];
	 }

	 for (int i = M; i < M + RightSize; i++)
	 {
		 right[i - M] = arr[i];
	 }

	//02 �鲢����
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

//�������򣬽����е������ֳɵ���Ԫ�أ��ӵ���Ԫ�ؿ�ʼ��������
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

////---------------------------------------------------08 �����������----------------------------------------------

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




