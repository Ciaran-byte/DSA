#pragma once
#include "Dictionary.h"
#include "Bitmap.h"
#include "Entry.h"

template<typename K,typename V>
class Hashtable :public Dictionary<K, V>
{
private:
	Entry<K, V>** ht; //桶数组,用来储存桶的指针
	int M; //桶数组容量
	int N; //词条数量
	Bitmap* lazyRemoval; //懒惰删除的标记
	
#define lazilyRemoved(x)(lazyRemoval->test(x))
#define markAsRemoved(x)(lazyRemoval->set(x))
protected:
	int prob4Hit(const K& k); //沿着关键码k对应的查找链找到匹配桶
	int probe4Free(const K& k); //沿着关键码k对应的查找链，找到首个可用的通
	void rehash(); //扩充桶容量

public:
	Hashtable(int c = 5); //创建一个容量不小于c的散列表
	~Hashtable(); //释放桶数组及其中各个元素所指向的词条
	int size()const { return N; } //当前词条数目
	V* get(K k); //读取
	bool put(K, V); //插入
	bool remove(K k); //删除

};
//-------------------------------辅助函数---------------------------------------
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

//-------------------------------辅助函数结束-------------------------------------------
template<typename K,typename V>
Hashtable<K, V>::Hashtable(int c) //创建容量为c的哈希表
{
	M = primeNLT(c, 1048575, "prim1.txt"); //寻找一个素数表长
	N = 0;
	ht = new Entry<K, V> * [M]; //开辟桶数组
	memset(ht, 0, sizeof(Entry<K, V>*) * M); //初始化各个桶
	lazyRemoval = new Bitmap(M); //懒惰删除标记位图
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
	//只有两种停止搜索的可能，不是空桶，而且key值对应，或者是空桶，但是具有删除标记。
}

template<typename K,typename V>
bool Hashtable<K, V>::remove(K k)
{
	int r = prob4Hit(k); //沿查找链找到这个结点
	if (!ht[r])return false; //如果是空就删除

	delete ht[r];
	ht[r] = nullptr;
	markAsRemoved(r); //不空的话，删除要设置懒惰标记位，防止查找链的断裂
	N--;
	return true;
}

template<typename K,typename V>
bool Hashtable<K, V>::put(K k, V v)
{
	if (ht[prob4Hit(k)])return false; //雷同元素不必插入
	int r = probe4Free(k); //为新词条找到空桶
	ht[r] = new Entry<K, V>(k, v);
	N++;
	if (N * 2 > M)rehash(); //装填因子超过50%以后重新散列
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
	M = primeNLT(2*M, 1048575, "prim1.txt"); //寻找一个素数表长
	N = 0;
	memset(ht, 0, sizeof(Entry<K, V>*) * M); //初始化各个桶
	delete lazyRemoval;
	lazyRemoval = new Bitmap(M);

	for (int i = 0; i < old_capacity; i++)
	{
		if (old_ht[i])
			put(old_ht[i]->key, old_ht[i]->value);
	}
	delete old_ht;
}

