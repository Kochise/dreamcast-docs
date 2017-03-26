/*
   Tiki

   drawable.cpp

   Copyright (C)2002,2003,2004 Dan Potter
   Copyright (C)2005 Cryptic Allusion, LLC
*/

#include "pch.h"
#include "Tiki/debug.h"

#include <stdarg.h>

using namespace Tiki::Debug;

int Debug::printf(const char * fmt,...) {
// This unfortunately has to go elsewhere for Win32 since it chops off any
// console output in a GUI app.
#if TIKI_PLAT == TIKI_WIN32
	va_list args;
	char buffer[4096];
	va_start(args, fmt);
	int i = vsprintf(buffer, fmt, args);
	va_end(args);

	OutputDebugString(buffer);

	return i;
#else
	va_list args;
	
	va_start(args, fmt);
	int i = vprintf(fmt, args);
	va_end(args);
	
	return i;
#endif
}

