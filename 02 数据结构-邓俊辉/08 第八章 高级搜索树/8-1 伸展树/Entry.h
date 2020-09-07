#pragma once
//��������
template<typename K,typename V>
struct Entry
{
	K key; //�ؼ���
	V value; //ֵ
	Entry(K k=K(),V v = V()):key(k),value(v){}//Ĭ�Ϲ��캯��
	Entry(const Entry<K,V>& e):key(e.key),value(e.value){}//�������캯��
	bool operator<(const Entry<K, V>& e) { return key < e.key; }
	bool operator>(const Entry<K, V>& e) { return !(*this < e); }
	bool operator==(const Entry<K, V>& e) { return key == e.key; }
	bool operator!=(const Entry<K, V>& e) { return !(*this == e); }



};
