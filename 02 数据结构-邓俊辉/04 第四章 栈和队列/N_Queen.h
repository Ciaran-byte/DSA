#pragma once
#include "stack_vector.h"
//ջ�㷨��N�ʺ�����---���ݷ�
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
	int nSolution=0; //�����������
	while (q.x>0|| q.y < N) //����ж���˼�ȼ��ڣ�����һ���ʺ�ŵ�(0,N)��λ��ʱ��˵����̽�Լ�ȫ��������
	{
		if (solution.size() >= N || q.y >= N) //���ҵ�һ��N�ʺ�Ľ⣬������̽�������������˻�û���ʵ�,�ͻ���
		{
			q=solution.pop(); //����ҵ�һ�����ˣ���������·�߲����ˣ�����һ���ʺ�������ʺ���+1��������
			q.y++;
		}
		else //��������ػ�����һ��
		{
			while ((q.y<N)&&(solution.find(q) >= 0)) //�ҵ�������ǰ�����еĻʺ��岻��ͻ��λ��
													//�о��ж�������ǰһ���ּӲ�������ν���Ͼ����˶��ȥ����λ�ã�����ȥһ��λ��ûʲô����
			{
				q.y++; 
			}
			if (q.y < N) //�����С��N��˵���ҵ����Ǹ����Է����ӵĵ㣬�ͷ�����
			{
				solution.push(q);
				if (solution.size() >= N)nSolution++; //���ջ��N��Ԫ���ˣ�˵���ҵ�һ����ˣ���ĸ���+1
				q.x++; //�ٴ���һ�����߿���û���µĽ�
				q.y = 0; //��һ���ʺ������(x+1,0)��λ����
			}

		}
	}
	return nSolution;
}