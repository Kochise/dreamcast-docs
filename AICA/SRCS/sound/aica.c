#include "aica.h"

#define AICA(n) ((volatile unsigned int *)(void*)(0x800000+(n)))

void aica_reset()
{
  int i, j;
  volatile unsigned int *hwptr = AICA(0);

  *AICA(0x2800) = 0;

  /* Reset all 64 channels to a silent state */
  for(i=0; i<64; i++) {
    hwptr[0] = 0x8000;
    hwptr[5] = 0x1f;
    hwptr[1] = 0;
    hwptr[2] = 0;
    hwptr[3] = 0;
    hwptr[4] = 0;
    for(j=6; j<32; j++)
      hwptr[j] = 0;
    hwptr += 32;
  }

  *AICA(0x2800) = 15;
}

void play_sound(int channel, void *data, int mode, int nsamp, int freq,
		int vol, int pan)
{
  volatile unsigned int *hwptr = AICA(channel<<7);
  unsigned long freq_lo, freq_base = 5644800;
  int freq_hi = 7;

  /* Set sample format and buffer address */
  hwptr[0] = 0x4200 | (mode<<7) | (((unsigned long)data)>>16);
  hwptr[1] = ((unsigned long)data) & 0xffff;
  /* Number of samples */
  hwptr[3] = nsamp;
  /* Need to convert frequency to floating point format
     (freq_hi is exponent, freq_lo is mantissa).
     Formula is  freq = 44100*2^freq_hi*(1+freq_lo/1024)  */
  while(freq < freq_base && freq_hi > -8) {
    freq_base >>= 1;
    --freq_hi;
  }
  freq_lo = (freq<<10)/freq_base;
  /* Write resulting values */
  hwptr[6] = (freq_hi<<11)|(freq_lo&1023);
  /* Set volume, pan, and some other stuff */
  ((volatile unsigned char *)(hwptr+9))[4] = 0x24;
  ((volatile unsigned char *)(hwptr+9))[1] = 0xf;
  ((volatile unsigned char *)(hwptr+9))[5] = vol;
  ((volatile unsigned char *)(hwptr+9))[0] = pan;
  hwptr[4] = 0x1f;
  /* Enable playback */
  hwptr[0] |= 0xc000;
}

void stop_sound(int channel)
{
  volatile unsigned int *hwptr = AICA(channel<<7);

  /* Disable playback */
  hwptr[0] = (hwptr[0] & ~0x4000) | 0x8000;
}
