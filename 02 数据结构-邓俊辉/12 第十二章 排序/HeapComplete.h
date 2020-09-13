#pragma once
#define InHeap(n,i)(((-1)<(i))&&((i)<(n))) //判断P[i]是否合法
#define Parent(i)  ((i-1)>>2) //父亲结点
#define LastInternal(n) Parent(n-1)  //最后一个内部结点，就是末结点的父节点
#define LChild(i) (1+((i)<<1)) //左孩子
#define RChild(i) ((1+(i))<<1) //右孩子
#define ParentValid(i) (i>0) //判断父节点是否存在
#define LChildValid(n,i) InHeap(n,LChild(i)) //判断是否存在左孩子
#define RChildValid(n,i) InHeap(n,RChild(i)) //判断是否存在右孩子
#define Bigger(PQ,i,j) ((PQ[i]>PQ[j])?i:j) //返回最大者的秩,相等的时候取前者
#define ProperParent(PQ,n,i) \
(RChildValid(n,i)?Bigger(PQ,Bigger(PQ,i,LChild(i)),RChild(i))\
:(LChildValid(n,i)?Bigger(PQ,i,LChild(i)):i))

template<typename T>
void swap(T& a, T& b)
{
	int temp = a;
	a = b;
	b = temp;
}


template <typename T> void heapify(T* A, int n); //Floyd建堆算法
template <typename T> int percolateDown(T* A, int n, int i); //下滤
template <typename T> int percolateUp(T* A, int i); //上滤		

template <typename T> void heapify(T* A, const int n) { //Floyd建堆算法，O(n)时间
	for (int i = n / 2 - 1; 0 <= i; i--) //自底而上，依次
 /*DSA*///{
		percolateDown(A, n, i); //下滤各内部节点
  /*DSA*///for ( int k = 0; k < n; k++ ) {
  /*DSA*///  int kk = k; while ( i < kk ) kk = (kk - 1) / 2;
  /*DSA*///  i == kk ? print(A[k]) : print("    " );
  /*DSA*///}; printf("\n");
  /*DSA*///}
}

//对向量前n个词条中的第i个实施下滤，i < n
template <typename T> int percolateDown(T* A, int n, int i) {
	int j; //i及其（至多两个）孩子中，堪为父者
	while (i != (j = ProperParent(A, n, i))) //只要i非j，则
	{
		swap(A[i], A[j]); i = j;
	} //二者换位，并继续考查下降后的i
	return i; //返回下滤抵达的位置（亦i亦j）
}
//对向量中的第i个词条实施上滤操作，i < _size
template <typename T> int percolateUp(T* A, int i) {
	while (0 < i) { //在抵达堆顶之前，反复地
		int j = Parent(i); //考查[i]之父亲[j]
		if (lt(A[i], A[j])) break; //一旦父子顺序，上滤旋即完成；否则
		swap(A[i], A[j]); i = j; //父子换位，并继续考查上一层
	} //while
	return i; //返回上滤最终抵达的位置
}



