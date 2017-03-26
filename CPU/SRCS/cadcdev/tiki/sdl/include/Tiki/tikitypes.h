/*
   Tiki

   types.h

   Copyright (C)2000,2001 Dan Potter
   Copyright (C)2005 Cryptic Allusion, LLC
*/

#ifndef __TIKI_TYPES_H
#define __TIKI_TYPES_H

#include <stddef.h>

// This gets included in the main tiki.h, so it should suffice.
#define TIKI_OSX	0
#define TIKI_WIN32	1
#define TIKI_SDL	2
#define TIKI_DC		3
#define TIKI_PLAT	TIKI_SDL

namespace Tiki {

// Generic types
typedef unsigned long long uint64;
typedef unsigned long uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;
typedef long long int64;
typedef long int32;
typedef short int16;
typedef char int8;

// Volatile types
typedef volatile uint64 vuint64;
typedef volatile uint32 vuint32;
typedef volatile uint16 vuint16;
typedef volatile uint8 vuint8;
typedef volatile int64 vint64;
typedef volatile int32 vint32;
typedef volatile int16 vint16;
typedef volatile int8 vint8;

// Pointer arithmetic types
typedef uint32 ptr_t;

};

#endif	// __TIKI_TYPES_H

