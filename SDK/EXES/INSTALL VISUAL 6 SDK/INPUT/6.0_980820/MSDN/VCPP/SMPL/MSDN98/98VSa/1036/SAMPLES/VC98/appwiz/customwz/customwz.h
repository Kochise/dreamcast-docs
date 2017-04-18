// customwz.h : Declares the initialization routines for the DLL.
//
// Copyright (c) 1985-1998, Microsoft Corporation. All rights reserved.
//

#ifndef __CUSTOMWZ_H__
#define __CUSTOMWZ_H__

#include "resource.h"

#define APWZ_EXPORT __declspec(dllexport)

#define NUM_APWZ_EXE_STEPS      7
#define NUM_APWZ_EXE_DOC_STEPS  6
#define NUM_APWZ_EXE_DLG_STEPS  4
#define NUM_APWZ_DLL_STEPS      1

/////////////////////////////////////////////////////////////////////////////
// Miscellaneous utility functions

void DefineMacro(LPCTSTR lpszKey, LPCTSTR lpszValue);
void UndefMacro(LPCTSTR lpszKey);

void DefineIntMacro(LPCTSTR pszKey, int iValue);
void DefineIntMacro(LPCTSTR pszKey, int iItem, int iValue);
void DefineBoolMacro(LPCTSTR pszKey, BOOL bValue);
void DefineBoolMacro(LPCTSTR pszKey, int iItem, BOOL bValue);
void DefineStringMacro(LPCTSTR pszKey, LPCTSTR pszValue);
void DefineStringMacro(LPCTSTR pszKey, int iItem, LPCTSTR pszValue);

BOOL ReportError(UINT nIDP, LPCTSTR szArg);
void ReportAndThrow(UINT nIDP, LPCTSTR szArg);

#endif //__CUSTOMWZ_H__
