#include<iostream>
#include "stack_vector.h"
#include "stack_application.h"
#include "N_Queen.h"
using namespace std;
int main()
{
	//---------------------------------------------------栈的应用---------------------------------------
	//01 进制转换
	cout << "进制转换" << endl;
	int num = 200;
	stack<char> s;
	
	convert(s, 50000, 2);

	while (!s.empty())
	{
		cout<<s.pop();
	}
	cout << endl;
	
	//02 括号匹配
	cout << endl;
	cout << "括号匹配" << endl;
	const char exp[10] = { '(','{','[',']','}',')','0','7','6','6'};
	cout << paren(exp, 0, 10) << endl;

	//03 栈混洗
	cout << endl;
	cout << "栈混洗验证" << endl;
	int B[3] = { 1,2,3 };
	if (stackPermutation(B, 3) == true)cout << "true" << endl;
	else cout << "flase" << endl;
	
	//04 中缀表达式
	cout << endl;
	cout << "中缀表达式" << endl;
	
	char expression[] = { '3','*','(','2','+','5','!',')','\0' };
	
	cout << evaluate(expression) << endl;
//------------------------------------回溯算法的应用--------------------------------------------------
	//05 N皇后
	cout << endl;
	cout << "N皇后问题" << endl;

	cout << placeQueens(8) << endl;



		return 0;
}
