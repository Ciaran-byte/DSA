#include<iostream>
#include "stack_vector.h"
#include "stack_application.h"
#include "N_Queen.h"
using namespace std;
int main()
{
	//---------------------------------------------------ջ��Ӧ��---------------------------------------
	//01 ����ת��
	cout << "����ת��" << endl;
	int num = 200;
	stack<char> s;
	
	convert(s, 50000, 2);

	while (!s.empty())
	{
		cout<<s.pop();
	}
	cout << endl;
	
	//02 ����ƥ��
	cout << endl;
	cout << "����ƥ��" << endl;
	const char exp[10] = { '(','{','[',']','}',')','0','7','6','6'};
	cout << paren(exp, 0, 10) << endl;

	//03 ջ��ϴ
	cout << endl;
	cout << "ջ��ϴ��֤" << endl;
	int B[3] = { 1,2,3 };
	if (stackPermutation(B, 3) == true)cout << "true" << endl;
	else cout << "flase" << endl;
	
	//04 ��׺���ʽ
	cout << endl;
	cout << "��׺���ʽ" << endl;
	
	char expression[] = { '3','*','(','2','+','5','!',')','\0' };
	
	cout << evaluate(expression) << endl;
//------------------------------------�����㷨��Ӧ��--------------------------------------------------
	//05 N�ʺ�
	cout << endl;
	cout << "N�ʺ�����" << endl;

	cout << placeQueens(8) << endl;



		return 0;
}
