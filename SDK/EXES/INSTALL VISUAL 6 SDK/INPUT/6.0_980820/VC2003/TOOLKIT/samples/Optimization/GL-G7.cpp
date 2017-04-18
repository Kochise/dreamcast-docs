// GL-G7.cpp : Defines the entry point for the console application.
//

#include <iostream>
using namespace std;

// _ReturnAddress should be prototyped before use 
#ifdef __cplusplus
extern "C"
#endif
void * _ReturnAddress(void);

#pragma intrinsic(_ReturnAddress)

//prototyping here to save #include of windows.h -- functions are in kernel32

typedef unsigned long       DWORD;
typedef void *HANDLE;
typedef long LONG;
typedef int                 BOOL;
typedef __int64 LONGLONG;
typedef union _LARGE_INTEGER {
    struct {
        DWORD LowPart;
        LONG HighPart;
    };
    struct {
        DWORD LowPart;
        LONG HighPart;
    } u;
    LONGLONG QuadPart;
} LARGE_INTEGER;

#define WINBASEAPI
#define WINAPI      __stdcall
#define IN
#define OUT
#define VOID void

#ifdef __cplusplus
extern "C" {
#endif
WINBASEAPI BOOL WINAPI QueryPerformanceCounter(OUT LARGE_INTEGER *lpPerformanceCount);
WINBASEAPI BOOL WINAPI QueryPerformanceFrequency(OUT LARGE_INTEGER *lpFrequency);
WINBASEAPI DWORD WINAPI SetThreadAffinityMask(IN HANDLE hThread,IN DWORD dwThreadAffinityMask);
WINBASEAPI HANDLE WINAPI GetCurrentThread(VOID);
#ifdef __cplusplus
}
#endif

//end of replacement for windows.h


void* inlineReturnAddress; // set in Add()
int Add(int a, int b); // implementation in module.cpp

void DisplayAdd(int a, int b)
{
	cout << a << " + " << b << " = " << a + b << endl;
   cout << "Return address from " << __FUNCTION__ << " " << _ReturnAddress() << endl;
}

void Test1()
{
	DisplayAdd(1,2); 
	cout << "1 + 2 = " << Add(1,2) << endl;

	cout << "Return address from Add " << inlineReturnAddress << endl;

	cout << "Return address from " << __FUNCTION__ << " " << _ReturnAddress() << endl;
}


#define INT_ARRAY_LEN 100000
int intarray[INT_ARRAY_LEN];
int intCalculate()
{
	int total = 0;

	for (int i = 1; i < INT_ARRAY_LEN; i++)
	{
			total += intarray[i-1]*7;
	}

	return total;
}
void Test2()
{
	int var1 = 2;
	int i;

	for (i = 0; i < INT_ARRAY_LEN; i++)
	{
			intarray[i] = i*5;
			var1 += 2;
	}

	LARGE_INTEGER start, end;
	LARGE_INTEGER freq;

	SetThreadAffinityMask(GetCurrentThread(), 1);
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);
	double total = 0;

	for (i = 0; i < 100000; i++)
	{
		total += intCalculate();
	}

	QueryPerformanceCounter(&end);

	cout << "Total = " << total << endl;

	cout << (end.QuadPart - start.QuadPart)/(double)freq.QuadPart << " seconds" << endl;
}

#define ARRAY_LEN 10000
double array[ARRAY_LEN];

double Calculate()
{
	double total = 0;

	for (int i = 1; i < ARRAY_LEN; i++)
	{
			total += array[i-1]*array[i];
	}

	return total;
}

void Test3()
{
	double var1 = 2;
	int i;

	for (i = 0; i < ARRAY_LEN; i++)
	{
			array[i] = var1;
			var1 += .012;
	}

	LARGE_INTEGER start, end;
	LARGE_INTEGER freq;

	SetThreadAffinityMask(GetCurrentThread(), 1);
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);
	double total = 0;

	for (i = 0; i < 100000; i++)
	{
		total += Calculate();
	}

	QueryPerformanceCounter(&end);

	cout << "Total = " << total << endl;

	cout << (end.QuadPart - start.QuadPart)/(double)freq.QuadPart << " seconds" << endl;
}

int main(int argc, char* argv[])
{
 	if (argc > 1) 
	{
		int test = atoi(argv[1]);
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
			default:
				break;
		}
	}
    else
    {
       cout << "usage: gl-g7 num1 num2" << endl;
       cout << "num1 is 1 through 3." << endl;
    }


   return 0;
}
