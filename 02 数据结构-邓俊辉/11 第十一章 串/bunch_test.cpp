#include "bunch.h"
#include <iostream>
using namespace std;
int main()
{
	//01 �����㷨
	cout << "�����㷨" << endl;
	char T[10] = { 'a','b','s','t','r','a','c','t',' ' };
	char P[4] = { 'a','c','t' };
	string S1 = "abcd";
	string S2 = "ab";
	int tag = BruteMatch2(S2.c_str(), S1.c_str());
	cout << tag << endl;
	if (tag > S1.size() - S2.size())
	{
		cout << "ƥ��ʧ��" << endl;
	}
	else
	{
		cout << "ƥ��ɹ�" << endl;
	}
	//02 KMP�㷨
	cout << endl;
	cout << "KMP�㷨" << endl;
	int tag2 = KMP_1(S2.c_str(), S1.c_str());
	if (tag2 > S1.size() - S2.size())
	{
		cout << "ƥ��ʧ��" << endl;
	}
	else
	{
		cout << "ƥ��ɹ�" << endl;
	}

	cout << "KMP2" << endl;
	int tag3 = KMP_2(S2.c_str(), S1.c_str());
	if (tag3 > S1.size() - S2.size())
	{
		cout << "ƥ��ʧ��" << endl;
	}
	else
	{
		cout << "ƥ��ɹ�" << endl;
	}

	//03 BM�㷨
	cout << endl;
	cout << "BM�㷨_BC" << endl;
	string S3= "VDBMDBCDABCD";
	string S4 = "ABCD";
	int tag4 = BM_BC(S4.c_str(), S3.c_str());
	if (tag4 > S3.size() - S4.size())
	{
		cout << "ƥ��ʧ��" << endl;
	}
	else
	{
		cout << "ƥ��ɹ�" << endl;
	}
	cout << "BM�㷨_GS" << endl;
	int tag5 = BM_GS(S4.c_str(), S3.c_str());
	if (tag5 > S3.size() - S4.size())
	{
		cout << "ƥ��ʧ��" << endl;
	}
	else
	{
		cout << "ƥ��ɹ�" << endl;
	}
	return 0;
}

