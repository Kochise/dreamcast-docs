/*
   Tiki
        
   endian.h

   Copyright (C)2005 Dan Potter
*/

#ifndef __TIKI_ENDIAN_H
#define __TIKI_ENDIAN_H

#include <machine/endian.h>

namespace Tiki {
namespace Endian {

static inline uint16 swap(uint16 src) {
	src = ((src & 0xff00) >> 8)
		| ((src & 0x00ff) << 8);
	return src;
}

static inline uint32 swap(uint32 src) {
	src = ((src & 0x000000ff) << 24)
		| ((src & 0x0000ff00) << 8)
		| ((src & 0x00ff0000) >> 8)
		| ((src & 0xff000000) >> 24);
	return src;
}

static inline uint16 convertFromLe(uint16 src) {
#if BYTE_ORDER == BIG_ENDIAN
	return swap(src);
#else
	return src;
#endif
}

static inline uint32 convertFromLe(uint32 src) {
#if BYTE_ORDER == BIG_ENDIAN
	return swap(src);
#else
	return src;
#endif
}

static inline uint16 convertFromBe(uint16 src) {
#if BYTE_ORDER == BIG_ENDIAN
	return src;
#else
	return swap(src);
#endif
}

static inline uint32 convertFromBe(uint32 src) {
#if BYTE_ORDER == BIG_ENDIAN
	return src;
#else
	return swap(src);
#endif
}

}
}

#endif	// __TIKI_ENDIAN_H

