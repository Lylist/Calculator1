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
	int s, x, y;// s ������   
	x = c.real;
	y = c.imag;

	if (c.real == 0)//���ַ�ĸΪ0�������Ӳ�Ϊ0ʱ   
	{
		cout << "0";
		goto end;
	}

	if (c.imag == 0)//���ַ���Ϊ0������ĸ��Ϊ0ʱ   
	{
		cout << "\n��ĸ����Ϊ0";
		goto end;
	}

	if (c.imag == c.real)//���ַ��ӷ�ĸ��ͬʱ   
	{
		cout << "1";
		goto end;
	}

	if (c.imag == -(c.real))//���ַ��ӷ�ĸ�ľ���ֵ��ͬʱ   
	{
		cout << "-1";
		goto end;
	}

	s = y % x;
	while (s != 0)//(s=y%x)!=0    ���򲿷�   
	{
		y = x; x = s; s = y % x;
	}

	if (c.real / x<0 || c.imag / x<0)   //    �������   
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
	int s, x, y;// s ������   
	x = c.real;
	y = c.imag;
	string str;

	if (c.real == 0)//���ַ�ĸΪ0�������Ӳ�Ϊ0ʱ   
	{
		return "0";
		goto end;
	}

	if (c.imag == 0)//���ַ���Ϊ0������ĸ��Ϊ0ʱ   
	{
		return "\n��ĸ����Ϊ0";
		goto end;
	}

	if (c.imag == c.real)//���ַ��ӷ�ĸ��ͬʱ   
	{
		return "1";
		goto end;
	}

	if (c.imag == -(c.real))//���ַ��ӷ�ĸ�ľ���ֵ��ͬʱ   
	{
		return "-1";
		goto end;
	}

	s = y % x;
	while (s != 0)//(s=y%x)!=0    ���򲿷�   
	{
		y = x; x = s; s = y % x;
	}

	if (c.real / x<0 || c.imag / x<0)   //    �������   
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

string MidToBack(string s);    //��׺���ʽת��׺���ʽ
complex Caculate(string s);		//������׺���ʽ����


string MidToBack(string s)       //ת��׺���ʽ������ջ
{
	string ret;
	stack<int> stk;
	int pos; 
	while ((pos = s.find("**"))!=s.npos)  //��**ת����^
	{
		s.replace(pos, 2, "^");
	}
	for (string::size_type i = 0; i< s.size(); i++)
	{
		if (isdigit(s[i]))
		{
			ret += s[i];
			if ((i < s.size() - 1 && !isdigit(s[i + 1])) || i == (s.size() - 1))
				ret += ' ';//�������ÿո��������Ÿ�����Ŀ�����ں�׺��������ȡ����ʱ����Щ�����ܲ�ֹһλ�����û�пո����һ����λ�����ᱻ����Ϊ�Ƕ����λ����
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
	complex num1;//�Ҳ�����
	complex num2;//�������
	complex temp;
	for (string::size_type i = 0; i<s.size(); i++)
	{
		if (isdigit(s[i]))
		{
			int k = atoi(&s[i]);//��string���͵Ĳ�����ת��Ϊint��
			int m = k / 10;
			while (m)
			{
				m /= 10;
				i++;     //�ƶ���������λ��
			}
			i++; //��������������Ŀո��
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
