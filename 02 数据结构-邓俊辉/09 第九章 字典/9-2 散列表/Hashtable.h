#pragma once
#include "Dictionary.h"
#include "Bitmap.h"
#include "Entry.h"

template<typename K,typename V>
class Hashtable :public Dictionary<K, V>
{
private:
	Entry<K, V>** ht; //Ͱ����,��������Ͱ��ָ��
	int M; //Ͱ��������
	int N; //��������
	Bitmap* lazyRemoval; //����ɾ���ı��
	
#define lazilyRemoved(x)(lazyRemoval->test(x))
#define markAsRemoved(x)(lazyRemoval->set(x))
protected:
	int prob4Hit(const K& k); //���Źؼ���k��Ӧ�Ĳ������ҵ�ƥ��Ͱ
	int probe4Free(const K& k); //���Źؼ���k��Ӧ�Ĳ��������ҵ��׸����õ�ͨ
	void rehash(); //����Ͱ����

public:
	Hashtable(int c = 5); //����һ��������С��c��ɢ�б�
	~Hashtable(); //�ͷ�Ͱ���鼰���и���Ԫ����ָ��Ĵ���
	int size()const { return N; } //��ǰ������Ŀ
	V* get(K k); //��ȡ
	bool put(K, V); //����
	bool remove(K k); //ɾ��

};
//-------------------------------��������---------------------------------------
static size_t hashCode(char c) { return size_t(c); }
static size_t hashCode(int k) { return size_t(k); }
static size_t hashCode(long long i) { return (size_t)((i>>32)+(int)i); }
static size_t hashCode(char s[])
{
	int h = 0;
	for (size_t n = strlen(s), i = 0; i < n; i++)
	{
		h = (h << 5) | (h >> 27);
		h += (int)s[i];
	}
	return (size_t)h;
}

//-------------------------------������������-------------------------------------------
template<typename K,typename V>
Hashtable<K, V>::Hashtable(int c) //��������Ϊc�Ĺ�ϣ��
{
	M = primeNLT(c, 1048575, "prim1.txt"); //Ѱ��һ��������
	N = 0;
	ht = new Entry<K, V> * [M]; //����Ͱ����
	memset(ht, 0, sizeof(Entry<K, V>*) * M); //��ʼ������Ͱ
	lazyRemoval = new Bitmap(M); //����ɾ�����λͼ
}

template<typename K,typename V>
Hashtable<K, V>::~Hashtable()
{
	for (int i = 0; i < M; i++)
	{
		if (ht[i])delete(ht[i]);
	}
	delete ht;
	delete lazyRemoval;
}

template<typename K,typename V>
V* Hashtable<K, V>::get(K k)
{
	int r = prob4Hit(k);
	return ht[r] ? &(ht[r]->value) : nullptr;
}


template<typename K,typename V>
int Hashtable<K, V>::prob4Hit(const K& k)
{
	int r = hashCode(k) % M;
	while ((ht[r] && k != ht[r]->key) || (!ht[r] && lazilyRemoved(r))
	{
		r = (r + 1) % M;
	}
	return r;
	//ֻ������ֹͣ�����Ŀ��ܣ����ǿ�Ͱ������keyֵ��Ӧ�������ǿ�Ͱ�����Ǿ���ɾ����ǡ�
}

template<typename K,typename V>
bool Hashtable<K, V>::remove(K k)
{
	int r = prob4Hit(k); //�ز������ҵ�������
	if (!ht[r])return false; //����ǿվ�ɾ��

	delete ht[r];
	ht[r] = nullptr;
	markAsRemoved(r); //���յĻ���ɾ��Ҫ����������λ����ֹ�������Ķ���
	N--;
	return true;
}

template<typename K,typename V>
bool Hashtable<K, V>::put(K k, V v)
{
	if (ht[prob4Hit(k)])return false; //��ͬԪ�ز��ز���
	int r = probe4Free(k); //Ϊ�´����ҵ���Ͱ
	ht[r] = new Entry<K, V>(k, v);
	N++;
	if (N * 2 > M)rehash(); //װ�����ӳ���50%�Ժ�����ɢ��
	return true;


}

template<typename K, typename V>
int Hashtable<K, V>::probe4Free(const K& k)
{
	int r = hashCode(k) % M;
	while (ht[r])r = (r + 1) % M;
	return r;
}

template<typename K, typename V>
void Hashtable<K, V>::rehash()
{
	int old_capacity = M;
	Entry<K, V>** old_ht = ht;
	M = primeNLT(2*M, 1048575, "prim1.txt"); //Ѱ��һ��������
	N = 0;
	memset(ht, 0, sizeof(Entry<K, V>*) * M); //��ʼ������Ͱ
	delete lazyRemoval;
	lazyRemoval = new Bitmap(M);

	for (int i = 0; i < old_capacity; i++)
	{
		if (old_ht[i])
			put(old_ht[i]->key, old_ht[i]->value);
	}
	delete old_ht;
}

