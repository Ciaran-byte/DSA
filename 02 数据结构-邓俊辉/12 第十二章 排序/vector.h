
#pragma once

#define DefaultCapacity 3
#include<ctime>
#include<iostream>
#include "Fib.h"
#include "HeapComplete.h"


template <typename T>
class vector
{
	
public:

	//--------------------------------------------控制函数---------------------------------------------
	//构造函数
	vector(int s = 0, int c = DefaultCapacity, T v = 0)//默认构造函数
	{
		_elem = new T[_capacity = c];
		_size = s;
		for (int i = 0; i < _size; i++)
		{
			_elem[i] = v;
		}
	}
	vector(const T* elem, int size) { CopyFrom(elem, 0, size); } //数组整体拷贝
	vector(const T* elem, int l, int h) { CopyFrom(elem, l, h); }//数组局部拷贝
	vector(const vector<T>& v) { CopyFrom(v._elem, 0, v._size); }//向量拷贝构造函数
	vector(const vector<T>& v, int l, int h) { CopyFrom(v._elem, l, h); }//向量局部拷贝
	//拷贝复制函数
	vector<T>& operator=(const vector<T>&);
	//析构
	~vector() { delete[] _elem; }

	//--------------------------------------------控制函数结束---------------------------------------------



	//--------------------------------------------功能函数--------------------------------------------
	inline int size() const { return _size; } //长度
	inline bool empty() const { return !_size; } //是否为空
	T& operator[](int r)const;
	void unsort(int l, int h); //打乱l到h区间的数字
	void unsort() { unsort(0, _size); }
	int find(const T& elem,int l, int h)const; //静态查找
	int find(const T& elem)const { return find(elem, 0, _size); }
	int search(const T& elem, int l, int h)const;//有序查找
	int search(const T& elem)const { return search(elem, 0, _size); }
	int binSearchA(const T& elem, int l, int h)const;//二分查找A
	int binSearchB(const T& elem, int l, int h)const; //二分查找版本B
	int binSearchC(const T& elem, int l, int h)const; //二分查找版本C
	int fibSearch(const T& elem, int l, int h)const; //斐波那契查找
	int insertSearch(const T& elem, int l, int h)const;//插值查找
	void sort(int l, int h); //排序算法
	void sort() { sort(0, _size); }
	void bubbleSortA(int l, int h);//比较低效的冒泡排序
	bool bubbleA(int l, int h);//低效冒泡排序内循环
	void bubbleSortB(int l, int h); //比较高效的冒泡排序
	int bubbleB(int l, int h); //高效冒泡排序外循环
	void mergeSort(int l, int h); //归并排序
	void merge(int l, int m, int h); //二路归并算法
	void selectSort(int l, int h); //选择排序
	void heapSort(int l, int h); //堆排序
	int selectMax(int l, int h);//选择最大值
	int selectMax() { selectMax(0, _size); }//全局选择最大值
	void insertSort(int l, int h); //插入排序
	void quickSortA(int l, int h); //快速排序版本A
	void quickSortB(int l, int h);// 快速排序版本B
	int partitionA(int l, int h); //构造轴点
	int partitionB(int l, int h); //构造轴点
	int insert(const T& elem, int r); //插入元素
	int insert(const T& elem) { return insert(elem, size()); }
	int remove(int l, int h); //删除区间内的元素
	T remove(int r) { T e = _elem[r]; remove(r, r + 1); return e; } //删除单个元素
	void deduplicate();//无序向量去重
	void traverse(void (*visit)(T& t));//遍历操作
	template<typename VST> void traverse(VST& visit); //函数对象的遍历操作
	bool disorder()const; //判断函数是否已经从小到大排序完成
	void unique(); //有序向量去重
	

	//--------------------------------------------功能函数结束--------------------------------------------


protected:
	//--------------------------------------------数据定义--------------------------------------------
	int _size; //定义数据长度
	int _capacity; //定义容量
	T* _elem; //定义数据
	//--------------------------------------------数据定义结束--------------------------------------------



	//--------------------------------------------工具函数--------------------------------------------
	inline void CopyFrom(const T* elem, int l, int h);//拷贝数组
	void expand(); //扩容
	void shrink(); //缩容
	void swap(T& lhs, T& rhs); //交换数组元素
	bool lessthan(T a, T b) { return a < b; } //a小于b
	//--------------------------------------------工具函数结束--------------------------------------------
	
};



