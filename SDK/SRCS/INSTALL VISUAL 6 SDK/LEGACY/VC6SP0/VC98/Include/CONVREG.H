// --convreg.h------------------------------------------------------------------
// 
//  Conversion registry class.
//  Locates converters that are stored in DLLs from info stored in the 
//  registry.
//
// Copyright 1986 - 1998 Microsoft Corporation.  All Rights Reserved.
//
// -----------------------------------------------------------------------------

#if !defined(_CONVREG_H)
#define _CONVREG_H

//$$--CEDKConvReg--------------------------------------------------------------
//
//  DESCRIPTION: the conversion registry keeps track of conversion configuration.
//
// ---------------------------------------------------------------------------
class CEDKConvReg
{
public:

    CEDKConvReg() ;
    ~CEDKConvReg() ;

    HRESULT HrEDKInitialize() ;

    HRESULT HrEDKSearchOpen(
        IN LPCWSTR pszConversionPoint,
        IN LPCWSTR pszContentClass,
        OUT CDllEntryPoint * &pep) ;

    HRESULT HrEDKSearchNext() ;

    void EDKSearchClose() ;

    void EDKDumpMappings() ;

    // Deletes common member data (static class names list & DLL cache)
    void EDKFree() ;

    // function to retrieve a cached DLL handle
    static inline HRESULT CEDKConvReg::HrGetDllHandle(
        IN LPWSTR pszDllName,       // name of DLL to get instance handle for
        OUT HINSTANCE * phInst)     // instance handle pointer
    {
        ASSERTERROR(ms_pDllCache != NULL, "Bad ms_pDllCache");

        RETURN(((CDllCache *) CEDKConvReg::ms_pDllCache)->HrFind(pszDllName, phInst));
    }

protected:   
    // helper functions
    HRESULT HrEDKParseConfiguration() ;
    HRESULT HrEDKRecordValues(
        IN HKEY const hkEntryPoint, 
        IN LPCWSTR pszDll, 
        IN LPCWSTR pszEntryPoint) ;
    VOID EDKSyntaxError(
        IN LPWSTR pszDll,
        IN LPWSTR pszEntryPoint,
        IN LPWSTR pszClass,
        IN LPWSTR pszOptions,
        IN LPWSTR pszPoint) ;

    // common values
    BOOL m_bSyntaxError ;                           // true when a syntax error has occurred.

    // common storage
    static HKEY ms_hkConversions ;                  // handle to conversion data in registry
    static CClassName * ms_pcnClasses ;             // in memory cache of conversion data
    static CDllCache * ms_pDllCache;                // DLL instance handle cache

    // cursor information
    CDllEntryPoint ** m_ppep ;                      // where to store the entry point pointer
    CClassName * m_pcnCurrentClass ;                // current class.
    LPCWSTR m_pszConversionPoint ;                  // name of conversion point.
    LPCWSTR m_pszContentClass ;                     // name of class
} ;

#endif
