/* KallistiOS ##version##

   ports.h
   Copyright (C)2003 Dan Potter
   
   $Id: ports.h,v 1.1 2003/08/01 03:18:37 bardtx Exp $
*/

#ifndef __IA32_PORTS_H
#define __IA32_PORTS_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>

// These macros determine if the port number is small enough to do it
// directly. If so it save some code space and registers.
#define inb(port) ({ \
	uint8 _data; \
	if (((port) & 0xffff) < 0x100) \
		_data = inbc(port); \
	else \
		_data = inbv(port); \
	_data; })

#define outb(port, data) ({ \
	if (((port) & 0xffff) < 0x100) \
		outbc(port, data); \
	else \
		outbv(port, data); })

static inline uint8 inbc(int port) {
	uint8 data;

	asm volatile("inb %1,%0" : "=a" (data) : "id" ((uint16)port));
	return data;
}

static inline void outbc(int port, uint8 data) {
	asm volatile("outb %0,%1" : : "a" (data), "id" ((uint16)port));
}

static inline uint8 inbv(int port) {
	uint8 data;

	asm volatile("inb %%dx,%0" : "=a" (data) : "d" ((uint16)port));
	return data;
}

static inline void outbv(int port, uint8 data) {
	asm volatile("outb %0,%%dx" : : "a" (data), "d" ((uint16)port));
}


__END_DECLS

#endif	/* __IA32_PORTS_H */

