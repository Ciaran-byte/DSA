#pragma once
#include "stack_vector.h"
#define N_OPTR 9 //定义了有九个运算符符，分别是+ - * / ^ ( ) ! \0

//栈的应用中，中缀表达式的实现需要这个类，定义了操作符的优先级别
typedef enum { ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE } Operator;
const char pri[N_OPTR][N_OPTR] = { //运算符优先级
	//-----------------------------------------------当前运算符------------------------------
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

bool isdigit(char c){return (c >= '0' && c <= '9') ? true : false;} //判断字符是否为数字
void readNumber(char*& S, stack<float> &opnd) //把数字送入操作数栈中
{
	
	opnd.push((float)(*S - '0'));
	while (isdigit(*(++S)))
		opnd.push(opnd.pop() * 10 + (float)(*S - '0'));
	if ('.' != *S)return; //如果没有小数点，解析结束
	float fraction = 1; //否则，意味着还有小数部分
	while (isdigit(*(++S))) //逐位加入
		opnd.push(opnd.pop() + (*S - '0') * (fraction /= 10)); //小数部分

	
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
char orderBetween(char opt_1,char opt_2)//比较栈顶运算符和下一个未入栈的运算符之间的关系
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