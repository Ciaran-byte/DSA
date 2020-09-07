#pragma once
#define DefaultCapacity 3
#include<ctime>
#include<iostream>
#include "Fib.h"
template <typename T>
class vector
{
	
public:

	//--------------------------------------------���ƺ���---------------------------------------------
	//���캯��
	vector(int s = 0, int c = DefaultCapacity, T v = 0)//Ĭ�Ϲ��캯��
	{
		_elem = new T[_capacity = c];
		_size = s;
		for (int i = 0; i < _size; i++)
		{
			_elem[i] = v;
		}
	}
	vector(const T* elem, int size) { CopyFrom(elem, 0, size); } //�������忽��
	vector(const T* elem, int l, int h) { CopyFrom(elem, l, h); }//����ֲ�����
	vector(const vector<T>& v) { CopyFrom(v._elem, 0, v._size); }//�����������캯��
	vector(const vector<T>& v, int l, int h) { CopyFrom(v._elem, l, h); }//�����ֲ�����
	//�������ƺ���
	vector<T>& operator=(const vector<T>&);
	//����
	~vector() { delete[] _elem; }

	//--------------------------------------------���ƺ�������---------------------------------------------



	//--------------------------------------------���ܺ���--------------------------------------------
	inline int size() const { return _size; } //����
	inline bool empty() const { return !_size; } //�Ƿ�Ϊ��
	T& operator[](int r)const;
	void unsort(int l, int h); //����l��h���������
	void unsort() { unsort(0, _size); }
	int find(const T& elem,int l, int h)const; //��̬����
	int find(const T& elem)const { return find(elem, 0, _size); }
	int search(const T& elem, int l, int h)const;//�������
	int search(const T& elem)const { return search(elem, 0, _size); }
	int binSearchA(const T& elem, int l, int h)const;//���ֲ���A
	int binSearchB(const T& elem, int l, int h)const; //���ֲ��Ұ汾B
	int binSearchC(const T& elem, int l, int h)const; //���ֲ��Ұ汾C
	int binSearchD(const T& elem)const { return  binSearchC(elem, 0,size()); }
	int fibSearch(const T& elem, int l, int h)const; //쳲���������
	int insertSearch(const T& elem, int l, int h)const;//��ֵ����
	void sort(int l, int h); //�����㷨
	void sort() { sort(0, _size); }
	void bubbleSortA(int l, int h);//�Ƚϵ�Ч��ð������
	bool bubbleA(int l, int h);//��Чð��������ѭ��
	void bubbleSortB(int l, int h); //�Ƚϸ�Ч��ð������
	int bubbleB(int l, int h); //��Чð��������ѭ��
	void mergeSort(int l, int h); //�鲢����
	void merge(int l, int m, int h); //��·�鲢�㷨
	void selectSort(int l, int h); //ѡ������
	int selectMax(int l, int h);//ѡ�����ֵ
	int selectMax() { selectMax(0, _size); }//ȫ��ѡ�����ֵ
	void insertSort(int l, int h); //��������
	int insert(const T& elem, int r); //����Ԫ��
	int insert(const T& elem) { return insert(elem, size()); }
	int remove(int l, int h); //ɾ�������ڵ�Ԫ��
	T remove(int r) { T e = _elem[r]; remove(r, r + 1); return e; } //ɾ������Ԫ��
	void deduplicate();//��������ȥ��
	void traverse(void (*visit)(T& t));//��������
	template<typename VST> void traverse(VST& visit); //��������ı�������
	bool disorder()const; //�жϺ����Ƿ��Ѿ���С�����������
	void unique(); //��������ȥ��

	//--------------------------------------------���ܺ�������--------------------------------------------


protected:
	//--------------------------------------------���ݶ���--------------------------------------------
	int _size; //�������ݳ���
	int _capacity; //��������
	T* _elem; //��������
	//--------------------------------------------���ݶ������--------------------------------------------



	//--------------------------------------------���ߺ���--------------------------------------------
	inline void CopyFrom(const T* elem, int l, int h);//��������
	void expand(); //����
	void shrink(); //����
	void swap(T& lhs, T& rhs); //��������Ԫ��
	bool lessthan(T a, T b) { return a < b; } //aС��b
	//--------------------------------------------���ߺ�������--------------------------------------------
	
};



//------------------------------------------------------���ƺ���--------------------------
template<typename T>
vector<T>& vector<T>::operator=(const vector<T>& rhs)//��������
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

