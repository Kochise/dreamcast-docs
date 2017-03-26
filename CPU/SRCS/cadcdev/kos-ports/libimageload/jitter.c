#include <imageload/jitterdefs.h>

#include <stdlib.h>

#define jitterx(x,y,s) (ujitter[((x+(y<<2))+ijitter[(x+s)&JITTER_MASK])&JITTER_MASK])
#define jittery(x,y,s) (vjitter[((y+(x<<2))+ijitter[(y+s)&JITTER_MASK])&JITTER_MASK])

void jitter_init(void)
{
  unsigned int i;

  for(i = 0; i < JITTER_TABLE_SIZE; i++)
    ujitter[i] = (float)(rand()%LARGE_NUMBER)/(float)LARGE_NUMBER;
  for(i = 0; i < JITTER_TABLE_SIZE; i++)
    vjitter[i] = (float)(rand()%LARGE_NUMBER)/(float)LARGE_NUMBER;
  for(i = 0; i < JITTER_TABLE_SIZE; i++)
    ijitter[i] = JITTER_TABLE_SIZE*
      (float)(rand()%LARGE_NUMBER)/(float)LARGE_NUMBER;
}

unsigned char jitter(unsigned char c, unsigned char n, unsigned char shift, unsigned char noise, unsigned short x, unsigned short y)
{
  const unsigned char lowbit = 1 << shift;
  unsigned int p,q;
  
  if (c < 248)
  {
    p = c % lowbit;
    q = (unsigned int)(jitterx(x,y,n)*(lowbit+1.0));
    if (p >= q)
      c += lowbit;

    q = lowbit * ((unsigned int)((jittery(x,y,n)*(2.0*noise))+0.5)-noise);
    q += c;

    if (q>= 0 && q <= 255)
      return q;
    else
      return c;
  }
  else
    return c;
}
