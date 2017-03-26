/*
   Tiki

   time.h

   Copyright (C)2005 Cryptic Allusion, LLC
*/

#ifndef __TIKI_TIME_H
#define __TIKI_TIME_H

#include "Tiki/tikitypes.h"

namespace Tiki {

namespace Time {
	/// Get the current system time, in microseconds since Jan 1, 1970.
	uint64 gettime();

	/// Sleep the specified number of microseconds.
	void sleep(uint64 us);
};

};

#endif	// __TIKI_TIME_H
