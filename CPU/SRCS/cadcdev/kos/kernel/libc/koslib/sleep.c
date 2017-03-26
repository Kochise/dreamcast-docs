/* KallistiOS ##version##

   sleep.c
   Copyright (C)2005 Walter van Niftrik
*/

#include <kos/thread.h>

unsigned int sleep(unsigned int seconds)
{
	thd_sleep(seconds * 1000);

	return 0;
}
