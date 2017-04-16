
#include "stdafx.h"
#include "cctlreg.h"
#ifdef _WIN32
#define LOADLIBRARY_FAILED(x) (x == 0)
#include "winver.h"
#else
#define LOADLIBRARY_FAILED(x) (x <= HINSTANCE_ERROR)
#include "ver.h" 
#endif

#include <memory.h>

//
//
//
typedef HRESULT (STDAPICALLTYPE *CTLREGPROC)(void) ; //see COMPOBJ.H

//
//
//
CCtlReg::CCtlReg(CString PathName)
{
	m_strPathName = PathName ;
}

//
//
//
CCtlReg::~CCtlReg()
{
	m_strPathName.Empty() ;	
}

//
//
//
BOOL CCtlReg::Register()
{
	BOOL bResult = FALSE;
	ASSERT(!m_strPathName.IsEmpty()) ;

	if (SupportsSelfRegister()) 
	{  
		char* szPathName = m_strPathName.GetBuffer(m_strPathName.GetLength()) ;
		HINSTANCE hModule = ::LoadLibrary(szPathName) ;
		m_strPathName.ReleaseBuffer(-1) ;
		if (LOADLIBRARY_FAILED(hModule)) return FALSE ;
				
		CTLREGPROC DLLRegisterServer = (CTLREGPROC)::GetProcAddress(hModule,"DllRegisterServer" ) ;
		if (DLLRegisterServer != NULL)
		{
			HRESULT regResult = DLLRegisterServer() ;
			bResult = (regResult == NOERROR) ; 
		}		
		::FreeLibrary(hModule) ;          
			
	}
	return bResult;	
}

//
//
//
BOOL CCtlReg::Unregister()
{
	BOOL bResult = FALSE ;
	ASSERT(!m_strPathName.IsEmpty()) ;

	if (SupportsSelfRegister()) 
	{                                    
		char* szPathName = m_strPathName.GetBuffer(m_strPathName.GetLength()) ;
		HMODULE hModule = ::LoadLibrary(szPathName) ;
		m_strPathName.ReleaseBuffer(-1) ;
		if (LOADLIBRARY_FAILED(hModule)) return FALSE ;
				
		CTLREGPROC DllUnregisterServer = (CTLREGPROC)::GetProcAddress(hModule,"DllUnregisterServer" ) ;
		if (DllUnregisterServer != NULL)
		{
			HRESULT regResult = DllUnregisterServer() ;
			bResult = (regResult == NOERROR) ; 
		}		
		FreeLibrary(hModule) ;
	}                                     
	return bResult;	
} 

//
//
//
BOOL CCtlReg::SupportsSelfRegister()
{
	BOOL bResult = FALSE;
	DWORD  handle;
	DWORD  uiInfoSize;
	UINT  uiVerSize ;
	UINT  uiSize ;
	DWORD* lpBuffer;
	CString strName	;
	char szName[128] ;

	// Get the size of the version information.
	uiInfoSize = ::GetFileVersionInfoSize((LPTSTR)(LPCTSTR)m_strPathName, &handle);
	if (uiInfoSize == 0) 
		return FALSE ;

	// Allocate a buffer for the version information.
	char* pbData = new char[uiInfoSize] ;

	// Fill the buffer with the version information.
	bResult = ::GetFileVersionInfo((LPTSTR)(LPCTSTR)m_strPathName, handle, uiInfoSize, pbData);	
	if (!bResult) goto NastyGoto ;

	// Get the translation information.
	bResult = ::VerQueryValue(pbData, "\\VarFileInfo\\Translation", (void**)&lpBuffer, &uiVerSize);
	if (!bResult) goto NastyGoto ;

	bResult = uiVerSize ;
	if (!bResult) goto NastyGoto ;

	// Build the path to the key OLESelfRegister using the translation information.
	wsprintf(szName,"\\StringFileInfo\\%04hX%04hX\\OLESelfRegister",LOWORD(*lpBuffer),HIWORD(*lpBuffer)) ;

	// Search for the key.
    bResult = ::VerQueryValue(pbData, szName, (void**)&lpBuffer, &uiSize);

NastyGoto:
	delete [] pbData ;
	return bResult ;
}
