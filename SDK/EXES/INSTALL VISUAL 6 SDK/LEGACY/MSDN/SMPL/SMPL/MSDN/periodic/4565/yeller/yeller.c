#include <windows.h>
#include <windowsx.h>
#include <math.h>

//========================================================
// Takes an integer and creates "String number n" from it.

LPSTR _export WINAPI GetString(int i)
{
	LPSTR rval;
	rval = GlobalAllocPtr(GHND, 32);
	wsprintf(rval, "String number %d", i);
	return rval;
}
 
//========================================================
// Prints text into a passed-in string, and returns the
// total number of bytes used.
 
int _export WINAPI GetStringA(LPSTR strg, int i)
{
	return wsprintf(strg, "StringA number %d", i);
}

//========================================================
// Takes two integers and returns the value of the first
// raised to the second.

double _export WINAPI Powers(int x, int y)
{
	static double dbl;
	
	dbl = pow(x, y);
	return dbl;
}