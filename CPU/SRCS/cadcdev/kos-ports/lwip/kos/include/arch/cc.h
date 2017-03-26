/*
 * Copyright (c) 2001-2003 Swedish Institute of Computer Science.
 * All rights reserved. 
 * 
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions 
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED 
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO 
 * EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 * 
 * Author: Adam Dunkels <adam@sics.se>
 *
 */

/* Modified for KOS by Dan Potter */

#ifndef __ARCH_CC_H__
#define __ARCH_CC_H__

#include <arch/types.h>
#include <arch/arch.h>
#include <kos/fs.h>

#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>

#include "lwipopts.h"

#define BYTE_ORDER LITTLE_ENDIAN

typedef uint8   u8_t;
typedef int8    s8_t;
typedef uint16  u16_t;
typedef int16   s16_t;
typedef uint32  u32_t;
typedef int32   s32_t;

typedef ptr_t mem_ptr_t;

#define PACK_STRUCT_FIELD(x) x __attribute__((packed))
#define PACK_STRUCT_STRUCT __attribute__((packed))
#define PACK_STRUCT_BEGIN
#define PACK_STRUCT_END

#if 0
#define _SYS_TYPES_FD_SET
#define NBBY    8               /* number of bits in a byte */

typedef long    fd_mask;
#define NFDBITS (sizeof (fd_mask) * NBBY)       /* bits per mask */
#ifndef howmany 
#define howmany(x,y)    (((x)+((y)-1))/(y))
#endif /* howmany */

typedef struct _types_fd_set {
        fd_mask fds_bits[howmany(FD_SETSIZE, NFDBITS)];
} _types_fd_set;

#define fd_set _types_fd_set

#define FD_SET(n, p)    ((p)->fds_bits[(n)/NFDBITS] |= (1L << ((n) % NFDBITS)))
#define FD_CLR(n, p)    ((p)->fds_bits[(n)/NFDBITS] &= ~(1L << ((n) % NFDBITS)))
#define FD_ISSET(n, p)  ((p)->fds_bits[(n)/NFDBITS] & (1L << ((n) % NFDBITS)))
#define FD_ZERO(p)       do {                   \
  size_t __i;                                \
  char *__tmp = (char *)p;                   \
  for (__i = 0; __i < sizeof (*(p)); ++__i)  \
    *__tmp++ = 0;                            \
} while (0)
#endif
                      
#ifndef LWIP_PLATFORM_DIAG
#define LWIP_PLATFORM_DIAG(x)   do {printf x;} while(0)
#endif

#ifndef LWIP_PLATFORM_ASSERT
#define LWIP_PLATFORM_ASSERT(x) do {printf("Assertion \"%s\" failed at line %d in %s\n", \
	x, __LINE__, __FILE__); assert(0);} while(0)
#endif

#define LWIP_COMPAT_SOCKETS 1

#define GET_CALLER_PC arch_get_ret_addr

#endif /* __ARCH_CC_H__ */
