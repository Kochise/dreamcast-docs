// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__19818502_B837_11D0_8DF1_00C04FB68D60__INCLUDED_)
#define AFX_STDAFX_H__19818502_B837_11D0_8DF1_00C04FB68D60__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define VC_EXTRALEAN        // Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC OLE automation classes
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>         // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
#include <afxpriv.h>
#include <afxctl.h>
#include <afxtempl.h>
#include <afxconv.h>
#include <comcat.h>
#include <windowsx.h>
#include <activscp.h>
#include <objsafe.h>
#include <shlwapi.h>

#undef SubclassWindow  // Conflicts with CWnd::SubclassWindow

#pragma warning( disable: 4310 )  // Cast truncates constant value
#pragma warning( disable: 4244 )  // Conversion: possible loss of data
#pragma warning( disable: 4099 )  // class/struct confusion

#include <comdef.h>

#pragma warning( default: 4310 )  // Cast truncates constant value
#pragma warning( default: 4244 )  // Conversion: possible loss of data
#pragma warning( default: 4099 )  // class/struct confusion

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__19818502_B837_11D0_8DF1_00C04FB68D60__INCLUDED_)
