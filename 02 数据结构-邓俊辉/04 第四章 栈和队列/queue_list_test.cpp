#include "Queue_list.h"
#include<iostream>
#include "queue_serve.h"
using namespace std;
int main()
{
	//01 ���л����÷�
	queue<int> q;
	for (int i = 0; i < 10; i++)
	{
		q.enqueue(i);
	}
	for (int i = 0; i < 10; i++)
	{
		cout << q.dequeue() << endl;
	}
	//02 ���з���ģ��
	serve(2, 10);
	return 0;
}