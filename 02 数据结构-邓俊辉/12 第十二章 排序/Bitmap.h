#pragma once
#include<memory>
class Bitmap
{
private:
	char* M; //比特图的存放空间
	int N; //容量为N*sizeof(char)*8比特
protected:
	void init(int n) { M = new char[N = n + 7 / 8]; memset(M, 0, N); } 
	//表示用N个字节的空间存存储n个数据的存在与否，memset用于把M开始的前N个字节初始化为给定值
public:
	Bitmap(int n = 8) { init(n); }//构造函数，让位图的初始化
	~Bitmap() { delete[]M; M = nullptr; }//析构函数


	void set(int k)//设置第k位为1
	{
		expand(k); //先检查是否需要扩容
		//因为一个字节表示一个数字，k>>3表示k除以8，得到的数字表示数组的第几个byte中含有k这个数字的信息
		M[k >> 3] |= (0x80 >> k & 0x07);
		//k&0x07表示k与0111做位于运算，得到除以8的余数v，也就是第几个数字是k
		//0x80是1000 0000 ，也就是一个字节的长度，把1往右边移动v位置，就可以把1放到k所代表的那位上，与这个字节做位或运算，实现置1操作
	}
	void clear(int k)//设置第k为为0
	{
		expand(k);
		M[k>>3]&= ~(0x80 >> k & 0x07); //把k那位置0，与这个字节做位于运算
	}
	bool test(int k) //查询第k位的标记
	{
		expand(k);
		return M[k>>3]& (0x80 >> k & 0x07);
	}

	void expand(int k)//扩容函数
	{
		if (k < 8 * N)return; //如果当前的bit空间能够表示k个数字，不需要扩
		int oldN = N;
		char* oldM = M;
		init(2 * k);
		memcpy_s(M, N, oldM, oldN); //把原来空间的N个字节的数据复制到新空间
		delete[]oldM; //删除旧空间的数据

	}

	char* bits2string(int n) //把前n位转换为字符串返回
	{
		expand(n - 1);
		char* s = new char[n + 1];
		s[n] = '\0';
		for (int i = 0; i < n; i++)
		{
			s[i] = test(i) ? 1 : 0;
		}
		return s;
	}
};
