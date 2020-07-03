#include<iostream>
#include<cstring>
#include<vector>
using namespace std;

//01 普通模式匹配算法的缺陷在于，重复的进行没必要的回溯

//02 KMP算法的核心包括两个
//02-1 从主串角度来考虑
//主串的索引不会变小，当到某出与模式串不匹配的时候，模式串进行回溯。其原理是，一旦中间为了完全匹配了，模式串
//可以直接跳过这些匹配的部分，因为前后串元素不同，不可能匹配

//02-2 从模式串角度来考虑
//如果模式串每个字符都不一样，直接往后平移，将首字符对应好主串的上一个匹配失败的位置
//如果模式串有部分字符相同，就是前缀和尾缀相同，那么平移的时候，应该让前缀移到尾缀的位置，并且沿着前缀的
//下一个位置进行继续匹配

//所以，这个算法要做的事情就是
//(1)主串和模式串从头匹配，匹配成功返回成功。匹配不成功，找到匹配不成功的位置，准备继续匹配
//(2) 模式串应该有一个匹配表，根据字符串的相似程度，判断，当在模式串某个位置匹配不成功的时候，应该
//回溯到哪个元素

string t="ababaaaba";


										//j-2 j-1 j      i-2 i-1 i
//获取next表思路是
//(1)如果前面字符都配上了比如 A B C       A   B  C ，如果j+1和i+1还能继续配对，那么
//next[i+1] = next[i]+1 匹配数+1
//(2) 如果next[i+1]和next[j+1]没配上，我们就找next[j+1]的next表值，如果不是0，说明0-j部分，还是有对称
//的元素，我们就把j回溯到前一个对称值的下一个位置，再更小范围内搜索看看有没有匹配项

void get_next(const char* t,int * next) //获取回溯的表
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
			next[i] = j;
		}
		else
		{
			j = next[j]; //如果没匹配上，寻找有没有对称的子列，顺着上一个对称的位置继续匹配
			//比如ABCABDABCABE   ，前面ABCAB和后面ABCAB是完全匹配的，但是ABCABD和ABCABE不匹配,
			//我们就要把指向D位置的j指针回溯，回溯到哪里呢？我们发现ABCABD前面的ABCAB是有对称元素的
			//那么ABD与后面不匹配，缩小范围，前面的ABC有没有可能与后面的继续匹配呢？如果匹配了，就顺着
			//这个地方的next值继续+1，不匹配就再往前回溯
		}
	}
}

int Index_KMP(const char*S,const char*T )
{
	int next[100]; 
	get_next(T, next);//获取模式串用于标识回溯位置的表
	int i = 0;
	int j = 0;
	int Slen = strlen(S);//主串
	int Tlen = strlen(T); //模式串
	while (i < Slen && j < Tlen)
	{
		if (j==-1||S[i] == T[j])
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
	const char* a= "ABCABDABCABE";
	int n = Index_KMP(b, a);
	cout << n << endl;


	
	return 0;
}


