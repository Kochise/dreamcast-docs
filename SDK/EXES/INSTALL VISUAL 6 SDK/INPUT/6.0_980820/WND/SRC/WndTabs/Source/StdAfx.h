/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/


// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__6A06C12F_4748_11D1_BC91_0000010016A6__INCLUDED_)
#define AFX_STDAFX_H__6A06C12F_4748_11D1_BC91_0000010016A6__INCLUDED_

#include "3rdParty\AggressiveOptimize.h"

#define VC_EXTRALEAN        // Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxdisp.h>
#include <afxcmn.h>
#include <afxtempl.h>
#include <afxdlgs.h>
#include <afxmt.h>

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>

#include <shlobj.h>

// Developer Studio Object Model
#include <ObjModel\addauto.h>
#include <ObjModel\appdefs.h>
#include <ObjModel\appauto.h>
#include <ObjModel\blddefs.h>
#include <ObjModel\bldauto.h>
#include <ObjModel\textdefs.h>
#include <ObjModel\textauto.h>
#include <ObjModel\dbgdefs.h>
#include <ObjModel\dbgauto.h>

// 3rd Party
#include <bcgcb.h>
#include "3rdParty\Hyperlink.h"
#include "3rdParty\htmlhelp.h"

//
//The supported WM_APPCOMMAND events
//
#ifndef WM_APPCOMMAND

#define WM_APPCOMMAND                       0x319
#define APPCOMMAND_BROWSER_BACKWARD         1
#define APPCOMMAND_BROWSER_FORWARD          2
#define APPCOMMAND_BROWSER_STOP             4
#define FAPPCOMMAND_MASK                    0x8000
#define GET_APPCOMMAND_LPARAM(lParam) ((short)(HIWORD(lParam) & ~FAPPCOMMAND_MASK))

#endif


#include "globals.h"  // program globals

/////////////////////////////////////////////////////////////////////////////
// Debugging support

// Use VERIFY_OK around all calls to the Developer Studio objects which
//  you expect to return S_OK.
// In DEBUG builds of your add-in, VERIFY_OK displays an ASSERT dialog box
//  if the expression returns an HRESULT other than S_OK.  If the HRESULT
//  is a success code, the ASSERT box will display that HRESULT.  If it
//  is a failure code, the ASSERT box will display that HRESULT plus the
//  error description string provided by the object which raised the error.
// In RETAIL builds of your add-in, VERIFY_OK just evaluates the expression
//  and ignores the returned HRESULT.

#ifdef _DEBUG

void GetLastErrorDescription(CComBSTR& bstr);       // Defined in WndTabs.cpp
#define VERIFY_OK(f) \
    { \
        HRESULT hr = (f); \
        if (hr != S_OK) \
        { \
            if (FAILED(hr)) \
            { \
                CComBSTR bstr; \
                GetLastErrorDescription(bstr); \
                _RPTF2(_CRT_ASSERT, "Object call returned %lx\n\n%S", hr, (BSTR) bstr); \
            } \
            else \
                _RPTF1(_CRT_ASSERT, "Object call returned %lx", hr); \
        } \
    }

#else //_DEBUG

#define VERIFY_OK(f) (f);

#endif //_DEBUG

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__6A06C12F_4748_11D1_BC91_0000010016A6__INCLUDED)
