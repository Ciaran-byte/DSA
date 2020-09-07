#pragma once
#include "stack_vector.h"
#define N_OPTR 9 //�������оŸ�����������ֱ���+ - * / ^ ( ) ! \0

//ջ��Ӧ���У���׺���ʽ��ʵ����Ҫ����࣬�����˲����������ȼ���
typedef enum { ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE } Operator;
const char pri[N_OPTR][N_OPTR] = { //��������ȼ�
	//-----------------------------------------------��ǰ�����------------------------------
//					+		-		*		/		!		^		(		)		\0
	/*	+	*/		'>',    '>',   '<',    '<',    '<',     '<',   '<',    '>',     '>',
	/*	-	*/		'>',    '>',   '<',    '<',    '<',     '<',   '<',    '>',     '>',
	/*	*	*/		'>',    '>',   '>',    '>',    '<',     '<',   '<',    '>',     '>',
	/*	/	*/		'>',    '>',   '>',    '>',    '<',     '<',   '<',    '>',     '>',
	/*	^	*/		'>',    '>',   '>',    '>',    '<',     '>',   '<',    '>',     '>',
	/*	!	*/		'>',    '>',   '>',    '>',    '>',     '>',   ' ',    '>',     '>',
	/*	(	*/		'<',    '<',   '<',    '<',    '<',     '<',   '<',    '=',     ' ',
	/*	)	*/		' ',    ' ',   ' ',    ' ',    ' ',     ' ',   ' ',    ' ',     ' ',
	/*	\0	*/		'<',    '<',   '<',    '<',    '<',     '<',   '<',    ' ',     '=',
};

bool isdigit(char c){return (c >= '0' && c <= '9') ? true : false;} //�ж��ַ��Ƿ�Ϊ����
void readNumber(char*& S, stack<float> &opnd) //���������������ջ��
{
	
	opnd.push((float)(*S - '0'));
	while (isdigit(*(++S)))
		opnd.push(opnd.pop() * 10 + (float)(*S - '0'));
	if ('.' != *S)return; //���û��С���㣬��������
	float fraction = 1; //������ζ�Ż���С������
	while (isdigit(*(++S))) //��λ����
		opnd.push(opnd.pop() + (*S - '0') * (fraction /= 10)); //С������

	
}

Operator optConvert(char opt)
{
	switch (opt)
	{
	case '+':
		return ADD;
		
	case '-':
		return SUB;
		
	case '*':
		return MUL;
		
	case '/':
		return DIV;
		
	case '^':
		return POW;

	case '!':
		return FAC;
	
	case '(':
		return L_P;

	case ')':
		return R_P;
	
	case '\0':
		return EOE;
	default:
		exit(-1);
	
	}
}
char orderBetween(char opt_1,char opt_2)//�Ƚ�ջ�����������һ��δ��ջ�������֮��Ĺ�ϵ
{
	return pri[optConvert(opt_1)][optConvert(opt_2)];
}

float calcu(char op,float num)
{
	float i = 1;
	while (num > 1)
		i *= (num--);	
	return i;
}

float calcu(float num1, char op, float num2)
{
	float num = 0;
	switch (op)
	{
	case '+':
		num = num1 + num2;
		break;
	case '-':
		num = num1 - num2;
		break;
	case '*':
		num = num1 * num2;
		break;
	case '/':
		num = num1 / num2;
		break;
	case '^':
		num = pow(num1, num2);
		break;
	  }
	return num;
}