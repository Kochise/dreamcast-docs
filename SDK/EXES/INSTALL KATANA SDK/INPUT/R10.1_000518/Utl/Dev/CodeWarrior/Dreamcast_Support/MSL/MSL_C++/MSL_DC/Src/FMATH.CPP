#include <fmath>

bool isfinite(double x)
{
	int hx = __HI(x); 
	return (unsigned)((hx & 0x7fffffff)-0x7ff00000)>>31;
}
