// --convclss.h-----------------------------------------------------------------
//
//  Defines CClassName - a C++ class that keeps track of conversion classes
// 
// Copyright 1986 - 1998 Microsoft Corporation.  All Rights Reserved.
//
// -----------------------------------------------------------------------------

#if !defined(_CONVCLSS_H)
#define _CONVCLSS_H

//$$--CClassName---------------------------------------------------------------
//
//  DESCRIPTION: This class manages entry point name information.
//
// ---------------------------------------------------------------------------
class CClassName
{
protected:
    LPWSTR m_pszClassName ;                 // name of the class supported.
    CDllEntryPoint * m_pEntryPoint ;        // entry point details.

public:
    CClassName * m_pcnNext ;                // next pointer.
    CClassName();
    ~CClassName();

    void EDKDump() ;
     
    HRESULT HrEDKSet(LPCWSTR pszClassName, CDllEntryPoint * pEntryPoint) ;

    LPWSTR const pszClassName()  { return  m_pszClassName; } 
    int const cNameLength()      { ASSERTERROR(m_pszClassName != NULL, "NULL m_pszClassName"); 
                                   return lstrlenW(m_pszClassName); } 
    CDllEntryPoint * pEntryPoint() 
                                 { return (m_pEntryPoint); }
};

#endif
