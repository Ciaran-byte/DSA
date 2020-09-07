#pragma once
#include "listNode.h"
#include<ctime>
#include<iostream>
template<typename T>
class List
{
private:
	//-----------------------------------数据变量---------------------------------------------
	int _size; //规模
	ListNodePosi(T) header; //头哨兵
	ListNodePosi(T) tailer; //尾哨兵
	//-----------------------------------数据变量定义结束---------------------------------------------


protected:
	//-----------------------------------工具函数---------------------------------------------
	void init(); //初始化函数
	void copyNodes(ListNodePosi(T) p, int n); //从某个结点开始，复制n个结点到列表的最后
	void clear();//清除所有结点
	void swap(T& a, T& b);
	//-----------------------------------工具函数定义结束---------------------------------------------



public:
	//-----------------------------------构造和控制函数---------------------------------------------
	List() { init(); } //构造函数
	List(ListNodePosi(T) p, int n); //从给定结点复制n个元素，以构造list
	List(const List<T>& lst); //通过给定列表进行复制构造
	List(const List<T>& lst, int r, int n); //复制[r,n)到列表
	~List();//析构函数
	//-----------------------------------构造和控制函数定义结束---------------------------------------------


	//-----------------------------------功能函数---------------------------------------------
	int size()const { return _size; } //规模
	bool empty()const { return _size <= 0; } //是否为空
	ListNodePosi(T)& first()const; //返回首结点
	ListNodePosi(T)& last()const; //返回尾结点
	T& operator[](int r)const; //下标运算符重载
	ListNodePosi(T) find(const T& e,int n, ListNodePosi(T)p)const; //在某个结点p的n个前驱结点中，查找是否具有某个元素e
	ListNodePosi(T)find(const T& e)const {return find(e,_size,tailer); } //查找
	ListNodePosi(T) insertAsFirst(const T& e);//插入一个新结点作为首结点
	ListNodePosi(T) insertAsLast(const T& e); //插入一个新结点作为末结点
	ListNodePosi(T) insertBefore(ListNodePosi(T) p, const T& e); //在给定结点前插入新结点
	ListNodePosi(T) insertAfter(ListNodePosi(T) p, const T& e); //在给定结点后插入新结点
	T remove(ListNodePosi(T)p); //删除结点，并返回结点的值
	void deduplicate(); //无序列表的去重
	void uniquify();//有序列表的去重
	ListNodePosi(T) search(const T& elem, int n, ListNodePosi(T) P)const;//有序查找，效率没比无序查找有任何提高
	ListNodePosi(T)search(const T& e)const { return search(e, _size, tailer); } //有序查找
	ListNodePosi(T) selectMax(ListNodePosi(T) p, int n); //从结点P开始往后n个结点中找到最大的那个
	bool lessthan(T a, T b) { return a < b; }//a小于b
	void sort(ListNodePosi(T) p, int n);//排序
	void sort() { sort(first(), _size); }//排序
	void selectSortA(ListNodePosi(T) p,int n); //选择排序版本A
	void selectSortB(ListNodePosi(T) p, int n); //选择排序版本B
	void insertSort(ListNodePosi(T)p, int n); //插入排序
	void mergeSort(ListNodePosi(T)&p, int n); //归并排序，失败了，没写成功
	void merge(ListNodePosi(T)&p,int n,List<T>& L,ListNodePosi(T)q, int m); //二路归并算法
	void reverse(); //列表元素前后倒置

	//-----------------------------------功能函数定义结束---------------------------------------------
};



//-----------------------------------------------构造和控制函数-------------------------------------------
template<typename T> //构造函数
List<T>::List(ListNodePosi(T) p, int n)
{
	copyNodes(p, n);
}
template<typename T> //拷贝构造函数
List<T>::List(const List<T>& lst)
{
	copyNodes(lst.first(), lst.size());
}
template<typename T> //构造函数
List<T>::List(const List<T>& lst, int r, int n)
{
	copyNodes(lst[r], n);
}

template<typename T> 
List<T>::~List() //析构函数
{
	clear();
	delete header;
	delete tailer;

}
//-------------------------------------------------工具函数-------------------------------------------------

template<typename T>
void List<T>::init() //初始化函数
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
void List<T>::copyNodes(ListNodePosi(T)p,int n)//从某个结点开始，复制n个结点到列表的最后
{
	init();
	while (n--)
	{
		this->insertAsLast(p->data);
	}
}
template<typename T>
void List<T>::clear() //清空所有结点
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
//------------------------------------------------功能函数--------------------------------------------------
template<typename T> //首节点
ListNodePosi(T)& List<T>::first()const
{
	return header->succ;
}

template<typename T>
ListNodePosi(T)& List<T>::last()const //末结点
{
	return tailer->pred;
}

