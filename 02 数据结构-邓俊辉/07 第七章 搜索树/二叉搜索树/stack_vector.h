#pragma once
#include "vector.h"
//基于vector的栈的模板类
template <typename T>
class stack:public vector<T>
{
public:
	void push(const T& elem) { this->insert(elem, this->_size); }
	T pop() { return this->remove(this->_size - 1); }
	T& top() { return (*this)[this->_size - 1]; }
};
