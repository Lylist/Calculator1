#include <iostream>
#include <cstring>
#include <string>
using namespace std;

class complex     //表示分数
{
public:

	complex() { real = imag = 0; }
	complex(int r, int i)
	{
		real = r ; imag = i ;
	}
	//重载分数的运算
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
	int real, imag;//real分子imag分母    
};


extern string takeTest();
extern complex Caculate(string s);