//------------------------------------------���ܺ���------------------------------------------------
template<typename T>
T& vector<T>::operator[](int r)const
{
	return this->_elem[r];
}

template<typename T>
void vector<T>::unsort(int l, int h) //����˳��
{
	srand(time(0));
	T* elem = _elem + l;
	for (int i = h - l; i > 0; i--)
	{
		swap(elem[i-1], elem[rand() % i]);
	}
}
template<typename T>
int vector<T>::find(const T& elem, int l, int h)const //��̬����
{
	while ((l < h--) && _elem[h] != elem);
	return h;
}
template<typename T>
int vector<T>::insert(const T& elem, int r)//����Ԫ��
{
	expand(); //�ȼ����û�б�Ҫ����
	_size++;
	for (int i = _size - 1; i > r; i--)
	{
		_elem[i] = _elem[i - 1];
	}
	_elem[r] = elem;
	return r;
}
template<typename T>
int vector<T>::remove(int l, int h) //ɾ�������ڵ�Ԫ��[l,h)
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
void vector<T>::deduplicate() //����ȥ��
{
	int i = 1;
	while (i < _size)
	{
		find(_elem[i], 0, i) < 0 ? i++: remove(i);
	}
}
template<typename T>
void vector<T>::traverse(void(*visit)(T& t))//���ú���ָ�룬ʵ�ֱ�������
{
	for (int i = 0; i < _size; i++)
	{
		visit(_elem[i]);
	}
}
template<typename T> template<typename VST>
void vector<T>::traverse(VST& visit) //����
{
	for (int i = 0; i < _size; i++)
	{
		visit(_elem[i]);
	}
}

