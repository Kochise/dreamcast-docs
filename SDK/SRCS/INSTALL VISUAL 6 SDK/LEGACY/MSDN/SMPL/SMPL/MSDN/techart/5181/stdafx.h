// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__BA23F755_FC73_11D0_9F8B_400004491341__INCLUDED_)
#define AFX_STDAFX_H__BA23F755_FC73_11D0_9F8B_400004491341__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define STRICT

#include <afxwin.h>
#include <afxdisp.h>

#define _WIN32_WINNT 0x0400

#include <atlbase.h>
extern CComModule _Module;
#include <atlcom.h>

#include <comdef.h>
 
// Include the STL. Once included here, project source files need not include
// any STL headers, speeding compilation.
//
#include <algorithm>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <vector>
#include <xstring>

using namespace std;

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__BA23F755_FC73_11D0_9F8B_400004491341__INCLUDED)
