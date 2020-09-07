#pragma once
//词条类型
template<typename K,typename V>
struct Entry
{
	K key; //关键字
	V value; //值
	Entry(K k=K(),V v = V()):key(k),value(v){}//默认构造函数
	Entry(const Entry<K,V>& e):key(e.key),value(e.value){}//拷贝构造函数
	bool operator<(const Entry<K, V>& e) { return key < e.key; }
	bool operator>(const Entry<K, V>& e) { return !(*this < e); }
	bool operator==(const Entry<K, V>& e) { return key == e.key; }
	bool operator!=(const Entry<K, V>& e) { return !(*this == e); }



};
