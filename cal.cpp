#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
#include <vector>
#include <string>
#include <map>
#include <stack>
#include "cal.h"
using namespace std;

inline complex complex::operator +(const complex &c)
{

	if (c.imag == imag)
		return complex((real + c.real), imag);
	else
		return complex((real*c.imag + c.real*imag), (imag*c.imag));
}

inline complex complex::operator -(const complex &c)
{
	if (c.imag == imag)
		return complex((real - c.real), imag);
	else
		return complex((real*c.imag - c.real*imag), (imag*c.imag));
}

inline complex complex::operator *(const complex &c)
{
	return complex(real*c.real, imag*c.imag);
}

inline complex complex::operator /(const complex &c)
{
	return complex((real*c.imag), (c.real*imag));
}

inline complex complex::operator ^(int a)
{
	complex ans(real, imag);
	for (int i = 0; i < a; i++)ans = ans * ans;
	return ans;
}

void print(const complex &c)
{
	int s, x, y;// s 是余数   
	x = c.real;
	y = c.imag;

	if (c.real == 0)//出现分母为0，而分子不为0时   
	{
		cout << "0";
		goto end;
	}

	if (c.imag == 0)//出现分子为0，而分母不为0时   
	{
		cout << "\n分母不能为0";
		goto end;
	}

	if (c.imag == c.real)//出现分子分母相同时   
	{
		cout << "1";
		goto end;
	}

	if (c.imag == -(c.real))//出现分子分母的绝对值相同时   
	{
		cout << "-1";
		goto end;
	}

	s = y % x;
	while (s != 0)//(s=y%x)!=0    化简部分   
	{
		y = x; x = s; s = y % x;
	}

	if (c.real / x<0 || c.imag / x<0)   //    输出部分   
	{
		if (c.imag / x == 1)
			cout << "-" << abs(c.real / x);
		else
			cout << "-" << abs(c.real / x) << "/" << abs(c.imag / x);
	}
	else
	{
		if (c.imag / x == 1)
			cout << c.real;
		else
			cout << c.real / x << "/" << c.imag / x;
	}
end:;
}

string To_string(const complex &c)
{
	int s, x, y;// s 是余数   
	x = c.real;
	y = c.imag;
	string str;

	if (c.real == 0)//出现分母为0，而分子不为0时   
	{
		return "0";
		goto end;
	}

	if (c.imag == 0)//出现分子为0，而分母不为0时   
	{
		return "\n分母不能为0";
		goto end;
	}

	if (c.imag == c.real)//出现分子分母相同时   
	{
		return "1";
		goto end;
	}

	if (c.imag == -(c.real))//出现分子分母的绝对值相同时   
	{
		return "-1";
		goto end;
	}

	s = y % x;
	while (s != 0)//(s=y%x)!=0    化简部分   
	{
		y = x; x = s; s = y % x;
	}

	if (c.real / x<0 || c.imag / x<0)   //    输出部分   
	{
		if (c.imag / x == 1)
			return str="-" + to_string(abs(c.real / x));
		else
			return str="-" + to_string(abs(c.real / x)) + "/" + to_string(abs(c.imag / x));
	}
	else
	{
		if (c.imag / x == 1)
			return to_string(c.real);
		else
			return str=to_string(c.real / x) + "/" + to_string(c.imag / x);
	}
end:;
}

int getreal(const complex &c)
{
	return c.real;
}
int getimag(const complex &c)
{
	return c.imag;
}

string MidToBack(string s);    //中缀表达式转后缀表达式
complex Caculate(string s);		//利用中缀表达式计算


string MidToBack(string s)       //转后缀表达式，利用栈
{
	string ret;
	stack<int> stk;
	int pos; 
	while ((pos = s.find("**"))!=s.npos)  //将**转换成^
	{
		s.replace(pos, 2, "^");
	}
	for (string::size_type i = 0; i< s.size(); i++)
	{
		if (isdigit(s[i]))
		{
			ret += s[i];
			if ((i < s.size() - 1 && !isdigit(s[i + 1])) || i == (s.size() - 1))
				ret += ' ';//这里是用空格将数跟符号隔开。目的是在后缀计算中提取数的时候，有些数可能不止一位，如果没有空格符，一个多位的数会被误认为是多个个位数。
		}
		else
		{
			switch (s[i])
			{
			case '(':
				stk.push(s[i]);
				break;
			case ')':
				while (!stk.empty() && stk.top() != '(')
				{
					ret += stk.top();
					stk.pop();
				}
				stk.pop();
				break;
			case '+':
			case '-':
				while (!stk.empty() && stk.top() != '(')
				{
					ret += stk.top();
					stk.pop();
				}
				stk.push(s[i]);
				break;
			case '*':
			case '/':
				while (!stk.empty() && (stk.top() == '*' || stk.top() == '/' || stk.top() == '^'))
				{
					ret += stk.top();
					stk.pop();
				}
				stk.push(s[i]);
				break;
			case '^': stk.push(s[i]); break;
			}

		}
	}
	while (!stk.empty())
	{
		ret += stk.top();
		stk.pop();
	}
	return ret;
}

complex Caculate(string s)
{
	s = MidToBack(s);
	complex result;
	stack<complex> stk;
	complex num1;//右操作数
	complex num2;//左操作数
	complex temp;
	for (string::size_type i = 0; i<s.size(); i++)
	{
		if (isdigit(s[i]))
		{
			int k = atoi(&s[i]);//将string类型的操作数转化为int型
			int m = k / 10;
			while (m)
			{
				m /= 10;
				i++;     //移动操作数的位数
			}
			i++; //跳过操作数后面的空格符
			stk.push(complex(k,1));
		}
		else
		{
			num1 = stk.top();
			stk.pop();
			num2 = stk.top();
			stk.pop();
			switch (s[i])
			{
			case '+':
				temp = num2 + num1;
				break;
			case '-':
				temp = num2 - num1;
				break;
			case '*':
				temp = num2 * num1;
				break;
			case '/':
				temp = num2 / num1;
				break;
			case '^':
				temp = complex(1, 1);
				for (int i = 1; i <= getreal(num1); i++)
				{
					temp = temp * num2;
				}
			}
			stk.push(temp);
		}
	}
	result = stk.top();
	return result;
}
