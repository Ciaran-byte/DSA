#pragma once
template<typename T> struct PQ
{
	virtual void insert(T) = 0; //����
	virtual T getMax() = 0; //ȡ�����ȼ���ߵĴ���
	virtual T delMax() = 0; //ɾ�����ȼ���ߵĴ���
};