// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1993-1997  Microsoft Corporation.  All Rights Reserved.
//
// Modudule: ICONHDLR.CPP
//
// Purpose:  Implements the IExtractIcon and IPersistFile member
//           functions necessary to support the icon handler portion
//           of this shell extension.
//

#include "priv.h"
#include "shellext.h"

extern HINSTANCE g_hmodThisDll; // Handle to this DLL itself.

// *********************** IExtractIcon Implementation *************************

STDMETHODIMP CShellExt::GetIconLocation(UINT   uFlags,
                                        LPSTR  szIconFile,
                                        UINT   cchMax,
                                        int   *piIndex,
                                        UINT  *pwFlags)
{  
    ODS("CShellExt::GetIconLocation()\r\n");

    GetModuleFileName(g_hmodThisDll, szIconFile, cchMax);

    *piIndex = (int)GetPrivateProfileInt("IconImage", 
                                         "Index", 
                                         0, 
                                         m_szFileUserClickedOn);

    return S_OK;
}


STDMETHODIMP CShellExt::Extract(LPCSTR pszFile,
                                UINT   nIconIndex,
                                HICON  *phiconLarge,
                                HICON  *phiconSmall,
                                UINT   nIconSize)
{
    ODS("CShellExt::Extract()\r\n");

    return S_FALSE;
}


// *********************** IPersistFile Implementation ******************

STDMETHODIMP CShellExt::GetClassID(LPCLSID lpClassID)
{
    ODS("CShellExt::GetClassID()\r\n");

    return E_FAIL;
}

STDMETHODIMP CShellExt::IsDirty()
{
    ODS("CShellExt::IsDirty()\r\n");

    return S_FALSE;
}

STDMETHODIMP CShellExt::Load(LPCOLESTR lpszFileName, DWORD grfMode)
{
    ODS("CShellExt::Load()\r\n");

    WideCharToMultiByte(CP_ACP,                // CodePage
                        0,		              // dwFlags
                        lpszFileName,          // lpWideCharStr
                        -1,                    // cchWideChar
                        m_szFileUserClickedOn, // lpMultiByteStr
                        sizeof(m_szFileUserClickedOn),  // cchMultiByte,
                        NULL,                  // lpDefaultChar,
                        NULL);                 // lpUsedDefaultChar

    return NOERROR;
}

STDMETHODIMP CShellExt::Save(LPCOLESTR lpszFileName, BOOL fRemember)
{
    ODS("CShellExt::Save()\r\n");

    return E_FAIL;
}

STDMETHODIMP CShellExt::SaveCompleted(LPCOLESTR lpszFileName)
{
    ODS("CShellExt::SaveCompleted()\r\n");

    return E_FAIL;
}

STDMETHODIMP CShellExt::GetCurFile(LPOLESTR FAR* lplpszFileName)
{
    ODS("CShellExt::GetCurFile()\r\n");

    return E_FAIL;
}
