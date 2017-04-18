#ifndef _duck_wav_h
#define _duck_wav_h

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct tDKWAVEFORM
{
	unsigned short	wFormatTag;        /* format type */
	unsigned short	nChannels;         /* number of channels (i.e. mono, stereo...) */
	unsigned long   nSamplesPerSec;    /* sample rate */
	unsigned long	nAvgBytesPerSec;   /* for buffer estimation */
	unsigned short	nBlockAlign;       /* block size of data */
	unsigned short	wBitsPerSample;    /* Number of bits per sample of mono data */
	unsigned short	cbSize;            /* The count in bytes of the size of
									extra information (after cbSize) */
	unsigned short	wSamplesPerBlock;

} DKWAVEFORM;

#if defined(__cplusplus)
}
#endif
#endif
