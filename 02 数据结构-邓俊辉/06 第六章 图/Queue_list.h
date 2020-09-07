#pragma once
#include "list.h"
//����ģ����
template <typename T>
class queue :public List<T>
{
public:
	void enqueue(const T& elem) { this->insertAsLast(elem); }
	T dequeue() { return this->remove(this->first()); }
	T& front() { return this->first()->data; }
};