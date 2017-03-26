/* KallistiOS ##version##

   clock.c
   (c)2002 Jeffrey McBeth

   $Id: clock.c,v 1.1 2002/03/15 06:45:42 bardtx Exp $
*/

#include <time.h>

/* clock() */
/* According to the POSIX standard, if the process time can't be determined
 * clock should return (clock_t)-1
 */
clock_t clock(void) {
	return (clock_t)-1;
}

