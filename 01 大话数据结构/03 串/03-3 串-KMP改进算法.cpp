#include<iostream>
#include<cstring>
#include<vector>
using namespace std;



string t = "ababaaaba";



void get_next(const char* t, int* next) //��ȡ���ݵı�
{

	int len = strlen(t);
	int i = 0;
	int j = -1;  //β׺
	next[0] = -1; //ǰ׺
	while (i < len)
	{
		if (j == -1 || t[i] == t[j])
		{
			j++;
			i++;

			//����ͨKMP����ĵط�
			if (t[i] != t[j])
			{
				next[i] = j;
			}
			else
			{
				next[i] = next[j];
				//�����Ҫ�ǿ���ƥ��ʧ�ܵ�ʱ�����ƥ��ʧ���ˣ���Ȼ���ػ��ݣ�����������ݵ���һ��
				//�ط��������Ԫ�أ���Ȼû�����壬��Ҫ��ǰ���ݣ��ǾͰ�ǰһ��Ԫ�صĻ���ֱֵ�ӽ�������Ϳ�����
				
				//����  S = abacababc
				//		T = abab
				//ƥ����ĸ�Ԫ�ز�ͬ����Ȼ��ǰ���ݣ����
				//      S = abacababc
				//		  T = abab
				//���ŵĻ���b��������ƥ��ɹ��ġ�
				//���ԣ������ƥ����Ӵ�����������һ��Ԫ��Ҳ��ͬ���Ǿ���ζ�ţ������һ��Ԫ��ƥ��ʧ�ܵ�ʱ��
				//��ǰ���ݣ���ӦԪ�ػ������ֵ��
			}
			//�������
		
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
	get_next(T, next);//��ȡģʽ�����ڱ�ʶ����λ�õı�
	int i = 0;
	int j = 0;
	int Slen = strlen(S);//����
	int Tlen = strlen(T); //ģʽ��
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
	if (j == Tlen)//ƥ��ɹ�
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


