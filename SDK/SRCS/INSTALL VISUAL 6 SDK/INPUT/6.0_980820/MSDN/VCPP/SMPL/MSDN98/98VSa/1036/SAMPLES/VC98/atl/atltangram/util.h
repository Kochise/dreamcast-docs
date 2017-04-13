// util.h - shared utilities
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

#ifndef __Util_h__
#define __Util_h__

#include <assert.h>

// Displays a message box with an error string in it.
void ErrorMessage(LPCTSTR str, HRESULT hr) ;

// Determine if two interfaces below to the same component.
BOOL InterfacesAreOnSameComponent(IUnknown* pI1, IUnknown* pI2) ;

// Displays messages using OutputDebugString
void __cdecl MyTrace(LPCTSTR lpszFormat, ...);

// Determine if an address is accessable.
BOOL IsValidAddress(const void* lp, UINT nBytes = 1, BOOL bReadWrite = FALSE) ;

// Determine if interface pointer is accessable.
inline BOOL IsValidInterface(IUnknown* p)
{
	return (p != NULL) && IsValidAddress(p, sizeof(IUnknown*), FALSE) ;
}

// Determine if the out parameter for an interface pointer is accessable.
template <class T>
inline BOOL IsValidInterfaceOutParam(T** p)
{
	return (p != NULL) && IsValidAddress(p, sizeof(IUnknown*), TRUE) ;
}

/////////////////////////////////////////////////////////////////////////////
// Diagnostic support
// Helper function for checking HRESULTs.

#ifdef _DEBUG
inline void CheckResult(HRESULT hr)
{
	if (FAILED(hr))
	{
		ErrorMessage(NULL, hr) ;
		assert(FAILED(hr)) ;
	}
}

#define ASSERT_HRESULT      CheckResult
#else
#define ASSERT_HRESULT
#endif

/////////////////////////////////////////////////////////////////////////////
// More Diagnostic support which mimics MFC

#ifndef __AFX_H__   // Only define these if MFC has not already been included
#ifdef _DEBUG

#define ASSERT              assert
#define VERIFY(f)           ASSERT(f)
#define DEBUG_ONLY(f)       (f)

#define TRACE               ::MyTrace
#define TRACE0(sz)          ::MyTrace(_T("%s"), _T(sz))

#else   // _DEBUG

#define ASSERT
#define VERIFY(f)           ((void)(f))
#define ASSERT_VALID(pOb)   ((void)0)
#define DEBUG_ONLY(f)       ((void)0)

#define TRACE
#define TRACE0(sz)

#endif // !_DEBUG

#define ASSERT_POINTER(p, type) \
	ASSERT(((p) != NULL) && IsValidAddress((p), sizeof(type), FALSE))

#define ASSERT_NULL_OR_POINTER(p, type) \
	ASSERT(((p) == NULL) || IsValidAddress((p), sizeof(type), FALSE))

#endif // TRACE

#endif // __Util_h__
