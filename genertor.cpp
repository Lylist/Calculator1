#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
#include "cal.h"
using namespace std;
string getSignal(int n);                      //��ȡ������������
int random(double, double);             //��ȡ���������
string takeTest();                        //��Ŀ���ɺ���

string getSignal(int n)
{
	string signal[2][5] = { "+","-","*","/","**","+","-","*","/","^" };

	return signal[sec-1][rand() % n];
}

int random(double start, double end)
{
	return (int)(start + (end - start)*rand() / (RAND_MAX + 1.0));
}


string takeTest()
{
	
	int num1, num2;
	string signal;
	string ans = "";

	signal = getSignal(5);
	num1 = random(1, 100);
	num2 = random(1, 100);

	if (signal == "'")
	{
		if (num1<num2)
		{
			swap(num1, num2);
		}
	}

	if (signal == "**"||signal=="^")
	{
		num2 /= 35;
	}

	if (signal == "/")
	{
		if (num2 == 0)
		{
			swap(num1, num2);
		}
	}

	ans = ans + to_string(num1) + signal + to_string(num2);
	signal = getSignal(4);
	ans = ans + signal;

	signal = getSignal(5);
	num1 = random(1, 100);
	num2 = random(1, 100);

	if (signal == "'")
	{
		if (num1<num2)
		{
			swap(num1, num2);
		}
	}

	if (signal == "**" || signal == "^")
	{
		num2 /= 35;
	}

	if (signal == "/")
	{
		if (num2 == 0)
		{
			swap(num1, num2);
		}
	}

	ans = ans + to_string(num1) + signal + to_string(num2);

	return ans;
}