#pragma once
#include "list.h"
//基于list的栈的实现
template <typename T>
class stack :public List<T>
{
public:
	void push(const T& elem) { insertAsLast(elem); }
	T pop() { remove(last()); }
	T& top() { return last()->data; }
};
