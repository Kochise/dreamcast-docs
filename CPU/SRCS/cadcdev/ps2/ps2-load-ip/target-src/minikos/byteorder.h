/* ps2-load-ip

   byteorder.h
   Copyright (c)2001-2002 Dan Potter
   License: BSD

   $Id: byteorder.h,v 1.1 2002/10/30 05:34:13 bardtx Exp $
*/
            
/* Byte-order translation functions */
#include "types.h"

/* Network to Host short */
static inline uint16 ntohs(uint16 value) {
	return ((value >> 8) & 0xff)
		| ((value << 8) & 0xff00);
}

/* Network to Host long */
static inline uint32 ntohl(uint32 value) {
	return ((value >> 24) & 0xff)
		| (( (value >> 16) & 0xff ) << 8)
		| (( (value >> 8) & 0xff) << 16)
		| (( (value >> 0) & 0xff) << 24);
}

/* Host to Network short */
static inline uint32 htons(uint32 value) { return ntohs(value); }

/* Host to Network long */
static inline uint32 htonl(uint32 value) { return ntohl(value); }
