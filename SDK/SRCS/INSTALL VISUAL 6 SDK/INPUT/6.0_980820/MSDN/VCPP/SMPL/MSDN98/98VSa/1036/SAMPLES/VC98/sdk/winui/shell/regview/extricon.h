/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright 1997 Microsoft Corporation.  All Rights Reserved.
**************************************************************************/

/**************************************************************************

   File:          ExtrIcon.h
   
   Description:   CExtractIcon definitions.

**************************************************************************/

#ifndef EXTRACTICON_H
#define EXTRACTICON_H

/**************************************************************************
   #include statements
**************************************************************************/

#include <windows.h>
#include <shlobj.h>

#include "PidlMgr.h"

/**************************************************************************
   global variables
**************************************************************************/

extern HINSTANCE  g_hInst;
extern UINT       g_DllRefCount;
extern HIMAGELIST g_himlLarge;
extern HIMAGELIST g_himlSmall;

/**************************************************************************

   CExtractIcon class definition

**************************************************************************/

class CExtractIcon : public IExtractIcon
{
protected:
   DWORD m_ObjRefCount;

public:
   CExtractIcon(LPCITEMIDLIST);
   ~CExtractIcon();

   //IUnknown methods
   STDMETHOD (QueryInterface) (REFIID riid, LPVOID * ppvObj);
   STDMETHOD_ (ULONG, AddRef) (void);
   STDMETHOD_ (ULONG, Release) (void);

   //IExtractIcon methods
   STDMETHOD (GetIconLocation) (UINT, LPTSTR, UINT, LPINT, LPUINT);
   STDMETHOD (Extract) (LPCTSTR, UINT, HICON*, HICON*, UINT);

private:
	LPITEMIDLIST m_pidl;
   LPPIDLMGR m_pPidlMgr;
};

#define ICON_INDEX_BINARY     0
#define ICON_INDEX_STRING     1
#define ICON_INDEX_FOLDER     2
#define ICON_INDEX_FOLDEROPEN 3

#endif   //EXTRACTICON_H
