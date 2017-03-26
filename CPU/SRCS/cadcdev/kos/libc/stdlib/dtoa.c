/* KallistiOS ##version##

   dtoa.c
   (c)2001 Vincent Penne

   $Id: dtoa.c,v 1.1 2002/02/09 06:15:43 bardtx Exp $
*/


/*

  Very simple and inacurate dtoa function. 
  We do not consider the "mode" parameter ...

 */

#include <math.h>

char * 
dtoa(double d, 
     int mode, 
     int ndigits, 
     int *decpt, 
     int *sign, 
     char **rve)
{
	static char result[256];
	char * s;

	double tmp;

	int ex;


	if (d < 0) {
		*sign = 1;
		d = -d;
	} else
		*sign = 0;

	ex = 0;
	tmp = d; 

	while (tmp >= 10) {
		tmp /= 10;
		ex++;
	}
	while (tmp > 0 && tmp < 1) {
		tmp *= 10;
		ex--;
	}

	*decpt = ex+1;

	s = result;
	if (ndigits > sizeof(result)-1)
		ndigits = sizeof(result)-1;
	while (ndigits--) {
		int i = tmp;
    
		*s++ = '0'+i;

		tmp -= i;
		tmp *= 10;
	}

	*s++ = 0;

	if (rve)
		*rve = s-1;
  
	return result;
}