template<typename T>
T& List<T>::operator[](int r)const //下标运算符的重载
{
	ListNodePosi(T) ptr = this->first();
	while (0 < r--)
	{
		ptr = ptr->succ;
	}
	return ptr->data;
}
template<typename T>
ListNodePosi(T) List<T>::find(const T& e, int n, ListNodePosi(T) p)const //查找
{
	while (0 < n--)
	{
		if (e == ((p = p->pred)->data))return p;//在结点p的n个前驱结点中，寻找是否存在元素e

	}
	return nullptr;
}
template<typename T>
ListNodePosi(T) List<T>::insertAsFirst(const T& e)//插入一个新结点作为首结点
{
	_size++;
	return header->insertAsSucc(e);
}

template<typename T>
ListNodePosi(T)  List<T>::insertAsLast(const T& e)//插入一个新结点作为末结点
{
	_size++;
	return tailer->insertAsPred(e);
}
template<typename T>
ListNodePosi(T)  List<T>::insertBefore(ListNodePosi(T) p, const T& e)//在给定结点前插入新结点
{
	_size++;
	return p->insertAsPred(e);
}
template<typename T>
ListNodePosi(T)  List<T>::insertAfter(ListNodePosi(T) p, const T& e)//在给定结点后插入新结点
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
void List<T>::deduplicate() //无序列表去重
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
void List<T>::uniquify()  //有序列表去重
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
ListNodePosi(T) List<T>::search(const T& elem,int n,ListNodePosi(T) p) const //找到不大于e的最后一个结点
{
	while (0 <= n--)
	{
		if ((p = p->pred)->data <= elem)break;
	}
	return p;
}

template<typename T>
ListNodePosi(T)List<T>::selectMax(ListNodePosi(T) p, int n) //从结点p后的n个结点中选择最大的返回
{
	ListNodePosi(T) max = p;
	for (ListNodePosi(T)cur = p; n > 1; n--)
	{
		if (!lessthan((cur = cur->succ)->data, max->data))max = cur; //大于等于max都会进行更新
	}
	return max;
}

template<typename T>
void List<T>::sort(ListNodePosi(T) p, int n) //排序
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
void List<T>::selectSortA(ListNodePosi(T) p, int n) //选择排序版本A
{
	ListNodePosi(T) head = p->pred;
	ListNodePosi(T) tail = p;
	for (int i = 0; i < n;i++)tail = tail->succ; //在(head,tail)范围内进行选择排序
	for (int i = n; i > 1; i--)
	{
		insertBefore(tail, remove(selectMax(head->succ, i)));
		tail = tail->pred;
	}
	
}
template<typename T>
void List<T>::selectSortB(ListNodePosi(T) p, int n) //选择排序版本B
{
	ListNodePosi(T) head = p->pred;
	ListNodePosi(T) tail = p;
	for (int i = 0; i < n; i++)tail = tail->succ; //在(head,tail)范围内进行选择排序
	for (int i = n; i > 1; i--)
	{
		ListNodePosi(T) max = selectMax(head->succ, i);
		swap(max->data, tail->pred->data);
		tail = tail->pred;
	}

}
template<typename T>
void List<T>::insertSort(ListNodePosi(T)p, int n) //插入排序
{

	for (int i = 0; i < n; i++)
	{
		insertAfter(search(p->data, i, p), p->data);
		p = p->succ;
		remove(p->pred);
	}
}

//List的归并排序不好用，放弃了
template<typename T>
void List<T>::merge(ListNodePosi(T)&p, int n,List<T>&L, ListNodePosi(T)q, int m) //左边结点后的n个元素和右边结点后的m个元素进行二路归并
{
	ListNode<T> pp = *(p->pred); //保留前驱指针，保证排序后的p是第一个元素，从而保证头结点不变
	//非常奇怪，如果用了ListNodePosi(T)类型，p=p->succ这一句话，会改变pp的指代对象
	//ListNodePosi(T) pp = p->pred;
	while (m > 0)
	{
		if ((n > 0) && (p->data <= q->data))
		{
			
			std::cout << "if" << std::endl;
			p = p->succ;
			
			if (q == p)break;//用处:(1)如果p后面就是q了，不用排了(2)如果p后面是q，执行insertBefore的时候，p就是被删结点，无法运行该函数
			
			n--;
		}
		else
		{
		
			
			q = q->succ;

			T elem = L.remove(q->pred);
			
			insertBefore(p,elem ); //为什么insertBefore会改变p指代的位置呢?好像p是引用的时候会改变，p不是引用就不会变。好奇怪
			
			
			m--;
			
		}
	}
	
	//std::cout << "ppsuccdata"<<pp.succ->data << std::endl;
	p = pp.succ;
	//p = pp->succ;
}

template<typename T>
void List<T>::mergeSort(ListNodePosi(T)& p, int n) //归并排序
{
	if (n < 2)return; //小于2个数字的时候，以及有序，返回
	int m = (n >> 1); //取中间
	ListNodePosi(T) q = p;
	for (int i = 0; i < m; i++)
	{
		q = q->succ;
	}

	
mergeSort(p, m); mergeSort(q, n - m); //对前后列表归并排序
	merge(p, m,*this,q, n - m);//二分归并算法
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