/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright 1997 Microsoft Corporation.  All Rights Reserved.
**************************************************************************/

/**************************************************************************

   File:          ShlFldr.h
   
   Description:   CShellFolder definitions.

**************************************************************************/

#ifndef SHELLFOLDER_H
#define SHELLFOLDER_H

/**************************************************************************
   #include statements
**************************************************************************/

#include <windows.h>
#include <shlobj.h>

#include "EnumIDL.h"
#include "PidlMgr.h"

/**************************************************************************
   global variables
**************************************************************************/

extern HINSTANCE  g_hInst;
extern UINT       g_DllRefCount;

/**************************************************************************

   CShellFolder class definition

**************************************************************************/

class CShellFolder : public IShellFolder, 
                     public IPersistFolder
{
friend class CShellView;

protected:
   DWORD m_ObjRefCount;

public:
   CShellFolder(CShellFolder*, LPCITEMIDLIST);
   ~CShellFolder();

   //IUnknown methods
   STDMETHOD (QueryInterface) (REFIID riid, LPVOID * ppvObj);
   STDMETHOD_ (ULONG, AddRef) (void);
   STDMETHOD_ (ULONG, Release) (void);

   //IPersist methods
   STDMETHODIMP GetClassID(LPCLSID);

   //IPersistFolder methods
   STDMETHODIMP Initialize(LPCITEMIDLIST);

   //IShellFolder methods
   STDMETHOD (ParseDisplayName) (HWND, LPBC, LPOLESTR, LPDWORD, LPITEMIDLIST*, LPDWORD);
   STDMETHOD (EnumObjects) (HWND, DWORD, LPENUMIDLIST*);
   STDMETHOD (BindToObject) (LPCITEMIDLIST, LPBC, REFIID, LPVOID*);
   STDMETHOD (BindToStorage) (LPCITEMIDLIST, LPBC, REFIID, LPVOID*);
   STDMETHOD (CompareIDs) (LPARAM, LPCITEMIDLIST, LPCITEMIDLIST);
   STDMETHOD (CreateViewObject) (HWND, REFIID, LPVOID* );
   STDMETHOD (GetAttributesOf) (UINT, LPCITEMIDLIST*, LPDWORD);
   STDMETHOD (GetUIObjectOf) (HWND, UINT, LPCITEMIDLIST*, REFIID, LPUINT, LPVOID*);
   STDMETHOD (GetDisplayNameOf) (LPCITEMIDLIST, DWORD, LPSTRRET);
   STDMETHOD (SetNameOf) (HWND, LPCITEMIDLIST, LPCOLESTR, DWORD, LPITEMIDLIST*);

private:
	LPITEMIDLIST m_pidl;
	HKEY m_hKeyRoot;
	LPTSTR m_lpszSubKey;
	CShellFolder *m_pSFParent;
	LPMALLOC m_pMalloc;
   LPPIDLMGR m_pPidlMgr;

   //utility functions
   BOOL GetFolderPath(LPTSTR, DWORD);
   BOOL GetFolderText(LPTSTR, DWORD);
	HKEY GetRootKey(void);
};

#endif   //SHELLFOLDER_H
