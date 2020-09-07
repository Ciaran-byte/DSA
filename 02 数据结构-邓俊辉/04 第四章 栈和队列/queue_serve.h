#pragma once
#include "Queue_list.h"
#include <ctime>
#include<iostream>
using namespace std;
//ģ�����з����Ŷӵ����
class customer
{
public:
	int window; //���񴰿�
	int time; //����ʱ��
};
int bestWindow(queue<customer>* window, int nWin);
void serve(int nWin, int servTime);

void serve(int nWin, int servTime)//���п��ż������ڣ�����ʱ���Ƕ೤
{
	
	srand(time(0));
	queue<customer>* window = new queue<customer>[nWin]; //���п����˼������ڣ�ÿ�����ڶ���һЩ�����Ŷ�
	for (int now = 0; now < servTime; now++)
	{
		cout << "���з�����" << endl;
		if (rand() % (nWin + 1)) //����˿����ˣ��˿ͳ��ֵĸ�����nWin/nWin+1
		{
			int bestWin = bestWindow(window, nWin); //������˿��������ٵĴ��ڵȴ�
			customer c;
			c.window = bestWin;//���񴰿�
			c.time = rand() % 100 ; //����ʱ�������[0,100)
			window[bestWin].enqueue(c);
		}
		for (int i = 0; i < nWin; i++)
		{
			if (!window[i].empty())
			{
				if (--window[i].front().time <= 0)
				{
					window[i].dequeue();
				}
			}
		}

	}
	cout << "�������з������" << endl;
	delete[]window;


}

int bestWindow(queue<customer>* window, int nWin) 
{
	int minSize = window[0].size();
	int bestWin = 0;
	for (int i = 1; i < nWin; i++)
	{
		if (window[i].size() < minSize)
		{
			minSize = window[i].size();
			bestWin = i;
		}
	}
	return bestWin;
}