//------------------------------------------------------控制函数--------------------------
template<typename T>
vector<T>& vector<T>::operator=(const vector<T>& rhs)//拷贝复制
{
	if (this->_elem != rhs._elem)
	{
		if (_elem)
		{
			delete[]_elem;
		}
	
		CopyFrom(rhs._elem, 0, rhs._size);
	}
	return *this;
}

//------------------------------------------功能函数------------------------------------------------
template<typename T>
T& vector<T>::operator[](int r)const
{
	return this->_elem[r];
}

template<typename T>
void vector<T>::unsort(int l, int h) //打乱顺序
{
	srand(time(0));
	T* elem = _elem + l;
	for (int i = h - l; i > 0; i--)
	{
		swap(elem[i-1], elem[rand() % i]);
	}
}
template<typename T>
int vector<T>::find(const T& elem, int l, int h)const //静态查找
{
	while ((l < h--) && _elem[h] != elem);
	return h;
}
template<typename T>
int vector<T>::insert(const T& elem, int r)//插入元素
{
	expand(); //先检查有没有必要扩容
	_size++;
	for (int i = _size - 1; i > r; i--)
	{
		_elem[i] = _elem[i - 1];
	}
	_elem[r] = elem;
	return r;
}
template<typename T>
int vector<T>::remove(int l, int h) //删除区间内的元素[l,h)
{
	if (l == h)return 0;
	while (h < _size)
	{
		_elem[l++] = _elem[h++];
	}
	_size = l;
	shrink();
	return h - l;
}
template<typename T>
void vector<T>::deduplicate() //无序去重
{
	int i = 1;
	while (i < _size)
	{
		find(_elem[i], 0, i) < 0 ? i++: remove(i);
	}
}
template<typename T>
void vector<T>::traverse(void(*visit)(T& t))//利用函数指针，实现遍历操作
{
	for (int i = 0; i < _size; i++)
	{
		visit(_elem[i]);
	}
}
template<typename T> template<typename VST>
void vector<T>::traverse(VST& visit) //遍历
{
	for (int i = 0; i < _size; i++)
	{
		visit(_elem[i]);
	}
}

template<typename T>
bool vector<T>::disorder()const //判断是否从小到大排序
{
	for (int i = 1; i < _size; i++)
	{
		if (_elem[i] < _elem[i - 1])
		{
			return false;
		}
	}
	return true;
}

template<typename T>
void vector<T>::unique() //有序向量的去重
{
	int i = 0;
	int j = 0;
	while (++j < _size)
	{
		if (_elem[i] != _elem[j])
		{
			_elem[++i] = _elem[j];
		}
	}
	_size = ++i;
	shrink();
}
template<typename T>
int vector<T>::search(const T& elem, int l, int h)const
{
	srand(time(0));
	int tag = rand() %5;
	
	switch (tag)
	{
	case 0:
		return binSearchA(elem, l, h);
		
	case 1:
		return binSearchB(elem, l, h);
		
	case 2:
		return binSearchC(elem, l, h);
		
	case 3:
		return fibSearch(elem, l, h);
	default:
		return insertSearch(elem, l, h);
	}

}
template<typename T>
int vector<T>::binSearchA(const T& elem, int l, int h)const //二分查找版本A
{
	while (l < h)
	{
		int mid = (l + h) >> 1;  //分了比elem小，等于elem和大于elem三种情况，三分迭代
		if (_elem[mid] < elem)
		{
			l = mid;
		}
		else if (_elem[mid] > elem)
		{
			h = mid - 1;
		}
		else return mid;
	}
	return -1;
}

template<typename T>
int vector<T>::binSearchB(const T& elem, int l, int h)const //二分查找版本B
{
	while (h - l > 1) //分了比elem小和不小于elem两种情况，进行二分迭代
	{
		int mid = (l + h) >> 1;
		(_elem[mid] > elem) ? h = mid : l = mid;

	}
	return (_elem[l] == elem) ? l : -1;
}

template<typename T>
int vector<T>::binSearchC(const T& elem, int l, int h)const //二分查找版本C
{
	while (l < h)
	{
		int mid = (l + h) >> 1;
		( elem<_elem[mid]) ? h = mid : l = mid+1;
	}
	return --l; //进行二分迭代，并且返回不大于elem的最左边的元素
}

template<typename T>
int vector<T>::fibSearch(const T& elem, int l, int h)const //斐波那契查找
{
	Fib f(h - l); 
	while (l < h)
	{
		while ((h - 1) < f.get())f.prev();
		int mid = l+f.get() - 1;
		if (_elem[mid] > elem)
		{
			h = mid;
		}
		else if (_elem[mid] < elem)
		{
			l = mid + 1;
		}
		else return mid;
	}
	return -1;
}