template<typename T>
bool vector<T>::disorder()const //�ж��Ƿ��С��������
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
void vector<T>::unique() //����������ȥ��
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
int vector<T>::binSearchA(const T& elem, int l, int h)const //���ֲ��Ұ汾A
{
	while (l < h)
	{
		int mid = (l + h) >> 1;  //���˱�elemС������elem�ʹ���elem������������ֵ���
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
int vector<T>::binSearchB(const T& elem, int l, int h)const //���ֲ��Ұ汾B
{
	while (h - l > 1) //���˱�elemС�Ͳ�С��elem������������ж��ֵ���
	{
		int mid = (l + h) >> 1;
		(_elem[mid] > elem) ? h = mid : l = mid;

	}
	return (_elem[l] == elem) ? l : -1;
}

template<typename T>
int vector<T>::binSearchC(const T& elem, int l, int h)const //���ֲ��Ұ汾C
{
	
	while (l < h)
	{
		int mid = (l + h) >> 1;
		( elem<_elem[mid]) ? h = mid : l = mid+1;
	}
	
	return --l; //���ж��ֵ��������ҷ��ز�����elem������ߵ�Ԫ��
}

template<typename T>
int vector<T>::fibSearch(const T& elem, int l, int h)const //쳲���������
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
int vector<T>::insertSearch(const T& elem, int l, int h)const //��ֵ����
{
	while (l < h)
	{
		int mid = l + ((elem - _elem[l]) / (_elem[h] - _elem[l])) * (h - l); //���������ֲ����ȵ���������ֵ����Ч�ʸ�
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
void vector<T>::sort(int l, int h) //�����㷨
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
void vector<T>::bubbleSortA(int l, int h) //��Ч��ð������
{
	while (!bubbleA(l, h--));
}

template<typename T>
bool vector<T>::bubbleA(int l, int h) //��Чð��������ѭ��
{
	bool sorted = true; //��Ч��ԭ���ǣ�ֻ�ܼ�������ȫ��������ɵ���������ǰ����в���Ԫ����ȫ�����Ǽ�鲻������

	while (++l < h)
	{
		if (_elem[l - 1] > _elem[l])
		{
			swap(_elem[l - 1], _elem[l ]);
			sorted = false; //ͨ��������������Ƿ����������ˣ����û������ԣ����������
		}
	}
	return sorted;

}
template<typename T>
void vector<T>::bubbleSortB(int l, int h) //��Ч��ð������
{
	while (l < (h = bubbleB(l, h)));
}

template<typename T>
int vector<T>::bubbleB(int l, int h) //��Ч��ð��������ѭ��
{
	int last = l;
	while (++l < h) //ͨ��������һ�ν���������ʲô�ط�������жϳ����һ�ν����ĺ���ȫ����Ԫ�أ����Ѿ����������Ч��
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
void vector<T>::mergeSort(int l, int h) //�鲢����[l,h)�Ĺ鲢����
{
	if (h-l<2)return;
	int m = (l + h) >> 1;
	mergeSort(l, m); mergeSort(m, h); //�鲢����ʹ��ÿһ������ҿ����䶼ʣ��һ��Ԫ��
	merge(l, m, h);
}

template<typename T>
void vector<T>::merge(int l, int m, int h) //��·�鲢�㷨
{
	T* A = _elem + l; //ԭʼ������Ԫ��
	int lb = m - l;//������[l,m)�ĳ���
	T* B = new T[lb]; //����������䵽������
	for (int i = 0; i < lb; B[i] = A[i++]);
	T* C = _elem + m; //�ұ����䲻�������ٿռ䣬��Ϊ���������Ԫ�ز��ᱻ����
	int lc = h - m; //�ұ�����[m,h)�ĳ���

	for (int j = 0, k = 0, i = 0; (j < lb) || (k < lc);) //j���������α꣬k���������α꣬i��ԭ��Ҳ����������Ԫ�ص��α�
	{
		if (j < lb && (!(k < lc) || B[j] <= C[k])) A[i++] = B[j++];
		if (k < lc && (!(j < lb) || C[k] < B[j]))A[i++] = C[k++];
	}
	delete[]B;
}

template<typename T>
void vector<T>::selectSort(int l, int h) //ѡ������
{
	for (int i = h; i > l+1; i--)
	{
		int max = selectMax(l, i); //ѡ��[l,i)�����ֵ���±�
		swap(_elem[max], _elem[i-1]); //���ϰ�ǰ��ļ����������ֵ����������

	}
}
template<typename T>
int vector<T>::selectMax(int l, int h) //ѡ��[l,h)��������ֵ����
{
	int max = l;
	for (int i = l + 1; i < h; i++)
	{
		if (!lessthan(_elem[i], _elem[max])) max = i;
	}
	return max;
}
template<typename T>
void vector<T>::insertSort(int l, int h) //��������
{
	for (int i = l + 1; i < h; i++)//��һ��Ԫ�ز���Ҫ�Ƚϴ�С��ֱ�ӷ��Ǿ���
	{
		int rank=binSearchC(_elem[i], l, i); //��[l,i)�������У�ʹ�ö��ֲ��ң�����_elem[i]Ӧ�ñ����뵽˭�ĺ���
		int elem = _elem[i]; //����һ��_elem[i]��Ԫ��
		for (int j = i; j > rank+1; j--) //Ԫ�غ��ƣ���rank+1��i��Ԫ��ȫ������һλ
		{
			_elem[j] = _elem[j - 1];
		}
		_elem[rank+1] = elem; //rank��λ�÷���ԭ����i��Ԫ��
		
		

	}
}
//------------------------------------------------------���ߺ���--------------------------
template<typename T>
inline void vector<T>::CopyFrom(const T* elem, int l, int h) //��������[l,h)
{
	_elem = new T[_capacity=2*(h-l)];//����ռ䣬�����������ڶ��������볤��
	_size = 0; //������鳤��
	while (l < h)
	{
		_elem[_size++] = elem[l++];
	}

}

template<typename T>
void vector<T>::expand()//����
{
	if (_size < _capacity)return; //����������ʱ������
	if (_capacity < DefaultCapacity)_capacity = DefaultCapacity; //������С��Ĭ������
	T* oleElem = _elem;
	_elem = new T[_capacity <<= 1]; //��������
	for (int i = 0; i < this->size(); i++)
	{
		_elem[i] = oleElem[i];
	}
	delete[] oleElem;
	

}
template<typename T>
void vector<T>::shrink()//����
{
	if (_size  < DefaultCapacity<<1)return; //��������С��Ĭ������
	if (_size << 2 < _capacity) //װ������С��0.25��ʱ�򣬻Ὺʼ����
	{
		T* oldElem = _elem;
		_elem = new T[_capacity >> 1]; //����һ��
		for (int i = 0; i < _size; i++)
		{
			_elem[i] = oldElem[i];
		}
		delete []oldElem;
	}
}
template<typename T>
void vector<T>::swap(T& lhs, T& rhs) //��������Ԫ��
{
	T temp = rhs;
	rhs = lhs;
	lhs = temp;
}



