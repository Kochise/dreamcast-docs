/*
   Tiki

   pch.h

   Copyright (C)2005 Cryptic Allusion, LLC
*/

// This is mainly just a placeholder on non-Win32 platforms. If we don't
// include a file at the top of every source file, Visual C++ is too stupid
// to do it on its own. It's a convenient excuse to predefine some other
// stuff too though.

// This header does most of the useful work for  bringing in stuff.
#include "Tiki/tiki.h"

// Don't bother with namespace poo inside the framework itself.
using namespace Tiki;

// Packed structs need some compiler-specific foo.
#define PACKED_STRUCT_BEGIN
#define PACKED_STRUCT_END
#define PACKED_STRUCT_MEMBER __attribute__((packed))
