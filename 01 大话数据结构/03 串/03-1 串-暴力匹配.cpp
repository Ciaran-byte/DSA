#include<iostream>
#include<cstring>
using namespace std;

int ViolentMatch(const char* S, const char* T)
{
	int Slen = strlen(S); //����
	int Tlen = strlen(T);  //ģʽ��
	
	int i = 0;
	int j = 0;
	while (i < Slen &&j < Tlen)
	{
		if (S[i] == T[j])
		{
			i++; //�ַ������ƥ�䣬�ͼ�����ǰ����
			j++;
		}
		else
		{
			i = i - j + 1; //�����ƥ�䣬�������������ĳ��ȣ���������ƫ��һ��λ��
			j = 0; //ģʽ����ͷ��������
		}

		
	}

	if (j == Tlen)
	{
		return i - j; //����ƥ��λ��
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

