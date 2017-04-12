// GS-RTC.cpp : Defines the entry point for the console application.
//
#include <stdlib.h>
#include <iostream>

using namespace std;

// will get a runtime error with /RTCs and with /GS because return address is compromised as well as
// other stack variables
void Test1()
{
	char buffer1[100];

	for (int i=0 ; i < 200; i++)
	{
		buffer1[i] = 'a';
	}

	buffer1[sizeof(buffer1)-1] = 0;

	cout << buffer1 << endl;
}

// will get a runtime error with /RTCs, but not /GS because return address not compromised, only other
// stack variables
void Test2()
{
	char buffer1[100];
	char buffer2[100];

	buffer1[0] = 0;

	for (int i=0 ; i <= sizeof(buffer2); i++)
	{
		buffer2[i] = 'a';
	}

	buffer2[sizeof(buffer2)-1] = 0;

	cout << buffer2 << '-' << buffer1 << endl;
}

// underrun buffer 3 - caught by RTCs
void Test3()
{
	char buffer1[100];
	char buffer2[100];

	memset(buffer1,'a',sizeof(buffer1)-1);
	buffer1[sizeof(buffer1)-1]=0;
	memset(buffer2,'b',sizeof(buffer2)-1);
	buffer2[sizeof(buffer2)-1]=0;

	*(buffer1-1) = 'c';
	cout << buffer1 << endl;
	cout << buffer2 << endl;
}

// show starting values with /RTCs
void Test4()
{
	unsigned int var;

	cout << hex << var;
}

// truncate an integer into a char (/RTCc)
void Test5(int value)
{
	unsigned char ch;
	ch = (unsigned char)value;
}

// Use uninitialized variables (/RTCu)
void Test6(int value)
{
	int uninitialized;
	int var;

	switch (value) 
	{
		case 3:
			uninitialized = 4;
		case 2:
			var = 5 * uninitialized;
			break;
		case 1:
			int* var2 = &uninitialized;
			var = 5 * uninitialized;
			break;
	}
}

int main(int argc, char* argv[])
{
	if (argc > 1) {
		int test = atoi(argv[1]);
		int value = 0;
		if (argc > 2) 
		{
			value = atoi(argv[2]);
		}
		switch (test) 
		{
			case 1:
				Test1();
				break;
			case 2:
				Test2();
				break;
			case 3:
				Test3();
				break;
			case 4:
                Test4();
				break;
			case 5:
                Test5(value);
				break;
			case 6:
                Test6(value);
				break;
			default:
				break;
		}
	}
    else
    {
       cout << "usage: gs-rtc num1 num2" << endl;
       cout << "num1 is 1 through 6. Tests 5 and 6 require an integer parameter, default 0" << endl;
    }

	return 0;
}

