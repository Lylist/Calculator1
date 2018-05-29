#include <iostream>
#include <cstring>
#include <string>
using namespace std;

class complex     //��ʾ����
{
public:

	complex() { real = imag = 0; }
	complex(int r, int i)
	{
		real = r ; imag = i ;
	}
	//���ط���������
	complex operator +(const complex &c);
	complex operator -(const complex &c);
	complex operator *(const complex &c);
	complex operator /(const complex &c);
	complex operator ^(int a);
	friend void print(const complex &c);
	friend string To_string(const complex &c);
	friend int getreal(const complex &c);
	friend int getimag(const complex &c);

private:
	int real, imag;//real����imag��ĸ    
};


extern string takeTest();
extern complex Caculate(string s);