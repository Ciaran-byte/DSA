#include<iostream>
#include<algorithm>
#include "vector.h"
using namespace std;

int main()
{
	//01  ����vector
	int a[5] = { 0,1,2,3,4 };
	vector<int> v(a,5);
	cout << "��ǰԪ��Ϊ" << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << v[i] << endl;
	}
	cout << endl;
	//02 ����
	v.unsort();
	cout << "���Һ�Ԫ��Ϊ" << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << v[i] << endl;
	}
	cout << endl;

	//03 ��̬����(�������)
	cout << "Ԫ��2���±�Ϊ" << endl;
	cout << v.find(2) << endl;

	//04 �������
	cout << endl;
	cout << "��Ԫ��8���뵽�±�Ϊ5��λ�ã�����ӡ" << endl;
	v.insert(8, 5);
	cout << v[5] << endl;
	//05 ɾ������
	cout << "ɾ������" << endl;
	v.remove(5);
	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << endl;
	}
	
	//06 ��������ȥ��
	cout << endl;
	cout << "��������ȥ��" << endl;
	int b[5] = { 0,1,2,2,2 };
	vector<int> v2(b, 5);
	v2.unique();
	for (int i = 0; i < v2.size(); i++)
	{
		cout << v2[i] << endl;
	}
	
	//07 ����
	cout << endl;
	cout << "���ֲ��Ұ汾A" << endl;
	int s1[10] = { 0,2,3,4,5,6,7,8,11,14 };
	vector<int> v3(s1, 10);
	cout<<v3.binSearchA(9, 0, v3.size())<<endl;
	cout << endl;
	cout << "���ֲ��Ұ汾B" << endl;
	cout << v3.binSearchB(8, 0, v3.size()) << endl;

	cout << endl;
	cout << "���ֲ��Ұ汾C" << endl;
	cout << v3.binSearchC(8, 0, v3.size()) << endl;

	cout << endl;
	cout << "쳲���������" << endl;
	cout << v3.fibSearch(8, 0, v3.size()) << endl;

	cout << endl;
	cout << "��ֵ����" << endl;
	cout << v3.insertSearch(8, 0, v3.size()) << endl;

	cout << endl;
	cout << "����" << endl;
	cout << v3.search(9) << endl;


	//08 ����
	cout << "ð������" << endl;
	int s2[10] = { 1,6,4,2,7,9,0,3,5,6 };
	vector<int> v4(s2, 10);
	v4.bubbleSortB(0, v4.size());
	for (int i = 0; i < v4.size(); i++)
	{
		cout << v4[i] << endl;
	}

	cout << "�鲢����" << endl;
	vector<int> v5(s2, 10);
	v5.mergeSort(0, v5.size());
	for (int i = 0; i < v5.size(); i++)
	{
		cout << v5[i] << endl;
	}
	
	cout << "ѡ������" << endl;
	vector<int> v6(s2, 10);
	
	v6.selectSort(0, v6.size());
	for (int i = 0; i < v6.size(); i++)
	{
		cout << v6[i] << endl;
	}

	cout << "��������" << endl;
	vector<int> v7(s2, 10);

	v7.insertSort(0, v7.size());
	for (int i = 0; i < v7.size(); i++)
	{
		cout << v7[i] << endl;
	}
	return 0;
}