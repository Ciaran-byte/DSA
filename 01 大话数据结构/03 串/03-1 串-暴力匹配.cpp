#include<iostream>
#include<cstring>
using namespace std;

int ViolentMatch(const char* S, const char* T)
{
	int Slen = strlen(S); //主串
	int Tlen = strlen(T);  //模式串
	
	int i = 0;
	int j = 0;
	while (i < Slen &&j < Tlen)
	{
		if (S[i] == T[j])
		{
			i++; //字符串如果匹配，就继续向前搜索
			j++;
		}
		else
		{
			i = i - j + 1; //如果不匹配，主串回退搜索的长度，并且往后偏移一个位置
			j = 0; //模式串从头继续搜索
		}

		
	}

	if (j == Tlen)
	{
		return i - j; //返回匹配位置
	}
	else
	{
		return -1;
	}
}

int main()
{
	const char* a = "ABCERDS";
	const char* b = "RD";
	int n = ViolentMatch(a, b);
	cout << n << endl;
	
	return 0;
}

