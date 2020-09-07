#pragma once
#ifndef _FIB_H
#define _FIB_H
//产生斐波那契数列的头文件，用于vector模板类的斐波那契查找
class Fib
{
private:
	int f, g;
public:
	Fib(int n)
	{
		 f = 1, g = 0;
		while (g < n)
		{
			next();
		}
	}
	int get()
	{
		return g;
	}
	int next()
	{
		g += f;
		f = g - f;
		return g;
	}
	int prev()
	{
		f = g - f;
		g -= f;
		return g;
	}
};


#endif
