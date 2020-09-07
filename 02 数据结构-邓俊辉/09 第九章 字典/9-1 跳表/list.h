#pragma once
#include "listNode.h"
#include<ctime>
#include<iostream>
template<typename T>
class List
{
private:
	//-----------------------------------���ݱ���---------------------------------------------
	int _size; //��ģ
	ListNodePosi(T) header; //ͷ�ڱ�
	ListNodePosi(T) tailer; //β�ڱ�
	//-----------------------------------���ݱ����������---------------------------------------------


protected:
	//-----------------------------------���ߺ���---------------------------------------------
	void init(); //��ʼ������
	void copyNodes(ListNodePosi(T) p, int n); //��ĳ����㿪ʼ������n����㵽�б�����
	void clear();//������н��
	void swap(T& a, T& b);
	//-----------------------------------���ߺ����������---------------------------------------------



public:
	//-----------------------------------����Ϳ��ƺ���---------------------------------------------
	List() { init(); } //���캯��
	List(ListNodePosi(T) p, int n); //�Ӹ�����㸴��n��Ԫ�أ��Թ���list
	List(const List<T>& lst); //ͨ�������б���и��ƹ���
	List(const List<T>& lst, int r, int n); //����[r,n)���б�
	~List();//��������
	//-----------------------------------����Ϳ��ƺ����������---------------------------------------------


	//-----------------------------------���ܺ���---------------------------------------------
	int size()const { return _size; } //��ģ
	bool empty()const { return _size <= 0; } //�Ƿ�Ϊ��
	ListNodePosi(T)& first()const; //�����׽��
	ListNodePosi(T)& last()const; //����β���
	T& operator[](int r)const; //�±����������
	ListNodePosi(T) find(const T& e,int n, ListNodePosi(T)p)const; //��ĳ�����p��n��ǰ������У������Ƿ����ĳ��Ԫ��e
	ListNodePosi(T)find(const T& e)const {return find(e,_size,tailer); } //����
	ListNodePosi(T) insertAsFirst(const T& e);//����һ���½����Ϊ�׽��
	ListNodePosi(T) insertAsLast(const T& e); //����һ���½����Ϊĩ���
	ListNodePosi(T) insertBefore(ListNodePosi(T) p, const T& e); //�ڸ������ǰ�����½��
	ListNodePosi(T) insertAfter(ListNodePosi(T) p, const T& e); //�ڸ�����������½��
	T remove(ListNodePosi(T)p); //ɾ����㣬�����ؽ���ֵ
	void deduplicate(); //�����б��ȥ��
	void uniquify();//�����б��ȥ��
	ListNodePosi(T) search(const T& elem, int n, ListNodePosi(T) P)const;//������ң�Ч��û������������κ����
	ListNodePosi(T)search(const T& e)const { return search(e, _size, tailer); } //�������
	ListNodePosi(T) selectMax(ListNodePosi(T) p, int n); //�ӽ��P��ʼ����n��������ҵ������Ǹ�
	bool lessthan(T a, T b) { return a < b; }//aС��b
	void sort(ListNodePosi(T) p, int n);//����
	void sort() { sort(first(), _size); }//����
	void selectSortA(ListNodePosi(T) p,int n); //ѡ������汾A
	void selectSortB(ListNodePosi(T) p, int n); //ѡ������汾B
	void insertSort(ListNodePosi(T)p, int n); //��������
	void mergeSort(ListNodePosi(T)&p, int n); //�鲢����ʧ���ˣ�ûд�ɹ�
	void merge(ListNodePosi(T)&p,int n,List<T>& L,ListNodePosi(T)q, int m); //��·�鲢�㷨
	void reverse(); //�б�Ԫ��ǰ����

	//-----------------------------------���ܺ����������---------------------------------------------
};



//-----------------------------------------------����Ϳ��ƺ���-------------------------------------------
template<typename T> //���캯��
List<T>::List(ListNodePosi(T) p, int n)
{
	copyNodes(p, n);
}
template<typename T> //�������캯��
List<T>::List(const List<T>& lst)
{
	copyNodes(lst.first(), lst.size());
}
template<typename T> //���캯��
List<T>::List(const List<T>& lst, int r, int n)
{
	copyNodes(lst[r], n);
}

