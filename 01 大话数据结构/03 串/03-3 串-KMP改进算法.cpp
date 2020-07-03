#include<iostream>
#include<cstring>
#include<vector>
using namespace std;



string t = "ababaaaba";



void get_next(const char* t, int* next) //获取回溯的表
{

	int len = strlen(t);
	int i = 0;
	int j = -1;  //尾缀
	next[0] = -1; //前缀
	while (i < len)
	{
		if (j == -1 || t[i] == t[j])
		{
			j++;
			i++;

			//与普通KMP差异的地方
			if (t[i] != t[j])
			{
				next[i] = j;
			}
			else
			{
				next[i] = next[j];
				//这个主要是考虑匹配失败的时候，如果匹配失败了，必然往回回溯，但是如果回溯的下一个
				//地方还是这个元素，必然没有意义，还要往前回溯，那就把前一个元素的回溯值直接交给后面就可以了
				
				//比如  S = abacababc
				//		T = abab
				//匹配第四个元素不同，必然往前回溯，变成
				//      S = abacababc
				//		  T = abab
				//对着的还是b，不可能匹配成功的。
				//所以，如果有匹配的子串，而且其下一个元素也相同，那就意味着，如果下一个元素匹配失败的时候
				//往前回溯，对应元素还是这个值。
			}
			//差异结束
		
		}
		else
		{
			j = next[j]; 
		}
	}
}

int Index_KMP(const char* S, const char* T)
{
	int next[100];
	get_next(T, next);//获取模式串用于标识回溯位置的表
	int i = 0;
	int j = 0;
	int Slen = strlen(S);//主串
	int Tlen = strlen(T); //模式串
	while (i < Slen && j < Tlen)
	{
		if (j == -1 || S[i] == T[j])
		{
			i++;
			j++;
		}
		else
		{
			j = next[j];
		}
	}
	if (j == Tlen)//匹配成功
	{
		return i - j;
	}
	else
	{
		return -1;
	}

}
int main()
{
	const char* b = "AAAAAIIIISLSLSLABCABDABCABEPPPPSS";
	const char* a = "ABCABDABCABE";
	int n = Index_KMP(b, a);
	cout << n << endl;



	return 0;
}


