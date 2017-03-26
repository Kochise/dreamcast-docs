/* KallistiOS ##version##

   randnum.c
   (c)2000-2001 Dan Potter

   Utility function to pick a random number in a range
*/

#include <stdlib.h>

CVSID("$Id: randnum.c,v 1.1 2002/09/08 06:56:02 bardtx Exp $");

int randnum(int limit) {
	return (int)((double)rand() / ((double)RAND_MAX + 1) * limit);
}
