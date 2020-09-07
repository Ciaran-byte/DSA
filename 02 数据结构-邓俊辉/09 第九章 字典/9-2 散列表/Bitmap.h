#pragma once
#include<memory>

class Bitmap
{
private:
	char* M; //����ͼ�Ĵ�ſռ�
	int N; //����ΪN*sizeof(char)*8����
protected:
	void init(int n) { M = new char[N = (n + 7) / 8]; memset(M, 0, N); } 
	//��ʾ��N���ֽڵĿռ��洢n�����ݵĴ������memset���ڰ�M��ʼ��ǰN���ֽڳ�ʼ��Ϊ����ֵ
public:
	Bitmap(int n = 8) { init(n); }//���캯������λͼ�ĳ�ʼ��
	Bitmap(char* file, int n = 8)  //file�Ǹ��ļ�����ͨ��λͼ�ļ�����λͼ
	{
		init(n); FILE* fp = fopen(file, "r"); fread(M, sizeof(char), N, fp); fclose(fp);
	}
	~Bitmap() { delete[]M; M = nullptr; }//��������

	void dump(char* file) //��λͼ���嵼����ָ�����ļ����Ա�Դ˺����λͼ������ʼ��
	{
		FILE* fp = fopen(file, "w"); fwrite(M, sizeof(char), N, fp); fclose(fp);
	}


	void set(int k)//���õ�kλΪ1
	{
		expand(k); //�ȼ���Ƿ���Ҫ����
		//��Ϊһ���ֽڱ�ʾһ�����֣�k>>3��ʾk����8���õ������ֱ�ʾ����ĵڼ���byte�к���k������ֵ���Ϣ
		M[k >> 3] |= (0x80 >> (k & 0x07));
		//k&0x07��ʾk��0111��λ�����㣬�õ�����8������v��Ҳ���ǵڼ���������k
		//0x80��1000 0000 ��Ҳ����һ���ֽڵĳ��ȣ���1���ұ��ƶ�vλ�ã��Ϳ��԰�1�ŵ�k���������λ�ϣ�������ֽ���λ�����㣬ʵ����1����
	}
	void clear(int k)//���õ�kΪΪ0
	{
		expand(k);
		M[k>>3]&= ~(0x80 >> (k & 0x07)); //��k��λ��0��������ֽ���λ������
	}
	bool test(int k) //��ѯ��kλ�ı��
	{
		expand(k);
		return M[k>>3]& (0x80 >> (k & 0x07));
	}

	void expand(int k)//���ݺ���
	{
		if (k < 8 * N)return; //�����ǰ��bit�ռ��ܹ���ʾk�����֣�����Ҫ��
		int oldN = N;
		char* oldM = M;
		init(2 * k);
		memcpy_s(M, N, oldM, oldN); //��ԭ���ռ��N���ֽڵ����ݸ��Ƶ��¿ռ�
		delete[]oldM; //ɾ���ɿռ������

	}

	char* bits2string(int n) //��ǰnλת��Ϊ�ַ�������
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

//----------------------------��������----------------------------------------------
int min(int a, int b) { return a < b ? a : b; } //��Сֵ

void Eratosthenes(int n, char* file) //���������� 
//��file��д�뺬��n�������ı�0��1����������
{
	Bitmap B(n);
	B.set(0);
	B.set(1);
	for (int i = 2; i < n; i++)
	{
		if (!B.test(i))//��i�����������������i*i��ʼ���䱶��ȫ�����Ǻ��������Ϊ1
		{
			for (int j = min(i, 46340) * min(i, 46340); j < n; j += i)
			{
				B.set(j);
			}
		}

	}
	B.dump(file);
}

//������ѯ
int primeNLT(int c, int n, char* file) { //����file�ļ��еļ�¼����[c, n)��ȡ��С������
	Bitmap B(file, n); //file�Ѿ���λͼ��ʽ����¼��n���ڵ��������������ֻҪ
	while (c < n) //��c��ʼ����λ��
		if (B.test(c)) c++; //���ԣ�����
		else return c; //�����׸����ֵ�����
	return c; //��û������������������n��ʵ���в�����˼򻯴���
}
