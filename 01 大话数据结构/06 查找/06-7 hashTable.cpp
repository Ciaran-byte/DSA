#include<iostream>
using namespace std;

//--------------------------------------------散列表结构定义----------------------------------------------------

const int UNCESSFUL = 0;
const int NOKEY = -32768;
const int HASHSIZE = 12;

typedef struct HashTable
{
	int count;
	int* data;
}HashTable;




//--------------------------------------------散列表结构定义结束----------------------------------------------


//--------------------------------------------散列表初始化-----------------------------------------------------

bool HashTableInitialize(HashTable* hash)
{
	hash->count = HASHSIZE;
	hash->data = (int*)malloc(hash->count*sizeof(int*));
	if (!hash->data)
	{
		return false;
	}
	for (int i = 0; i < hash->count; i++)
	{
		hash->data[i] = NOKEY;
	}
	return true;
}

//--------------------------------------------散列表初始化结束-----------------------------------------------------

//--------------------------------------------散列函数定义-----------------------------------------------------
int Hash(int num)
{
	return num % HASHSIZE;
}

//--------------------------------------------散列函数定义结束-----------------------------------------------------

//--------------------------------------散列表的插入--------------------------------------------------------------

void InsertHash(HashTable* h,int data)
{
	int index = Hash(data);
	int i = 0;
	while (h->data[index] != NOKEY)
	{
		i++;
		index = Hash(data + i);
	}
	h->data[index] = data;
	
	
}

//------------------------------------------散列表插入结束-----------------------------------------------------

//------------------------------------------散列表查找-----------------------------------------------------

bool SearchHash(HashTable h, int data,int* addr)
{
	int index = Hash(data);
	int i = 0;
	while (h.data[index] != data)
	{
		
		i++;
		index = Hash(data + i);

		if (h.data[index] == NOKEY || index == Hash(data))
		{
			return false;
		}
	}
	*addr = index;
	return true;
}

//------------------------------------------散列表查找结束-----------------------------------------------------
int main()
{
	int arr[HASHSIZE] = { 12,67,56,16,25,37,22,29,15,47,48,34 };
	int  p, key, result;
	HashTable H;

	key = 29;

	HashTableInitialize(&H);
	for (int i = 0; i < HASHSIZE; i++)
		InsertHash(&H, arr[i]);

	result = SearchHash(H, key, &p);
	if (result)
		cout << "查找" << key << "的位置是" << p << endl;

	else
		cout << "查找失败" << endl;
		
	for (int i = 0; i < HASHSIZE; i++)
	{
		key = arr[i];
		SearchHash(H, key, &p);
		cout << "查找" << key << "的位置是" << p << endl;
		
	}
	
	return 0;
}