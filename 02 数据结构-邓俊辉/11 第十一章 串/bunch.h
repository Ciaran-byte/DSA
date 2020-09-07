#pragma once
//T是文本串
//P是模式串
#include<cstring>
#include<iostream>
using namespace std;
int BruteMatch1(const char* P, const char* T)
{
	size_t n = strlen(T); int i=0; //文本串长度 
	
	size_t m = strlen(P); int j=0;//模式串长度
	
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

	//i-j>n-m的时候，可以判定匹配失败
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
		if (j >= m)break; //匹配完成
	}
	return i; //如果i小于n-m，说明匹配成功
}
int* buildNext(const char* P)
{
	size_t n = strlen(P);
	int* next = new int[n];
	next[0] = -1;
	int t = -1; //前哨兵
	int j = 0; //后哨兵 
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
	int t = -1; //前哨兵
	int j = 0; //后哨兵 
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
		if (j < 0 || T[i] == P[j]) //如果模式串P回溯到了-1位置，或者匹配成功
		{
			i++;
			j++;
		}
		else
		{
			j = next[j]; //否则j回溯
		}
	}
	delete[]next;
	return i - j; //只有i-j小于n-m的时候，才匹配成功
}

int KMP_2(const char* P, const char* T)
{
	int* next = buildNextPro(P);
	int n = (int)strlen(T); int i = 0;
	int m = (int)strlen(P); int j = 0;
	while (i < n && j < m)
	{
		if (j < 0 || T[i] == P[j]) //如果模式串P回溯到了-1位置，或者匹配成功
		{
			i++;
			j++;
		}
		else
		{
			j = next[j]; //否则j回溯
		}
	}
	delete[]next;
	return i - j; //只有i-j小于n-m的时候，才匹配成功
}



int* buildBC(const char* P) //用画家算法构建坏字符表
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
	int i = 0; //记录模式串相对于文本串的起始位置
	while (n >= i + m)
	{
		int j = m - 1; //模式串P的末索引
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
		if (j > lo&&ss[m-1-(hi-j)]<=j-lo)//如果j在匹配区域中，并且右侧匹配序列相应的ss表长度不小于lo，那么直接按位置匹配相等即可
		{
			ss[j] = ss[m - 1 - (hi - j)];
		}
		else //如果j在匹配区域的左侧，或者ss表长度超过的lo，那么就需要重新匹配未知的字符位置
		{
			hi = j; //把hi位置更新到j，继续往后匹配测试
			lo = __min(hi, lo);
			while (lo >= 0 && P[lo] == P[m-1-(hi-lo)])//继续寻找当前最长匹配串
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
	int* bc = buildBC(P); //存放的是T中失陪字符在P中是第几个，方便移动到这个位置进行对齐
	int* gs = buildGS(P); //存放的是某个字符失配的滑动量
	int n = strlen(T);
	int m = strlen(P);
	

	int i = 0; //记录模式串相对于文本串的起始位置
	while (n >= i + m)
	{
		int j = m - 1; //模式串P的末索引
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
