#pragma once
//T���ı���
//P��ģʽ��
#include<cstring>
#include<iostream>
using namespace std;
int BruteMatch1(const char* P, const char* T)
{
	size_t n = strlen(T); int i=0; //�ı������� 
	
	size_t m = strlen(P); int j=0;//ģʽ������
	
	while (j < m && i < n)
	{
		if (T[i] == P[j])
		{
			i++;
			j++;
		}
		else
		{
			i -= j - 1;
			j = 0;
		}
	}

	//i-j>n-m��ʱ�򣬿����ж�ƥ��ʧ��
	return i - j;



}

int BruteMatch2(const char* P, const char* T)
{
	int m = strlen(P); int j;
	int n = strlen(T); int i=0;
	for (i = 0; i < n - m + 1; i++)
	{
		for (j = 0; j < m; j++)
		{
			if (T[i + j] != P[j])break;
		}
		if (j >= m)break; //ƥ�����
	}
	return i; //���iС��n-m��˵��ƥ��ɹ�
}
int* buildNext(const char* P)
{
	size_t n = strlen(P);
	int* next = new int[n];
	next[0] = -1;
	int t = -1; //ǰ�ڱ�
	int j = 0; //���ڱ� 
	while (j < n - 1)
	{
		if (t < 0 || P[t] == P[j])
		{
			t++;
			j++;
			next[j] = t;
		}
		else
		{
			t = next[t];

		}
	}
	return next;
}

int* buildNextPro(const char* P)
{
	size_t n = strlen(P);
	int* next = new int[n];
	next[0] = -1;
	int t = -1; //ǰ�ڱ�
	int j = 0; //���ڱ� 
	while (j < n - 1)
	{
		if (t < 0 || P[t] == P[j])
		{
			t++;
			j++;
			next[j] = (P[t]!= P[j]?t:next[t]);
		}
		else
		{
			t = next[t];

		}
	}
	return next;
}
int KMP_1(const char* P, const char* T)
{
	int* next = buildNext(P);
	int n = (int)strlen(T); int i = 0;
	int m = (int)strlen(P); int j = 0;
	while (i < n && j < m)
	{
		if (j < 0 || T[i] == P[j]) //���ģʽ��P���ݵ���-1λ�ã�����ƥ��ɹ�
		{
			i++;
			j++;
		}
		else
		{
			j = next[j]; //����j����
		}
	}
	delete[]next;
	return i - j; //ֻ��i-jС��n-m��ʱ�򣬲�ƥ��ɹ�
}

int KMP_2(const char* P, const char* T)
{
	int* next = buildNextPro(P);
	int n = (int)strlen(T); int i = 0;
	int m = (int)strlen(P); int j = 0;
	while (i < n && j < m)
	{
		if (j < 0 || T[i] == P[j]) //���ģʽ��P���ݵ���-1λ�ã�����ƥ��ɹ�
		{
			i++;
			j++;
		}
		else
		{
			j = next[j]; //����j����
		}
	}
	delete[]next;
	return i - j; //ֻ��i-jС��n-m��ʱ�򣬲�ƥ��ɹ�
}



int* buildBC(const char* P) //�û����㷨�������ַ���
{
	int* bc = new int[256];
	for (size_t i = 0; i < 256; i++)
	{
		bc[i] = -1;
	}
	for (size_t m = strlen(P), i = 0; i < m; i++)
	{
		bc[P[i]] = i;
	}

	return bc;
}

int BM_BC(const char* P, const char* T)
{
	int* bc = buildBC(P);
	int n = strlen(T);
	int m = strlen(P);
	int i = 0; //��¼ģʽ��������ı�������ʼλ��
	while (n >= i + m)
	{
		int j = m - 1; //ģʽ��P��ĩ����
		while (P[j] == T[i + j])
		{
			j--;
			if (j < 0)break;
		}
		if (j < 0)break;
		
		int index = bc[T[i + j]];
		if (index > j)
		{
			i++;
			
		}
		else
		{
			i += j - index;
		}
			
	



	}



	delete[]bc;
	return i;

}

int* buildSS(const char* P)
{
	int m = strlen(P);
	int* ss = new int[m];
	ss[m - 1] = m;
	for (int hi = m - 1, lo = m - 1, j = lo - 1; j >= 0; j--)
	{
		if (j > lo&&ss[m-1-(hi-j)]<=j-lo)//���j��ƥ�������У������Ҳ�ƥ��������Ӧ��ss���Ȳ�С��lo����ôֱ�Ӱ�λ��ƥ����ȼ���
		{
			ss[j] = ss[m - 1 - (hi - j)];
		}
		else //���j��ƥ���������࣬����ss���ȳ�����lo����ô����Ҫ����ƥ��δ֪���ַ�λ��
		{
			hi = j; //��hiλ�ø��µ�j����������ƥ�����
			lo = __min(hi, lo);
			while (lo >= 0 && P[lo] == P[m-1-(hi-lo)])//����Ѱ�ҵ�ǰ�ƥ�䴮
			{
				lo--; 
			}
			ss[j] = hi - lo;
		}
	}
	return ss;

}

int* buildGS(const char* P)
{
	int* ss = buildSS(P);
	size_t m = strlen(P);
	int* gs = new int[m];
	for (size_t j = 0; j < m - 1; j++)gs[j] = m;
	for (int i = 0, j = m - 1; j >= 0; j--)
	{
		if (ss[j] == j + 1)
		{
			while (i < m - 1 - j)
			{
				gs[i++] = m - j - 1;
			}
		}
	}
	for (size_t j = 0; j < m - 1; j++)
	{
		gs[m - 1 - ss[j]] = m - j - 1;
	}
	delete []ss;
	return gs;

}

int BM_GS(const char* P, const char* T)
{
	int* bc = buildBC(P); //��ŵ���T��ʧ���ַ���P���ǵڼ����������ƶ������λ�ý��ж���
	int* gs = buildGS(P); //��ŵ���ĳ���ַ�ʧ��Ļ�����
	int n = strlen(T);
	int m = strlen(P);
	

	int i = 0; //��¼ģʽ��������ı�������ʼλ��
	while (n >= i + m)
	{
		int j = m - 1; //ģʽ��P��ĩ����
		while (P[j] == T[i + j])
		{
			j--;
			if (j < 0)break;
		}
		if (j < 0)break;

		
		else
		{
			i += __max(j-bc[T[i+j]],gs[j]);
		}





	}



	delete[]bc;
	delete[]gs;
	return i;

}
