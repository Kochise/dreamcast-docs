//---------------------------------------------------------------------------
// Main.h
//---------------------------------------------------------------------------
// Main header file for all source files.  Hopefully, we'll then pre-compile
// this one header...
//---------------------------------------------------------------------------
// (C) Copyright 1997 by Microsoft Corporation.  All rights reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//---------------------------------------------------------------------------

#pragma warning(disable:4201) // nameless struct/union
#pragma warning(disable:4100) // unreferenced formal parameter
#pragma warning(disable:4514) // unreferenced inline function has been removed


// External Headers
#define  STRICT
#include <Windows.h>
#include <StdLib.h>
#include <Memory.h>
#include <OleCtl.h>

// ActiveX Scripting related headers
#include "ActivScp.h"
#include "MultInfo.h"
#include "VBSGuids.h"
#include "CompMgr.h"

// VC++ Created Headers
#include "Resource.h"     // From Spruuids.rc  via RC.exe
#include "Spruuids.h"     // From Spruuids.odl via MkTypeLib.exe

// Globals
extern HINSTANCE g_hinst;
extern ITypeLib *g_ptlMain;
extern ITypeLib *g_ptlGameSubObj;
extern IUnknown *g_punkApplicationNA;   // For .Application properties (not AddRef'd)
extern HBRUSH    g_hbrushStock;

// Global TypeInformation
extern ITypeInfo *g_ptinfoClsGame;
extern ITypeInfo *g_ptinfoIntGame;
extern ITypeInfo *g_ptinfoClsGameOA;
extern ITypeInfo *g_ptinfoIntGameOA;
extern ITypeInfo *g_ptinfoClsSpriteClass;
extern ITypeInfo *g_ptinfoIntSpriteClass;
extern ITypeInfo *g_ptinfoClsSprite;
extern ITypeInfo *g_ptinfoIntSprite;

// Internal Headers
#include "Debug.h"
#include "Helpers.h"
#include "OleAuto.h"

//--- EOF -------------------------------------------------------------------
