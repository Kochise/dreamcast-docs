// --convdlle.h-----------------------------------------------------------------
// 
// Defines an entry point to a conversion DLL.
//
// Copyright 1986 - 1998 Microsoft Corporation.  All Rights Reserved.
//
// -----------------------------------------------------------------------------

#if !defined(_CONVDLLE_H)
#define _CONVDLLE_H

//$$--CDllEntryPoint-----------------------------------------------------------
//
//  DESCRIIPTION: class that represetns entry point info.  Manages reference couting.
//
// ---------------------------------------------------------------------------
class CDllEntryPoint
{
protected:
    LPWSTR m_pszDllName ;
    LPSTR  m_pszEntryPoint ;
    LPWSTR m_pszGwPoint ;
    LPWSTR m_pszOptions ;

    WORD m_nRefs ;                // reference count.

public:
    CDllEntryPoint() ;
    ~CDllEntryPoint() ;

    void AddRef() { DEBUGPRIVATE("CDLLEntryPoint::AddRef()\n"); m_nRefs++; }
    void Release() ;
    void EDKFree() ;

    void EDKDump() ;

    HRESULT HrEDKSet(LPCWSTR pszDllName, LPCWSTR pszEntryPoint, LPCWSTR pszGwPoint, LPCWSTR pszOptions) ;

    // standard get member functions
    LPWSTR const pszDllName()    { return (m_pszDllName) ; }
    LPSTR  const pszEntryPoint() { return (m_pszEntryPoint) ; }
    LPWSTR const pszGwPoint()    { return (m_pszGwPoint); }
    LPWSTR const pszOptions()    { return (m_pszOptions); }
} ;

#endif
