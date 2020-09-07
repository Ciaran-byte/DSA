#pragma once
#include "list.h"
//����list��ջ��ʵ��
template <typename T>
class stack :public List<T>
{
public:
	void push(const T& elem) { this->insertAsLast(elem); }
	T pop() { return this->remove(this->last()); }
	T& top() { return this->last()->data; }
};
