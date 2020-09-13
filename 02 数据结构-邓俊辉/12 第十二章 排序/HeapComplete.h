#pragma once
#define InHeap(n,i)(((-1)<(i))&&((i)<(n))) //�ж�P[i]�Ƿ�Ϸ�
#define Parent(i)  ((i-1)>>2) //���׽��
#define LastInternal(n) Parent(n-1)  //���һ���ڲ���㣬����ĩ���ĸ��ڵ�
#define LChild(i) (1+((i)<<1)) //����
#define RChild(i) ((1+(i))<<1) //�Һ���
#define ParentValid(i) (i>0) //�жϸ��ڵ��Ƿ����
#define LChildValid(n,i) InHeap(n,LChild(i)) //�ж��Ƿ��������
#define RChildValid(n,i) InHeap(n,RChild(i)) //�ж��Ƿ�����Һ���
#define Bigger(PQ,i,j) ((PQ[i]>PQ[j])?i:j) //��������ߵ���,��ȵ�ʱ��ȡǰ��
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


template <typename T> void heapify(T* A, int n); //Floyd�����㷨
template <typename T> int percolateDown(T* A, int n, int i); //����
template <typename T> int percolateUp(T* A, int i); //����		

template <typename T> void heapify(T* A, const int n) { //Floyd�����㷨��O(n)ʱ��
	for (int i = n / 2 - 1; 0 <= i; i--) //�Ե׶��ϣ�����
 /*DSA*///{
		percolateDown(A, n, i); //���˸��ڲ��ڵ�
  /*DSA*///for ( int k = 0; k < n; k++ ) {
  /*DSA*///  int kk = k; while ( i < kk ) kk = (kk - 1) / 2;
  /*DSA*///  i == kk ? print(A[k]) : print("    " );
  /*DSA*///}; printf("\n");
  /*DSA*///}
}

//������ǰn�������еĵ�i��ʵʩ���ˣ�i < n
template <typename T> int percolateDown(T* A, int n, int i) {
	int j; //i���䣨���������������У���Ϊ����
	while (i != (j = ProperParent(A, n, i))) //ֻҪi��j����
	{
		swap(A[i], A[j]); i = j;
	} //���߻�λ�������������½����i
	return i; //�������˵ִ��λ�ã���i��j��
}
//�������еĵ�i������ʵʩ���˲�����i < _size
template <typename T> int percolateUp(T* A, int i) {
	while (0 < i) { //�ڵִ�Ѷ�֮ǰ��������
		int j = Parent(i); //����[i]֮����[j]
		if (lt(A[i], A[j])) break; //һ������˳������������ɣ�����
		swap(A[i], A[j]); i = j; //���ӻ�λ��������������һ��
	} //while
	return i; //�����������յִ��λ��
}



