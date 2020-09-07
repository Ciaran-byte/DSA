#pragma once

template<typename K,typename V>
struct Dictionary
{
	virtual int size()const = 0;  //当前词条总数
	virtual bool put(K, V) = 0; //插入词条
	virtual V* get(K k) = 0; //读取词条
	virtual bool remove(K k) = 0; //删除词条
};
