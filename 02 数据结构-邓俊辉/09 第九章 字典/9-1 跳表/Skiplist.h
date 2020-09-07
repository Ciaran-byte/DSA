#pragma once
#include "list.h"
#include "Entry.h"
#include "Quadlist.h"
#include "Dictionary.h"
#include<iostream>
#include<ctime>

template<typename K,typename V>
class Skiplist :public Dictionary<K, V>, public List<Quadlist<Entry<K, V>>*>
{
protected:
	bool skipSearch(
		ListNode<Quadlist<Entry<K, V>>*>*& qlist,  //从指定层开始搜索
		QuadlistNode<Entry<K, V>>*& p,  //该层某个结点开始搜索
		K& k //搜索关键码k
	); 
public:
	int size()const { return this->empty()?0:this->last()->data->size(); } //返回底层Quadlist的规模
	int level() { return List::size(); }//返回层高
	bool put(K, V); //插入操作
	V* get(K k); //读取操作
	bool remove(K k); //删除操作

};

template<typename K,typename V>
V* Skiplist<K, V>::get(K k)
{
	if (this->empty())return nullptr;
	ListNode<Quadlist<Entry<K, V>>*>* qlist = this->first();  //从顶层开始查找
	QuadlistNode<Entry<K, V>>* p = qlist->data->first(); //从顶层的第一个结点开始查找
	return skipSearch(qlist, p, k) ? &(p->entry.value) : nullptr; //如果找到了，返回这个结点是值
}

//------------------------------------------skipSearch------------------------------------------------------
//说明:用于跳表查找的工具函数
//输入：qlist为顶层列表，p为qlist的首结点
// 输出: 若成功，p为找到的那个结点的塔顶结点，qlist为该层的四联表。如果失败，p是不大于k的最右边结点，qlist为空
//约定：如果有多个词条命中，返回四联表的最后一个
template<typename K,typename V>
bool Skiplist<K, V>::skipSearch
(
	ListNode<Quadlist<Entry<K, V>>*>*& qlist, //指定层
	QuadlistNode<Entry<K, V>>*& p, //指定层的指定结点
	K& k //要查找的元素
)
{
	while (true)
	{
		while (p->succ && p->entry.key <= k) //如果该层结点p还没有变成tailer或者，p还没有超过k，继续往前搜索
		{
			p = p->succ;
		}
		p = p->pred; //如果停止，要么p是tailer，要么p以及大于k了，找他前面一个
		//判断p是否是搜索到了的那个结点
		if(p->pred&&k==p->entry.key)//只有p不是header，才能进行查找
		{
			return true;
		}
		//如果p并不是要找的点，我们往下一层搜索
		qlist = qlist->succ;//如果qlist以及是最后一层了，qlist->succ就是tailer
		if (!qlist->succ)return false;  //如果qlist以及是tailer了，没有可以查找的元素了，返回false
		p = (p->pred) ? p->below : qlist->data->first(); //如果p不是header，直接往下一层，如果是header，就等于现在qlist层的首元素

	}
}
//-----------------------------------skipSearch 结束-------------------------------------------------------------------

template<typename K,typename V>
bool Skiplist<K, V>::put(K k, V v)
{
	srand(time(0));
	Entry<K, V> e = Entry<K, V>(k, v); //创建新的词条

	if (this->empty())this->insertAsFirst(new Quadlist<Entry<K, V>>); //如果跳表高度为0，就插入一层
	ListNode<Quadlist<Entry<K, V>>*>* qlist = this->first(); //最上层
	QuadlistNode<Entry<K, V>>* p = qlist->data->first(); //首个结点
	if (skipSearch(qlist, p,k)) //如果找到一样的，就把p移动到最底层，插入时插入到p的右边
	{
		while (p->below)p = p->below;
	}

	qlist = this->last(); //插入结点是从最底层开始插入的
	QuadlistNode<Entry<K, V>>* b= qlist->data->insertAfterabove(e, p); //在最底层p后面插入e结点，below默认是nullptr

	while (rand() & 1) //凭概率增加跳表的高度
	{
		while (qlist->data->valid(p) && !p->above)p = p->pred; //p本来是插入结点b的前一个结点，现在往前找，找到高度比当前层高的最近结点，用于在上一层插入结点
		if (!qlist->data->valid(p)) //如果结点p是header了
		{
			if (qlist== this->first()) //并且当前已经在跳表的第一层了
			{
				this->insertAsFirst(new Quadlist<Entry<K, V>>);
			}
			p = qlist->pred->data->first()->pred;
		}
		else //如果不是header，往上面找一层即可
		{
			p = p->above;
		}
		qlist = qlist->pred;
		b = qlist->data->insertAfterabove(e,p, b);
		


	}
	return true;
}


template<typename K,typename V>
bool Skiplist<K, V>::remove(K k)//删除操作
{
	if (this->empty())return false; //如果已经空了
	ListNode<Quadlist<Entry<K, V>>*>* qlist = this->first(); //首层
	QuadlistNode<Entry<K, V>>* p = qlist->data->first(); //首结点
	if (!skipSearch(qlist, p, k)) //找不到，返回false
	{
		return false;
	}

	do
	{
		QuadlistNode<Entry<K, V>>* lower = p->below;
		qlist->data->remove(p);
		p = lower;
		qlist = qlist->succ;

	} while (qlist->succ);

	while (!this->empty() && this->first()->data->empty())//如果经过删除操作以后，顶层空了，要把顶层删除
	{
		List<Quadlist<Entry<K, V>>*>::remove(this->first());
	}
	return true;
}

