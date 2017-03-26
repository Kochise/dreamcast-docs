/*
 * SH part of sound example.  This program just writes the ARM code
 * to the sound memory and reboots the ARM
 */


/* memcpy that copies 4 bytes at a time */
void *memcpy4(void *s1, const void *s2, unsigned int n)
{
  unsigned int *p1 = s1;
  const unsigned int *p2 = s2;
  n>>=2;
  while(n--)
    *p1++ = *p2++;
  return s1;
}

/* memset that fills 4 bytes at a time */
void *memset4(void *s, int c, unsigned int n)
{
  unsigned int *p = s;
  n>>=2;
  while(n--)
    *p++ = c;
  return s;  
}


/* Dummy stub to keep libgcc happy... */
void atexit() { }


#include "music.h"


int main()
{
  int i;

  /* Pull RESET low on ARM */
  *((volatile unsigned long *)(void *)0xa0702c00) |= 1;

  /* Clear entire sound RAM */
  memset4((void*)0xa0800000, 0, 2*1024*1024);

  /* Copy ARM code to beginning of sound RAM */
  memcpy4((void*)0xa0800000, the_code, sizeof(the_code));

  /* Release RESET which will cause ARM to start executing */
  *((volatile unsigned long *)(void *)0xa0702c00) &= ~1;

  /* Wait for a little bit so we know that the ARM has done its
     basic initialization.                                      */
  for(i=0; i<0x200000; i++);

  /* Now the ARM will handle itself.  No reason to hang around
     much longer.                                               */

  return 0;  /* Return to serial slave.  Replace with infinite loop
		if you're going to run the code from CD or something. */
}
