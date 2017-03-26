/*
   Tiki

   endian.cpp

   Copyright (C)2005 Cryptic Allusion, LLC
*/

#include "pch.h"
#include <machine/endian.h>

static uint16 doswap(uint16 s) {
	return ((s & 0xff) << 8)
		| ((s & 0xff00) >> 8);
}

static uint32 doswap(uint32 s) {
	return ((s & 0xff) << 24)
		| ((s & 0xff00) << 8)
		| ((s & 0xff0000) >> 8)
		| ((s & 0xff000000) >> 24);
}

uint16 Tiki::swaple(uint16 src) {
#if BYTE_ORDER == BIG_ENDIAN
	return doswap(src);
#else
	return src;
#endif
}

uint32 Tiki::swaple(uint32 src) {
#if BYTE_ORDER == BIG_ENDIAN
	return doswap(src);
#else
	return src;
#endif
}

uint16 Tiki::swapbe(uint16 src) {
#if BYTE_ORDER == BIG_ENDIAN
	return src;
#else
	return doswap(src);
#endif
}

uint32 Tiki::swapbe(uint32 src) {
#if BYTE_ORDER == BIG_ENDIAN
	return src;
#else
	return doswap(src);
#endif
}
