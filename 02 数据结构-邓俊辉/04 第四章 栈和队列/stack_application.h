#pragma once
#include "stack_vector.h"
#include "operator.h"
//栈应用，包括:逆序输出（进制转换）;递归嵌套（括号匹配、栈混洗);延迟计算（中缀表达式)

void convert(stack<char>& s, __int64 n, int base) //把10进制的n转换为base进制的数字，存入stack中
{
	static char digit[16] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E' };
	while (n > 0)
	{
		int remind =(int)n % base;
		s.push(digit[remind]);
		n /= base;
	}


}
bool paren(const char exp[],int l,int h)//检测括号是否匹配
{
	stack<char> s;
	for (int i = l; i < h; i++)
	{
		switch (exp[i])
		{
		case '(':case'[':case'{':s.push(exp[i]); break;
		case ')': if (s.empty() || s.pop() != '(')return false; break;
		case ']': if (s.empty() || s.pop() != '[')return false; break;
		case '}': if (s.empty() || s.pop() != '{')return false; break;
		default:break;
		}
	}
	return s.empty();
}

bool stackPermutation(int *B,int n) //判断是否是数列1,2......,n的有效的栈混洗
{
	
	//数组B是输出序列，也就是要输入的栈混洗数列
	int A = 1; //A模拟的是原序列
	stack<int> C; //栈C模拟的是中间储存序列
	for (int k = 0; k < n; k++)
	{
		while (C.empty() || C.top() != B[k])
		{
			if (A == n+1)break;
			C.push(A++);
			
		}
		
		if (B[k] != C.pop())
		{
			return false;
		}
	}
	return true;
}

float evaluate(char* S) //中缀表达式的输出
{
	stack<float> opnd;//操作数
	stack<char> optr; //操作符
	optr.push('\0');
	while (!optr.empty()) //运算符为空的时候，输出计算结果
	{
		if (isdigit(*S)) //如果是操作数
		{
			readNumber(S, opnd); 
		}
		else //如果是操作符
		{
			
			switch (orderBetween(optr.top(), *S))
			{
			case '<':
				optr.push(*S); S++; //如果运算符后面的优先级高，说明还不到运算的时候，加入下一个运算符
				break;
			case '=':
				optr.pop(); S++; //如果相等，只有可能是括号和结束符，那就把左边一半出栈，右边一半丢弃
				break;
			case '>': //如果比后面运算符优先级高，说明该计算了
			{
				char op = optr.pop();//取出运算符
				
				if (op == '!')
				{
					float num = opnd.pop(); //单目运算符，只需要取出一个数字
					opnd.push(calcu(op, num));
				}
				else
				{
					float num2 = opnd.pop();
					float num1 = opnd.pop();
					opnd.push(calcu(num1, op, num2));
				}
				break;

			}
			default:
				exit(-1);


			}//switch
		}//else
	}//while
	return opnd.pop();
}