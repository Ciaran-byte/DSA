#pragma once
#include "stack_vector.h"
#include "operator.h"
//ջӦ�ã�����:�������������ת����;�ݹ�Ƕ�ף�����ƥ�䡢ջ��ϴ);�ӳټ��㣨��׺���ʽ)

void convert(stack<char>& s, __int64 n, int base) //��10���Ƶ�nת��Ϊbase���Ƶ����֣�����stack��
{
	static char digit[16] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E' };
	while (n > 0)
	{
		int remind =(int)n % base;
		s.push(digit[remind]);
		n /= base;
	}


}
bool paren(const char exp[],int l,int h)//��������Ƿ�ƥ��
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

bool stackPermutation(int *B,int n) //�ж��Ƿ�������1,2......,n����Ч��ջ��ϴ
{
	
	//����B��������У�Ҳ����Ҫ�����ջ��ϴ����
	int A = 1; //Aģ�����ԭ����
	stack<int> C; //ջCģ������м䴢������
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

float evaluate(char* S) //��׺���ʽ�����
{
	stack<float> opnd;//������
	stack<char> optr; //������
	optr.push('\0');
	while (!optr.empty()) //�����Ϊ�յ�ʱ�����������
	{
		if (isdigit(*S)) //����ǲ�����
		{
			readNumber(S, opnd); 
		}
		else //����ǲ�����
		{
			
			switch (orderBetween(optr.top(), *S))
			{
			case '<':
				optr.push(*S); S++; //����������������ȼ��ߣ�˵�������������ʱ�򣬼�����һ�������
				break;
			case '=':
				optr.pop(); S++; //�����ȣ�ֻ�п��������źͽ��������ǾͰ����һ���ջ���ұ�һ�붪��
				break;
			case '>': //����Ⱥ�����������ȼ��ߣ�˵���ü�����
			{
				char op = optr.pop();//ȡ�������
				
				if (op == '!')
				{
					float num = opnd.pop(); //��Ŀ�������ֻ��Ҫȡ��һ������
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