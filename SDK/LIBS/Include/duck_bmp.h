#ifndef _duck_bmp_h
#define _duck_bmp_h

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct tDKBITMAP
{                                                   
	unsigned long	ulFormatTag;
	unsigned short	usWidth;			/* width */
	unsigned short	usHeight;			/* height */	
    unsigned short  usDepth;
    unsigned long	ulHandler;
} DKBITMAP;

#if defined(__cplusplus)
}
#endif
#endif
