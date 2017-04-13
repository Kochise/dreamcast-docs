/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright 1997 Microsoft Corporation.  All Rights Reserved.
**************************************************************************/

/**************************************************************************

   File:          EnumIDL.h
   
   Description:   CEnumIDList definitions.

**************************************************************************/

#ifndef ENUMIDLIST_H
#define ENUMIDLIST_H

#include <windows.h>
#include <shlobj.h>

#include "PidlMgr.h"
#include "Utility.h"

/**************************************************************************
   structure defintions
**************************************************************************/

typedef struct tagENUMLIST
   {
   struct tagENUMLIST   *pNext;
   LPITEMIDLIST         pidl;
   }ENUMLIST, FAR *LPENUMLIST;

/**************************************************************************
   global variables
**************************************************************************/

extern HINSTANCE  g_hInst;
extern UINT       g_DllRefCount;

/**************************************************************************

   CEnumIDList class definition

**************************************************************************/

class CEnumIDList : public IEnumIDList
{
protected:
   DWORD m_ObjRefCount;
   
public:
   CEnumIDList(HKEY, LPCTSTR, DWORD, HRESULT*);
   ~CEnumIDList();
   
   //IUnknown methods
   STDMETHOD (QueryInterface)(REFIID, LPVOID*);
   STDMETHOD_ (DWORD, AddRef)();
   STDMETHOD_ (DWORD, Release)();
   
   //IEnumIDList
   STDMETHOD (Next) (DWORD, LPITEMIDLIST*, LPDWORD);
   STDMETHOD (Skip) (DWORD);
   STDMETHOD (Reset) (void);
   STDMETHOD (Clone) (LPENUMIDLIST*);
   
private:
   BOOL CreateEnumList(HKEY, LPCTSTR, DWORD);
   BOOL AddToEnumList(LPITEMIDLIST);
   BOOL DeleteList(void);

private:
   LPMALLOC m_pMalloc;
   LPENUMLIST m_pFirst;
   LPENUMLIST m_pLast;
   LPENUMLIST m_pCurrent;
   LPPIDLMGR  m_pPidlMgr;
};

#endif   //ENUMIDLIST_H
