#include<iostream>
using namespace std;

//--------------------------------------------ɢ�б�ṹ����----------------------------------------------------

const int UNCESSFUL = 0;
const int NOKEY = -32768;
const int HASHSIZE = 12;

typedef struct HashTable
{
	int count;
	int* data;
}HashTable;




//--------------------------------------------ɢ�б�ṹ�������----------------------------------------------


//--------------------------------------------ɢ�б��ʼ��-----------------------------------------------------

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

//--------------------------------------------ɢ�б��ʼ������-----------------------------------------------------

//--------------------------------------------ɢ�к�������-----------------------------------------------------
int Hash(int num)
{
	return num % HASHSIZE;
}

//--------------------------------------------ɢ�к����������-----------------------------------------------------

//--------------------------------------ɢ�б�Ĳ���--------------------------------------------------------------

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

//------------------------------------------ɢ�б�������-----------------------------------------------------

//------------------------------------------ɢ�б����-----------------------------------------------------

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

//------------------------------------------ɢ�б���ҽ���-----------------------------------------------------
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
		cout << "����" << key << "��λ����" << p << endl;

	else
		cout << "����ʧ��" << endl;
		
	for (int i = 0; i < HASHSIZE; i++)
	{
		key = arr[i];
		SearchHash(H, key, &p);
		cout << "����" << key << "��λ����" << p << endl;
		
	}
	
	return 0;
}