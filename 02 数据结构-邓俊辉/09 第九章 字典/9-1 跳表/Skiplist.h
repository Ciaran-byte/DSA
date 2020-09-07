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
		ListNode<Quadlist<Entry<K, V>>*>*& qlist,  //��ָ���㿪ʼ����
		QuadlistNode<Entry<K, V>>*& p,  //�ò�ĳ����㿪ʼ����
		K& k //�����ؼ���k
	); 
public:
	int size()const { return this->empty()?0:this->last()->data->size(); } //���صײ�Quadlist�Ĺ�ģ
	int level() { return List::size(); }//���ز��
	bool put(K, V); //�������
	V* get(K k); //��ȡ����
	bool remove(K k); //ɾ������

};

template<typename K,typename V>
V* Skiplist<K, V>::get(K k)
{
	if (this->empty())return nullptr;
	ListNode<Quadlist<Entry<K, V>>*>* qlist = this->first();  //�Ӷ��㿪ʼ����
	QuadlistNode<Entry<K, V>>* p = qlist->data->first(); //�Ӷ���ĵ�һ����㿪ʼ����
	return skipSearch(qlist, p, k) ? &(p->entry.value) : nullptr; //����ҵ��ˣ�������������ֵ
}

//------------------------------------------skipSearch------------------------------------------------------
//˵��:����������ҵĹ��ߺ���
//���룺qlistΪ�����б�pΪqlist���׽��
// ���: ���ɹ���pΪ�ҵ����Ǹ�����������㣬qlistΪ�ò�����������ʧ�ܣ�p�ǲ�����k�����ұ߽�㣬qlistΪ��
//Լ��������ж���������У���������������һ��
template<typename K,typename V>
bool Skiplist<K, V>::skipSearch
(
	ListNode<Quadlist<Entry<K, V>>*>*& qlist, //ָ����
	QuadlistNode<Entry<K, V>>*& p, //ָ�����ָ�����
	K& k //Ҫ���ҵ�Ԫ��
)
{
	while (true)
	{
		while (p->succ && p->entry.key <= k) //����ò���p��û�б��tailer���ߣ�p��û�г���k��������ǰ����
		{
			p = p->succ;
		}
		p = p->pred; //���ֹͣ��Ҫôp��tailer��Ҫôp�Լ�����k�ˣ�����ǰ��һ��
		//�ж�p�Ƿ����������˵��Ǹ����
		if(p->pred&&k==p->entry.key)//ֻ��p����header�����ܽ��в���
		{
			return true;
		}
		//���p������Ҫ�ҵĵ㣬��������һ������
		qlist = qlist->succ;//���qlist�Լ������һ���ˣ�qlist->succ����tailer
		if (!qlist->succ)return false;  //���qlist�Լ���tailer�ˣ�û�п��Բ��ҵ�Ԫ���ˣ�����false
		p = (p->pred) ? p->below : qlist->data->first(); //���p����header��ֱ������һ�㣬�����header���͵�������qlist�����Ԫ��

	}
}
//-----------------------------------skipSearch ����-------------------------------------------------------------------

template<typename K,typename V>
bool Skiplist<K, V>::put(K k, V v)
{
	srand(time(0));
	Entry<K, V> e = Entry<K, V>(k, v); //�����µĴ���

	if (this->empty())this->insertAsFirst(new Quadlist<Entry<K, V>>); //�������߶�Ϊ0���Ͳ���һ��
	ListNode<Quadlist<Entry<K, V>>*>* qlist = this->first(); //���ϲ�
	QuadlistNode<Entry<K, V>>* p = qlist->data->first(); //�׸����
	if (skipSearch(qlist, p,k)) //����ҵ�һ���ģ��Ͱ�p�ƶ�����ײ㣬����ʱ���뵽p���ұ�
	{
		while (p->below)p = p->below;
	}

	qlist = this->last(); //�������Ǵ���ײ㿪ʼ�����
	QuadlistNode<Entry<K, V>>* b= qlist->data->insertAfterabove(e, p); //����ײ�p�������e��㣬belowĬ����nullptr

	while (rand() & 1) //ƾ������������ĸ߶�
	{
		while (qlist->data->valid(p) && !p->above)p = p->pred; //p�����ǲ�����b��ǰһ����㣬������ǰ�ң��ҵ��߶ȱȵ�ǰ��ߵ������㣬��������һ�������
		if (!qlist->data->valid(p)) //������p��header��
		{
			if (qlist== this->first()) //���ҵ�ǰ�Ѿ�������ĵ�һ����
			{
				this->insertAsFirst(new Quadlist<Entry<K, V>>);
			}
			p = qlist->pred->data->first()->pred;
		}
		else //�������header����������һ�㼴��
		{
			p = p->above;
		}
		qlist = qlist->pred;
		b = qlist->data->insertAfterabove(e,p, b);
		


	}
	return true;
}


template<typename K,typename V>
bool Skiplist<K, V>::remove(K k)//ɾ������
{
	if (this->empty())return false; //����Ѿ�����
	ListNode<Quadlist<Entry<K, V>>*>* qlist = this->first(); //�ײ�
	QuadlistNode<Entry<K, V>>* p = qlist->data->first(); //�׽��
	if (!skipSearch(qlist, p, k)) //�Ҳ���������false
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

	while (!this->empty() && this->first()->data->empty())//�������ɾ�������Ժ󣬶�����ˣ�Ҫ�Ѷ���ɾ��
	{
		List<Quadlist<Entry<K, V>>*>::remove(this->first());
	}
	return true;
}

