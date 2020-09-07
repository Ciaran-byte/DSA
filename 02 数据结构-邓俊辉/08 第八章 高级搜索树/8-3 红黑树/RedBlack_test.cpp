#include<iostream>
using namespace std;
#include "RedBlack.h"

OT<int> out;
int main()
{
	//01 ºìºÚÊ÷²åÈë²Ù×÷
	RedBlack<int> r;
	for (int i = 0; i <15; i++)
	{
		r.insert(i);
	}
	r.traverseIn_R(r.root(),out);

	//02 ºìºÚÊ÷É¾³ı²Ù×÷
	cout << endl;
	for (int i = 0; i < 5; i++)
	{
		r.remove(i);
	}
	r.traverseIn_R(r.root(), out);
	return 0;
}