template<typename T> 
List<T>::~List() //��������
{
	clear();
	delete header;
	delete tailer;

}
//-------------------------------------------------���ߺ���-------------------------------------------------

template<typename T>
void List<T>::init() //��ʼ������
{
	header = new ListNode<T>;
	tailer = new ListNode<T>;
	
	header->pred = nullptr;
	header->succ = tailer;

	tailer->pred = header;
	tailer->succ = nullptr;

	_size = 0;

}

template<typename T>
void List<T>::copyNodes(ListNodePosi(T)p,int n)//��ĳ����㿪ʼ������n����㵽�б�����
{
	init();
	while (n--)
	{
		this->insertAsLast(p->data);
	}
}
template<typename T>
void List<T>::clear() //������н��
{
	while (_size>0)
	{
		remove(header->succ);
	}
}

template<typename T>
void List<T>::swap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}
//------------------------------------------------���ܺ���--------------------------------------------------
template<typename T> //�׽ڵ�
ListNodePosi(T)& List<T>::first()const
{
	return header->succ;
}

template<typename T>
ListNodePosi(T)& List<T>::last()const //ĩ���
{
	return tailer->pred;
}

template<typename T>
T& List<T>::operator[](int r)const //�±������������
{
	ListNodePosi(T) ptr = this->first();
	while (0 < r--)
	{
		ptr = ptr->succ;
	}
	return ptr->data;
}
template<typename T>
ListNodePosi(T) List<T>::find(const T& e, int n, ListNodePosi(T) p)const //����
{
	while (0 < n--)
	{
		if (e == ((p = p->pred)->data))return p;//�ڽ��p��n��ǰ������У�Ѱ���Ƿ����Ԫ��e

	}
	return nullptr;
}
template<typename T>
ListNodePosi(T) List<T>::insertAsFirst(const T& e)//����һ���½����Ϊ�׽��
{
	_size++;
	return header->insertAsSucc(e);
}

template<typename T>
ListNodePosi(T)  List<T>::insertAsLast(const T& e)//����һ���½����Ϊĩ���
{
	_size++;
	return tailer->insertAsPred(e);
}
template<typename T>
ListNodePosi(T)  List<T>::insertBefore(ListNodePosi(T) p, const T& e)//�ڸ������ǰ�����½��
{
	_size++;
	return p->insertAsPred(e);
}
template<typename T>
ListNodePosi(T)  List<T>::insertAfter(ListNodePosi(T) p, const T& e)//�ڸ�����������½��
{
	_size++;
	return p->insertAsSucc(e);
}
template<typename T>
T List<T>::remove(ListNodePosi(T) p)
{
	T elem = p->data;

	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	delete p;
	_size--;
	return elem;
}

template<typename T>
void List<T>::deduplicate() //�����б�ȥ��
{
	if (_size < 2)return;
	ListNodePosi(T) p = this->first();
	int r = 1;
	while (tailer != (p = p->succ))
	{
		ListNodePosi(T) q = find(p->data, r, p);
		q ? remove(q) : r++;
	}
}

template<typename T>
void List<T>::uniquify()  //�����б�ȥ��
{
	if (_size < 2)return;
	ListNodePosi(T) p = this->first();
	ListNodePosi(T) q;
	while (tailer != (q = p->succ))
	{
		if (p->data != q->data)p = q;
		else remove(q);
	}

}
template<typename T>
ListNodePosi(T) List<T>::search(const T& elem,int n,ListNodePosi(T) p) const //�ҵ�������e�����һ�����
{
	while (0 <= n--)
	{
		if ((p = p->pred)->data <= elem)break;
	}
	return p;
}

template<typename T>
ListNodePosi(T)List<T>::selectMax(ListNodePosi(T) p, int n) //�ӽ��p���n�������ѡ�����ķ���
{
	ListNodePosi(T) max = p;
	for (ListNodePosi(T)cur = p; n > 1; n--)
	{
		if (!lessthan((cur = cur->succ)->data, max->data))max = cur; //���ڵ���max������и���
	}
	return max;
}

