/*
   Tiki

   types.h

   Copyright (C)2000,2001 Dan Potter
   Copyright (C)2005 Cryptic Allusion, LLC
*/

#ifndef __TIKI_TYPES_H
#define __TIKI_TYPES_H

#include <ctype.h>
#include <arch/types.h>
#include <dc/pvr.h>
#include <dc/sound/stream.h>
#include <dc/sound/sfxmgr.h>

// This gets included in the main tiki.h, so it should suffice.
#define TIKI_OSX	0
#define TIKI_WIN32	1
#define TIKI_SDL	2
#define TIKI_DC		3
#define TIKI_PLAT	TIKI_DC

namespace Tiki {

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

#define GL_RGBA GL_ARGB1555
};

#endif	// __TIKI_TYPES_H

