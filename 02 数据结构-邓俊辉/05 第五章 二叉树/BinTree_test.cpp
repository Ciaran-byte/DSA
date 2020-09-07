#include "BinTree.h"
#include<iostream>
#include<ctime>
using namespace std;

template<typename T>
class seeOut
{
public:
	void operator()(const T& elem) { cout << elem << endl; }
};
int main()
{
	//01 ���ڵ㴴��
	cout << "���������" << endl;
	BinTree<int> S;
	S.insertAsRoot(0);
	cout<<S.root()->data<<endl;
	//02 �ӽڵ㴴��
	cout << endl;
	cout << "�����ӽڵ�" << endl;
	S.insertAsLC(S.root(), 2);
	S.insertAsRC(S.root(), 5);
	cout << S.root()->lchild->data << endl;
	cout << S.root()->rchild->data << endl;

	//03 ɾ�����
	cout << endl;
	cout << "ɾ�����" << endl;
	S.remove(S.root()->lchild);
	cout << !(S.root()->lchild) << endl;

	//04 ������
	cout << endl;
	cout << "������" << endl;
	BinTree<int> Q;
	Q.insertAsRoot(7);
	Q.insertAsLC(S.root(), 71);
	Q.insertAsRC(S.root(), 56);
	BinTree<int>* Pointer = &Q;
	S.attachAsLC(S.root(), Pointer);
	cout << S.root()->lchild->data << endl;

	//05 �ݹ����
	cout << endl;
	cout << "�ݹ������" << endl;
	seeOut<int> c;
	cout << "ǰ" << endl;
	S.traversePre_R<seeOut<int>>(S.root(), c);
	cout << "��" << endl;
	S.traverseIn_I1<seeOut<int>>(S.root(), c);
	cout << "��" << endl;
	S.traversePost_R<seeOut<int>>(S.root(), c);

	//06 ��������
	
	return 0;
}

