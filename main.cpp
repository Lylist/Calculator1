#include <cstdio>
#include <cstring>
#include <time.h>
#include <cstdlib>
#include <iostream>
#include "cal.h"
using namespace std;

int read(char str[])
{
	int Number = 0;
	int len = strlen(str);
	for (int i = 0; i < len; i++)
	{
		if (str[i]<'0' || str[i]>'9') return -1;
		Number = Number * 10 + str[i] - '0';
	}
	if (Number < 1) return -1;
	return Number;
}

int main(int argc, char *argv[])
{
	int rightans = 0, wrong = 0;
	if (argc < 2)
	{
		printf("Plwase use the parameters\n");
		return 0;
	}
	else if (strcmp(argv[1], "-a") == 0)
	{
		int Num = read(argv[2]);
		if (Num == -1)
		{
			printf("Please use useful number\n");
			return 0;
		}
		
		while (Num--)
		{
			string str = takeTest();
			cout << str << endl << "Please answer" << endl;;
			string ans;
			cin >> ans;
			complex true_ans = Caculate(str);
			print(true_ans);
			cout << endl;
			if (ans == To_string(true_ans))
			{
				printf("You are right!\n");
				rightans++;
			}
			else printf("You are wrong!\n"),wrong++;
		}
	}
	else printf("Please use ture command\n");
	printf("ÕıÈ·ÂÊ£º%d/%d\n", rightans, rightans + wrong);
	system("Pause");
	return 0;
}