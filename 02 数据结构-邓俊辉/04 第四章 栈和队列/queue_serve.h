#pragma once
#include "Queue_list.h"
#include <ctime>
#include<iostream>
using namespace std;
//模拟银行服务排队的情况
class customer
{
public:
	int window; //服务窗口
	int time; //服务时间
};
int bestWindow(queue<customer>* window, int nWin);
void serve(int nWin, int servTime);

void serve(int nWin, int servTime)//银行开放几个窗口，服务时间是多长
{
	
	srand(time(0));
	queue<customer>* window = new queue<customer>[nWin]; //银行开放了几个窗口，每个窗口都有一些人在排对
	for (int now = 0; now < servTime; now++)
	{
		cout << "银行服务中" << endl;
		if (rand() % (nWin + 1)) //假设顾客来了，顾客出现的概率是nWin/nWin+1
		{
			int bestWin = bestWindow(window, nWin); //让这个顾客在人数少的窗口等待
			customer c;
			c.window = bestWin;//服务窗口
			c.time = rand() % 100 ; //服务时间可能是[0,100)
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
	cout << "今日银行服务结束" << endl;
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