template<typename T>
int vector<T>::insertSearch(const T& elem, int l, int h)const //插值查找
{
	while (l < h)
	{
		int mid = l + ((elem - _elem[l]) / (_elem[h] - _elem[l])) * (h - l); //如果是区间分布均匀的向量，插值查找效率高
		if (elem < _elem[mid])
		{
			h = mid;
		}
		else if (elem > _elem[mid])
		{
			l = mid + 1;
		}
		else
		{
			return mid;
		}
	}
	return -1;
}
template<typename T>
void vector<T>::sort(int l, int h) //排序算法
{
	srand(time(0));
	int n = rand() % 4;
	switch (n)
	{
	case 0:
		bubbleSortA(l, h);
		break;
	case 1:
		bubbleSortB(l, h);
		break;
	case 2:
		mergeSort(l, h);
		break;
	case 3:
		selectSort(l, h);
		break;
	case 4:
		insertSort(l, h);
		break;
	}
}
template<typename T>
void vector<T>::bubbleSortA(int l, int h) //低效的冒泡排序
{
	while (!bubbleA(l, h--));
}

template<typename T>
bool vector<T>::bubbleA(int l, int h) //低效冒泡排序内循环
{
	bool sorted = true; //低效的原因是，只能检测出后面全部排序完成的情况，如果前面具有部分元素完全有序，是检查不出来的

	while (++l < h)
	{
		if (_elem[l - 1] > _elem[l])
		{
			swap(_elem[l - 1], _elem[l ]);
			sorted = false; //通过检测整个向量是否具有逆序对了，如果没有逆序对，就排序结束
		}
	}
	return sorted;

}
template<typename T>
void vector<T>::bubbleSortB(int l, int h) //高效的冒泡排序
{
	while (l < (h = bubbleB(l, h)));
}

template<typename T>
int vector<T>::bubbleB(int l, int h) //高效的冒泡排序内循环
{
	int last = l;
	while (++l < h) //通过检测最后一次交换发生在什么地方，借此判断出最后一次交换的后面全部的元素，都已经有序。能提高效率
	{
		if (_elem[l - 1] > _elem[l])
		{
			swap(_elem[l - 1], _elem[l]);
			last = l;
		}
	}
	return last;

}

template<typename T>
void vector<T>::mergeSort(int l, int h) //归并排序[l,h)的归并排序
{
	if (h-l<2)return;
	int m = (l + h) >> 1;
	mergeSort(l, m); mergeSort(m, h); //归并排序使得每一个左闭右开区间都剩下一个元素
	merge(l, m, h);
}

template<typename T>
void vector<T>::merge(int l, int m, int h) //二路归并算法
{
	T* A = _elem + l; //原始向量的元素
	int lb = m - l;//做区间[l,m)的长度
	T* B = new T[lb]; //拷贝左半区间到缓冲区
	for (int i = 0; i < lb; B[i] = A[i++]);
	T* C = _elem + m; //右边区间不单独开辟空间，因为排序过程中元素不会被覆盖
	int lc = h - m; //右边区间[m,h)的长度

	for (int j = 0, k = 0, i = 0; (j < lb) || (k < lc);) //j是左区间游标，k是右区间游标，i是原来也是最终向量元素的游标
	{
		if (j < lb && (!(k < lc) || B[j] <= C[k])) A[i++] = B[j++];
		if (k < lc && (!(j < lb) || C[k] < B[j]))A[i++] = C[k++];
	}
	delete[]B;
}

