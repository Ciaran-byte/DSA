#include<iostream>
#include "list.h"
using namespace std;
int main()
{
	//01 �б�������ܲ���
	cout << "�б�������ܲ���" << endl;
	int a[10] = { 0,4,5,6,2,8,8,9,8,8 };
	List<int> lst1;
	for (int i = 0; i < 10; i++)
	{
		lst1.insertAsLast(a[i]);
		cout << lst1[i] << endl;
	}
	cout << "���ҹ���" << endl;
	cout<<lst1.find(4)->data<<endl;

	//02 ȥ��
	cout << endl;
	cout << "ȥ��" << endl;
	lst1.deduplicate();
	for (int i = 0; i < lst1.size(); cout << lst1[i++] << endl);
	
	//03 ����ȥ��
	cout << endl;
	cout << "����ȥ��" << endl;
	List<int> lst2;
	int b[10] = {0,1,1,1,2,2,2,3,5,6 };
	for (int i = 0; i < 10; i++)
	{
		lst2.insertAsLast(b[i]);
		
	}
	lst2.uniquify();
	for (int i = 0; i < lst2.size(); cout << lst2[i++] << endl);

	//04 ����
	cout << endl;
	
	cout << "����" << endl;
	List<int> lst3;
	int e[4] = {2,1,2,1};
	for (int i = 0; i < 10; i++)
	{
		lst3.insertAsLast(a[i]);
		cout << lst3[i] << endl;
	}


	cout << "�����" << endl;
	
	//�б�Ĺ鲢����ʧ�ܣ�����
	lst3.insertSort(lst3.first(), lst3.size());
	for (int i = 0; i < lst3.size(); i++)
	{
		cout << lst3[i] << endl;
	}

	//05 ����
	cout << endl;
	cout << "����" << endl;
	lst3.reverse();
	for (int i = 0; i < lst3.size(); i++)
	{
		cout << lst3[i] << endl;
	}
	return 0;
}

