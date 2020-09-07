#pragma once
#include "stack_vector.h"
//栈算法，N皇后问题---回溯法
class Queen
{
public:
	int x, y;
	Queen(int xx=0,int yy=0 ):x(xx),y(yy){}
	bool operator==(const Queen& q)const
	{
		return	(x == q.x)
			|| (y == q.y)
			|| (x + y == q.x + q.y)
			|| (x - y == q.x - q.y);
	}
	bool operator!=(const Queen& q)const
	{
		return !(*this == q);
	}
};

int placeQueens(int N)
{
	stack<Queen> solution;
	Queen q(0, 0);
	int nSolution=0; //解决方案数量
	while (q.x>0|| q.y < N) //这个判断意思等价于，当第一个皇后放到(0,N)的位置时，说明试探以及全部结束了
	{
		if (solution.size() >= N || q.y >= N) //当找到一个N皇后的解，或者试探过程中列试完了还没合适的,就回溯
		{
			q=solution.pop(); //如果找到一个解了，或者这条路线不对了，回退一个皇后，让这个皇后列+1，再试试
			q.y++;
		}
		else //如果还不必回溯上一行
		{
			while ((q.y<N)&&(solution.find(q) >= 0)) //找到这行与前面所有的皇后棋不冲突的位置
													//感觉判断条件的前一部分加不加无所谓，毕竟大不了多出去几个位置，跟出去一个位置没什么区别
			{
				q.y++; 
			}
			if (q.y < N) //如果列小于N，说明找到了那个可以放棋子的点，就放棋子
			{
				solution.push(q);
				if (solution.size() >= N)nSolution++; //如果栈有N个元素了，说明找到一组解了，解的个数+1
				q.x++; //再从下一列走走看有没有新的解
				q.y = 0; //下一个皇后放置在(x+1,0)的位置上
			}

		}
	}
	return nSolution;
}