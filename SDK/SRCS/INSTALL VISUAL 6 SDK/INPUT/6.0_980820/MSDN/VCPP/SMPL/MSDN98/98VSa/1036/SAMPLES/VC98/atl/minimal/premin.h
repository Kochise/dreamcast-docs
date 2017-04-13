// premin.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently
//
// This is a part of the Active Template Library.
// Copyright (C) 1996-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Active Template Library Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Active Template Library product.

// save by having dummy critical sections and simple ++/-- operators
// instead of InterlockedIncrement()/InterlockedDecrement() calls
#define _ATL_SINGLE_THREAD


#include <atlbase.h>

// You may derive a class from CComModule and use it if you want
// to override something, but do not change the name of _Module

extern CComModule _Module;

#include <atlcom.h>
