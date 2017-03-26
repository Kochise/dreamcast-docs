/*
   Tiki

   tiki.h

   Copyright (C)2005 Cryptic Allusion, LLC
*/

#ifndef __TIKI_TIKI_H
#define __TIKI_TIKI_H

// Lay out the namespaces up front.
namespace Tiki {
	namespace Time { }
	namespace Debug { }
	namespace Math { }
	namespace GL {
		namespace Plxcompat { }
		namespace Frame { }
	}
	namespace Hid { }
	namespace Audio {
		namespace OggVorbis { }
	}
}

// Bring in our custom types.
#include "Tiki/tikitypes.h"

#if TIKI_PLAT==TIKI_WIN32
#pragma comment(lib, "tiki.lib")
#endif

#include <string>
namespace Tiki {
	// Bring STL string into the namespace.
	using std::string;

	// Global init/shutdown functions.
	bool init(int argc, char **argv);
	void shutdown();
	void setName(const char *name, const char *icon);
	namespace GL {
		void showCursor(bool visible);
	}
	// Endian swapping functions.
	uint16 swaple(uint16 src);
	uint32 swaple(uint32 src);
	uint16 swapbe(uint16 src);
	uint32 swapbe(uint32 src);
}

// Bring in debug stuff, we'll use it everywhere.
#include "Tiki/debug.h"

// We may want to shim this later.
#include <assert.h>

// Ditto.
#define _USE_MATH_DEFINES		// Win32 needs this.
#include <math.h>

#endif	// __TIKI_TIKI_H