template<typename T>
void List<T>::sort(ListNodePosi(T) p, int n) //����
{
	srand(time(0));
	int tag = rand() % 3;
	switch (tag)
	{
	case 0:
		selectSortA(p, n);
		break;
	case 1:
		selectSortB(p, n);
		break;
	case 2:
		insertSort(p, n);
		break;
	
	}
}

template<typename T>
void List<T>::selectSortA(ListNodePosi(T) p, int n) //ѡ������汾A
{
	ListNodePosi(T) head = p->pred;
	ListNodePosi(T) tail = p;
	for (int i = 0; i < n;i++)tail = tail->succ; //��(head,tail)��Χ�ڽ���ѡ������
	for (int i = n; i > 1; i--)
	{
		insertBefore(tail, remove(selectMax(head->succ, i)));
		tail = tail->pred;
	}
	
}
template<typename T>
void List<T>::selectSortB(ListNodePosi(T) p, int n) //ѡ������汾B
{
	ListNodePosi(T) head = p->pred;
	ListNodePosi(T) tail = p;
	for (int i = 0; i < n; i++)tail = tail->succ; //��(head,tail)��Χ�ڽ���ѡ������
	for (int i = n; i > 1; i--)
	{
		ListNodePosi(T) max = selectMax(head->succ, i);
		swap(max->data, tail->pred->data);
		tail = tail->pred;
	}

}
template<typename T>
void List<T>::insertSort(ListNodePosi(T)p, int n) //��������
{

	for (int i = 0; i < n; i++)
	{
		insertAfter(search(p->data, i, p), p->data);
		p = p->succ;
		remove(p->pred);
	}
}

//List�Ĺ鲢���򲻺��ã�������
template<typename T>
void List<T>::merge(ListNodePosi(T)&p, int n,List<T>&L, ListNodePosi(T)q, int m) //��߽����n��Ԫ�غ��ұ߽����m��Ԫ�ؽ��ж�·�鲢
{
	ListNode<T> pp = *(p->pred); //����ǰ��ָ�룬��֤������p�ǵ�һ��Ԫ�أ��Ӷ���֤ͷ��㲻��
	//�ǳ���֣��������ListNodePosi(T)���ͣ�p=p->succ��һ�仰����ı�pp��ָ������
	//ListNodePosi(T) pp = p->pred;
	while (m > 0)
	{
		if ((n > 0) && (p->data <= q->data))
		{
			
			std::cout << "if" << std::endl;
			p = p->succ;
			
			if (q == p)break;//�ô�:(1)���p�������q�ˣ���������(2)���p������q��ִ��insertBefore��ʱ��p���Ǳ�ɾ��㣬�޷����иú���
			
			n--;
		}
		else
		{
		
			
			q = q->succ;

			T elem = L.remove(q->pred);
			
			insertBefore(p,elem ); //ΪʲôinsertBefore��ı�pָ����λ����?����p�����õ�ʱ���ı䣬p�������þͲ���䡣�����
			
			
			m--;
			
		}
	}
	
	//std::cout << "ppsuccdata"<<pp.succ->data << std::endl;
	p = pp.succ;
	//p = pp->succ;
}

template<typename T>
void List<T>::mergeSort(ListNodePosi(T)& p, int n) //�鲢����
{
	if (n < 2)return; //С��2�����ֵ�ʱ���Լ����򣬷���
	int m = (n >> 1); //ȡ�м�
	ListNodePosi(T) q = p;
	for (int i = 0; i < m; i++)
	{
		q = q->succ;
	}

	
mergeSort(p, m); mergeSort(q, n - m); //��ǰ���б�鲢����
	merge(p, m,*this,q, n - m);//���ֹ鲢�㷨
}

template<typename T>
void List<T>::reverse()
{
	ListNodePosi(T) p = header;
	ListNodePosi(T) q = tailer;
	for (int i = 1; i < _size; i += 2)
	{
		swap((p = p->succ)->data, (q = q->pred)->data);
	}
}