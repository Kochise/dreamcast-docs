// WOSA/XRT XRTFrame Sample Application Version 1.01
//
// Copyright (c) 1993-94 Microsoft Corporation, All Rights Reserved.
//
//      This is a part of the Microsoft Source Code Samples. 
//      This source code is only intended as a supplement to 
//      Microsoft Development Tools and/or WinHelp documentation.
//      See these sources for detailed information regarding the 
//      Microsoft samples programs.
//
// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions (including VB)
#include <afxole.h>         // MFC OLE classes
#include <afxdisp.h>        // MFC OLE automation classes

#define UNUSED

#ifndef STRICT
#define STRICT
#endif

// Disable "unrefereced formal parameter"
#pragma warning( disable : 4100 )

// Disable "Note: Creating new precompiled header" 
#pragma warning( disable : 4699 )

// Disable "4706: assignment within conditional expression"
#pragma warning( disable : 4706 )

#if _MSC_VER == 800
// Disable "C4702" "unreachable code" (only happens with 
// C8.
#pragma warning( disable : 4702 )
#endif

