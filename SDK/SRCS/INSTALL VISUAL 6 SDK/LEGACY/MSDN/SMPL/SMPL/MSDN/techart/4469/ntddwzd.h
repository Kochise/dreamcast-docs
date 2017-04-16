#ifndef __NTDDWZD_H__
#define __NTDDWZD_H__

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

// TODO: You may add any other custom AppWizard-wide declarations here.
/////////////////////////////////////////////////////////////////////////////
// Miscellaneous utility functions

void DefineMacro(LPCTSTR lpszKey, LPCTSTR lpszValue);
void UndefMacro(LPCTSTR lpszKey);

void DefineIntMacro(LPCTSTR pszKey, int iValue);
void DefineIntMacro(LPCTSTR pszKey, int iItem, int iValue);
void DefineBoolMacro(LPCTSTR pszKey, BOOL bValue=TRUE);
void DefineBoolMacro(LPCTSTR pszKey, int iItem, BOOL bValue);
void DefineStringMacro(LPCTSTR pszKey, LPCTSTR pszValue);
void DefineStringMacro(LPCTSTR pszKey, int iItem, LPCTSTR pszValue);

void ReportError(UINT nIDP, LPCTSTR szArg);
void ReportAndThrow(UINT nIDP, LPCTSTR szArg);



#endif //__NTDDWZD_H__
