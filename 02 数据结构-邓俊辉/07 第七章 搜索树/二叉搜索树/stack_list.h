#pragma once
#include "list.h"
//����list��ջ��ʵ��
template <typename T>
class stack :public List<T>
{
public:
	void push(const T& elem) { insertAsLast(elem); }
	T pop() { remove(last()); }
	T& top() { return last()->data; }
};
