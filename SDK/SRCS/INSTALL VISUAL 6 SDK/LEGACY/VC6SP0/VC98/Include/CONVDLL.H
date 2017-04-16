// --convdll.h------------------------------------------------------------------
// 
// Defines the DLL access class
//
// Copyright 1986 - 1998 Microsoft Corporation.  All Rights Reserved.
//
// -----------------------------------------------------------------------------

#if !defined(_CONVDLL_H)
#define _CONVDLL_H

//$$--CEDKConvDll---------------------------------------------------------------
//
//  DESCRIPTION: class that manages loading DLLs.
//
// ---------------------------------------------------------------------------
class CEDKConvDll
{
public:
    CEDKConvDll(
        IN CDllEntryPoint * pep, 
        IN HANDLE hEventSource) ;
    ~CEDKConvDll() ;

    HRESULT HrEDKLoad() ;
    HRESULT HrEDKUnLoad() ;

    HRESULT HrEDKQueryCapability(
        IN PEDKCNVENV pEnv,
        IN LPCWSTR pszContentClass,
        IN PVOID pContent,
        OUT BOOL &bAmCandidate) ;

    HRESULT HrEDKConvert(
        IN PEDKCNVENV pEnv,
        IN LPCWSTR pszContentClass,
        IN PVOID pContentIn,
        OUT PVOID pContentOut,
        OUT EDKCNVRES & crResult) ;

protected:
    CDllEntryPoint * m_pepEntry ;       // DLL and entry pont.
    
	HINSTANCE m_hDll ;                     // DLL handle.

    PCONVDLLVECT m_pDllVector ;         // Vector.
	HANDLE m_hEventSource ;
} ; 

#endif
