/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright 1997 Microsoft Corporation.  All Rights Reserved.
**************************************************************************/

/**************************************************************************

   File:          InfoTip.h
   
   Description:   CQueryInfo definitions.

**************************************************************************/

#include <windows.h>
#include <shlobj.h>

#if (_WIN32_IE < 0x0400)
#define CQueryInfo  IUnknown

#else //(_WIN32_IE >= 0x0400)

#ifndef INFOTIP_H
#define INFOTIP_H

/**************************************************************************
   #include statements
**************************************************************************/

#include "PidlMgr.h"

/**************************************************************************
   global variables
**************************************************************************/

extern HINSTANCE  g_hInst;
extern UINT       g_DllRefCount;

/**************************************************************************

   CQueryInfo class definition

**************************************************************************/

class CQueryInfo : public IQueryInfo
{
protected:
   DWORD m_ObjRefCount;

public:
   CQueryInfo(LPCITEMIDLIST);
   ~CQueryInfo();

   //IUnknown methods
   STDMETHOD (QueryInterface) (REFIID riid, LPVOID * ppvObj);
   STDMETHOD_ (ULONG, AddRef) (void);
   STDMETHOD_ (ULONG, Release) (void);

   //IQueryInfo methods
   STDMETHOD(GetInfoTip)(DWORD dwFlags, WCHAR **ppwszTip);
   STDMETHOD(GetInfoFlags)(LPDWORD pdwFlags);

private:
	LPITEMIDLIST m_pidl;
	LPMALLOC m_pMalloc;
   LPPIDLMGR m_pPidlMgr;
};

#endif   //INFOTIP_H

#endif   //(_WIN32_IE >= 0x0400)
