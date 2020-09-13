#pragma once
#include"vector.h"

template<typename T>
T trivialMedian(vector<T>& s1, int l1, int n1, vector<T>& s2, int l2, int n2)//����������λ��
{
	//��������s1[l1,l1+n1)��s2[l2,l2+n2)���й鲢��������λ��
	vector<T> S;
	int h1 = l1 + n1;
	int h2 = l2 + n2;
	while (l1 < h1 && l2 < h2)
	{
		while (l1<h1&&s1[l1] <= s2[l2])
			S.insert(s1[l1++]);
			
		
		while (l2 < h2 && s1[l1] >= s2[l2])
			S.insert(s2[l2++]);
			
		
	}
	while (l1 < h1)
		S.insert(s1[l1++]);
		
	
	while (l2 < h2)
		S.insert(s2[l2++]);
		
	
	return S[(n1+n2)/2];
}

template<typename T>
T median(vector<T>& s1, int l1, vector<T>& s2, int l2, int n) //��Ч����λ����������,�����ȳ���ʱ��
{
	//s1[l1,l1+n); s2[l2,l2+n);
	if (n < 3)return trivialMedian(s1, l1, n, s2, l2, n);
	int mid1 = l1 + n / 2;  
	int mid2 = l2 + n / 2;
	if (s1[mid1] < s2[mid2])
	{
		return median(s1, mid1, s2, l2,lo1+n-mid1);
	}
	else if (s1[mid1] > s2[mid2])
	{
		return median(s1, l1, s2, mid2, lo2 + n - mid2);
	}
	else
	{
		return s1[mid1];
	}
}

template<typename T>
void quickSelect(vector<T>& A, int k) //��A��ѡȡ��k���Ԫ��
{
	for (int l = 0, h = A.size() - 1; l < h;)
	{
		int i = l;
		int j = h;
		T pivot = A[l];
		while (i < j)
		{
			while (i<j && A[j]>pivot) { j--; }A[i] = A[j];
			while (i < j && A[i] < pivot) { i++; }A[j] = A[i];
		}

		A[j] = pivot;
		if (k >= j)
		{
			l = j+1;
		}
		if(k<=j)
		{
			h = j-1;
		}
		
		//����A[k]����ҪѰ�ҵ�Ԫ��

	}
}