template<typename T>
void vector<T>::selectSort(int l, int h) //选择排序
{
	for (int i = h; i > l+1; i--)
	{
		int max = selectMax(l, i); //选出[l,i)的最大值的下标
		swap(_elem[max], _elem[i-1]); //不断把前面的检测出来的最大值交换到后面

	}
}
template<typename T>
int vector<T>::selectMax(int l, int h) //选择[l,h)区间的最大值在哪
{
	int max = l;
	for (int i = l + 1; i < h; i++)
	{
		if (!lessthan(_elem[i], _elem[max])) max = i;
	}
	return max;
}
template<typename T>
void vector<T>::insertSort(int l, int h) //插入排序
{
	for (int i = l + 1; i < h; i++)//第一个元素不需要比较大小，直接放那就行
	{
		int rank=binSearchC(_elem[i], l, i); //在[l,i)的区间中，使用二分查找，搜索_elem[i]应该被插入到谁的后面
		int elem = _elem[i]; //保留一下_elem[i]的元素
		for (int j = i; j > rank+1; j--) //元素后移，把rank+1到i的元素全部后移一位
		{
			_elem[j] = _elem[j - 1];
		}
		_elem[rank+1] = elem; //rank的位置放入原来在i的元素
		
		

	}
}
template<typename T>
void vector<T>::heapSort(int l, int h) //堆排序
{
	//PQ_ComplHeap<T> H(_elem + l, h - l); //用向量中的数据建堆
	//while (!H.empty())
	//{
	//	_elem[--h] = H.delMax();
	//}

	T* A = _elem + l; int n = h - l; heapify(A, n); //将待排序区间建成一个完全二叉堆，O(n)
	while (0 < --n) //反复地摘除最大元并归入已排序的后缀，直至堆空
	{
		swap(A[0], A[n]); percolateDown(A, n, 0);
	} //堆顶与末元素对换，再下滤
}
template<typename T>
int vector<T>::partitionA(int l, int h)// [l,h]内找轴点
{
	
	swap(_elem[l], _elem[l + rand() % (h - l+1 )]); //把首字母和随机一个元素进行交换

	T pivot = _elem[l]; //首元素作为轴点
	
	while (l < h)
	{
		while (l<h&&_elem[h] >= pivot)h--;
		_elem[l] = _elem[h];
		while (l<h&&_elem[l] <= pivot)l++;
		_elem[h] = _elem[l];
	}
	_elem[l] = pivot;
	return l;

}
template<typename T>
void vector<T>::quickSortA(int l, int h)
{
	if (h - l < 2)return;//[l,h)
	int mi = partitionA(l, h - 1); //在[l,h-1]构造轴点
	quickSortA(l, mi);
	quickSortA(mi + 1, h);
}


template<typename T>
int vector<T>::partitionB(int l, int h)// [l,h]内找轴点
{

	swap(_elem[l], _elem[l + rand() % (h - l + 1)]); //把首字母和随机一个元素进行交换

	T pivot = _elem[l]; //首元素作为轴点

	while (l < h)
	{
		while (l < h)
		{
			if (_elem[h] >= pivot)
			{
				h--;
			}
			else
			{
				_elem[l++] = _elem[h];
				break;
			}
		}
		while (l < h)
		{
			if (_elem[l] <= pivot)
			{
				l++;
			}
			else
			{
				_elem[h--] = _elem[l];
				break;
			}
		}
	}
	_elem[l] = pivot;
	return l;

}


template<typename T>
void vector<T>::quickSortB(int l, int h)
{
	if (h - l < 2)return;//[l,h)
	int mi = partitionB(l, h - 1); //在[l,h-1]构造轴点
	quickSortB(l, mi);
	quickSortB(mi + 1, h);
}
//------------------------------------------------------工具函数--------------------------
template<typename T>
inline void vector<T>::CopyFrom(const T* elem, int l, int h) //拷贝数组[l,h)
{
	_elem = new T[_capacity=2*(h-l)];//申请空间，并且容量等于二倍的输入长度
	_size = 0; //清空数组长度
	while (l < h)
	{
		_elem[_size++] = elem[l++];
	}

}

template<typename T>
void vector<T>::expand()//扩容
{
	if (_size < _capacity)return; //不到该扩的时候不运行
	if (_capacity < DefaultCapacity)_capacity = DefaultCapacity; //容量不小于默认容量
	T* oleElem = _elem;
	_elem = new T[_capacity <<= 1]; //二倍扩容
	for (int i = 0; i < this->size(); i++)
	{
		_elem[i] = oleElem[i];
	}
	delete[] oleElem;
	

}
template<typename T>
void vector<T>::shrink()//缩容
{
	if (_size  < DefaultCapacity<<1)return; //容量不会小于默认容量
	if (_size << 2 < _capacity) //装填因子小于0.25的时候，会开始缩容
	{
		T* oldElem = _elem;
		_elem = new T[_capacity >> 1]; //缩容一半
		for (int i = 0; i < _size; i++)
		{
			_elem[i] = oldElem[i];
		}
		delete []oldElem;
	}
}
template<typename T>
void vector<T>::swap(T& lhs, T& rhs) //交换数组元素
{
	T temp = rhs;
	rhs = lhs;
	lhs = temp;
}


