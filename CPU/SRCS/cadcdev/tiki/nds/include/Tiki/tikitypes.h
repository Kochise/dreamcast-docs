/*
   Tiki

   types.h

   Copyright (C)2000,2001 Dan Potter
   Copyright (C)2005 Cryptic Allusion, LLC
*/

#ifndef __TIKI_TYPES_H
#define __TIKI_TYPES_H

#include <stddef.h>
#include <sys/cdefs.h>
#include <nds/jtypes.h>

// This gets included in the main tiki.h, so it should suffice.
#define TIKI_OSX	0
#define TIKI_WIN32	1
#define TIKI_SDL	2
#define TIKI_DC		3
#define TIKI_GP2X	4
#define TIKI_NDS        5
#define TIKI_PLAT	TIKI_NDS

namespace Tiki {

// Pointer arithmetic types
typedef uint32 ptr_t;

};

#endif	// __TIKI_TYPES_H

