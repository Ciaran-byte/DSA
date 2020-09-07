#include "Skiplist.h"
#include<iostream>
using namespace std;
int main()
{
	Skiplist<char, int> spk;
	for(int i=0;i<10;i++)
	
	{
		spk.put(i+'0', i);
		
	}
	for (int i = 0; i < 10; i++)
	{
		spk.remove(i + '0');
	}
	return 0;
}