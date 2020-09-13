#pragma once
template<typename T> struct PQ
{
	virtual void insert(T) = 0; //插入
	virtual T getMax() = 0; //取出优先级最高的词条
	virtual T delMax() = 0; //删除优先级最高的词条
};